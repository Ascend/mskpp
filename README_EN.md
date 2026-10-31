<h1 align="center">MindStudio Kernel Performance Prediction</h1>

<div align="center">
<p><b><span style="font-size:24px;">Ascend AI Operator Design Tool</span></b></p>

[![Quick Start](https://badgen.net/badge/Quick%20Start/QuickStart/blue)](./docs/en/quick_start/mskpp_quick_start.md)
[![Exact Search](https://badgen.net/badge/Exact%20Search/ReadTheDocs/blue)](https://mindstudio-operator-tools-docs.readthedocs.io/zh-cn/latest/)
[![AI Q&A](https://badgen.net/badge/AI%20Q%26A/DeepWiki/blue)](https://deepwiki.com/mindstudio-docs/master)
[![AI Q&A](https://badgen.net/badge/AI%20Q%26A/ZRead/blue)](https://zread.ai/mindstudio-docs/master)
[![Ascend Community](https://badgen.net/badge/Ascend%20Community/Community/blue)](https://www.hiascend.com/en/developer/software/mindstudio)
[![Report Issues](https://badgen.net/badge/Report%20Issues/Issues/blue)](https://gitcode.com/Ascend/mskpp/issues)

</div>

English | [简体中文](./README.md)

## ✨ Latest News

<span style="font-size:14px;">

🔹 **[Dec 31, 2025]**: MindStudio Kernel Performance Prediction is fully open-sourced.

</span>

## ️ ℹ️ Overview

MindStudio Kernel Performance Prediction (msKPP) is a performance simulation tool that supports quick prediction of the peak performance of an operator based on the given algorithm implementation. The execution time is estimated based on the input/output scale, without actual computation. The result can be returned in seconds, and the simulation speed is several orders of magnitude faster than that of the cycle-level simulator.

## ⚙️ Features

| Function| Description|
|---------|--------|
| **Operator Feature Modeling**| Simulates the operator time consumption based on the APIs provided by msKPP.|
| **Operator Computing and Transferring Specification Analysis**| Generates the transfer pipeline statistics file and instruction information statistics file to view the msKPP modeling result.|
| **Peak Performance Analysis** | Generates the instruction pipeline diagram and instruction proportion pie chart to view the msKPP modeling result.|
| **Preliminary Design of Operator Tiling**| Quickly filters out optimal tiling policies.|

## 🚀 Quick Start

For details, see [msKPP Quick Start](./docs/en/quick_start/mskpp_quick_start.md).

## 📦 Installation Guide

This section describes the environment dependencies and installation methods of the msKPP tool. For details, see [msKPP Installation Guide](./docs/en/install_guide/mskpp_install_guide.md).

## 📘 User Guide

For details about how to use the tool, see [msKPP User Guide](./docs/en/user_guide/mskpp_user_guide.md).

## 📚 API Reference

The msKPP tool provides two types of APIs: basic APIs and instruction APIs. For details, see [msKPP API Reference](./docs/en/api_reference/mskpp_api_reference.md).

## 🌌 Smart Search

To improve the efficiency of document retrieval, we provide the following efficient search methods:  
🔹 [AI Q&A (DeepWiki)](https://deepwiki.com/mindstudio-docs/master): Natural language Q&A to quickly grasp the project architecture and module relationships   
🔹 [AI Q&A (ZRead)](https://zread.ai/mindstudio-docs/master): Better Chinese Q&A experience, precisely locating feature usage and details   
🔹 [Precise Search (ReadTheDocs)](https://mindstudio-operator-tools-docs.readthedocs.io/zh-cn/latest/): Full-text keyword search, directly accessing APIs, parameters, and error messages  

## 🛠️ Contribution Guide

You are welcome to contribute to the project. For details, see [Contribution Guide](./docs/en/contributing/contributing_guide.md). 

## ⚖️ Related Notes

🔹 [Release Notes](https://gitcode.com/Ascend/mskpp/releases)   
🔹 [License Notice](./docs/en/legal/license_notice.md)   
🔹 [Security Statement](./docs/en/legal/security_statement.md)   
🔹 [Disclaimer](./docs/en/legal/disclaimer.md) 

## 🤝 Suggestions and Communication

You are welcome to contribute to the community. If you have any questions or suggestions, please submit an [Issues](https://gitcode.com/Ascend/mskpp/issues). We will reply as soon as possible. Thank you for your support.

|                                                                  Live Chat (WeChat Group)                                                                   |                                                                           Official Info (WeChat Official Account)                                                                            | In-Depth Support (Assistant/Forum)                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
|:-----------------------------------------------------------------------------------------------------------------------------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| <img src="https://raw.gitcode.com/Ascend/docs/files/master/common/Writing_Template/figures/qr_code_wechat_work.png" width="120"><br><sub>*Scan to join the tech group*</sub> | <img src="https://raw.gitcode.com/Ascend/docs/files/master/common/Writing_Template/figures/qr_code_wechat_official_account.png" width="120"><br><sub>*Scan to follow the official account*</sub> | Scan to join the group and follow the official account for the fastest way to reach the MindStudio user and developer community:<br> **Quick Questions:** Discuss technical issues with community members in real time.<br>**Stay Updated:** Get version release and feature update notifications first.<br> **Share Experience:** Exchange best practices and practical insights with developers.  <br> <br> **More Support Channels**: 👉 Ascend Assistant: [![WeChat](https://img.shields.io/badge/WeChat-07C160?style=flat-square&logo=wechat&logoColor=white)](https://gitcode.com/Ascend/msit/blob/master/docs/zh/figures/readme/xiaozhushou.png) 👉 Ascend Forum: [![Website](https://img.shields.io/badge/Website-%231e37ff?style=flat-square&logo=RSS&logoColor=white)](https://www.hiascend.com/forum/) |

## 🙏 Acknowledgements

This tool is jointly contributed by Huawei Technologies Co., Ltd. and developers.

Thanks for every PR from the community, and contributions are welcome.
