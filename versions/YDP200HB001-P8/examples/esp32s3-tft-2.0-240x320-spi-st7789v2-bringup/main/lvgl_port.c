#include "lvgl_port.h"

#include "board_config.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_lvgl_port.h"
#include "st7789_lcd.h"

static const char *TAG = "lvgl_port";

static lv_display_t *s_disp;

esp_err_t lvgl_port_init_all(void)
{
    ESP_RETURN_ON_ERROR(st7789_lcd_init(), TAG, "lcd init failed");

    const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_RETURN_ON_ERROR(lvgl_port_init(&lvgl_cfg), TAG, "lvgl port init failed");

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = st7789_lcd_io(),
        .panel_handle = st7789_lcd_panel(),
        .buffer_size = LCD_H_RES * (LCD_V_RES / 10),
        .double_buffer = true,
        .hres = LCD_H_RES,
        .vres = LCD_V_RES,
        .monochrome = false,
        .color_format = LV_COLOR_FORMAT_RGB565,
        .rotation = {
            .swap_xy = LCD_SWAP_XY,
            .mirror_x = LCD_MIRROR_X,
            .mirror_y = LCD_MIRROR_Y,
        },
        .flags = {
            .buff_dma = true,
            .buff_spiram = false,
            .swap_bytes = true,
            .full_refresh = false,
            .direct_mode = false,
        },
    };

    s_disp = lvgl_port_add_disp(&disp_cfg);
    ESP_RETURN_ON_FALSE(s_disp, ESP_FAIL, TAG, "lvgl_port_add_disp failed");

    ESP_LOGI(TAG, "LVGL on %dx%d ST7789", LCD_H_RES, LCD_V_RES);
    return ESP_OK;
}

lv_display_t *lvgl_port_get_display(void)
{
    return s_disp;
}
