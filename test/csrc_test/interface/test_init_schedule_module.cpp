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
#include "init_module.h"
#include "../core/task_schedule/task_generator.h"
#include "../core/task_schedule/pipeline.h"

using namespace Mskpp;

// 定义一个task包含的所有内容
static PyObject* cost_time(PyObject* self, PyObject* args) {
    return PyLong_FromLong(200);
}
// 定义一个task包含的所有内容
static PyObject* cost_time_float(PyObject* self, PyObject* args) {
    return PyFloat_FromDouble(100.256);
}
static PyObject* size(PyObject* self, PyObject* args) {
    return PyLong_FromLong(30);
}
static PyObject* pre_func(PyObject* self, PyObject* args) {
    return PyUnicode_FromString("pre_func");
}
static PyObject* is_ready(PyObject* self, PyObject* args) {
    return PyBool_FromLong(1);
}
static PyObject* post_func(PyObject* self, PyObject* args) {
    return PyUnicode_FromString("post_func");
}
static PyMethodDef taskMethods[] = {
        {"cost_time", cost_time, METH_NOARGS, nullptr},
        {"size", size, METH_NOARGS, nullptr},
        {"is_ready", is_ready, METH_NOARGS, nullptr},
        {"pre_func", pre_func, METH_NOARGS, nullptr},
        {"post_func", post_func, METH_NOARGS, nullptr},
        {nullptr, nullptr, 0, nullptr}
};

static PyMethodDef taskMethodsB[] = {
        {"cost_time", cost_time_float, METH_NOARGS, nullptr},
        {"size", size, METH_NOARGS, nullptr},
        {"is_ready", is_ready, METH_NOARGS, nullptr},
        {"pre_func", pre_func, METH_NOARGS, nullptr},
        {"post_func", post_func, METH_NOARGS, nullptr},
        {nullptr, nullptr, 0, nullptr}
};

// 模块定义
static struct PyModuleDef taskModule = {
        PyModuleDef_HEAD_INIT,
        "task",
        nullptr,
        -1,
        taskMethods
};

// 模块定义
static struct PyModuleDef taskModuleB = {
        PyModuleDef_HEAD_INIT,
        "taskB",
        nullptr,
        -1,
        taskMethodsB
};

class ScheduleTest : public testing::Test {
protected:
    PyObject *GetmoduleClass(const std::string &className)
    {
        PyObject *taskSchedule = InitTaskScheduleModule();
        PyObject *moduleClass = PyObject_GetAttrString(taskSchedule, className.c_str());
        return moduleClass;
    }

    // 模块初始化函数
    PyObject* PyInit_task(void) {
        // 创建模块对象
        PyObject* m = PyModule_Create(&taskModule);
        if (m != NULL) {
            // 创建字符串对象
            PyObject* name = PyUnicode_FromString("MMAD");
            PyObject* owner = PyUnicode_FromString("AIC0-PIPE-M");
            PyObject* start_time = PyLong_FromLong(0);
            PyObject* end_time = PyLong_FromLong(0);

            // 将字符串对象添加到模块中
            if (PyModule_AddObject(m, "name", name) < 0) {
                Py_DECREF(name);
                Py_DECREF(m);
                return NULL;
            }
            // 将字符串对象添加到模块中
            if (PyModule_AddObject(m, "owner", owner) < 0) {
                Py_DECREF(owner);
                Py_DECREF(m);
                return NULL;
            }
            // 将字符串对象添加到模块中
            if (PyModule_AddObject(m, "start_time", start_time) < 0) {
                Py_DECREF(start_time);
                Py_DECREF(m);
                return NULL;
            }
            // 将字符串对象添加到模块中
            if (PyModule_AddObject(m, "name", end_time) < 0) {
                Py_DECREF(end_time);
                Py_DECREF(m);
                return NULL;
            }
        }
        return m;
    }

