#pragma once

#include "driver/gpio.h"
#include "driver/spi_master.h"

/* BOE 2.0" IPS 240x320, ST7789V2, SPI：DIN=9 CLK=10 CS=11 DC=12 RST=13 BL=14 */
#define LCD_SPI_HOST        SPI2_HOST

#define LCD_PIN_MOSI        GPIO_NUM_9   /* DIN */
#define LCD_PIN_SCLK        GPIO_NUM_10  /* CLK */
#define LCD_PIN_CS          GPIO_NUM_11
#define LCD_PIN_DC          GPIO_NUM_12
#define LCD_PIN_RST         GPIO_NUM_13
#define LCD_PIN_BL          GPIO_NUM_14

#define LCD_H_RES           240
#define LCD_V_RES           320
#define LCD_PIXEL_CLOCK_HZ  (40 * 1000 * 1000)

/* 若画面偏移/镜像不对，在此调整 */
#define LCD_X_GAP           0
#define LCD_Y_GAP           0
#define LCD_MIRROR_X        false
#define LCD_MIRROR_Y        false
#define LCD_SWAP_XY         false
#define LCD_INVERT_COLOR    true

#define LCD_BL_ON_LEVEL     1
