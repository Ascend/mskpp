<h1 align="center">MindStudio Kernel Performance Prediction</h1>

<div align="center">
<h2>昇腾 AI 算子设计工具</h2>
  
 [![Ascend](https://img.shields.io/badge/Community-MindStudio-blue.svg)](https://www.hiascend.com/developer/software/mindstudio) 
 [![License](https://badgen.net/badge/License/MulanPSL-2.0/blue)](./LICENSE)

</div>

## ✨ 最新消息

<span style="font-size:14px;">

🔹 **[2025.12.31]**：MindStudio Kernel Performance Prediction 项目全面开源

</span>

## ️ ℹ️ 简介

MindStudio Kernel Performance Prediction（算子设计，msKPP）是一款性能仿真工具，支持基于算子表达式快速预测其在给定算法实现下的性能上限。无需执行真实计算，仅依据输入/输出规模估算执行时间，可在秒级返回结果，仿真速度较cycle级仿真器提升数个数量级。

## ⚙️ 功能介绍

| 功能名称 | 功能描述 |
|---------|--------|
| **算子特性建模** | 基于 msKPP 提供的接口模拟算子耗时。 |
| **算子计算搬运规格分析** | 生成搬运流水统计文件和指令信息统计文件，用于查看 msKPP 建模结果。 |
| **极限性能分析** | 生成指令流水图和指令占比饼图，用于查看 msKPP 建模结果。 |
| **算子 tiling 初步设计** | 快速筛选出若干较优的 tiling 策略。 |

## 🚀 快速入门

详细操作步骤请参见 [《msKPP 快速入门》](./docs/zh/quick_start/mskpp_quick_start.md)。

## 📦 安装指南

介绍msKPP工具的环境依赖及安装方式，具体请参见 [《msKPP 安装指南》](./docs/zh/install_guide/mskpp_install_guide.md)。

## 📘 使用指南

工具的详细使用方法，请参见 [《msKPP 使用指南》](./docs/zh/user_guide/mskpp_user_guide.md)。

## 📚 API参考 

msKPP工具分为基础功能接口和指令接口两种接口类型。具体内容请参见 [《msKPP 对外接口使用说明》](./docs/zh/api_reference/mskpp_api_reference.md)。

## 🛠️ 贡献指南

欢迎参与项目贡献，请参见 [《贡献指南》](./docs/zh/contributing/contributing_guide.md)。  

## ⚖️ 相关说明

🔹 [《版本说明》](./docs/zh/release_notes/release_notes.md)  
🔹 [《许可证声明》](./docs/zh/legal/license_notice.md)  
🔹 [《安全声明》](./docs/zh/legal/security_statement.md)  
🔹 [《免责声明》](./docs/zh/legal/disclaimer.md)  

## 🤝 建议与交流

欢迎大家为社区做贡献。如果有任何疑问或建议，请提交[Issues](https://gitcode.com/Ascend/mskpp/issues)，我们会尽快回复。感谢您的支持。

|                                      📱 关注 MindStudio 公众号                                       | 💬 更多交流与支持                                                                                                                                                                                                                                                                                                                                                                                                                     |
|:-----------------------------------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| <img src="https://gitcode.com/Ascend/msot/blob/master/docs/zh/figures/readme/officialAccount.png" width="120"><br><sub>*扫码关注获取最新动态*</sub> | 💡 **加入微信交流群**：<br>关注公众号，回复“交流群”即可获取入群二维码。<br><br>🛠️ **其他渠道**：<br>👉 昇腾助手：[![WeChat](https://img.shields.io/badge/WeChat-07C160?style=flat-square&logo=wechat&logoColor=white)](https://gitcode.com/Ascend/msot/blob/master/docs/zh/figures/readme/xiaozhushou.png)<br>👉 昇腾论坛：[![Website](https://img.shields.io/badge/Website-%231e37ff?style=flat-square&logo=RSS&logoColor=white)](https://www.hiascend.com/forum/) |

## 🙏 致谢

本工具由华为公司的下列部门联合贡献：    
🔹 昇腾计算MindStudio开发部  
🔹 昇腾计算生态使能部  
🔹 华为云昇腾云服务  
🔹 2012编译器实验室  
🔹 2012马尔科夫实验室  
感谢来自社区的每一个 PR，欢迎贡献！
