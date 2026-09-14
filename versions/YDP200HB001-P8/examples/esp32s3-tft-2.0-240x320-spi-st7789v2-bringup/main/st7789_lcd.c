#include "st7789_lcd.h"

#include "board_config.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_heap_caps.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "st7789";

static esp_lcd_panel_io_handle_t s_io;
static esp_lcd_panel_handle_t s_panel;

static esp_err_t panel_tx_param(int cmd, const void *param, size_t param_size)
{
    return esp_lcd_panel_io_tx_param(s_io, cmd, param, param_size);
}

/* 来自 1_BOE2.0IPS(PV020QVQ-N81-1Q00)+ST7789V2-2.2Gamma-20200702.txt（跳过 SLPOUT/COLMOD/MADCTL/DISPON） */
static esp_err_t st7789_apply_boe_gamma(void)
{
    const uint8_t b2[] = {0x0C, 0x0C, 0x00, 0x33, 0x33};
    const uint8_t d0[] = {0xA4, 0xA1};
    const uint8_t e0[] = {0xD0, 0x0A, 0x10, 0x0C, 0x0C, 0x18, 0x35, 0x43, 0x4D,
                          0x39, 0x13, 0x13, 0x2D, 0x34};
    const uint8_t e1[] = {0xD0, 0x05, 0x0B, 0x06, 0x05, 0x02, 0x35, 0x43, 0x4D,
                          0x16, 0x15, 0x15, 0x2E, 0x32};

    ESP_RETURN_ON_ERROR(panel_tx_param(0xB2, b2, sizeof(b2)), TAG, "cmd B2 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0x35, (uint8_t[]){0x00}, 1), TAG, "cmd 35 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xB7, (uint8_t[]){0x35}, 1), TAG, "cmd B7 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xBB, (uint8_t[]){0x34}, 1), TAG, "cmd BB failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xC0, (uint8_t[]){0x2C}, 1), TAG, "cmd C0 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xC2, (uint8_t[]){0x01}, 1), TAG, "cmd C2 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xC3, (uint8_t[]){0x13}, 1), TAG, "cmd C3 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xC4, (uint8_t[]){0x20}, 1), TAG, "cmd C4 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xC6, (uint8_t[]){0x0F}, 1), TAG, "cmd C6 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xD0, d0, sizeof(d0)), TAG, "cmd D0 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xD6, (uint8_t[]){0xA1}, 1), TAG, "cmd D6 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xE0, e0, sizeof(e0)), TAG, "cmd E0 failed");
    ESP_RETURN_ON_ERROR(panel_tx_param(0xE1, e1, sizeof(e1)), TAG, "cmd E1 failed");
    return ESP_OK;
}

static void backlight_on(void)
{
    gpio_config_t bl_cfg = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << LCD_PIN_BL,
    };
    gpio_config(&bl_cfg);
    gpio_set_level(LCD_PIN_BL, LCD_BL_ON_LEVEL);
}

esp_lcd_panel_io_handle_t st7789_lcd_io(void)
{
    return s_io;
}

esp_lcd_panel_handle_t st7789_lcd_panel(void)
{
    return s_panel;
}

esp_err_t st7789_lcd_init(void)
{
    backlight_on();

    spi_bus_config_t buscfg = {
        .sclk_io_num = LCD_PIN_SCLK,
        .mosi_io_num = LCD_PIN_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_H_RES * LCD_V_RES * sizeof(uint16_t),
    };
    ESP_RETURN_ON_ERROR(spi_bus_initialize(LCD_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO), TAG,
                        "spi_bus_initialize failed");

    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = LCD_PIN_DC,
        .cs_gpio_num = LCD_PIN_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    ESP_RETURN_ON_ERROR(
        esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_SPI_HOST, &io_config, &s_io), TAG,
        "panel_io_spi failed");

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = LCD_PIN_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_st7789(s_io, &panel_config, &s_panel), TAG,
                        "new_panel_st7789 failed");

    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(s_panel), TAG, "panel_reset failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(s_panel), TAG, "panel_init failed");
    ESP_RETURN_ON_ERROR(st7789_apply_boe_gamma(), TAG, "boe gamma failed");

    ESP_RETURN_ON_ERROR(esp_lcd_panel_set_gap(s_panel, LCD_X_GAP, LCD_Y_GAP), TAG, "set_gap failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_swap_xy(s_panel, LCD_SWAP_XY), TAG, "swap_xy failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_mirror(s_panel, LCD_MIRROR_X, LCD_MIRROR_Y), TAG,
                        "mirror failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_invert_color(s_panel, LCD_INVERT_COLOR), TAG,
                        "invert failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(s_panel, true), TAG, "disp_on failed");

    ESP_LOGI(TAG, "ST7789V2 %dx%d ready", LCD_H_RES, LCD_V_RES);
    return ESP_OK;
}

uint16_t st7789_rgb565_swap(uint16_t rgb565)
{
    return (rgb565 >> 8) | (rgb565 << 8);
}

esp_err_t st7789_lcd_blit(int x, int y, int w, int h, const uint16_t *pixels)
{
    ESP_RETURN_ON_FALSE(x >= 0 && y >= 0 && w > 0 && h > 0, ESP_ERR_INVALID_ARG, TAG,
                        "invalid blit rect");
    ESP_RETURN_ON_FALSE(x + w <= LCD_H_RES && y + h <= LCD_V_RES, ESP_ERR_INVALID_ARG, TAG,
                        "blit out of bounds");
    return esp_lcd_panel_draw_bitmap(s_panel, x, y, x + w, y + h, pixels);
}

esp_err_t st7789_lcd_fill_rect(int x, int y, int w, int h, uint16_t rgb565)
{
    ESP_RETURN_ON_FALSE(w > 0 && h > 0, ESP_ERR_INVALID_ARG, TAG, "invalid rect");
    const size_t line_bytes = (size_t)w * sizeof(uint16_t);
    uint16_t *line = heap_caps_malloc(line_bytes, MALLOC_CAP_DMA);
    ESP_RETURN_ON_FALSE(line, ESP_ERR_NO_MEM, TAG, "line alloc failed");

    const uint16_t pixel = st7789_rgb565_swap(rgb565);
    for (int i = 0; i < w; i++) {
        line[i] = pixel;
    }
    for (int row = 0; row < h; row++) {
        ESP_RETURN_ON_ERROR(esp_lcd_panel_draw_bitmap(s_panel, x, y + row, x + w, y + row + 1, line),
                            TAG, "fill_rect row %d failed", row);
    }
    heap_caps_free(line);
    return ESP_OK;
}

esp_err_t st7789_lcd_fill_color(uint16_t rgb565)
{
    const size_t line_bytes = LCD_H_RES * sizeof(uint16_t);
    uint16_t *line = heap_caps_malloc(line_bytes, MALLOC_CAP_DMA);
    ESP_RETURN_ON_FALSE(line, ESP_ERR_NO_MEM, TAG, "line buffer alloc failed");

    const uint16_t pixel = st7789_rgb565_swap(rgb565);
    for (int x = 0; x < LCD_H_RES; x++) {
        line[x] = pixel;
    }

    for (int y = 0; y < LCD_V_RES; y++) {
        ESP_RETURN_ON_ERROR(
            esp_lcd_panel_draw_bitmap(s_panel, 0, y, LCD_H_RES, y + 1, line), TAG,
            "draw_bitmap line %d failed", y);
    }

    heap_caps_free(line);
    return ESP_OK;
}
