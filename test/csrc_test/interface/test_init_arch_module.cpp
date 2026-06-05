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
#include "arch/arch_info.h"

using namespace Mskpp;

class ArchModule : public testing::Test {
protected:
    PyObject *GetMethodList(const std::string &funcName)
    {
        PyObject *arch = InitArchInfoModule();
        PyObject *func = PyObject_GetAttrString(arch, funcName.c_str());
        return func;
    }

    static void SetUpTestSuite() {
        Py_Initialize();
    }

    static void TearDownTestSuite() {
        Py_Finalize();  // 关闭 Python 解释器
    }

};

TEST_F(ArchModule, Set_Chip_Success)
{
    std::string funcName = "get";
    PyObject *getFunc = GetMethodList(funcName);
    EXPECT_TRUE(getFunc != NULL);
    EXPECT_TRUE(PyCallable_Check(getFunc));

    // 调用get函数
    PyObject *getRes = PyObject_CallObject(getFunc, NULL);
    EXPECT_TRUE(getRes != NULL);
    const char *chipType = nullptr;
    Py_ssize_t len;
    chipType = PyUnicode_AsUTF8AndSize(getRes, &len);
    EXPECT_STREQ(chipType, "ascend910b3");

    // 调用set函数
    PyObject *pArgs = PyTuple_New(1);
    PyObject *chipName = PyUnicode_FromString("Ascend910b1");  // chip type
    PyTuple_SetItem(pArgs, 0, chipName);
    funcName = "set";
    PyObject *setFunc = GetMethodList(funcName);
    EXPECT_TRUE(setFunc != NULL);
    EXPECT_TRUE(PyCallable_Check(setFunc));
    PyObject_CallObject(setFunc, pArgs);

    PyObject *getResNew = PyObject_CallObject(getFunc, NULL);
    EXPECT_TRUE(getResNew != NULL);
    const char *chipTypeNew = nullptr;
    Py_ssize_t lenNew;
    chipTypeNew = PyUnicode_AsUTF8AndSize(getResNew, &lenNew);
    EXPECT_STREQ(chipTypeNew, "ascend910b1");

    Py_DECREF(getFunc);
    Py_DECREF(getRes);
    Py_DECREF(pArgs);
    Py_DECREF(setFunc);
    Py_DECREF(getResNew);
}

TEST_F(ArchModule, Set_Chip_Fail)
{
    // 调用set函数
    PyObject *pArgs = PyTuple_New(2);
    PyObject *chipName = PyUnicode_FromString("Ascend910b1");  // chip type
    PyObject *chipName2 = PyUnicode_FromString("Ascend910b2");  // chip type
    PyTuple_SetItem(pArgs, 0, chipName);
    PyTuple_SetItem(pArgs, 1, chipName2);
    std::string funcName = "set";
    PyObject *setFunc = GetMethodList(funcName);
    EXPECT_TRUE(setFunc != NULL);
    EXPECT_TRUE(PyCallable_Check(setFunc));
    EXPECT_EQ(PyObject_CallObject(setFunc, pArgs), nullptr); PyErr_Clear();

    PyObject *args = PyTuple_New(1);
    PyObject *chipName3 = PyLong_FromLong(123.123);  // chip type
    PyTuple_SetItem(args, 0, chipName3);
    EXPECT_EQ(PyObject_CallObject(setFunc, args), nullptr); PyErr_Clear();

    Py_DECREF(pArgs);
    Py_DECREF(setFunc);
}

TEST_F(ArchModule, Cal_Duration_Fail)
{
    std::string funcName = "cal_duration";
    PyObject *calDuration = GetMethodList(funcName);
    EXPECT_TRUE(calDuration != NULL);
    EXPECT_TRUE(PyCallable_Check(calDuration));

    // 调用cal_duration函数
    PyObject *pArgs = PyTuple_New(2);
    PyObject *cycle = PyLong_FromLong(256);  // cycle
    PyObject *cycle2 = PyLong_FromLong(256);  // cycle
    PyTuple_SetItem(pArgs, 0, cycle);
    PyTuple_SetItem(pArgs, 1, cycle2);
    PyObject *errArgs = PyObject_CallObject(calDuration, pArgs);
    EXPECT_EQ(errArgs, nullptr); PyErr_Clear();
    Py_DECREF(pArgs);
    Py_XDECREF(errArgs);

    // 调用cal_duration函数
    PyObject *pArgs2 = PyTuple_New(1);
    PyObject *cycle3 = PyUnicode_FromString("cycle");  // cycle
    PyTuple_SetItem(pArgs2, 0, cycle3);
    PyObject *errFormat = PyObject_CallObject(calDuration, pArgs2);
    EXPECT_EQ(errFormat, nullptr); PyErr_Clear();
    Py_XDECREF(errFormat);
    Py_DECREF(pArgs2);

    Py_DECREF(calDuration);
}

