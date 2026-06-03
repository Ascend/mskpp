<h1 align="center">MindStudio Kernel Performance Prediction</h1>

<div align="center">
<h2>Ascend AI Operator Design Tool</h2>
  
 [![Ascend](https://img.shields.io/badge/Community-MindStudio-blue.svg)](https://www.hiascend.com/developer/software/mindstudio) 
 [![License](https://badgen.net/badge/License/MulanPSL-2.0/blue)](./LICENSE)

</div>

## ✨Latest News

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

## 🛠️ Contribution Guide

You are welcome to contribute to the project. For details, see [Contribution Guide](./docs/en/contributing/contributing_guide.md). 

## ⚖️ Related Notes

🔹 [Release Notes](./docs/en/release_notes/release_notes.md) 
🔹 [License Notice](./docs/en/legal/license_notice.md) 
🔹 [Security Statement](./docs/en/legal/security_statement.md) 
🔹 [Disclaimer](./docs/en/legal/disclaimer.md) 

## 🤝 Suggestions and Communication

You are welcome to contribute to the community. If you have any questions or suggestions, please submit a [Issues](https://gitcode.com/Ascend/mskpp/issues). We will reply as soon as possible. Thank you for your support.

|                                      📱 Follow the MindStudio WeChat Account                                      | 💬 Communication and Support Channels                                                                                                                                                                                                                                                                                                                                                                                                                    |
|:-----------------------------------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| <img src="https://gitcode.com/Ascend/msot/blob/master/docs/zh/figures/readme/officialAccount.png" width="120"><br><sub>*Scan the QR code to follow us and get the latest updates.*</sub>| 💡 **Join the WeChat group**:<br>Follow the WeChat account and reply "communication group" to obtain the QR code for joining the group.<br><br>🛠️ ️**Other channels**:<br><br>|

## 🙏 Acknowledgements

This tool is jointly developed by the following Huawei departments:  
🔹 Ascend Computing MindStudio Development Department  
🔹 Ascend Computing Ecosystem Enablement Department  
🔹 Huawei Cloud AI Compute Service  
🔹 Compiler Technologies Lab, 2012 Labs  
🔹 Markov Lab, 2012 Labs  
Thank you to everyone in the community for your PRs. We warmly welcome your contributions.
