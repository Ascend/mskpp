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
#include "init_module.h"
#include "../prof_data/data_model_define.h"

namespace Mskpp {
PyDoc_STRVAR(MSKPP_PROFDATA_METHOD_GET_DOC, "Get estimated data for instructions.");

#define PYTHON_FUNC_DEFINE_END {nullptr, nullptr, 0, nullptr}

#define PROFDATA_METHOD_GET_DEFINE(func) \
    {"get", static_cast<PyCFunction>(func), METH_VARARGS, MSKPP_PROFDATA_METHOD_GET_DOC},

/**
 * init_profdata_module.cpp中提供了大量的python接口，将各个指令所具有的方法作为一个类对外提供
 * 由于指令的性能数据处理函数存在大量重复，这里根据指令类型和入参不同，定义了三种宏
 * MOV_DATA_REGISTER用于定义mov类指令调用Get方法的封装函数宏，没有入参，Get方法三个入参
 * MMAD_DATA_REGISTER用于定义mmad类指令调用Get方法的封装函数宏，没有入参，Get方法两个入参
 * VEC_DATA_REGISTER用于定义vector类指令调用Get方法的封装函数宏，一个入参，Get方法两个入参
 * 其余类似GetPeak和GetConv函数，虽有部分重复代码，但仅封装一次，暂不使用宏进行封装
 * **/

#define MOV_DATA_REGISTER(instrName) \
    static PyObject *MSKPP_PROFDATA_##instrName##Register(PyObject *self, PyObject *pstArgs) { \
        const char *src = nullptr; \
        const char *dst = nullptr; \
        long dataSize; \
        int transEnable; \
        /* 这里需要使用long接收dataSize */ \
        if (!PyArg_ParseTuple(pstArgs, "ssli", &src, &dst, &dataSize, &transEnable)) { \
            return NULL; \
        } \
        auto instrName##Instr = MovFactory::instance()->Create(#instrName); \
        if (instrName##Instr == nullptr) { \
            return NULL; \
        } \
        return PyFloat_FromDouble( \
            instrName##Instr->Get(std::string(src), std::string(dst), dataSize, (bool)transEnable)); \
    }

#define MMAD_DATA_REGISTER(instrName) \
    static PyObject *MSKPP_PROFDATA_##instrName##Register(PyObject *self, PyObject *pstArgs) { \
        long granularity; \
        const char *instrType = nullptr; \
        if (!PyArg_ParseTuple(pstArgs, "ls", &granularity, &instrType)) { \
            return NULL; \
        } \
        auto instrName##Instr = MmadFactory::instance()->Create(#instrName); \
        if (instrName##Instr == nullptr) { \
            return NULL; \
        } \
        return PyFloat_FromDouble(instrName##Instr->Get(granularity, std::string(instrType))); \
    }

#define VEC_DATA_REGISTER(instrName) \
    static PyObject *MSKPP_PROFDATA_##instrName##Register(PyObject *self, PyObject *pstArgs) { \
        long granularity; \
        const char *instrType = nullptr; \
        if (!PyArg_ParseTuple(pstArgs, "ls", &granularity, &instrType)) { \
            return NULL; \
        } \
        auto instrName##Instr = VecFactory::instance()->Create(#instrName, #instrName); \
        if (instrName##Instr == nullptr) { \
            return NULL; \
        } \
        return PyFloat_FromDouble(instrName##Instr->Get(granularity, std::string(instrType))); \
    }

// 调用指令方法
static PyObject *MSKPP_PROFDATA_MovDataGetPeak(PyObject *self, PyObject *pstArgs) {
    const char *src = nullptr;
    const char *dst = nullptr;
    if (!PyArg_ParseTuple(pstArgs, "ss", &src, &dst)) {
        PyErr_SetString(PyExc_ValueError, "Invalid Input.");
        return NULL;
    }
    if (src == nullptr || dst == nullptr) {
        PyErr_SetString(PyExc_ValueError, "src/dst cannot be None.");
        return NULL;
    }
    if (std::string(src).empty() || std::string(dst).empty()) {
        PyErr_SetString(PyExc_ValueError, "src/dst cannot be empty strings");
        return NULL;
    }
    auto movInstr = MovFactory::instance()->Create("MOV");
    if (!movInstr) {
        Py_RETURN_NONE;
    }
    return PyFloat_FromDouble(movInstr->GetPeak(std::string(src), std::string(dst)));
}

static PyObject *MSKPP_PROFDATA_MovDataGetRepeat(PyObject *self, PyObject *pstArgs) {
    const char *src = nullptr;
    const char *dst = nullptr;
    uint32_t repeat;
    if (!PyArg_ParseTuple(pstArgs, "ssi", &src, &dst, &repeat)) {
        PyErr_SetString(PyExc_ValueError, "Invalid Input.");
        return NULL;
    }
    if (src == nullptr || dst == nullptr) {
        PyErr_SetString(PyExc_ValueError, "src/dst cannot be None.");
        return NULL;
    }
    if (std::string(src).empty() || std::string(dst).empty()) {
        PyErr_SetString(PyExc_ValueError, "src/dst cannot be empty strings");
        return NULL;
    }
    auto movInstr = MovFactory::instance()->Create("MOV");
    if (!movInstr) {
        Py_RETURN_NONE;
    }
    return PyFloat_FromDouble(movInstr->GetRepeat(std::string(src), std::string(dst), repeat));
}

MMAD_DATA_REGISTER(MMAD)
MOV_DATA_REGISTER(MOV)
VEC_DATA_REGISTER(VABS)
VEC_DATA_REGISTER(VADD)
VEC_DATA_REGISTER(VADDRELU)
VEC_DATA_REGISTER(VADDRELUCONV)
VEC_DATA_REGISTER(VADDS)
VEC_DATA_REGISTER(VAND)
VEC_DATA_REGISTER(VAXPY)
VEC_DATA_REGISTER(VBRCB)
VEC_DATA_REGISTER(VCADD)
VEC_DATA_REGISTER(VCGADD)
VEC_DATA_REGISTER(VCGMAX)
VEC_DATA_REGISTER(VCGMIN)
VEC_DATA_REGISTER(VCMAX)
VEC_DATA_REGISTER(VCMIN)
VEC_DATA_REGISTER(VCMP)
VEC_DATA_REGISTER(VCMPV)
VEC_DATA_REGISTER(VCMPVS)
VEC_DATA_REGISTER(VCOPY)
VEC_DATA_REGISTER(VCONV)
VEC_DATA_REGISTER(VCONVDEQ)
VEC_DATA_REGISTER(VCONVVDEQ)
VEC_DATA_REGISTER(VCPADD)
VEC_DATA_REGISTER(VDIV)
VEC_DATA_REGISTER(VECTORDUP)
VEC_DATA_REGISTER(VEXP)
VEC_DATA_REGISTER(VLN)
VEC_DATA_REGISTER(VLRELU)
VEC_DATA_REGISTER(VMADD)
VEC_DATA_REGISTER(VMAX)
VEC_DATA_REGISTER(VMAXS)
VEC_DATA_REGISTER(VMIN)
VEC_DATA_REGISTER(VMINS)
VEC_DATA_REGISTER(VMRGSORT)
VEC_DATA_REGISTER(VMUL)
VEC_DATA_REGISTER(VMULS)
VEC_DATA_REGISTER(VNOT)
VEC_DATA_REGISTER(VOR)
VEC_DATA_REGISTER(VRELU)
VEC_DATA_REGISTER(VREC)
VEC_DATA_REGISTER(VSUB)
VEC_DATA_REGISTER(VRSQRT)
VEC_DATA_REGISTER(VSEL)
VEC_DATA_REGISTER(VSHL)
VEC_DATA_REGISTER(VSHR)
VEC_DATA_REGISTER(VSQRT)
VEC_DATA_REGISTER(VSUBRELUCONV)
VEC_DATA_REGISTER(VSUBRELU)
VEC_DATA_REGISTER(VMADDRELU)
VEC_DATA_REGISTER(VMLA)
VEC_DATA_REGISTER(VREDUCEV2)
VEC_DATA_REGISTER(VREDUCE)
VEC_DATA_REGISTER(VMULCONV)
VEC_DATA_REGISTER(VGATHER)
VEC_DATA_REGISTER(VGATHERB)

// 将指令方法放入python对象方法列表
static PyMethodDef g_mmadDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_MMADRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_movDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_MOVRegister){
        "get_peak", static_cast<PyCFunction>(MSKPP_PROFDATA_MovDataGetPeak), METH_VARARGS, nullptr},
    {"get_repeat", static_cast<PyCFunction>(MSKPP_PROFDATA_MovDataGetRepeat), METH_VARARGS, nullptr},
    PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vconvDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCONVRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vabsDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VABSRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vaddDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VADDRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vaddreluDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VADDRELURegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vaddreluconvDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VADDRELUCONVRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vaddsDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VADDSRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vandDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VANDRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vaxpyDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VAXPYRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vbrcbDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VBRCBRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcaddDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCADDRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcgaddDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCGADDRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcgmaxDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCGMAXRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcgminDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCGMINRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcmaxDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCMAXRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcminDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCMINRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcmpDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCMPRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcmpvDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCMPVRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcmpvsDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCMPVSRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vconvdeqDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCONVDEQRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vconvvdeqDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCONVVDEQRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcopyDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCOPYRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vcpaddDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VCPADDRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vdivDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VDIVRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vectorDupDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VECTORDUPRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vexpDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VEXPRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vlnDataMethods[] = {PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VLNRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vlreluDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VLRELURegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmaddDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMADDRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmaxDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMAXRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmaxsDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMAXSRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vminDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMINRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vminsDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMINSRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmrgsortDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMRGSORTRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmulDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMULRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmulsDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMULSRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vnotDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VNOTRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vorDataMethods[] = {PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VORRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vreluDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VRELURegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vrecDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VRECRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vsubDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VSUBRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vrsqrtDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VRSQRTRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vselDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VSELRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vshlDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VSHLRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vshrDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VSHRRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vsqrtDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VSQRTRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vsubReluConvDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VSUBRELUCONVRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vsubReluDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VSUBRELURegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmaddReluDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMADDRELURegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmlaDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMLARegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vreducev2DataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VREDUCEV2Register) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vreduceDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VREDUCERegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vmulconvDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VMULCONVRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vgatherDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VGATHERRegister) PYTHON_FUNC_DEFINE_END};
