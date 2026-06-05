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
#include <string>
#include "init_module.h"
namespace Mskpp {
PyDoc_STRVAR(MSKPP_C_MODULE_DOC, "Optimized C implementation for the mskpp module.");
using MSKPP_InitModuleFunc = PyObject *(*)();
std::map<std::string, MSKPP_InitModuleFunc> g_mskppCModuleList = {
    {"arch", InitArchInfoModule}, {"prof_data", InitProfdataModule}, {"task_schedule", InitTaskScheduleModule}};

PyObject *BasePyNew(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    return PyBaseObject_Type.tp_new(type, args, kwds);
}

static int MSKPP_InitSubModule(PyObject *baseModule) {
    PyObject *submodule = nullptr;
    for (auto &iter : g_mskppCModuleList) {
        submodule = iter.second();
        if (submodule == nullptr) {
            PyErr_Format(PyExc_ImportError, "Failed to import module %s.", iter.first.c_str());
            Py_DECREF(baseModule);
            return -1;
        }
        Py_INCREF(submodule);
        if (PyModule_AddObject(baseModule, iter.first.c_str(), submodule) < 0) {
            Py_DECREF(submodule);
            Py_DECREF(baseModule);
            PyErr_Format(PyExc_ImportError, "Failed to import module %s.", iter.first.c_str());
            return -1;
        }
    }
    return 0;
}

static struct PyModuleDef g_mskppCModuleDef = {
    PyModuleDef_HEAD_INIT, "mskpp._C", /* m_name */
    MSKPP_C_MODULE_DOC, /* m_doc */
    -1, /* m_size */
    nullptr, /* m_methods */
};

#ifdef __cplusplus
extern "C" {
#pragma GCC visibility push(default)
#endif
PyMODINIT_FUNC PyInit__C(void) {
    PyObject *m = nullptr;
    m = PyModule_Create(&g_mskppCModuleDef);
    if (m == nullptr || MSKPP_InitSubModule(m) != 0) {
        return nullptr;
    }
    return m;
}
#pragma GCC visibility pop
#ifdef __cplusplus
}
}
#endif
