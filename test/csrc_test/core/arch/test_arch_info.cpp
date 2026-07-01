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

#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "arch/arch_info.h"
#include "arch/arch_info.h"

using namespace Mskpp;

TEST(ArchInfo, GetMemoryTypeEnumByName_All)
{
    EXPECT_EQ(GetMemoryTypeEnumByName("GM"), 0);
    EXPECT_EQ(GetMemoryTypeEnumByName("UB"), 1);
    EXPECT_EQ(GetMemoryTypeEnumByName("L1"), 2);
    EXPECT_EQ(GetMemoryTypeEnumByName("L0C"), 3);
    EXPECT_EQ(GetMemoryTypeEnumByName("L0A"), 4);
    EXPECT_EQ(GetMemoryTypeEnumByName("L0B"), 5);
    EXPECT_EQ(GetMemoryTypeEnumByName("BT"), 6);
    EXPECT_EQ(GetMemoryTypeEnumByName("FB"), 7);
    EXPECT_EQ(GetMemoryTypeEnumByName("NULL"), -1);
}

TEST(ArchInfo, TheoreticalBandwidth_All)
{
    EXPECT_EQ(TheoreticalBandwidth("GM", "UB"), 128);
    EXPECT_EQ(TheoreticalBandwidth("GM", "L1"), 256);
    EXPECT_EQ(TheoreticalBandwidth("GM", "L0A"), 128);
    EXPECT_EQ(TheoreticalBandwidth("GM", "L0B"), 128);
    EXPECT_EQ(TheoreticalBandwidth("UB", "UB"), 128);
    EXPECT_EQ(TheoreticalBandwidth("L1", "L0A"), 256);
    EXPECT_EQ(TheoreticalBandwidth("L1", "L0B"), 128);
    EXPECT_EQ(TheoreticalBandwidth("L0C", "GM"), 128);

    EXPECT_EQ(TheoreticalBandwidth("L0A", "GM"), -1);
    EXPECT_EQ(TheoreticalBandwidth("L0B", "GM"), -1);
    EXPECT_EQ(TheoreticalBandwidth("L1", "L1"), -1);
    EXPECT_EQ(TheoreticalBandwidth("VEC", "L1"), -1);
    EXPECT_EQ(TheoreticalBandwidth("L1", "CUBE"), -1);
}

TEST(ArchInfo, GetDataTypeSizeOf_All)
{
    EXPECT_EQ(GetDataTypeSizeOf("FP16"), 2);
    EXPECT_EQ(GetDataTypeSizeOf("FP32"), 4);
    EXPECT_EQ(GetDataTypeSizeOf("INT8"), 1);

    EXPECT_EQ(GetDataTypeSizeOf("NULL"), -1);
}

TEST(ArchInfo, GetPipeByIO_All)
{
    EXPECT_STREQ(GetPipeByIO("L1", "GM").c_str(), "PIPE-MTE3");
    EXPECT_STREQ(GetPipeByIO("L1", "FB").c_str(), "PIPE-FIX");
    EXPECT_STREQ(GetPipeByIO("L1", "NULL").c_str(), "PIPE-MTE1");

    EXPECT_STREQ(GetPipeByIO("GM", "NULL").c_str(), "PIPE-MTE2");

    EXPECT_STREQ(GetPipeByIO("UB", "L0C").c_str(), "PIPE-V");
    EXPECT_STREQ(GetPipeByIO("UB", "NULL").c_str(), "PIPE-MTE3");

    EXPECT_STREQ(GetPipeByIO("L0C", "UB").c_str(), "PIPE-V");
    EXPECT_STREQ(GetPipeByIO("L0C", "GM").c_str(), "PIPE-FIX");

    EXPECT_STREQ(GetPipeByIO("L0C", "NULL").c_str(), "PIPE-FIX");
    EXPECT_STREQ(GetPipeByIO("NULL", "NULL").c_str(), "PIPE-FIX");
}