TEST_F(ArchModule, Cal_Duration_Success)
{
    std::string funcName = "cal_duration";
    PyObject *calDuration = GetMethodList(funcName);
    EXPECT_TRUE(calDuration != NULL);
    EXPECT_TRUE(PyCallable_Check(calDuration));

    // 调用cal_duration函数
    PyObject *pArgs = PyTuple_New(1);
    PyObject *cycle = PyLong_FromLong(256);  // cycle
    PyTuple_SetItem(pArgs, 0, cycle);

    PyObject *dur = PyObject_CallObject(calDuration, pArgs);
    EXPECT_TRUE(dur != NULL);
    auto res = PyFloat_AsDouble(dur);
    EXPECT_DOUBLE_EQ(res, 0.13837837837837838);

    // 调用cal_duration函数
    PyObject *pArgs2 = PyTuple_New(1);
    PyObject *cycle2 = PyFloat_FromDouble(128.256);  // cycle
    PyTuple_SetItem(pArgs2, 0, cycle2);

    PyObject *dur2 = PyObject_CallObject(calDuration, pArgs2);
    EXPECT_TRUE(dur2 != NULL);
    auto res2 = PyFloat_AsDouble(dur2);
    EXPECT_DOUBLE_EQ(res2, 0.069327567567567569);

    Py_DECREF(calDuration);
    Py_DECREF(pArgs);
    Py_DECREF(pArgs2);
    Py_DECREF(dur);
    Py_DECREF(dur2);
}

TEST_F(ArchModule, Mte_Is_Valid_Success)
{
    std::string funcName = "mte_is_valid";
    PyObject *mteIsValid = GetMethodList(funcName);
    EXPECT_TRUE(mteIsValid != NULL);
    EXPECT_TRUE(PyCallable_Check(mteIsValid));

    // 调用mte_is_valid函数
    PyObject *pArgs = PyTuple_New(2);
    PyObject *src = PyUnicode_FromString("GM");   // src
    PyObject *dst = PyUnicode_FromString("UB");   // dst
    PyTuple_SetItem(pArgs, 0, src);
    PyTuple_SetItem(pArgs, 1, dst);

    PyObject *valid = PyObject_CallObject(mteIsValid, pArgs);
    EXPECT_TRUE(valid != NULL);
    EXPECT_EQ(valid, Py_True);
    Py_DECREF(pArgs);
    Py_DECREF(valid);

    PyObject *pArgs1 = PyTuple_New(2);
    PyObject *src1 = PyUnicode_FromString("GM");   // src
    PyObject *dst1 = PyUnicode_FromString("GM");   // dst
    PyTuple_SetItem(pArgs1, 0, src1);
    PyTuple_SetItem(pArgs1, 1, dst1);

    PyObject *valid1 = PyObject_CallObject(mteIsValid, pArgs1);
    EXPECT_TRUE(valid1 != NULL);
    EXPECT_EQ(valid1, Py_False);
    Py_DECREF(pArgs1);
    Py_DECREF(valid1);

Py_DECREF(mteIsValid);

}

TEST_F(ArchModule, Mte_Is_Valid_Fail)
{
    std::string funcName = "mte_is_valid";
    PyObject *mteIsValid = GetMethodList(funcName);
    EXPECT_TRUE(mteIsValid != NULL);
    EXPECT_TRUE(PyCallable_Check(mteIsValid));

    // 调用mte_is_valid函数
    PyObject *pArgs = PyTuple_New(1);
    PyObject *src = PyUnicode_FromString("GM");   // src
    PyTuple_SetItem(pArgs, 0, src);
    EXPECT_EQ(PyObject_CallObject(mteIsValid, pArgs), nullptr); PyErr_Clear();

    PyObject *pArgs0 = PyTuple_New(2);
    PyObject *src0 = PyFloat_FromDouble(64.32);   // src
    PyObject *dst0 = PyFloat_FromDouble(128.1);   // dst
    PyTuple_SetItem(pArgs0, 0, src0);
    PyTuple_SetItem(pArgs0, 1, dst0);
    EXPECT_EQ(PyObject_CallObject(mteIsValid, pArgs0), nullptr); PyErr_Clear();

    Py_DECREF(mteIsValid);
    Py_DECREF(pArgs);
    Py_DECREF(pArgs0);
}

