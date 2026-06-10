<h1 align="center">MindStudio Kernel Performance Prediction</h1>

<div align="center">
<p><b><span style="font-size:24px;">Ascend AI Operator Design Tool</span></b></p>

 [![快速入门](https://badgen.net/badge/快速入门/QuickStart/blue)](./docs/zh/quick_start/mskpp_quick_start.md)[![AI问答(DeepWiki)](https://badgen.net/badge/AI问答/DeepWiki/blue)](https://deepwiki.com/mindstudio-docs/master) [![AI问答(ZRead)](https://badgen.net/badge/AI问答/ZRead/blue)](https://zread.ai/mindstudio-docs/master) [![精确搜索(ReadTheDocs)](https://badgen.net/badge/精确搜索/ReadTheDocs/blue)](https://mindstudio-operator-tools-docs.readthedocs.io/zh-cn/latest/) [![昇腾社区](https://badgen.net/badge/昇腾社区/Community/blue)](https://www.hiascend.com/cn/developer/software/mindstudio) [![报告问题](https://badgen.net/badge/报告问题/Issues/blue)](https://gitcode.com/Ascend/mskpp/issues) 

</div>


## ✨ Latest News

<span style="font-size:14px;">

🔹 **[2025.12.31]**: MindStudio Kernel Performance Prediction is fully open-sourced.

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
🔹 [AI Q&A (DeepWiki)](https://deepwiki.com/mindstudio-docs/master): Natural language Q&A to quickly grasp the project architecture and module relationships.   
🔹 [AI Q&A (ZRead)](https://zread.ai/mindstudio-docs/master): Better Chinese Q&A experience, precisely locating feature usage and details.   
🔹 [Precise Search (ReadTheDocs)](https://mindstudio-operator-tools-docs.readthedocs.io/zh-cn/latest/): Full-text keyword search, directly accessing APIs, parameters, and error messages.  

## 🛠️ Contribution Guide

You are welcome to contribute to the project. For details, see [Contribution Guide](./docs/en/contributing/contributing_guide.md). 

## ⚖️ Related Notes

🔹 [Release Notes](./docs/en/release_notes/release_notes.md) 
🔹 [License Notice](./docs/en/legal/license_notice.md) 
🔹 [Security Statement](./docs/en/legal/security_statement.md) 
🔹 [Disclaimer](./docs/en/legal/disclaimer.md) 

## 🤝 Suggestions and Communication

You are welcome to contribute to the community. If you have any questions or suggestions, please submit an [Issues](https://gitcode.com/Ascend/mskpp/issues). We will reply as soon as possible. Thank you for your support.

|                                                                  Live Chat (WeChat Group)                                                                   |                                                                           Official Info (WeChat Official Account)                                                                            | In-Depth Support (Assistant/Forum)                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
|:-----------------------------------------------------------------------------------------------------------------------------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| <img src="https://raw.gitcode.com/mengguangxin/docs/files/dev_0526/common/Writing_Template/figures/qr_code_wechat_work.png" width="120"><br><sub>*Scan to join the tech group*</sub> | <img src="https://raw.gitcode.com/mengguangxin/docs/files/dev_0526/common/Writing_Template/figures/qr_code_wechat_official_account.png" width="120"><br><sub>*Scan to follow the official account*</sub> | Scan to join the group and follow the official account for the fastest way to reach the MindStudio user and developer community:<br> **Quick Questions:** Discuss technical issues with community members in real time<br>**Stay Updated:** Get version release and feature update notifications first<br> **Share Experience:** Exchange best practices and practical insights with developers  <br> <br> **More Support Channels**: 👉 Ascend Assistant: [![WeChat](https://img.shields.io/badge/WeChat-07C160?style=flat-square&logo=wechat&logoColor=white)](https://gitcode.com/Ascend/msit/blob/master/docs/zh/figures/readme/xiaozhushou.png) 👉 Ascend Forum: [![Website](https://img.shields.io/badge/Website-%231e37ff?style=flat-square&logo=RSS&logoColor=white)](https://www.hiascend.com/forum/) |

## 🙏 Acknowledgements

This tool is jointly developed by the following Huawei departments:  
🔹 Ascend Computing MindStudio Development Department  
🔹 Ascend Computing Ecosystem Enablement Department  
🔹 Huawei Cloud AI Compute Service  
🔹 Compiler Technologies Lab, 2012 Labs  
🔹 Markov Lab, 2012 Labs  
Thank you to everyone in the community for your PRs. We warmly welcome your contributions.
