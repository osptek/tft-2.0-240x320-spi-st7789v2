<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 2.0″ TFT 240×320（ST7789V2 · SPI）</h1>

<p align="center"><b>TFT / IPS 模组 · SPI · ST7789V2</b></p>

<p align="center"><a href="./README_EN.md">English</a> | 简体中文 · <a href="../../README.md">规格族索引</a></p>

<p align="center">
  <img alt="Size: 2.0 inch" src="https://img.shields.io/badge/Size-2.0%22-3498DB?style=flat-square" />
  <img alt="Resolution: 240x320" src="https://img.shields.io/badge/Resolution-240%C3%97320-8E44AD?style=flat-square" />
  <img alt="Interface: SPI" src="https://img.shields.io/badge/Interface-SPI-27AE60?style=flat-square" />
  <img alt="Driver: ST7789V2" src="https://img.shields.io/badge/Driver-ST7789V2-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 2.0 寸 240×320 TFT SPI 模组（ST7789V2）宣传图" src="./images/product.png" width="640" /></p>

## 目录

- [产品简介](#产品简介)
- [规格参数](#规格参数)
- [示例工程](#示例工程)
- [仓库结构](#仓库结构)
- [相关资料](#相关资料)
- [购买链接](#购买链接)
- [技术支持](#技术支持)

---

## 产品简介

OSPTEK **2.0 寸 240×320 TFT（IPS）** 是一款 **SPI** 接口彩色显示模组，显示驱动为 **ST7789V2**。适合手持终端、仪表与小型竖屏 HMI 等场景。

规格标识（仓库名）：`tft-2.0-240x320-spi-st7789v2`

当前模组版本：**YDP200HB001-P8**。外形细节以 [`docs/YDP200HB001-P8_外形图.pdf`](./docs/YDP200HB001-P8_%E5%A4%96%E5%BD%A2%E5%9B%BE.pdf) 为准。

## 规格参数

| 项目 | 规格 |
| ---- | ---- |
| 尺寸 | 2.0 英寸 |
| 类型 | TFT / IPS（彩色） |
| 分辨率 | 240×320 |
| 接口 | SPI |
| 驱动 IC | ST7789V2 |

> 完整外形尺寸、FPC 定义、供电与时序以产品规格书 / 驱动手册为准。

## 示例工程

| 说明 | 路径 |
| ---- | ---- |
| ESP32-S3 · ST7789V2 SPI + LVGL9（心率表盘 UI 演示） | [`examples/esp32s3-tft-2.0-240x320-spi-st7789v2-bringup/`](./examples/esp32s3-tft-2.0-240x320-spi-st7789v2-bringup/) |

## 仓库结构

```text
tft-2.0-240x320-spi-st7789v2/                                # 仓库根（导航见 ../../README.md）
└── versions/
    └── YDP200HB001-P8/                                # 本料号完整资料
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## 相关资料

### 本产品资料

| 资料 | 链接 |
| ---- | ---- |
| 外形图（YDP200HB001-P8） | [`docs/YDP200HB001-P8_外形图.pdf`](./docs/YDP200HB001-P8_%E5%A4%96%E5%BD%A2%E5%9B%BE.pdf) |
| 驱动 IC 数据手册（ST7789V2） | [`docs/ST_7789_V2_SPEC_V1_0_d12b618112.pdf`](./docs/ST_7789_V2_SPEC_V1_0_d12b618112.pdf) |
| 初始化序列（BOE 2.0 IPS · 2.2 Gamma） | [`docs/1_BOE2.0IPS(PV020QVQ-N81-1Q00)+ST7789V2-2.2Gamma-20200702.txt`](./docs/1_BOE2.0IPS%28PV020QVQ-N81-1Q00%29%2BST7789V2-2.2Gamma-20200702.txt) |

### 示例工程

- [ESP32-S3 ST7789V2 SPI + LVGL9 bringup](./examples/esp32s3-tft-2.0-240x320-spi-st7789v2-bringup/)

## 购买链接

<p align="center">
  <a href="https://shop110742373.taobao.com/"><img alt="淘宝官方店铺" src="https://img.shields.io/badge/淘宝-官方店铺-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="速卖通官方店铺" src="https://img.shields.io/badge/速卖通-官方店铺-FF6A00?style=for-the-badge" /></a>
</p>

**国内（淘宝）**

- 店铺：[鱼鹰光电工厂店](https://shop110742373.taobao.com/)

**海外（AliExpress）**

- 店铺：[OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

## 技术支持

- 技术支持 / 产品咨询：<luyu@osptek.com>
- QQ 技术交流群：**985881096**
- 公司官网：<https://osptek.com/>
- 有任何问题，都可以在本仓库 Issues 中提问

---

<p align="center"><sub>© 2026 OSPTEK 鱼鹰光电 · 本仓库资料采用 CC BY 4.0 许可</sub></p>
