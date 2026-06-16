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
import stat
from mskpp.utils import logger

MAX_FILE_SIZE = 10 * 1024**2
MAX_LIB_SIZE = 10 * 1024**3
SAVE_DATA_FILE_AUTHORITY = stat.S_IWUSR | stat.S_IRUSR
DATA_DIRECTORY_AUTHORITY = 0o750
OPEN_FLAGS = os.O_WRONLY | os.O_CREAT


def check_input_file(path, threshold=MAX_FILE_SIZE):
    if not os.path.isfile(path):
        raise OSError(f'{path} is not a valid file path.')
    path = os.path.abspath(path)
    if os.path.islink(path):
        logger.warning(f'The path {path} is insecure because is a soft link.')
    if not os.access(path, os.R_OK):
        raise PermissionError(f'Path {path} is not readable.')
    if os.path.getsize(path) >= threshold:
        logger.warning(f'The file {path} is too large.')
    if not check_path_owner_consistent(path):
        logger.warning(f'The file {path} is insecure because it does not belong to you.')
    check_group_others_w_permission(path)


def check_path_owner_consistent(path):
    # st_uid:user ID of owner, os.getuid: Return the current process's user id, root's uid is 0
    uid = os.stat(path).st_uid
    return uid == os.getuid() or uid == 0


def check_group_others_w_permission(path):
    mode = os.stat(path).st_mode
    if mode & stat.S_IWGRP:
        logger.warning(f'The path {path} is insecure because users in the same group have write permission.')
    if mode & stat.S_IWOTH:
        logger.warning(f'The path {path} is insecure because users in the other groups have write permission.')


def check_variable_type(var, expected_type):
    if not isinstance(var, expected_type):
        raise TypeError(f'The variable {var} is not of type {expected_type}.')


def check_exist(path):
    if not os.path.exists(path):
        raise OSError(f'Path {path} is not exist')
