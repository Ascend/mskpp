from setuptools import setup
from packaging.tags import sys_tags
import os

tag = next(sys_tags())

whl_version = os.environ.get('WHL_VERSION', '0.0.0.dev0')

setup(
    name = 'mindstudio-kpp',
    version = whl_version,
    author =' mskpp',
    author_email = 'mskpp',
    description = 'mskpp',
    long_description = open('README.md', encoding='utf-8').read(),
    long_description_content_type = 'text/markdown',
    url = 'https://gitee.com/Ascend/MindStudio-KPP',
    options={
    'bdist_wheel':{
        'plat_name': tag.platform}},
    packages = ['mskpp'],
    include_package_data = True,
    package_data={
        'mskpp': ['_C.so'],
    },

    install_requires = [
        'plotly>=5.11.0',
        'pandas>=1.0.0',
    ],
    license = "MIT",
    classifiers = [
        'Programming Language :: Python :: 3',
        'Operating System :: POSIX :: Linux',
    ],
    python_requires = '>=3.7'
)
