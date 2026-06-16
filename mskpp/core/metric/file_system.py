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

DIR_NAME_LENGTH_LIMIT = 1024
FILE_NAME_LENGTH_LIMIT = 200
INPUT_BINARY_FILE_MAX_SIZE = 100 * 1024 * 1024
DATA_DIRECTORY_AUTHORITY = 0o750


class FileChecker:
    def __init__(self, path, file_type, threshold=INPUT_BINARY_FILE_MAX_SIZE):
        self.path = path
        self.absolute_path = os.path.abspath(path)
        self.threshold = threshold
        self.file_type = file_type

    def check_input_file(self):
        if not self.is_string_char_valid():
            return False
        if not os.path.exists(self.absolute_path):
            logger.error(f"Path:{self.absolute_path} not exist.")
            return False
        if not self.path_len_check_valid():
            logger.warning(f"Path:{self.absolute_path} length is too long.")
        if self.is_soft_link_recusively():
            logger.warning(
                f"Path:{self.absolute_path} contains soft link which may cause security problems, please check."
            )
        if self.file_type != "dir" and os.path.isdir(self.absolute_path):
            logger.error(f"Path:{self.absolute_path} is dir, not a file.")
            return False
        path_permission = {"csv": os.R_OK, "dir": os.W_OK, "file": os.R_OK, "app": os.X_OK}
        if self.file_type not in path_permission:
            logger.warning(f"Path:{self.absolute_path}, the file type is unsupported.")
        file_mode = path_permission[self.file_type]
        self.check_path_permission(file_mode)
        if self.file_type != "dir" and (file_mode & os.R_OK) != 0 and not self.check_file_size_valid():
            logger.warning(f"Path:{self.absolute_path}, file size is too large, max file size:{self.threshold}.")
        return True

    def check_output_file(self):
        if os.path.exists(self.absolute_path):
            logger.error(f"Path:{self.absolute_path} already exists.")
            return False
        self.absolute_path = os.path.dirname(self.absolute_path)
        self.file_type = 'dir'
        return self.check_group_others_w_permission() and self.check_input_file()

    def is_string_char_valid(self):
        invalid_chars = {
            '\n': '\\n',
            '\f': '\\f',
            '\r': '\\r',
            '\b': '\\b',
            '\t': '\\t',
            '\v': '\\v',
            '\u007f': '\\u007F',
        }
        for key, value in invalid_chars.items():
            if key in self.absolute_path:
                logger.error(f"Path:{self.absolute_path} contains {value}, which is invalid.")
                return False
        return True

    def is_soft_link_recusively(self):
        while self.absolute_path.endswith('/'):
            self.absolute_path = self.absolute_path[:-1]
        if os.path.islink(self.absolute_path):
            return True
        dirs = self.absolute_path.split('/')
        curpath = ""
        for dir_name in dirs:
            if dir_name == "":
                continue
            curpath = curpath + '/' + dir_name
            if os.path.islink(curpath):
                return True
        return False

    def path_len_check_valid(self):
        if len(self.absolute_path) > DIR_NAME_LENGTH_LIMIT:
            return False
        dirs = self.absolute_path.split('/')
        for dir_name in dirs:
            if len(dir_name) > FILE_NAME_LENGTH_LIMIT:
                return False
        return True

    def check_path_permission(self, file_mode):
        # 读取文件状态信息
        file_stat = os.stat(self.absolute_path)
        # 将文件权限转换为八进制字符串并提取最后三位
        file_permission = oct(file_stat.st_mode)[-3:]
        # 提取所有者、组和其他用户的权限
        owner_permission = int(file_permission[0])
        group_permission = int(file_permission[1])  # 新增：提取组权限
        other_permission = int(file_permission[2])
        # 获取当前用户 UID
        uid = os.getuid()
        # 检查读权限
        if (file_mode & os.R_OK) != 0 and (owner_permission & os.R_OK) == 0:
            logger.warning(f"Path:{self.absolute_path} is not readable.")
        # 检查写权限
        if (file_mode & os.W_OK) != 0 and (owner_permission & os.W_OK) == 0:
            logger.warning(f"Path:{self.absolute_path} is not writable.")
        # 检查执行权限
        if (file_mode & os.X_OK) != 0 and (owner_permission & os.X_OK) == 0:
            logger.warning(f"Path:{self.absolute_path} is not executable.")
        # 检查组权限是否允许写操作
        if (group_permission & os.W_OK) != 0:
            logger.warning(f"Path:{self.absolute_path} is writable by the group.")
        # 检查其他用户是否有写权限
        if (other_permission & os.W_OK) != 0:
            logger.warning(f"Path:{self.absolute_path} is writable by any other users.")

        # 检查文件所有者是否与当前用户一致
        if uid != 0 and uid != file_stat.st_uid and file_stat.st_uid != 0:
            logger.warning(f"Path:{self.absolute_path} the current owner have inconsistent permission.")
        return True

    def check_file_size_valid(self):
        file_stat = os.stat(self.absolute_path)
        file_size = file_stat.st_size
        return file_size <= self.threshold

    def check_group_others_w_permission(self):
        mode = os.stat(self.absolute_path).st_mode
        if mode & stat.S_IWGRP:
            logger.warning(f"Path:{self.absolute_path} cannot have write permission of group.")
        if mode & stat.S_IWOTH:
            logger.warning(f"Path:{self.absolute_path} cannot have write permission of other users.")
        return True
