# -------------------------------------------------------------------------
# This file is part of the MindStudio project.
# Copyright (c) 2026 Huawei Technologies Co.,Ltd.
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

from setuptools import setup
from packaging.tags import sys_tags
import os

tag = next(sys_tags())

whl_version = os.environ.get('WHL_VERSION', '0.0.0.dev0')

with open('README.md', encoding='utf-8') as f:
    readme = f.read()

setup(
    name='mindstudio-kpp',
    version=whl_version,
    author=' mskpp',
    author_email='mskpp',
    description='mskpp',
    long_description=readme,
    long_description_content_type='text/markdown',
    url='https://gitee.com/Ascend/MindStudio-KPP',
    options={'bdist_wheel': {'plat_name': tag.platform}},
    packages=['mskpp'],
    include_package_data=True,
    package_data={
        'mskpp': ['_C.so'],
    },
    install_requires=[
        'plotly>=5.11.0',
        'pandas>=1.0.0',
    ],
    license="MIT",
    classifiers=[
        'Programming Language :: Python :: 3',
        'Operating System :: POSIX :: Linux',
    ],
    python_requires='>=3.7',
)