static PyMethodDef g_vgatherbDataMethods[] = {
    PROFDATA_METHOD_GET_DEFINE(MSKPP_PROFDATA_VGATHERBRegister) PYTHON_FUNC_DEFINE_END};

// 将python对象方法列表按顺初始化为python类
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataMmadData, "MmadData", g_mmadDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataMovData, "MovData", g_movDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVconvData, "VconvData", g_vconvDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVabsData, "vabs", g_vabsDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVaddData, "vadd", g_vaddDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVaddreluData, "vaddrelu", g_vaddreluDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVaddreluconvData, "vaddreluconv", g_vaddreluconvDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVaddsData, "vadds", g_vaddsDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVandData, "vand", g_vandDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVaxpyData, "vaxpy", g_vaxpyDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVbrcbData, "vbrcb", g_vbrcbDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcaddData, "vcadd", g_vcaddDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcgaddData, "vcgadd", g_vcgaddDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcgmaxData, "vcgmax", g_vcgmaxDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcgminData, "vcgmin", g_vcgminDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcmaxData, "vcmax", g_vcmaxDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcminData, "vcmin", g_vcminDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcmpData, "vcmp", g_vcmpDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcmpvData, "vcmpv", g_vcmpvDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcmpvsData, "vcmpvs", g_vcmpvsDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVconvdeqData, "vconvdeq", g_vconvdeqDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVconvvdeqData, "vconvvdeq", g_vconvvdeqDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcopyData, "vcopy", g_vcopyDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVcpaddData, "vcpadd", g_vcpaddDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVdivData, "vdiv", g_vdivDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVectorDupData, "vectorDup", g_vectorDupDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVexpData, "vexp", g_vexpDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVlnData, "vln", g_vlnDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVlreluData, "vlrelu", g_vlreluDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmaddData, "vmadd", g_vmaddDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmaxData, "vmax", g_vmaxDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmaxsData, "vmaxs", g_vmaxsDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVminData, "vmin", g_vminDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVminsData, "vmins", g_vminsDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmrgsortData, "vmrgsort", g_vmrgsortDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmulData, "vmul", g_vmulDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmulsData, "vmuls", g_vmulsDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVnotData, "vnot", g_vnotDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVorData, "vor", g_vorDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVreluData, "vrelu", g_vreluDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVrecData, "vrec", g_vrecDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVsubData, "vsub", g_vsubDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVrsqrtData, "vrsqrt", g_vrsqrtDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVselData, "vsel", g_vselDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVshlData, "vshl", g_vshlDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVshrData, "vshr", g_vshrDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVsqrtData, "vsqrt", g_vsqrtDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVsubReluConvData, "vsubreluconv", g_vsubReluConvDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVsubReluData, "vsubrelu", g_vsubReluDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmaddReluData, "vmaddrelu", g_vmaddReluDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmlaData, "vmla", g_vmlaDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVreducev2Data, "vreducev2", g_vreducev2DataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVreduceData, "vreduce", g_vreduceDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVmulconvData, "vmulconv", g_vmulconvDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVgatherData, "vgather", g_vgatherDataMethods, nullptr);
MSKPP_DEFINE_CLASS_NOMEMBER(g_mskppProfdataVgatherbData, "vgatherb", g_vgatherbDataMethods, nullptr);