    // 模块初始化函数
    PyObject* PyInit_taskB(void) {
        // 创建模块对象
        PyObject* m = PyModule_Create(&taskModuleB);
        if (m != NULL) {
            // 创建字符串对象
            PyObject* name = PyUnicode_FromString("MOV_GM_TO_UB");
            PyObject* owner = PyUnicode_FromString("AIC0-PIPE-MTE1");
            PyObject* start_time = PyLong_FromLong(0);
            PyObject* end_time = PyLong_FromLong(0);

            // 将字符串对象添加到模块中
            if (PyModule_AddObject(m, "name", name) < 0) {
                Py_DECREF(name);
                Py_DECREF(m);
                return NULL;
            }
            // 将字符串对象添加到模块中
            if (PyModule_AddObject(m, "owner", owner) < 0) {
                Py_DECREF(owner);
                Py_DECREF(m);
                return NULL;
            }
            // 将字符串对象添加到模块中
            if (PyModule_AddObject(m, "start_time", start_time) < 0) {
                Py_DECREF(start_time);
                Py_DECREF(m);
                return NULL;
            }
            // 将字符串对象添加到模块中
            if (PyModule_AddObject(m, "name", end_time) < 0) {
                Py_DECREF(end_time);
                Py_DECREF(m);
                return NULL;
            }
        }
        return m;
    }

    static void SetUpTestSuite() {
        Py_Initialize();
    }

    static void TearDownTestSuite() {
        Py_Finalize();  // 关闭 Python 解释器
    }

};

TEST_F(ScheduleTest, DebugMode_Default_Is_False_Success)
{
    std::string className = "Schedule";
    auto scheduleClass = GetmoduleClass(className);
    EXPECT_TRUE(scheduleClass != NULL);
    EXPECT_TRUE(PyCallable_Check(scheduleClass));
    PyObject *pInstance = NULL;
    pInstance = PyObject_CallObject(scheduleClass, NULL);
    EXPECT_TRUE(pInstance != NULL);

    // 从实例中获取get_debug_mode函数
    PyObject *getDebugMode = PyObject_GetAttrString(pInstance, "get_debug_mode");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(getDebugMode != NULL);
    EXPECT_TRUE(PyCallable_Check(getDebugMode));
    // 调用get_debug_mode函数获取mode的状态
    PyObject *debugMode = PyObject_CallObject(getDebugMode, NULL);
    EXPECT_EQ(debugMode, Py_False);  // mode初始状态为False
    Py_DECREF(getDebugMode);
    Py_DECREF(debugMode);
    Py_DECREF(pInstance);
}

TEST_F(ScheduleTest, DebugMode_Set_True_Success)
{
    std::string className = "Schedule";
    auto scheduleClass = GetmoduleClass(className);
    EXPECT_TRUE(scheduleClass != NULL);
    EXPECT_TRUE(PyCallable_Check(scheduleClass));
    PyObject *pInstance = NULL;
    pInstance = PyObject_CallObject(scheduleClass, NULL);
    EXPECT_TRUE(pInstance != NULL);
    // 从实例中获取set_debug_mode函数
    PyObject *setDebugMode = PyObject_GetAttrString(pInstance, "set_debug_mode");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(setDebugMode != NULL);
    EXPECT_TRUE(PyCallable_Check(setDebugMode));
    // 创建函数参数
    PyObject *pArgs = PyTuple_New(1);
    PyObject *pValue = PyBool_FromLong(1);  // debug_mode设置为1，既True
    PyTuple_SetItem(pArgs, 0, pValue);
    // 调用函数
    PyObject *pResult = PyObject_CallObject(setDebugMode, pArgs);
    Py_DECREF(pArgs);
    Py_DECREF(setDebugMode);
    Py_DECREF(pResult);
    // 从实例中获取get_debug_mode函数
    PyObject *getDebugMode = PyObject_GetAttrString(pInstance, "get_debug_mode");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(getDebugMode != NULL);
    EXPECT_TRUE(PyCallable_Check(getDebugMode));
    // 调用get_debug_mode函数获取mode的状态
    PyObject *debugMode = PyObject_CallObject(getDebugMode, NULL);
    EXPECT_EQ(debugMode, Py_True);
    Py_DECREF(getDebugMode);
    Py_DECREF(debugMode);
    Py_DECREF(pInstance);
}

