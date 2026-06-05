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

#include <map>
#include "../core/arch/arch_info.h"
#include "init_module.h"

namespace Mskpp {
PyObject *MSKPP_ARCH_Get(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    return PyUnicode_FromString(ArchInfo::instance()->GetChipType().c_str());
}

PyObject *MSKPP_ARCH_Set(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
    if (nargs != 1) {
        PyErr_Format(PyExc_TypeError, "Function set except 1 argument, got %zd.", nargs);
        return NULL;
    }
    const char *s = nullptr;
    Py_ssize_t len;
    s = PyUnicode_AsUTF8AndSize(args[0], &len);
    if (!s) {
        PyErr_SetString(PyExc_TypeError, "ChipType except a string value.");
        return NULL;
    }
    ArchInfo::instance()->SetChipType(std::string(s));
    Py_RETURN_NONE;
}

PyObject *MSKPP_ARCH_CalTimeByCycle(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
    if (nargs != 1) {
        PyErr_Format(PyExc_TypeError, "Function cal_duration except 1 argument, got %zd.", nargs);
        return NULL;
    }
    double cycle;
    if (PyLong_CheckExact(args[0])) {
        long long value = PyLong_AsLongLong(args[0]);
        if (value == -1 && PyErr_Occurred()) {
            PyErr_SetString(PyExc_OverflowError, "Function cal_duration value out of range for long long.");
            return NULL;
        }
        cycle = static_cast<double>(value);
    } else if (PyFloat_CheckExact(args[0])) {
        cycle = PyFloat_AsDouble(args[0]);
    } else {
        PyErr_SetString(PyExc_TypeError, "Function cal_duration except a number value.");
        return NULL;
    }
    int freq = ArchInfo::instance()->GetFreq();
    if (freq == 0) {
        Py_RETURN_NONE;
    }
    double time = cycle / freq;
    return PyFloat_FromDouble(time);
}

PyObject *MSKPP_ARCH_IsMteValid(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
    if (nargs != 2) { // MteIdValid函数需要传入2个参数
        PyErr_Format(PyExc_TypeError, "Function mte_is_valid except 2 arguments, got %zd.", nargs);
        return NULL;
    }
    if (!PyUnicode_Check(args[0]) || !PyUnicode_Check(args[1])) {
        PyErr_SetString(PyExc_TypeError, "Function mte_is_valid except 2 string value.");
        return NULL;
    }

    Py_ssize_t len;
    const char *src = PyUnicode_AsUTF8AndSize(args[0], &len);
    const char *dst = PyUnicode_AsUTF8AndSize(args[1], &len);
    if (src == nullptr || dst == nullptr) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to parse input.");
        return NULL;
    }
    if (ArchInfo::instance()->IsMteIdValid(std::string(src), std::string(dst))) {
        Py_RETURN_TRUE;
    } else {
        Py_RETURN_FALSE;
    }
}

PyObject *MSKPP_ARCH_GetCacheHitRatio(PyObject *self, PyObject *Py_UNUSED(ignored)) {
    return PyFloat_FromDouble(ArchInfo::instance()->GetCacheHitRatio());
}

PyObject *MSKPP_ARCH_SetCacheHitRatio(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
    double ratio;
    if (nargs != 1) {
        PyErr_Format(PyExc_TypeError, "Function set_cache_hit_ratio except 1 argument, got %zd.", nargs);
        return NULL;
    }
    if (PyLong_CheckExact(args[0])) {
        long long value = PyLong_AsLongLong(args[0]);
        if (value == -1 && PyErr_Occurred()) {
            PyErr_SetString(PyExc_OverflowError, "Function set_cache_hit_ratio value out of range for long long.");
            return NULL;
        }
        ratio = static_cast<double>(value);
    } else if (PyFloat_CheckExact(args[0])) {
        ratio = PyFloat_AsDouble(args[0]);
    } else {
        PyErr_SetString(PyExc_TypeError, "Function set_cache_hit_ratio except a number value.");
        return NULL;
    }
    ArchInfo::instance()->SetCacheHitRatio(ratio);
    Py_RETURN_NONE;
}

