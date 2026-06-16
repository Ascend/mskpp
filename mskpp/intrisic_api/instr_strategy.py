#!/usr/bin/python
# -*- coding: UTF-8 -*-
# -------------------------------------------------------------------------
# This file is part of the MindStudio project.
# Copyright (c) 2025 Huawei Technologies Co.,Ltd.
#
# MindStudio is licensed under Mulan PSL v2.
# You can use this software according to the terms and conditions of the Mulan PSL v2.
# You may obtain a copy of Mulan PSL v2 at:
#
#          http://license.coscl.org.cn/MulanPSL2
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PSL v2 for more details.
# -------------------------------------------------------------------------

from abc import ABC, abstractmethod
from ..core import Tensor
from ..core.common.checker import InstrInitParaCheck


def execute_func_by_instr_name(func_map, key):
    for instr_list in func_map:
        for name in instr_list:
            if key != name:
                continue
            func, *args = func_map[instr_list]
            func(*args)
            return


class InstrInitBase(ABC):  # 指令初始化策略接口，定义了指令在初始化时应该实现的策略方法
    @abstractmethod
    def instr_init(self, x, y, instr_obj, **kwargs):
        pass


class MmadInit(InstrInitBase):
    def instr_init(self, x, y, instr_obj, **kwargs):
        InstrInitParaCheck.check_type(kwargs, "is_inited", "bool")
        out = Tensor("L0C")
        InstrInitParaCheck.check_args_key(["b"], kwargs)
        if kwargs["is_inited"]:
            kwargs["b"].set_valid()
        instr_obj.inputs = (x, y, kwargs["b"])
        instr_obj.outputs = (out,)
        instr_obj.instr_type = "mmad"


class VecUnaryInit(InstrInitBase):
    def instr_init(self, x, y, instr_obj, **kwargs):
        instr_obj.inputs = (x,)
        instr_obj.outputs = (y,)


class VecBinaryInit(InstrInitBase):
    def instr_init(self, x, y, instr_obj, **kwargs):
        InstrInitParaCheck.check_args_key(["z"], kwargs)
        instr_obj.inputs = (x, y)
        instr_obj.outputs = (kwargs["z"],)


class VecBinaryInitV2(InstrInitBase):
    def instr_init(self, x, y, instr_obj, **kwargs):
        InstrInitParaCheck.check_args_key(["z"], kwargs)
        instr_obj.inputs = (x,)
        instr_obj.outputs = (kwargs["z"],)


class VecBinaryInitV2ByAttr(InstrInitBase):
    def instr_init(self, x, y, instr_obj, **kwargs):
        InstrInitParaCheck.check_args_key(["instr_name", "z"], kwargs)
        instr_obj.inputs = (x,)
        instr_obj.outputs = (kwargs["z"],)
        if kwargs["instr_name"] in ["VREDUCE", "VREDUCEV2"]:
            InstrInitParaCheck.check_type(kwargs, "reserve_num", "int")
        elif kwargs["instr_name"] in ["VAXPY"]:
            InstrInitParaCheck.check_type(kwargs, "if_mix", "bool")


class VecBinaryInitByAttr(InstrInitBase):
    def instr_init(self, x, y, instr_obj, **kwargs):
        InstrInitParaCheck.check_args_key(["z", "instr_name"], kwargs)
        instr_obj.inputs = (x, y)
        instr_obj.outputs = (kwargs["z"],)
        if kwargs["instr_name"] in ["VMLA"]:
            InstrInitParaCheck.check_type(kwargs, "if_mix", "bool")
        elif kwargs["instr_name"] in ["VMULCONV"]:
            InstrInitParaCheck.check_dtype_valid(kwargs, "dtype")


class VecUnaryInitByAttr(InstrInitBase):
    def instr_init(self, x, y, instr_obj, **kwargs):
        InstrInitParaCheck.check_args_key(["instr_name"], kwargs)
        instr_obj.inputs = (x,)
        instr_obj.outputs = (y,)
        instr_check_func = {
            ("VECTORDUP",): (InstrInitParaCheck.check_shape_valid, kwargs, "fill_shape"),
            ("VBRCB",): (InstrInitParaCheck.check_type, kwargs, "broadcast_num", "int"),
            ("VCONV",): (InstrInitParaCheck.check_dtype_valid, kwargs, "dtype"),
            ("VCONVDEQ", "VCONVVDEQ"): (InstrInitParaCheck.check_tensor_is_complete, x),
            ("VCADD", "VCGADD", "VCGMAX", "VCGMIN", "VCMAX", "VCMIN", "VCPADD"): (
                InstrInitParaCheck.check_type,
                kwargs,
                "reduce_num",
                "int",
            ),
        }
        execute_func_by_instr_name(instr_check_func, kwargs["instr_name"])


class InstrInitHandle:
    def __init__(self, init_strategy):
        self.init_strategy = init_strategy

    def set_instr_strategy(self, init_strategy):
        self.init_strategy = init_strategy

    def instr_init(self, x, y, instr_obj, **kwargs):
        return self.init_strategy.instr_init(x, y, instr_obj, **kwargs)