TEST_F(ArchModule, Set_Cache_Hit_Ratio_Success)
{
    std::string funcName = "get_cache_hit_ratio";
    PyObject *ratioFunc = GetMethodList(funcName);
    EXPECT_TRUE(ratioFunc != NULL);
    EXPECT_TRUE(PyCallable_Check(ratioFunc));

    // 调用get_cache_hit_ratio函数
    PyObject *ratioRes = PyObject_CallObject(ratioFunc, NULL);
    EXPECT_TRUE(ratioRes != NULL);
    EXPECT_DOUBLE_EQ(PyFloat_AsDouble(ratioRes), 2.1000000000000001);

    // 调用set_cache_hit_ratio函数
    PyObject *pArgs = PyTuple_New(1);
    PyObject *hitRatio = PyFloat_FromDouble(0.6);  // hit_ratio
    PyTuple_SetItem(pArgs, 0, hitRatio);
    funcName = "set_cache_hit_ratio";
    PyObject *setFunc = GetMethodList(funcName);
    EXPECT_TRUE(setFunc != NULL);
    EXPECT_TRUE(PyCallable_Check(setFunc));
    PyObject_CallObject(setFunc, pArgs);

    PyObject *getResNew = PyObject_CallObject(ratioFunc, NULL);
    EXPECT_TRUE(getResNew != NULL);
    EXPECT_DOUBLE_EQ(PyFloat_AsDouble(getResNew), 0.59999999999999998);

    // 调用set_cache_hit_ratio函数
    PyObject *pArgs2 = PyTuple_New(1);
    PyObject *hitRatio2 = PyLong_FromLong(1);  // hit_ratio
    PyTuple_SetItem(pArgs2, 0, hitRatio2);
    PyObject_CallObject(setFunc, pArgs2);

    PyObject *getResNew2 = PyObject_CallObject(ratioFunc, NULL);
    EXPECT_TRUE(getResNew2 != NULL);
    EXPECT_EQ(PyFloat_AsDouble(getResNew2), 1);

    Py_DECREF(ratioFunc);
    Py_DECREF(ratioRes);
    Py_DECREF(pArgs);
    Py_DECREF(setFunc);
    Py_DECREF(getResNew);
}

TEST_F(ArchModule, Set_Cache_Hit_Ratio_Fail)
{
    std::string funcName = "set_cache_hit_ratio";
    PyObject *setFunc = GetMethodList(funcName);
    EXPECT_TRUE(setFunc != NULL);
    EXPECT_TRUE(PyCallable_Check(setFunc));

    PyObject *pArgs0 = PyTuple_New(2);
    PyObject *ratio0 = PyFloat_FromDouble(0.1);
    PyObject *ratio1 = PyFloat_FromDouble(0.2);
    PyTuple_SetItem(pArgs0, 0, ratio0);
    PyTuple_SetItem(pArgs0, 1, ratio1);
    PyObject *twoArgs = PyObject_CallObject(setFunc, pArgs0);
    EXPECT_EQ(twoArgs, nullptr); PyErr_Clear();
    Py_DECREF(pArgs0);
    Py_XDECREF(twoArgs);

    PyObject *pArgs = PyTuple_New(1);
    PyObject *ratio = PyUnicode_FromString("GM");   // src
    PyTuple_SetItem(pArgs, 0, ratio);
    PyObject *errArgs = PyObject_CallObject(setFunc, pArgs);
    Py_DECREF(pArgs);
    EXPECT_EQ(errArgs, nullptr); PyErr_Clear();

    Py_DECREF(setFunc);
}

TEST_F(ArchModule, Get_Pipe_By_Io_Success)
{
    std::string funcName = "get_pipe_by_io";
    PyObject *getPipeByIo = GetMethodList(funcName);
    EXPECT_TRUE(getPipeByIo != NULL);
    EXPECT_TRUE(PyCallable_Check(getPipeByIo));

    // 调用get_pipe_by_io函数
    PyObject *pArgs = PyTuple_New(2);
    PyObject *src = PyUnicode_FromString("UB");   // src
    PyObject *dst = PyUnicode_FromString("L0C");   // dst
    PyTuple_SetItem(pArgs, 0, src);
    PyTuple_SetItem(pArgs, 1, dst);

    PyObject *pipe = PyObject_CallObject(getPipeByIo, pArgs);
    EXPECT_TRUE(pipe != NULL);
    Py_ssize_t len;
    const char *res = PyUnicode_AsUTF8AndSize(pipe, &len);
    EXPECT_STREQ(res, "PIPE-V");

    Py_DECREF(getPipeByIo);
    Py_DECREF(pArgs);
    Py_DECREF(pipe);
}

