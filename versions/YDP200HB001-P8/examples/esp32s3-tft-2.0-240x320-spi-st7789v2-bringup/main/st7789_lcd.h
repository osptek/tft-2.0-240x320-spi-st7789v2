#pragma once

#include "esp_err.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"

esp_err_t st7789_lcd_init(void);
esp_lcd_panel_io_handle_t st7789_lcd_io(void);
esp_lcd_panel_handle_t st7789_lcd_panel(void);
esp_err_t st7789_lcd_fill_color(uint16_t rgb565);
esp_err_t st7789_lcd_fill_rect(int x, int y, int w, int h, uint16_t rgb565);
esp_err_t st7789_lcd_blit(int x, int y, int w, int h, const uint16_t *pixels);
uint16_t st7789_rgb565_swap(uint16_t rgb565);