TEST(ArchInfo, IsSupportType_All)
{
    EXPECT_TRUE(IsSupportType("bool"));
    EXPECT_TRUE(IsSupportType("uint1"));
    EXPECT_TRUE(IsSupportType("int8"));
    EXPECT_TRUE(IsSupportType("uint8"));
    EXPECT_TRUE(IsSupportType("float16"));
    EXPECT_TRUE(IsSupportType("int16"));
    EXPECT_TRUE(IsSupportType("uint16"));
    EXPECT_TRUE(IsSupportType("float32"));
    EXPECT_TRUE(IsSupportType("int32"));
    EXPECT_TRUE(IsSupportType("uint32"));
    EXPECT_TRUE(IsSupportType("bfloat16"));
    EXPECT_TRUE(IsSupportType("int64"));
    EXPECT_TRUE(IsSupportType("uint64"));
}

TEST(ArchInfo, IsSupportFormat_All)
{
    EXPECT_TRUE(IsSupportFormat("ND"));
    EXPECT_TRUE(IsSupportFormat("NCHW"));
    EXPECT_TRUE(IsSupportFormat("NHWC"));
    EXPECT_TRUE(IsSupportFormat("HWCN"));
    EXPECT_TRUE(IsSupportFormat("NC1HWC0"));
    EXPECT_TRUE(IsSupportFormat("NHWC1C0"));
    EXPECT_TRUE(IsSupportFormat("NDHWC"));
    EXPECT_TRUE(IsSupportFormat("C1HWNC0"));
    EXPECT_TRUE(IsSupportFormat("NZ"));
    EXPECT_TRUE(IsSupportFormat("NDC1HWC0"));
    EXPECT_TRUE(IsSupportFormat("DHWNC"));
}

TEST(ArchInfo, ArchInfoNotInit_All)
{
    // 未初始化时chipType为unknown, freq=1800, cacheHitRatio=1.0
    EXPECT_STREQ(ArchInfo::instance()->GetChipType().c_str(), "unknown");
    EXPECT_EQ(ArchInfo::instance()->GetFreq(), 1850);
    EXPECT_EQ(ArchInfo::instance()->GetCacheHitRatio(), 0);
}

TEST(ArchInfo, ArchInfoSetChipType_All)
{
    // 使用非全小写字母初始化成功(此处初始化成功后，后续测试用例共享同一个arch info的单例且无法修改)
    ArchInfo::instance()->SetChipType("asCend910b3");
    EXPECT_STREQ(ArchInfo::instance()->GetChipType().c_str(), "ascend910b3");

    // 支持重新设置
    ArchInfo::instance()->SetChipType("ascend910b1");
    EXPECT_STREQ(ArchInfo::instance()->GetChipType().c_str(), "ascend910b1");

    // 无效设置
    ArchInfo::instance()->SetChipType("ascend910b4");
    EXPECT_STREQ(ArchInfo::instance()->GetChipType().c_str(), "unknown");
}

TEST(ArchInfo, ArchInfoSetCacheHitRatio_All)
{
    ArchInfo::instance()->SetCacheHitRatio(2.1);
    EXPECT_EQ(ArchInfo::instance()->GetCacheHitRatio(), 2.1);
}

TEST(ArchInfo, ArchInfoIsMteIdValid_All)
{
    // ArchInfo初始化为ascend910b1
    ArchInfo::instance()->SetChipType("ascend910b1");
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("GM", "L1"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("GM", "UB"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("UB", "GM"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("GM", "L0A"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("GM", "L0B"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("L0C", "GM"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("L1", "L0A"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("L1", "L0B"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("L1", "L0C"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("L0C", "L1"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("L1", "BT"));
    EXPECT_TRUE(ArchInfo::instance()->IsMteIdValid("L1", "FB"));
    EXPECT_FALSE(ArchInfo::instance()->IsMteIdValid("L1", "L1"));
}