TEST_F(ArchModule, Get_Pipe_By_Io_Fail)
{
    std::string funcName = "get_pipe_by_io";
    PyObject *getPipeByIo = GetMethodList(funcName);
    EXPECT_TRUE(getPipeByIo != NULL);
    EXPECT_TRUE(PyCallable_Check(getPipeByIo));

    // 调用get_pipe_by_io函数，入参个数不对
    PyObject *pArgs0 = PyTuple_New(1);
    PyObject *src0 = PyLong_FromLong(1);   // src
    PyTuple_SetItem(pArgs0, 0, src0);
    PyObject *errArgs = PyObject_CallObject(getPipeByIo, pArgs0);
    EXPECT_EQ(errArgs, nullptr); PyErr_Clear();
    Py_XDECREF(errArgs);
    Py_DECREF(pArgs0);

    // 调用get_pipe_by_io函数，入参类型不对
    PyObject *pArgs2 = PyTuple_New(2);
    PyObject *src2 = PyLong_FromLong(2);   // src
    PyObject *dst2 = PyLong_FromLong(3);   // dst
    PyTuple_SetItem(pArgs2, 0, src2);
    PyTuple_SetItem(pArgs2, 1, dst2);
    PyObject *falseArgs = PyObject_CallObject(getPipeByIo, pArgs2);
    EXPECT_EQ(falseArgs, nullptr); PyErr_Clear();
    Py_DECREF(pArgs2);
    Py_XDECREF(falseArgs);

    Py_DECREF(getPipeByIo);
}

TEST_F(ArchModule, Get_Size_Of_Success)
{
    std::string funcName = "get_size_of";
    PyObject *getSizeOf = GetMethodList(funcName);
    EXPECT_TRUE(getSizeOf != NULL);
    EXPECT_TRUE(PyCallable_Check(getSizeOf));

    // 调用cal_duration函数
    PyObject *pArgs = PyTuple_New(1);
    PyObject *dtype = PyUnicode_FromString("FP16");  // dtype
    PyTuple_SetItem(pArgs, 0, dtype);

    PyObject *size = PyObject_CallObject(getSizeOf, pArgs);
    EXPECT_TRUE(size != NULL);
    EXPECT_DOUBLE_EQ(PyLong_AsLong(size), 2);

    Py_DECREF(getSizeOf);
    Py_DECREF(pArgs);
    Py_DECREF(size);
}

TEST_F(ArchModule, Get_Size_Of_Fail)
{
    std::string funcName = "get_size_of";
    PyObject *getSizeOf = GetMethodList(funcName);
    EXPECT_TRUE(getSizeOf != NULL);
    EXPECT_TRUE(PyCallable_Check(getSizeOf));

    // 参数个数不对
    PyObject *pArgs0 = PyTuple_New(2);
    PyObject *dtype0 = PyLong_FromLong(2);  // dtype
    PyObject *dtype1 = PyLong_FromLong(2);  // dtype
    PyTuple_SetItem(pArgs0, 0, dtype0);
    PyTuple_SetItem(pArgs0, 1, dtype1);
    EXPECT_EQ(PyObject_CallObject(getSizeOf, pArgs0), nullptr); PyErr_Clear();
    Py_DECREF(pArgs0);

    // 参数类型不对
    PyObject *pArgs = PyTuple_New(1);
    PyObject *dtype = PyLong_FromLong(2);  // dtype
    PyTuple_SetItem(pArgs, 0, dtype);
    EXPECT_EQ(PyObject_CallObject(getSizeOf, pArgs), nullptr); PyErr_Clear();

    // 参数为空
    PyObject *pArgs2 = PyTuple_New(1);
    PyObject *dtype2 = PyUnicode_FromString("");  // dtype
    PyTuple_SetItem(pArgs2, 0, dtype2);
    EXPECT_EQ(PyObject_CallObject(getSizeOf, pArgs2), nullptr); PyErr_Clear();

    // 参数不对
    PyObject *pArgs3 = PyTuple_New(1);
    PyObject *dtype3 = PyUnicode_FromString("dtype");  // dtype
    PyTuple_SetItem(pArgs3, 0, dtype3);
    EXPECT_EQ(PyObject_CallObject(getSizeOf, pArgs3), nullptr); PyErr_Clear();

    Py_DECREF(getSizeOf);
    Py_DECREF(pArgs);
    Py_DECREF(pArgs2);
    Py_DECREF(pArgs3);
}
