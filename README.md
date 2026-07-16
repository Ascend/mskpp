<h1 align="center">MindStudio Kernel Performance Prediction</h1>

<div align="center">
<p><b><span style="font-size:24px;">昇腾 AI 算子设计工具</span></b></p>

 [![License](https://badgen.net/badge/快速入门/QuickStart/blue)](./docs/zh/quick_start/mskpp_quick_start.md)
 [![License](https://badgen.net/badge/精确搜索/ReadTheDocs/blue)](https://mindstudio-operator-tools-docs.readthedocs.io/zh-cn/latest/)
 [![License](https://badgen.net/badge/AI问答/DeepWiki/blue)](https://deepwiki.com/mindstudio-docs/master)
 [![License](https://badgen.net/badge/AI问答/ZRead/blue)](https://zread.ai/mindstudio-docs/master)
 [![License](https://badgen.net/badge/昇腾社区/Community/blue)](https://www.hiascend.com/cn/developer/software/mindstudio)
 [![License](https://badgen.net/badge/报告问题/Issues/blue)](https://gitcode.com/Ascend/mskpp/issues)

</div>

## ✨ 最新消息

<span style="font-size:14px;">

🔹 **[2025-12-31]**：MindStudio Kernel Performance Prediction 项目全面开源

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

详细操作步骤请参见《[msKPP 快速入门](./docs/zh/quick_start/mskpp_quick_start.md)》

## 📦 安装指南

介绍msKPP工具的环境依赖及安装方式，具体请参见《[msKPP 安装指南](./docs/zh/install_guide/mskpp_install_guide.md)》

## 📘 使用指南

工具的详细使用方法，请参见《[msKPP 使用指南](./docs/zh/user_guide/mskpp_user_guide.md)》

## 📚 API参考 

msKPP工具分为基础功能接口和指令接口两种接口类型。具体内容请参见 《[msKPP 对外接口使用说明](./docs/zh/api_reference/mskpp_api_reference.md)》

## 🌌 智能检索

为提升文档查阅效率，我们提供多种高效检索方式：  
🔹 [AI 问答（DeepWiki）](https://deepwiki.com/mindstudio-docs/master)：自然语言问答，快速把握项目架构与模块关系。   
🔹 [AI 问答（ZRead）](https://zread.ai/mindstudio-docs/master)：中文问答体验更优，精准定位功能用法与细节。   
🔹 [精确搜索（ReadTheDocs）](https://mindstudio-operator-tools-docs.readthedocs.io/zh-cn/latest/)：关键词全文检索，直达接口、参数与报错等信息。  

## 🛠️ 贡献指南

欢迎参与项目贡献，请参见《[贡献指南](./docs/zh/contributing/contributing_guide.md)》

## ⚖️ 相关说明

🔹《[版本说明](./docs/zh/release_notes/release_notes.md)》  
🔹《[许可证声明](./docs/zh/legal/license_notice.md)》  
🔹《[安全声明](./docs/zh/legal/security_statement.md)》  
🔹《[免责声明](./docs/zh/legal/disclaimer.md)》

## 🤝 建议与交流

欢迎大家为社区做贡献。如果有任何疑问或建议，请提交 [Issues](https://gitcode.com/Ascend/mskpp/issues)，我们会尽快回复。感谢您的支持。

|                                                                            即时互动（微信群）                                                                             |                                                                                  官方资讯（公众号）                                                                                   | 深度支持（助手/论坛）                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
|:------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| <img src="https://raw.gitcode.com/Ascend/docs/files/master/common/Writing_Template/figures/qr_code_wechat_work.png" width="120"><br><sub>*扫码加入技术交流群*</sub> | <img src="https://raw.gitcode.com/Ascend/docs/files/master/common/Writing_Template/figures/qr_code_wechat_official_account.png" width="120"><br><sub>*扫码关注官方公众号*</sub> | 扫码入群并关注公众号，直达 MindStudio 用户与开发者最快捷的交流平台：<br> **快速提问：** 与社区小伙伴即时探讨技术问题<br>**掌握动态：** 第一时间获取版本发布与功能更新通知<br> **经验共享：** 与广大开发者交流最佳实践与实战心得  <br> <br> **更多支持渠道**：👉 昇腾助手：[![WeChat](https://img.shields.io/badge/WeChat-07C160?style=flat-square&logo=wechat&logoColor=white)](https://gitcode.com/Ascend/msit/blob/master/docs/zh/figures/readme/xiaozhushou.png) 👉 昇腾论坛：[![Website](https://img.shields.io/badge/Website-%231e37ff?style=flat-square&logo=RSS&logoColor=white)](https://www.hiascend.com/forum/) |

## 🙏 致谢

本工具由华为公司的下列部门联合贡献：    
🔹 昇腾计算MindStudio开发部  
🔹 昇腾计算生态使能部  
🔹 华为云昇腾云服务  
🔹 2012编译器实验室  
🔹 2012马尔科夫实验室  
感谢来自社区的每一个 PR，欢迎贡献！