PyObject *MSKPP_ARCH_GetPipeByIO(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
    if (nargs != 2) { // GetPipeByIO函数需要传入2个参数
        PyErr_Format(PyExc_TypeError, "Function get_pipe_by_io except 2 arguments, got %zd.", nargs);
        return NULL;
    }

    PyObject *inputMemType = args[0];
    PyObject *outputMemType = args[1];
    if (!PyUnicode_CheckExact(inputMemType) || !PyUnicode_CheckExact(outputMemType)) {
        PyErr_SetString(PyExc_TypeError, "Invalid parameter, except string-type.");
        return NULL;
    }

    Py_ssize_t len;
    const char *i = PyUnicode_AsUTF8AndSize(inputMemType, &len);
    const char *o = PyUnicode_AsUTF8AndSize(outputMemType, &len);
    if (!i || !o) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to parse parameter.");
        return NULL;
    }
    std::string pipeName = GetPipeByIO(std::string(i), std::string(o));
    return PyUnicode_FromString(pipeName.c_str());
}

PyObject *MSKPP_ARCH_GetSizeOf(PyObject *self, PyObject *const *args, Py_ssize_t nargs) {
    if (nargs != 1) {
        PyErr_Format(PyExc_TypeError, "Function get_size_of except 1 argument, got %zd.", nargs);
        return NULL;
    }

    if (!PyUnicode_CheckExact(args[0])) {
        PyErr_SetString(PyExc_TypeError, "Function get_size_of except a string value.");
        return NULL;
    }

    const char *dtype = nullptr;
    Py_ssize_t len;
    int32_t ret;
    dtype = PyUnicode_AsUTF8AndSize(args[0], &len);
    if (!dtype) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to parse parameter.");
        return NULL;
    }
    ret = GetDataTypeSizeOf(std::string(dtype));
    if (ret < 0) {
        PyErr_Format(PyExc_RuntimeError, "The dtype(%s) is not support now. you can add it to map.", dtype);
        return NULL;
    }

    return PyLong_FromLong(ret);
}

static PyMethodDef g_mskppArchMethod[] = {{"get", reinterpret_cast<PyCFunction>(MSKPP_ARCH_Get), METH_NOARGS, nullptr},
    {"set", reinterpret_cast<PyCFunction>(MSKPP_ARCH_Set), METH_FASTCALL, nullptr},
    {"cal_duration", reinterpret_cast<PyCFunction>(MSKPP_ARCH_CalTimeByCycle), METH_FASTCALL, nullptr},
    {"mte_is_valid", reinterpret_cast<PyCFunction>(MSKPP_ARCH_IsMteValid), METH_FASTCALL, nullptr},
    {"get_cache_hit_ratio", reinterpret_cast<PyCFunction>(MSKPP_ARCH_GetCacheHitRatio), METH_NOARGS, nullptr},
    {"set_cache_hit_ratio", reinterpret_cast<PyCFunction>(MSKPP_ARCH_SetCacheHitRatio), METH_FASTCALL, nullptr},
    {"get_pipe_by_io", reinterpret_cast<PyCFunction>(MSKPP_ARCH_GetPipeByIO), METH_FASTCALL, nullptr},
    {"get_size_of", reinterpret_cast<PyCFunction>(MSKPP_ARCH_GetSizeOf), METH_FASTCALL, nullptr},
    {nullptr, nullptr, 0, nullptr}};

static struct PyModuleDef g_mskppArchModuleDef = {
    PyModuleDef_HEAD_INIT, "mskpp._C.arch", /* m_name */
    nullptr, /* m_doc */
    -1, /* m_size */
    g_mskppArchMethod, /* m_methods */
};

PyObject *InitArchInfoModule() { return PyModule_Create(&g_mskppArchModuleDef); }
}
