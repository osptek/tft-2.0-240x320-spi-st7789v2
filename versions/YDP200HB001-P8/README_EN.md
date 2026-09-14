<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 2.0″ TFT 240×320 (ST7789V2 · SPI)</h1>

<p align="center"><b>TFT / IPS module · SPI · ST7789V2</b></p>

<p align="center"><a href="./README.md">简体中文</a> | English · <a href="../../README_EN.md">Family index</a></p>

<p align="center">
  <img alt="Size: 2.0 inch" src="https://img.shields.io/badge/Size-2.0%22-3498DB?style=flat-square" />
  <img alt="Resolution: 240x320" src="https://img.shields.io/badge/Resolution-240%C3%97320-8E44AD?style=flat-square" />
  <img alt="Interface: SPI" src="https://img.shields.io/badge/Interface-SPI-27AE60?style=flat-square" />
  <img alt="Driver: ST7789V2" src="https://img.shields.io/badge/Driver-ST7789V2-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 2.0 inch 240×320 TFT SPI module (ST7789V2) product image" src="./images/product.png" width="640" /></p>

## Contents

- [Overview](#overview)
- [Specifications](#specifications)
- [Sample projects](#sample-projects)
- [Repository layout](#repository-layout)
- [Resources](#resources)
- [Buy](#buy)
- [Support](#support)

---

## Overview

OSPTEK **2.0″ 240×320 TFT (IPS)** is a **SPI** color display module driven by **ST7789V2**. Suited to handheld devices, instruments, and compact portrait HMI.

Spec ID (repository name): `tft-2.0-240x320-spi-st7789v2`

Current module version: **YDP200HB001-P8**. Outline details follow [`docs/YDP200HB001-P8_外形图.pdf`](./docs/YDP200HB001-P8_%E5%A4%96%E5%BD%A2%E5%9B%BE.pdf).

## Specifications

| Item | Spec |
| ---- | ---- |
| Size | 2.0 inch |
| Type | TFT / IPS (color) |
| Resolution | 240×320 |
| Interface | SPI |
| Driver IC | ST7789V2 |

> Full outline, FPC definition, power, and timing follow the product datasheet / driver IC datasheet.

## Sample projects

| Description | Path |
| ---- | ---- |
| ESP32-S3 · ST7789V2 SPI + LVGL9 (heart-rate dial UI demo) | [`examples/esp32s3-tft-2.0-240x320-spi-st7789v2-bringup/`](./examples/esp32s3-tft-2.0-240x320-spi-st7789v2-bringup/) |

## Repository layout

```text
tft-2.0-240x320-spi-st7789v2/                                # repo root (nav: ../../README_EN.md)
└── versions/
    └── YDP200HB001-P8/                                # full materials for this part number
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## Resources

### Product files

| Resource | Link |
| ---- | ---- |
| Outline drawing (YDP200HB001-P8) | [`docs/YDP200HB001-P8_外形图.pdf`](./docs/YDP200HB001-P8_%E5%A4%96%E5%BD%A2%E5%9B%BE.pdf) |
| Driver IC datasheet (ST7789V2) | [`docs/ST_7789_V2_SPEC_V1_0_d12b618112.pdf`](./docs/ST_7789_V2_SPEC_V1_0_d12b618112.pdf) |
| Init sequence (BOE 2.0 IPS · 2.2 Gamma) | [`docs/1_BOE2.0IPS(PV020QVQ-N81-1Q00)+ST7789V2-2.2Gamma-20200702.txt`](./docs/1_BOE2.0IPS%28PV020QVQ-N81-1Q00%29%2BST7789V2-2.2Gamma-20200702.txt) |

### Samples

- [ESP32-S3 ST7789V2 SPI + LVGL9 bringup](./examples/esp32s3-tft-2.0-240x320-spi-st7789v2-bringup/)

## Buy

<p align="center">
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="AliExpress store" src="https://img.shields.io/badge/AliExpress-Official_Store-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://shop110742373.taobao.com/"><img alt="Taobao store" src="https://img.shields.io/badge/Taobao-Official_Store-FF6A00?style=for-the-badge" /></a>
</p>

**Overseas (AliExpress)**

- Store: [OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

**China (Taobao)**

- Store: [鱼鹰光电工厂店](https://shop110742373.taobao.com/)

## Support

- Technical support / product inquiry: <luyu@osptek.com>
- QQ group: **985881096**
- Website: <https://osptek.com/>
- Feel free to open an Issue in this repository with any questions

---

<p align="center"><sub>© 2026 OSPTEK · Materials in this repository are licensed under CC BY 4.0</sub></p>
