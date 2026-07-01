/* -------------------------------------------------------------------------
 * This file is part of the MindStudio project.
 * Copyright (c) 2025 Huawei Technologies Co.,Ltd.
 *
 * MindStudio is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * ------------------------------------------------------------------------- */

#include "arch_info.h"

namespace Mskpp {

static constexpr int MKKPP_MEMORY_TYPE_GM = 0;
static constexpr int MKKPP_MEMORY_TYPE_UB = 1;
static constexpr int MKKPP_MEMORY_TYPE_L1 = 2;
static constexpr int MKKPP_MEMORY_TYPE_L0C = 3;
static constexpr int MKKPP_MEMORY_TYPE_L0A = 4;
static constexpr int MKKPP_MEMORY_TYPE_L0B = 5;
static constexpr int MKKPP_MEMORY_TYPE_BT = 6;
static constexpr int MKKPP_MEMORY_TYPE_FB = 7;
static constexpr int MKKPP_MEMORY_TYPE_VEC = 8;
static constexpr int MKKPP_MEMORY_TYPE_INVALID = -1;

int GetMemoryTypeEnumByName(const std::string &name) {
    std::map<std::string, int> transMap = {{"GM", MKKPP_MEMORY_TYPE_GM}, {"UB", MKKPP_MEMORY_TYPE_UB},
        {"L1", MKKPP_MEMORY_TYPE_L1}, {"L0C", MKKPP_MEMORY_TYPE_L0C}, {"L0A", MKKPP_MEMORY_TYPE_L0A},
        {"L0B", MKKPP_MEMORY_TYPE_L0B}, {"BT", MKKPP_MEMORY_TYPE_BT}, {"FB", MKKPP_MEMORY_TYPE_FB},
        {"VEC", MKKPP_MEMORY_TYPE_VEC}};
    if (transMap.count(name) == 0) {
        return MKKPP_MEMORY_TYPE_INVALID;
    }
    return transMap[name];
}

int TheoreticalBandwidth(const std::string &src, const std::string &dst) {
    int srcIndex = GetMemoryTypeEnumByName(src);
    int dstIndex = GetMemoryTypeEnumByName(dst);
    if (srcIndex < 0 || dstIndex < 0) {
        return -1;
    }
    if (srcIndex >= GetMemoryTypeEnumByName("L0A")) {
        return -1;
    }
    /**
     * 传输带宽映射表(从行到列表明传输方向),例如从GM->L1为256,L1->L0B为128, 顺序需遵照common_def.h中的宏定义
     *      GM   UB   L1  L0C  L0A  L0B  BT  FB  VEC
     * GM   -1  128  256   -1  128  128  -1  -1   -1
     * UB   -1  128   -1   -1   -1   -1  -1  -1   64
     * L1   128   -1   -1   -1  256  128  64  64   -1
     * L0C  128   -1  256   -1   -1   -1  -1  -1   -1
    * **/
    const std::vector<std::vector<int>> bandWidthsMap = {{-1, 128, 256, -1, 128, 128, -1, -1, -1},
        {-1, 128, -1, -1, -1, -1, -1, -1, 64}, {128, -1, -1, -1, 256, 128, 64, 64, -1},
        {128, -1, 256, -1, -1, -1, -1, -1, -1}};
    return bandWidthsMap[srcIndex][dstIndex];
}

int GetDataTypeSizeOf(const std::string &dtype) {
    std::map<std::string, int> dtypeLenMap = {{"FP16", 2}, {"FP32", 4}, {"INT8", 1}, {"INT16", 2}, {"UINT8", 1},
        {"INT4", 1}, {"UINT16", 2}, {"UINT32", 4}, {"INT32", 4}, {"UINT64", 8}, {"INT64", 8}, {"BF16", 2}};
    if (dtypeLenMap.count(dtype) == 0) {
        return -1;
    }
    return dtypeLenMap[dtype];
}

std::string GetPipeByIO(const std::string &inputTensorMemType, const std::string &outputTensorMemType) {
    if (inputTensorMemType == "VEC") {
        return "RVECST";
    }
    if (inputTensorMemType == "L1") {
        if (outputTensorMemType == "GM") {
            return "PIPE-MTE3";
        } else if (outputTensorMemType == "FB") {
            return "PIPE-FIX";
        }
        return "PIPE-MTE1";
    }
    if (inputTensorMemType == "GM") {
        return "PIPE-MTE2";
    }
    if (inputTensorMemType == "UB") {
        if (outputTensorMemType == "L0C") {
            return "PIPE-V";
        }
        if (outputTensorMemType == "VEC") {
            return "RVECLD";
        }
        return "PIPE-MTE3";
    }
    if (inputTensorMemType == "L0C") {
        if (outputTensorMemType == "UB") {
            return "PIPE-V";
        }
        if (outputTensorMemType == "GM") {
            // This is for A2 chip
            return "PIPE-FIX";
        }
    }
    return "PIPE-FIX";
}

bool IsSupportType(const std::string &tensorType) {
    std::set<std::string> supportDtype = {"bool", "uint1", "int8", "uint8", "float16", "int16", "uint16", "float32",
        "int32", "uint32", "bfloat16", "int64", "uint64", "int4"};
    return supportDtype.count(tensorType) == 1;
}

bool IsSupportFormat(const std::string &tensorFormat) {
    std::set<std::string> supportFormat = {
        "ND", "NCHW", "NHWC", "HWCN", "NC1HWC0", "NHWC1C0", "NDHWC", "C1HWNC0", "NZ", "NDC1HWC0", "DHWNC"};
    return supportFormat.count(tensorFormat) == 1;
}

ArchInfo::ArchInfo()
    : chipType_(ChipType::ASCEND_UNKNOWN), cacheHitRatio_(0), // 当前芯片频率初始化值均为1800
      cubeNum_(0), vectorNum_(0) {}

void ArchInfo::SetChipType(std::string inputChipType) {
    this->mte_ = {{"GM", "L1"}, {"L1", "GM"}, {"GM", "UB"}, {"UB", "GM"}, {"UB", "UB"}, {"GM", "L0A"}, {"GM", "L0B"},
        {"L0C", "GM"}, {"L1", "L0A"}, {"L1", "L0B"}, {"L1", "L0C"}, {"L0C", "L1"}, {"UB", "VEC"}, {"VEC", "UB"}};
    std::map<std::string, ChipType> chipTypeMap = {{"ascend910b1", ChipType::ASCEND_910_B1},
        {"ascend910b3", ChipType::ASCEND_910_B3}, {"ascend910_95", ChipType::ASCEND_910_95}};
    std::transform(inputChipType.begin(), inputChipType.end(), inputChipType.begin(), tolower);
    this->chipType_ = (chipTypeMap.count(inputChipType) != 0) ? chipTypeMap[inputChipType] : ChipType::ASCEND_UNKNOWN;
    if (chipType_ == ChipType::ASCEND_910_B1) {
        this->cubeNum_ = 25; // b1的cube个数为25
        this->vectorNum_ = 50; // b1的vector个数为50
        this->mte_.emplace_back("L1", "BT");
        this->mte_.emplace_back("L1", "FB");
    } else if (chipType_ == ChipType::ASCEND_910_95) {
        freq_ = 1650; // A5 freq = 1650 MHz
        this->mte_.emplace_back("L0C", "UB");
        this->mte_.emplace_back("L1", "UB");
        this->mte_.emplace_back("UB", "L1");
    } else if (chipType_ == ChipType::ASCEND_910_B3) {
        this->cubeNum_ = 20; // b3的cube个数为20
        this->vectorNum_ = 40; // b3的vector个数为40
    } else {
        return; //  未知芯片类型初始化失败
    }
}

std::string ArchInfo::GetChipType() {
    if (this->chipType_ == ChipType::ASCEND_910_B1) {
        return "ascend910b1";
    } else if (this->chipType_ == ChipType::ASCEND_910_B3) {
        return "ascend910b3";
    } else if (this->chipType_ == ChipType::ASCEND_910_95) {
        return "ascend91095";
    }
    return "unknown";
}

void ArchInfo::SetCacheHitRatio(double ratio) { cacheHitRatio_ = ratio; }

double ArchInfo::GetCacheHitRatio() const { return cacheHitRatio_; }

bool ArchInfo::IsMteIdValid(const std::string &fromType, const std::string &toType) const {
    for (const auto &m : this->mte_) {
        if ((m.first == fromType) && (m.second == toType)) {
            return true;
        }
    }
    return false;
}

int ArchInfo::GetFreq() const { return freq_; }
}