// 指令的性能数据处理python类列表
static std::map<std::string, PyTypeObject *> ProfDataClassList = {
    {"MmadData", &g_mskppProfdataMmadData},
    {"MovData", &g_mskppProfdataMovData},
    {"VconvData", &g_mskppProfdataVconvData},
    {"VabsData", &g_mskppProfdataVabsData},
    {"VaddData", &g_mskppProfdataVaddData},
    {"VaddreluData", &g_mskppProfdataVaddreluData},
    {"VaddreluconvData", &g_mskppProfdataVaddreluconvData},
    {"VandData", &g_mskppProfdataVandData},
    {"VaxpyData", &g_mskppProfdataVaxpyData},
    {"VaddsData", &g_mskppProfdataVaddsData},
    {"VbrcbData", &g_mskppProfdataVbrcbData},
    {"VcaddData", &g_mskppProfdataVcaddData},
    {"VcgaddData", &g_mskppProfdataVcgaddData},
    {"VcgmaxData", &g_mskppProfdataVcgmaxData},
    {"VcgminData", &g_mskppProfdataVcgminData},
    {"VcmaxData", &g_mskppProfdataVcmaxData},
    {"VcminData", &g_mskppProfdataVcminData},
    {"VcmpData", &g_mskppProfdataVcmpData},
    {"VcmpvData", &g_mskppProfdataVcmpvData},
    {"VcmpvsData", &g_mskppProfdataVcmpvsData},
    {"VconvdeqData", &g_mskppProfdataVconvdeqData},
    {"VconvvdeqData", &g_mskppProfdataVconvvdeqData},
    {"VcopyData", &g_mskppProfdataVcopyData},
    {"VcpaddData", &g_mskppProfdataVcpaddData},
    {"VdivData", &g_mskppProfdataVdivData},
    {"VectorDupData", &g_mskppProfdataVectorDupData},
    {"VexpData", &g_mskppProfdataVexpData},
    {"VlnData", &g_mskppProfdataVlnData},
    {"VlreluData", &g_mskppProfdataVlreluData},
    {"VmaddData", &g_mskppProfdataVmaddData},
    {"VmaxData", &g_mskppProfdataVmaxData},
    {"VmaxsData", &g_mskppProfdataVmaxsData},
    {"VminData", &g_mskppProfdataVminData},
    {"VminsData", &g_mskppProfdataVminsData},
    {"VmrgsortData", &g_mskppProfdataVmrgsortData},
    {"VmulData", &g_mskppProfdataVmulData},
    {"VmulsData", &g_mskppProfdataVmulsData},
    {"VnotData", &g_mskppProfdataVnotData},
    {"VorData", &g_mskppProfdataVorData},
    {"VreluData", &g_mskppProfdataVreluData},
    {"VrecData", &g_mskppProfdataVrecData},
    {"VsubData", &g_mskppProfdataVsubData},
    {"VrsqrtData", &g_mskppProfdataVrsqrtData},
    {"VselData", &g_mskppProfdataVselData},
    {"VshlData", &g_mskppProfdataVshlData},
    {"VshrData", &g_mskppProfdataVshrData},
    {"VsqrtData", &g_mskppProfdataVsqrtData},
    {"VsubReluConvData", &g_mskppProfdataVsubReluConvData},
    {"VsubReluData", &g_mskppProfdataVsubReluData},
    {"VmaddReluData", &g_mskppProfdataVmaddReluData},
    {"VmlaData", &g_mskppProfdataVmlaData},
    {"Vreducev2Data", &g_mskppProfdataVreducev2Data},
    {"VreduceData", &g_mskppProfdataVreduceData},
    {"VmulconvData", &g_mskppProfdataVmulconvData},
    {"VgatherData", &g_mskppProfdataVgatherData},
    {"VgatherbData", &g_mskppProfdataVgatherbData},
};

static struct PyModuleDef g_mskppProfDataModuleDef = {
    PyModuleDef_HEAD_INIT, "mskpp._C.prof_data", /* m_name */
    nullptr, /* m_doc */
    -1, /* m_size */
    nullptr, /* m_methods */
};

PyObject *InitProfdataModule() {
    PyObject *m = nullptr;
    m = PyModule_Create(&g_mskppProfDataModuleDef);
    if (m == nullptr) {
        return nullptr;
    }

    for (auto &it : ProfDataClassList) {
        if (PyType_Ready(it.second) < 0) {
            PyErr_Format(PyExc_SystemError, "Failed to init class %s.", it.first.c_str());
            goto error;
        }
        if (PyModule_AddObject(m, it.first.c_str(), (PyObject *)it.second) < 0) {
            PyErr_Format(PyExc_SystemError, "Failed to bind class %s.", it.first.c_str());
            goto error;
        }
    }
    return m;

error:
    Py_XDECREF(m);
    return nullptr;
}
}
