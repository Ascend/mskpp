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

#ifndef __MSKPP_TASKSCHEDULE_RAWTASK__
#define __MSKPP_TASKSCHEDULE_RAWTASK__

#include <string>
#include <Python.h>

/* [Name]: RawTask
 * [Description]: 提供python侧的task到cpp侧的映射，自身其实没什么业务逻辑
 * [Notice]: 1、建议构造前通过CheckPyObj函数对输入的python对象进行基础检查
 */
namespace Mskpp {
class RawTask {
public:
    explicit RawTask(PyObject *taskObj);
    RawTask(const RawTask &obj);
    RawTask &operator=(const RawTask &other);
    ~RawTask();
    std::string &GetOwner();
    std::string &GetName();
    int64_t GetEventId() const;
    uint64_t GetCostTime() const;
    int32_t SetDuration(uint64_t start, uint64_t end) const;
    int32_t Size() const; // return a negative number when an error occurs
    bool IsReady() const;
    void Run() const;
    static bool CheckPyObj(PyObject *taskObj); // Since it is not appropriate to throw exceptions in the constructor,
        // caller shall check the input valid.
private:
    int32_t RunPreFunc() const;
    int32_t RunImplFunc() const;
    int32_t RunPostFunc() const;

private:
    PyObject *pyTask;
    std::string name;
    std::string owner;
    uint64_t costTime = 0;
    int64_t eventId = -1;
};
}
#endif
