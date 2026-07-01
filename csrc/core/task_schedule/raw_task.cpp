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

#include <vector>
#include <iostream>
#include "raw_task.h"

namespace Mskpp {
RawTask::RawTask(PyObject *taskObj) : pyTask(taskObj) {
    const char *s = nullptr;
    Py_ssize_t len;
    PyObject *o = nullptr;

    Py_INCREF(pyTask);

    o = PyObject_GetAttrString(taskObj, "name");
    if (o) {
        s = PyUnicode_AsUTF8AndSize(o, &len);
        if (s) {
            name = std::string(s);
        }
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString(taskObj, "owner");
    if (o) {
        s = PyUnicode_AsUTF8AndSize(o, &len);
        if (s) {
            owner = std::string(s);
        }
        Py_DECREF(o);
    }

    o = PyObject_GetAttrString(taskObj, "event_id");
    if (o) {
        if (PyLong_CheckExact(o)) {
            eventId = PyLong_AsLong(o);
        }
        Py_DECREF(o);
    }

    o = PyObject_CallMethod(pyTask, "cost_time", nullptr);
    if (o) {
        if (PyLong_CheckExact(o)) {
            costTime = PyLong_AsUnsignedLongLong(o);
        } else if (PyFloat_CheckExact(o)) {
            costTime = static_cast<uint64_t>(PyFloat_AsDouble(o));
        }
        Py_DECREF(o);
    }
}

RawTask::RawTask(const RawTask &obj) {
    name = obj.name;
    owner = obj.owner;
    costTime = obj.costTime;
    eventId = obj.eventId;
    pyTask = obj.pyTask;
    Py_INCREF(pyTask);
}

RawTask &RawTask::operator=(const RawTask &other) {
    if (this != &other) {
        Py_XDECREF(pyTask);
        pyTask = other.pyTask;
        Py_INCREF(pyTask);
        name = other.name;
        owner = other.owner;
        costTime = other.costTime;
        eventId = other.eventId;
    }
    return *this;
}

RawTask::~RawTask() { Py_XDECREF(pyTask); }

std::string &RawTask::GetOwner() { return owner; }

std::string &RawTask::GetName() { return name; }

int64_t RawTask::GetEventId() const { return eventId; }

uint64_t RawTask::GetCostTime() const { return costTime; }

int32_t RawTask::SetDuration(uint64_t start, uint64_t end) const {
    PyObject *pyStart = PyLong_FromUnsignedLongLong(start);
    if (pyStart == nullptr) {
        return -1;
    }
    PyObject *pyEnd = PyLong_FromUnsignedLongLong(end);
    if (pyEnd == nullptr) {
        Py_DECREF(pyStart);
        return -1;
    }

    PyObject_SetAttrString(pyTask, "start_time", pyStart);
    PyObject_SetAttrString(pyTask, "end_time", pyEnd);
    Py_DECREF(pyStart);
    Py_DECREF(pyEnd);

    return 0;
}

int32_t RawTask::Size() const {
    uint64_t size = 1;
    PyObject *ret = PyObject_CallMethod(pyTask, "size", nullptr);
    if (ret && PyLong_CheckExact(ret)) {
        size = static_cast<uint64_t>(PyLong_AsUnsignedLongLong(ret));
    }
    Py_XDECREF(ret);
    return size;
}

bool RawTask::IsReady() const {
    long ready = 0;
    PyObject *ret = PyObject_CallMethod(pyTask, "is_ready", nullptr);
    /* PyBool is sub class of PyLong */
    if (ret && PyLong_Check(ret)) {
        ready = PyLong_AsLong(ret);
    }
    Py_XDECREF(ret);
    return ready != 0;
}

int RawTask::RunPreFunc() const {
    PyObject *ret = PyObject_CallMethod(pyTask, "pre_func", nullptr);
    if (ret == nullptr) {
        return -1;
    }
    Py_XDECREF(ret);
    return 0;
}

int RawTask::RunPostFunc() const {
    PyObject *ret = PyObject_CallMethod(pyTask, "post_func", nullptr);
    if (ret == nullptr) {
        return -1;
    }
    Py_XDECREF(ret);
    return 0;
}

int RawTask::RunImplFunc() const {
    /* do nothing, only for logic and expand */
    return 0;
}

void RawTask::Run() const {
    RunPreFunc();
    RunImplFunc();
    RunPostFunc();
}

bool RawTask::CheckPyObj(PyObject *taskObj) {
    if (taskObj == nullptr) {
        return false;
    }

    static std::vector<std::string> necessaryAttr = {
        "name", "owner", "cost_time", "size", "is_ready", "pre_func", "post_func"};

    for (uint32_t i = 0; i < necessaryAttr.size(); i++) {
        if (PyObject_HasAttrString(taskObj, necessaryAttr[i].c_str()) == 0) {
            std::cout << "ERROR: Task need attribute " + necessaryAttr[i] + "." << std::endl;
            return false;
        }
    }
    return true;
}

}
