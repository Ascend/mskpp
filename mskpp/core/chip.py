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

import time
import os
from datetime import datetime, timezone
from mskpp._C import arch, task_schedule
from mskpp.utils import logger
from .metric import Metrics
from .aicore import core_type_list
from .trace import Trace
from .common import checker
from .metric.file_system import FileChecker, DATA_DIRECTORY_AUTHORITY

sync_instr_dict = {"SET_FLAG": [], "WAIT_FLAG": []}
event_id_dict = {}  # 记录event_id的字典，保证set_flag时设置event_id,wait_flag是查找id


class Chip:
    support_list = ["Ascend910B1", "Ascend910B2", "Ascend910B3", "Ascend910B4", "Ascend910B4-1", "Ascend910B2C"]
    need_instr_log = True

    def __init__(self, name, debug_mode=False):
        self.chip_name = name
        self.need_trace = False
        self.need_metrics = False
        self.debug_mode = debug_mode
        self.output_dir = ''
        self.param_transfer()
        task_schedule.Schedule().set_debug_mode(debug_mode)

    def __enter__(self):
        self.create_output_dir()
        arch.set(self.chip_name)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        logger.info("MSKPP instruction performance modeling...")
        time.sleep(0)  # 通过cpu的等待，保证打印等信息的显示时序。
        if self.debug_mode or Chip.sync_instr_pre_check() is False:
            Trace().set_enable(False)
            Metrics().set_enable(False)
            task_schedule.Schedule().run()
            return
        duration = task_schedule.Schedule().run()
        if self.need_trace:
            Trace().dump(self.output_dir)
        if self.need_metrics:
            Metrics().set_total_duration(duration)
            Metrics().summary(self.output_dir)
        self.chip_resource_clear()

    @staticmethod
    def chip_resource_clear():
        sync_instr_dict["SET_FLAG"].clear()
        sync_instr_dict["WAIT_FLAG"].clear()
        core_type_list.clear()
        Chip.need_instr_log = True
        event_id_dict.clear()
        Metrics().metrics_clear()

    @staticmethod
    def sync_instr_pre_check():
        # diff number
        if len(sync_instr_dict["SET_FLAG"]) != len(sync_instr_dict["WAIT_FLAG"]):
            logger.error("The number of SET_FLAG = {} and WAIT_FLAG = {} instructions do not match".format(
                len(sync_instr_dict["SET_FLAG"]), len(sync_instr_dict["WAIT_FLAG"])))
            return False
        # duplicate element
        set_dup = set(sync_instr_dict["SET_FLAG"])
        wait_dup = set(sync_instr_dict["WAIT_FLAG"])
        if len(set_dup) != len(sync_instr_dict["SET_FLAG"]):
            logger.error("SET_FLAG has duplicate instructions {}".format(set_dup))
            return False
        if len(wait_dup) != len(sync_instr_dict["WAIT_FLAG"]):
            logger.error("WAIT_FLAG has duplicate instructions {}".format(wait_dup))
            return False
        # not matched
        no_match = set_dup ^ wait_dup
        if len(no_match) != 0:
            logger.error("No matching instruction {}".format(no_match))
            return False
        return True

    @staticmethod
    def set_cache_hit_ratio(config):
        arch.set_cache_hit_ratio(config["cache_hit_ratio"])

    @staticmethod
    def set_prof_summary_path(file_path):
        Metrics().set_prof_summary_path(file_path)

    @staticmethod
    def disable_instr_log():
        Metrics().disable_instr_log()
        Chip.need_instr_log = False

    def enable_trace(self):
        self.need_trace = True
        Trace().set_enable(True)

    def enable_metrics(self):
        self.need_metrics = True
        Metrics().set_enable(True)

    def param_transfer(self):
        if not checker.is_required_type(self.chip_name, str) or self.chip_name not in Chip.support_list:
            raise Exception("Parameter chip_name in Chip is unsupported, supported chip types: {}".format(Chip.support_list))
        self.chip_name = "Ascend910_95" if "_95" in self.chip_name else "Ascend910B1"
        if not checker.is_required_type(self.debug_mode, bool):
            raise Exception("Parameter debug_mode in Chip should be bool, but got: {}".format(type(self.debug_mode)))

    def create_output_dir(self):
        time_stamp = datetime.now(tz=timezone.utc).strftime("%Y%m%d%H%M%S")
        cur_dir = os.getcwd()
        self.output_dir = os.path.join(cur_dir, "MSKPP" + time_stamp)
        file_checker = FileChecker(self.output_dir, "dir")
        if not file_checker.check_output_file():
            raise Exception("Fail to Create output folder")
        os.makedirs(self.output_dir)
        os.chmod(self.output_dir, DATA_DIRECTORY_AUTHORITY)