TEST_F(ScheduleTest, Clear_TaskSchedule_Success)
{
    std::string className = "Schedule";
    auto scheduleClass = GetmoduleClass(className);
    EXPECT_TRUE(scheduleClass != NULL);
    EXPECT_TRUE(PyCallable_Check(scheduleClass));
    PyObject *pInstance = NULL;
    pInstance = PyObject_CallObject(scheduleClass, NULL);
    EXPECT_TRUE(pInstance != NULL);

    // 从实例中获取set_debug_mode函数,先将debug mode设置为true
    PyObject *setDebugMode = PyObject_GetAttrString(pInstance, "set_debug_mode");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(setDebugMode != NULL);
    EXPECT_TRUE(PyCallable_Check(setDebugMode));
    // 创建函数参数
    PyObject *pArgs = PyTuple_New(1);
    PyObject *pValue = PyBool_FromLong(1);  // debug_mode设置为1，既True
    PyTuple_SetItem(pArgs, 0, pValue);
    // 调用函数
    PyObject *pResult = PyObject_CallObject(setDebugMode, pArgs);
    Py_DECREF(pArgs);
    Py_DECREF(setDebugMode);
    Py_DECREF(pResult);

    // 从实例中获取clean函数,将调度内容清空，debug mode重新为false
    PyObject *clean = PyObject_GetAttrString(pInstance, "clean");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(clean != NULL);
    EXPECT_TRUE(PyCallable_Check(clean));
    // 调用函数
    PyObject *cleanResult = PyObject_CallObject(clean, NULL);
    Py_DECREF(clean);
    Py_DECREF(cleanResult);

    PyObject *getDebugMode = PyObject_GetAttrString(pInstance, "get_debug_mode");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(getDebugMode != NULL);
    EXPECT_TRUE(PyCallable_Check(getDebugMode));
    // 调用函数
    PyObject *debugMode = PyObject_CallObject(getDebugMode, NULL);
    EXPECT_EQ(debugMode, Py_False);
    Py_DECREF(getDebugMode);
    Py_DECREF(debugMode);
    Py_DECREF(pInstance);
}

TEST_F(ScheduleTest, TaskSchedule_Add_Task_And_Run_Fail)
{
    std::string className = "Schedule";
    auto scheduleClass = GetmoduleClass(className);
    EXPECT_TRUE(scheduleClass != NULL);
    EXPECT_TRUE(PyCallable_Check(scheduleClass));
    PyObject *pInstance = NULL;
    pInstance = PyObject_CallObject(scheduleClass, NULL);
    EXPECT_TRUE(pInstance != NULL);

    // 构造空task并添加到调度系统中
    PyObject* task = NULL;

    // 从实例中获取add_task函数
    PyObject *addTask = PyObject_GetAttrString(pInstance, "add_task");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(addTask != NULL);
    EXPECT_TRUE(PyCallable_Check(addTask));

    // 参数个数不对
    // 创建函数参数，将空值传入进去
    PyObject *pArgs0 = PyTuple_New(2);
    PyTuple_SetItem(pArgs0, 0, NULL);
    PyTuple_SetItem(pArgs0, 0, NULL);
    EXPECT_EQ(PyObject_CallObject(addTask, pArgs0), nullptr); PyErr_Clear();
    Py_DECREF(pArgs0);

    // 创建函数参数，将空值传入进去
    PyObject *pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, task);
    // 调用函数
    EXPECT_EQ(PyObject_CallObject(addTask, pArgs), nullptr); PyErr_Clear();
    Py_DECREF(pInstance);
    Py_DECREF(addTask);
    Py_DECREF(pArgs);
}

