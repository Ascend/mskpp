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

import os
from ..core.metric.file_system import FileChecker


def get_cann_path() -> str:
    cann_path = os.getenv('ASCEND_HOME_PATH')
    if cann_path is None or not os.path.isdir(cann_path):
        raise ValueError('ASCEND_HOME_PATH is invalid, please check your environment variables')
    real_path = os.path.realpath(cann_path)
    if not FileChecker(real_path, "dir").check_input_file():
        raise PermissionError(f"Check cann path: {cann_path} permission failed")
    return real_path


def check_runtime_impl():
    cann_path = get_cann_path()
    so_path = os.path.join(cann_path, "lib64/libruntime.so")
    if not os.path.exists(so_path):
        return False
    import ctypes

    runtime_lib = ctypes.CDLL(so_path, mode=ctypes.RTLD_LOCAL)
    if hasattr(runtime_lib, "rtKernelLaunchWithHandleV2") and callable(
        getattr(runtime_lib, "rtKernelLaunchWithHandleV2")
    ):
        return True
    return False
