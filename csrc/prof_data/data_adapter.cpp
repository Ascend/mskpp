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

#include "data_adapter.h"
#include "linearInterpolate.h"

namespace Mskpp {
double MovClass::Get(std::string src, std::string dst, long dataSize, bool transEnable) {
    std::string movPath = src + "_TO_" + dst;
    if (transEnable) {
        movPath = movPath + "_TRANS";
    }
    movPath =
        movPath + "_" + ArchInfo::instance()->GetChipType().substr(6, 5); // ascend910b*从6开始获取5个字符得到910b*
    // 如果当前指令的数据未获取，取出对应数据
    if (movDatasMap.count(movPath) == 0) {
        bool res = InitOneMovPathData(movPath);
        /* when there are no collected data, return theoretical data */
        if (!res) {
            /* a negative number is returned when an error occurs */
            return static_cast<double>(TheoreticalBandwidth(src, dst));
        }
    }
    std::map<uint32_t, double> &curves = movDatasMap[movPath];
    if (transEnable && src == "GM" && dst == "L1") {
        double maxTestBytes = 0.0;
        for (const auto &point : curves) {
            if (point.first > maxTestBytes) {
                maxTestBytes = point.first;
            }
        }
        if (static_cast<double>(dataSize) > maxTestBytes) {
            uint32_t func = 32 * 1024;
            uint32_t diff = static_cast<uint32_t>((static_cast<double>(dataSize) - maxTestBytes) / func + 1);
            if (func * diff / func == diff && dataSize > diff * func) {
                dataSize = dataSize - diff * func;
            }
        }
    }
    if (dataSize > UINT32_MAX) {
        dataSize = 0;
        printf("Warning : The input data volume exceeds uint32_max. Please reduce the input data size.");
    }
    return LinearInterpolate(curves, static_cast<uint32_t>(dataSize));
}

double MovClass::GetPeak(std::string src, std::string dst) {
    std::string movPath = src + "_TO_" + dst + "_" + ArchInfo::instance()->GetChipType().substr(6, 5); // 6开始取5个字符
    if (movDatasMap.count(movPath) == 0) {
        bool res = InitOneMovPathData(movPath);
        /* when there are no collected data, return theoretical data */
        if (!res) {
            /* a negative number is returned when an error occurs */
            return static_cast<double>(TheoreticalBandwidth(src, dst));
        }
    }
    double max = 0;
    for (const auto &point : movDatasMap[movPath]) {
        if (point.second > max) {
            max = point.second;
        }
    }
    return max;
}

double MovClass::GetRepeat(const std::string &src, const std::string &dst, uint32_t repeat) {
    std::string fullOpName =
        src + "_TO_" + dst + "_" + ArchInfo::instance()->GetChipType().substr(6, 5); // 6开始取5个字符
    auto res = GetMovRepeatTypeData(fullOpName);
    double maxV = 0;
    std::map<uint32_t, double> curves;
    uint32_t maxG = 0;
    for (const auto &data : res) {
        if (data.repeat > maxG) {
            maxG = data.repeat;
        }
        if (data.bandwidth > maxV) {
            maxV = data.bandwidth;
        }
        curves[data.repeat] = data.bandwidth;
    }
    if (repeat >= maxG) {
        return maxV;
    }
    if (curves.count(repeat) != 0) {
        return curves[repeat];
    }
    return LinearInterpolate(curves, repeat);
}

bool MovClass::InitOneMovPathData(std::string &movPath) {
    auto res = GetMovTypeData(movPath);
    if (res.empty()) {
        return false;
    }
    std::map<uint32_t, double> curves;
    for (const auto &data : res) {
        int freq = ArchInfo::instance()->GetFreq();
        if (data.numBursts < 0 || freq == 0) {
            return false;
        }
        uint32_t new_k_byte = static_cast<uint32_t>(data.numBursts * 1024);
        double new_v_byte_per_cycle =
            data.bandwidth * 1024 * 1024 * 1024 / (static_cast<double>(freq) * 1000000); // freq在初始化时固定为1800MHz
        curves[new_k_byte] = new_v_byte_per_cycle;
    }
    movDatasMap[movPath] = curves;
    return true;
}

double MmadClass::Get(long granularity, std::string instrType) {
    std::map<uint32_t, double> curves;
    uint32_t g;
    uint32_t maxG = 0;
    std::map<std::string, std::string> mmadMap = {{"ascend910b1", "MMAD_FP16_FP16_FP32_1_core_910b1"},
        {"ascend910b3", "MMAD_FP16_FP16_FP32_1_core_910b3"}, {"ascend91095", "MMAD_FP16_FP16_FP32_1_core_91095"}};
    std::string movPath = mmadMap[ArchInfo::instance()->GetChipType()];
    auto res = GetMmadTypeData(movPath);

    for (const auto &data : res) {
        g = data.mknSum;
        curves[g] = data.calPerf;
        if (g > maxG) {
            maxG = g;
        }
    }
    if (granularity > maxG) {
        /* a negative number is returned when an error occurs */
        return static_cast<double>(GetDataTypeSizeOf(instrType)) * 16 * 16 * 16; // 16为当前cube的大小
    }
    return LinearInterpolate(curves, granularity);
}

double VecClass::Get(long granularity, const std::string &instrType) {
    std::string fullOpName = instrName + "_" + instrType + "_1_core_" +
        ArchInfo::instance()->GetChipType().substr(6, 5); // 6开始取5个字符得到910b*
    auto res = GetVecTypeData(fullOpName);
    double maxV = 0;
    std::map<uint32_t, double> curves;
    uint32_t maxG = 0;
    for (const auto &data : res) {
        if (data.numSum > maxG) {
            maxG = data.numSum;
        }
        if (data.calPerf > maxV) {
            maxV = data.calPerf;
        }
        curves[data.numSum] = data.calPerf;
    }
    if (granularity >= maxG) {
        return maxV;
    }
    return LinearInterpolate(curves, granularity);
}
}