TEST_F(ScheduleTest, TaskSchedule_Add_Task_And_Run_Success)
{
    EXPECT_TRUE(TaskGenerator::instance()->IsAllPipesFinished());
    std::string className = "Schedule";
    auto scheduleClass = GetmoduleClass(className);
    EXPECT_TRUE(scheduleClass != NULL);
    EXPECT_TRUE(PyCallable_Check(scheduleClass));
    PyObject *pInstance = NULL;
    pInstance = PyObject_CallObject(scheduleClass, NULL);
    EXPECT_TRUE(pInstance != NULL);

    // 构造task并添加到调度系统中
    PyObject* task = PyInit_task();
    PyObject* taskB = PyInit_taskB();

    // 从实例中获取add_task函数
    PyObject *addTask = PyObject_GetAttrString(pInstance, "add_task");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(addTask != NULL);
    EXPECT_TRUE(PyCallable_Check(addTask));
    // 创建函数参数
    PyObject *pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, task);
    PyObject *pResult = PyObject_CallObject(addTask, pArgs);
    Py_DECREF(pArgs);
    // 创建函数参数
    PyObject *pArgs2 = PyTuple_New(1);
    PyTuple_SetItem(pArgs2, 0, taskB);
    PyObject *pResult2 = PyObject_CallObject(addTask, pArgs2);
    Py_DECREF(pArgs2);

    Py_DECREF(addTask);
    Py_DECREF(pResult);
    Py_DECREF(pResult2);
    EXPECT_FALSE(TaskGenerator::instance()->IsAllPipesFinished());

    // 启动调度器
    // 从实例中获取add_task函数
    PyObject *run = PyObject_GetAttrString(pInstance, "run");
    // 检查函数是否存在且可调用
    EXPECT_TRUE(run != NULL);
    EXPECT_TRUE(PyCallable_Check(run));
    // 调用函数
    PyObject *runResult = PyObject_CallObject(run, NULL);
    long ret = PyLong_AsLong(runResult);
    Py_DECREF(run);
    Py_DECREF(runResult);
    EXPECT_EQ(ret, 200);
    EXPECT_TRUE(TaskGenerator::instance()->IsAllPipesFinished());
}

TEST_F(ScheduleTest, Pipe_Line_Success)
{
    std::string pipe = "AIV0-PIPE-MTE2";
    Pipeline pipeline(pipe);
    auto res = pipeline.GetName();
    EXPECT_STREQ(pipe.c_str(), res.c_str());
    EXPECT_TRUE(pipeline.IsBlocked());
    pipeline.UpdateTime(258);
    EXPECT_EQ(pipeline.GetLastExecTime(), 258);
    res = pipeline.GetFirstTaskName();
    EXPECT_STREQ(res.c_str(), "");
}

TEST_F(ScheduleTest, RawTask_Init_Success)
{
    PyObject* task = PyInit_task();
    RawTask rawTask(task);
    auto res = rawTask.GetName();
    EXPECT_STREQ(res.c_str(), "");
    EXPECT_EQ(rawTask.Size(), 30);

}

TEST_F(ScheduleTest, Set_Debug_Mode_Fail)
{
    std::string className = "Schedule";
    PyObject *scheduleClass = GetmoduleClass(className);
    EXPECT_TRUE(scheduleClass != NULL);
    EXPECT_TRUE(PyCallable_Check(scheduleClass));
    PyObject *pInstance = NULL;
    pInstance = PyObject_CallObject(scheduleClass, NULL);
    EXPECT_TRUE(pInstance != NULL);

    PyObject *setDebugMode = PyObject_GetAttrString(pInstance, "set_debug_mode");
    EXPECT_TRUE(setDebugMode != NULL);
    EXPECT_TRUE(PyCallable_Check(setDebugMode));

    // 参数个数不对
    PyObject *pArgs0 = PyTuple_New(2);
    PyObject *dtype0 = PyLong_FromLong(2);  // dtype
    PyObject *dtype1 = PyLong_FromLong(2);  // dtype
    PyTuple_SetItem(pArgs0, 0, dtype0);
    PyTuple_SetItem(pArgs0, 0, dtype1);
    EXPECT_EQ(PyObject_CallObject(setDebugMode, pArgs0), nullptr); PyErr_Clear();
    Py_DECREF(pArgs0);

    // 参数类型不对
    PyObject *pArgs = PyTuple_New(1);
    PyObject *dtype = PyLong_FromLong(2);  // dtype
    PyTuple_SetItem(pArgs, 0, dtype);
    EXPECT_EQ(PyObject_CallObject(setDebugMode, pArgs), nullptr); PyErr_Clear();

    Py_DECREF(scheduleClass);
    Py_DECREF(pInstance);
    Py_DECREF(setDebugMode);
    Py_DECREF(pArgs);
}
