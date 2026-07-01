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

#include "init_module.h"
#include "../core/task_schedule/task_schedule.h"

namespace Mskpp {
static PyObject *MSKPP_SCHEDULE_Clean(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    TaskSchedule::instance()->Clear();
    Py_RETURN_NONE;
}

static PyObject *MSKPP_SCHEDULE_SetDebugMode(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
    if (nargs != 1) {
        PyErr_Format(PyExc_TypeError, "Function set_debug_mode except 1 argument, got %zd.", nargs);
        return NULL;
    }

    PyObject *pyMode = args[0];
    if (!PyBool_Check(pyMode)) {
        PyErr_SetString(PyExc_TypeError, "Function set_debug_mode except a boolean value.");
        return NULL;
    }
    bool mode = (PyLong_AsLong(pyMode) != 0);
    TaskSchedule::instance()->SetDebugMode(mode);
    Py_RETURN_NONE;
}

static PyObject *MSKPP_SCHEDULE_GetDebugMode(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    bool mode = TaskSchedule::instance()->GetDebugMode();
    PyObject *o = PyBool_FromLong(static_cast<long>(mode));
    return o;
}

static PyObject *MSKPP_SCHEDULE_AddTask(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
    if (nargs != 1) {
        PyErr_Format(PyExc_TypeError, "Function add_task except 1 argument, got %zd.", nargs);
        return NULL;
    }
    PyObject *o = args[0];
    if (!RawTask::CheckPyObj(o)) {
        PyErr_SetString(PyExc_TypeError, "Please construct the task using template class RawTask.");
        return NULL;
    }

    RawTask task(o);
    if (PyErr_Occurred()) {
        return NULL;
    }
    TaskSchedule::instance()->AddTask(task);
    Py_RETURN_NONE;
}

static PyObject *MSKPP_SCHEDULE_Run(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    int32_t ret = TaskSchedule::instance()->Run();
    if (ret < 0) {
        PyErr_SetString(PyExc_RuntimeError, "Task failed to run.");
        return NULL;
    }
    return PyLong_FromLong(ret);
}

static PyMethodDef g_scheduleMethods[] = {
    {"clean", reinterpret_cast<PyCFunction>(MSKPP_SCHEDULE_Clean), METH_NOARGS, nullptr},
    {"set_debug_mode", reinterpret_cast<PyCFunction>(MSKPP_SCHEDULE_SetDebugMode), METH_FASTCALL, nullptr},
    {"get_debug_mode", reinterpret_cast<PyCFunction>(MSKPP_SCHEDULE_GetDebugMode), METH_NOARGS, nullptr},
    {"add_task", reinterpret_cast<PyCFunction>(MSKPP_SCHEDULE_AddTask), METH_FASTCALL, nullptr},
    {"run", reinterpret_cast<PyCFunction>(MSKPP_SCHEDULE_Run), METH_NOARGS, nullptr}, {nullptr, nullptr, 0, nullptr}};

MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppScheduleClass, "Schedule", g_scheduleMethods, nullptr);

static struct PyModuleDef g_mskppScheduleModuleDef = {
    PyModuleDef_HEAD_INIT, "mskpp._C.task_schedule", /* m_name */
    nullptr, /* m_doc */
    -1, /* m_size */
    nullptr, /* m_methods */
};

PyObject *InitTaskScheduleModule() {
    PyObject *m = nullptr;

    m = PyModule_Create(&g_mskppScheduleModuleDef);
    if (m == nullptr) {
        return nullptr;
    }

    if (PyType_Ready(&g_mskppScheduleClass) < 0) {
        PyErr_SetString(PyExc_TypeError, "Failed to init class Schedule.");
        Py_DECREF(m);
        return nullptr;
    }

    if (PyModule_AddObject(m, "Schedule", reinterpret_cast<PyObject *>(&g_mskppScheduleClass)) < 0) {
        PyErr_SetString(PyExc_TypeError, "Failed to bind class Schedule.");
        Py_DECREF(m);
        return nullptr;
    }

    return m;
}
}
