<h1 align="center">MindStudio Kernel Performance Prediction</h1>

<div align="center">
<h2>昇腾 AI 算子设计工具</h2>
  
 [![Ascend](https://img.shields.io/badge/Community-MindStudio-blue.svg)](https://www.hiascend.com/developer/software/mindstudio) 
 [![License](https://badgen.net/badge/License/MulanPSL-2.0/blue)](./docs/LICENSE)

</div>

## ✨ 最新消息

* [2025.12.30]：MindStudio Kernel Performance Prediction项目首次上线 

<br>

## ️ ℹ️ 简介

MindStudio Kernel Performance Prediction（算子设计，msKPP）是一款性能仿真工具，支持用户输入算子表达，进而预测算子在这一算法实现下的性能上限。相较于cycle级仿真器，其仿真速度有数量级的提升。由于本身针对性能的预测不需要进行真实的计算，仅需要依据输入和输出的规模，给出对应算法的执行时间，故而，可以在秒级给出性能结果。  

## ⚙️ 功能介绍

- [算子特性建模](./docs/zh/user_guide/mskpp_user_guide.md)：基于msKPP提供的接口模拟出算子耗时。
- [算子计算搬运规格分析](./docs/zh/user_guide/mskpp_user_guide.md)：生成搬运流水统计文件和指令信息统计文件，可查看msKPP建模结果。
- [极限性能分析](./docs/zh/user_guide/mskpp_user_guide.md)：生成文件指令流水图和指令占比饼图，可查看msKPP建模结果。
- [算子tiling初步设计](./docs/zh/user_guide/mskpp_user_guide.md)：能够快速筛选出几种较优的tiling策略。

## 🚀 快速入门

详细操作步骤请参见[《msKPP 快速入门》](./docs/zh/quick_start/mskpp_quick_start.md)。

## 📦 安装指南

介绍msKPP工具的环境依赖及安装方式，具体请参见[《msKPP 安装指南》](./docs/zh/install_guide/mskpp_install_guide.md)。

## 📘 使用指南

工具的详细使用方法，请参见 [《msKPP 使用指南》](./docs/zh/user_guide/mskpp_user_guide.md)。

## 📚 API参考 

msKPP工具分为基础功能接口和指令接口两种接口类型。具体内容请参见[《msKPP 对外接口使用说明》](./docs/zh/api_reference/mskpp_api_reference.md)。

## 🛠️ 贡献指南

若您有意参与项目贡献，请参见 [《贡献指南》](./docs/zh/contributing/contributing_guide.md)。  

## ⚖️ 相关说明

* [《License声明》](./docs/zh/legal/license_notice.md) 
* [《安全声明》](./docs/zh/legal/security_statement.md) 
* [《免责声明》](./docs/zh/legal/disclaimer.md)

## 🤝 建议与交流

欢迎大家为社区做贡献。如果有任何疑问或建议，请提交[Issues](https://gitcode.com/Ascend/mskpp/issues)，我们会尽快回复。感谢您的支持。

## 🙏 致谢

本工具由华为公司 **计算产品线** 贡献。    
感谢来自社区的每一个PR，欢迎贡献。
