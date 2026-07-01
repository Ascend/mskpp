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
import pathlib
import json
import numpy as np

from mskpp.utils import logger, safe_check


def check_autotune_params(configs, warmup, repeat, device_ids):
    check_configs(configs)
    check_warmup(warmup)
    check_repeat(repeat)
    check_device_ids(device_ids)


def check_autotune_v2_params(configs, warmup_times):
    check_configs(configs)
    check_warmup_times(warmup_times)


def check_configs(configs):
    if not configs or not isinstance(configs, list):
        raise ValueError('The autotune configs is not a valid list.')
    for config in configs:
        if not isinstance(config, dict):
            raise ValueError(f'The config {config} is not a valid dict.')
        for key, val in config.items():
            if not key or not isinstance(key, str):
                raise ValueError(f'The key {key} is not a valid str.')
            if not val or not isinstance(val, str):
                raise ValueError(f'The val {val} is not a valid str.')


def check_warmup(warmup):
    if not isinstance(warmup, int) or warmup <= 0:
        raise ValueError('The warmup value is not a valid positive integer.')
    if warmup < 300:
        logger.warning(
            'The device requires 300μs to reach full frequency, but the warmup value you provided is less than 300μs.'
        )
    if warmup > 10**5:
        raise ValueError(f'The warmup value {warmup} is too large.')


def check_repeat(repeat):
    if not isinstance(repeat, int) or repeat <= 0:
        raise ValueError('The repeat value is not a valid positive integer.')
    if repeat > 10**4:
        raise ValueError(f'The warmup value {repeat} is too large.')


def check_warmup_times(warmup_times):
    if not isinstance(warmup_times, int) or warmup_times < 0:
        raise ValueError('The warmup_times value is not a valid non-negative integer.')
    if warmup_times > 500:
        raise ValueError(f'The warmup value {warmup_times} is too large.')


def check_device_ids(device_ids):
    if not isinstance(device_ids, list):
        raise ValueError(f'The device_ids: {device_ids} is not a list.')
    if not device_ids:
        raise ValueError('The device id list is empty.')
    if len(device_ids) > 10**2:
        raise ValueError('The device id list is too large.')
    for device_id in device_ids:
        if not isinstance(device_id, int) or device_id < 0:
            raise ValueError(f'The device id {device_id} is not valid.')
    if len(device_ids) > 1:
        logger.warning(
            'Multi-device parallel execution is not yet supported. '
            'Only the first device id in the device id list will be used currently.'
        )


def get_file_lines(file):
    if not file or not os.path.isfile(file):
        raise OSError(f'The kernel file {file} is not valid.')
    safe_check.check_input_file(file)
    with open(file, 'r', encoding='utf-8') as file_handler:
        lines = file_handler.readlines()
    return lines


def find_executable_custom(executable_name, additional_paths=None):
    """
    查找可执行文件，支持自定义搜索路径。
    :param executable_name: 可执行文件名（如 "python"）
    :param additional_paths: 额外搜索路径列表（可选）
    :return: 可执行文件的完整路径或 None
    """
    # 获取系统 PATH 环境变量
    paths = os.environ.get("PATH", "").split(os.pathsep)

    # 添加额外路径
    if additional_paths:
        paths = additional_paths + paths

    for path in paths:
        full_path = pathlib.Path(path) / executable_name
        if full_path.is_file() and os.access(full_path, os.X_OK):
            return str(full_path.resolve())

    return None


def is_torch_tensor_instance(obj):
    return (
        hasattr(obj, "__class__")
        and obj.__class__.__name__ == "Tensor"
        and obj.__class__.__module__.startswith("torch")
    )


def is_torch_or_numpy_tensor(obj):
    return is_torch_tensor_instance(obj) or isinstance(obj, np.ndarray)


def is_tensor_empty(obj):
    # torch Tensor
    if hasattr(obj, 'numel'):
        return obj.numel() == 0
    # numpy ndarray
    return obj.size == 0


# 调用方保证传入tensor合法性
def canonical_tensor(t, to_cpu: bool = True):
    if is_torch_tensor_instance(t):
        if t.device.type == 'npu' and to_cpu:
            t = t.cpu()
        if not t.is_contiguous():
            t = t.contiguous()
        return t
    # numpy.ndarray
    if not t.flags.contiguous:
        t = np.ascontiguousarray(t)
    return t


# lst is a positive integer list
def safe_prod(lst: list, limit=4294967295):
    res = 1
    for i in lst:
        res *= i
        if res > limit:
            return 0
    return res


class ChainHandler:
    def __init__(self, lst: list):
        self.chain = lst

    def run(self, *args, **kwargs) -> bool:
        handled = False
        for callee in self.chain:
            if callee(*args, **kwargs):
                handled = True
                break
        return handled

    def append(self, callee):
        self.chain.append(callee)


def pad_list_slice(lst: list, length: int, fill_value=None) -> list:
    if len(lst) >= length:
        return lst.copy()

    # 创建目标长度列表并用 None 填充
    padded = [fill_value] * length
    # 将原始列表值复制到新列表
    padded[: len(lst)] = lst
    return padded


def load_json(path: str):
    if not path or not isinstance(path, str):
        return False, ValueError(f'File {path} does not exist or is not a string.')
    if not os.path.isfile(path):
        return False, OSError(f'File {path} is not a file.')
    try:
        safe_check.check_input_file(path)
        with open(path, 'r', encoding='utf-8') as f:
            loaded_data = json.load(f)
        return True, loaded_data
    except json.JSONDecodeError as ex:
        return False, ex
    except Exception as ex:
        return False, ex
