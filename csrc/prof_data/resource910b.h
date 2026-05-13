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

#ifndef __MSKPP_PROFDATA_RESOURCE_910B1__
#define __MSKPP_PROFDATA_RESOURCE_910B1__

#include <cstdint>
#include <vector>
#include <string>
#include <map>

namespace Mskpp {
/**
 * MovType为mov类指令的统一结构体，目前暂用数据numBursts和bandwidth
 * 其可以包含的mov类指令的类型有三种表头格式：
 * "Num Bursts Total Cycles Total Data(GB) Task Time(us) Bandwidth(GB/s) l1_write_bw main_mem_read_bw"
 * "Num Bursts Bandwidth(GB/s)"
 * "Num Bursts Total Cycles Total Data(GB) Task Time(us) Bandwidth(GB/s)"
 * 新增加的mov类指令需填充以下结构体，对于缺少字段，统一填0
 */
struct MovType {
    double numBursts;
    double bandwidth;  // GB/s
    double totalData;  // GB
    double taskTime;   // us
    uint32_t totalCycles;
    uint32_t l1WriteBw;
    uint32_t mainMemReadBw;
};

/**
 * MovTypeRepeat为mov类指令中指定了repeat参数的结构体，根据指令类型，直接通过repeat得到bandwith
 */
struct MovTypeRepeat {
    uint32_t repeat;
    double bandwidth;  // GB/s
};

/**
 * MmadType为矩阵计算类指令的统一结构体，目前暂用数据mknSum和calPerf
 * 其可以包含的类型有一种表头格式：
 * {"", "m", "k", "n", "cal_perf(OPs/Cycle)", "mkn_sum"}
 */
struct MmadType {
    uint32_t null;
    uint32_t m;
    uint32_t k;
    uint32_t n;
    double calPerf;  // OPs/Cycle
    int mknSum;      // m*k*n
};

/**
 * VecType为向量计算类指令的统一结构体，目前暂用数据numSum和calPerf
 * 其可以包含的类型有三种表头格式：
 * {"repeat", "cal_perf(OPs/Cycle)", "num_sum", "total_cycles"}
 * {"", "repeat", "cal_perf(OPs/Cycle)", "num_sum"}
 * {"", "repeat", "cal_perf(OPs/Cycle)", "num_sum", "total_cycles"}
 */
struct VecType {
    uint32_t numSum;
    double calPerf;  // OPs/Cycle
    int null;
    uint32_t repeat;
    double totalCycles;
};

std::vector<MovType> GetMovTypeData(std::string opName);
std::vector<MovTypeRepeat> GetMovRepeatTypeData(const std::string& opName);
std::vector<MmadType> GetMmadTypeData(std::string opName);
std::vector<VecType> GetVecTypeData(std::string opName);
}
#endif
