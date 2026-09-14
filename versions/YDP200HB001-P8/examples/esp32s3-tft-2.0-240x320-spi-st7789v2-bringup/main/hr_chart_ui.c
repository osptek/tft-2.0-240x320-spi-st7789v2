#include "hr_chart_ui.h"

#include <stdio.h>
#include <stdlib.h>

#include "board_config.h"
#include "esp_random.h"
#include "lvgl.h"

#define CHART_POINTS    120
#define HEADER_H        62
#define TICK_MS         100

#define C_SCR_BG        lv_color_hex(0x0B0E0B)
#define C_HEADER_BG     lv_color_hex(0x121812)
#define C_PANEL_BG      lv_color_hex(0x060A06)
#define C_PANEL_BORDER  lv_color_hex(0x243024)
#define C_DIVIDER       lv_color_hex(0x1C261C)
#define C_GRID          lv_color_hex(0x162216)
#define C_TRACE         lv_color_hex(0x39FF14)
#define C_TEXT          lv_color_hex(0xB8C8B8)
#define C_SUBTEXT       lv_color_hex(0x5A6A5A)
#define C_UP          lv_color_hex(0xFF4D4F)
#define C_DOWN        lv_color_hex(0x3DD68C)

#define PRICE_MIN       80
#define PRICE_MAX       920
#define PRICE_SCALE     10

static lv_obj_t *s_chart;
static lv_chart_series_t *s_series;
static lv_obj_t *s_lbl_price;
static lv_obj_t *s_lbl_chg;

static int32_t s_price_fp = 500;
static int32_t s_open_fp = 500;
static int8_t s_trend = 0;
static int s_trend_ticks = 0;

static int32_t next_stock_value(void)
{
    if (s_trend_ticks <= 0) {
        s_trend = (int8_t)((esp_random() % 5) - 2);
        s_trend_ticks = 5 + (int)(esp_random() % 10);
    }
    s_trend_ticks--;

    int32_t step = s_trend * 6 + ((int32_t)(esp_random() % 7) - 3) * 5;
    if ((esp_random() % 8) == 0) {
        step += ((int32_t)(esp_random() % 11) - 5) * 8;
    }

    s_price_fp += step;
    if (s_price_fp < PRICE_MIN) {
        s_price_fp = PRICE_MIN;
        s_trend = 1;
        s_trend_ticks = 4;
    } else if (s_price_fp > PRICE_MAX) {
        s_price_fp = PRICE_MAX;
        s_trend = -1;
        s_trend_ticks = 4;
    }

    return s_price_fp / PRICE_SCALE;
}

static void update_quote_labels(void)
{
    const int32_t diff = s_price_fp - s_open_fp;
    const int pct_x10 = (int)((diff * 1000) / s_open_fp);

    char price_buf[16];
    char chg_buf[16];
    snprintf(price_buf, sizeof(price_buf), "%d.%d", (int)(s_price_fp / PRICE_SCALE),
             (int)abs((int)((s_price_fp % PRICE_SCALE) * 10 / PRICE_SCALE)));

    const lv_color_t quote_color = (diff >= 0) ? C_UP : C_DOWN;
    if (pct_x10 >= 0) {
        snprintf(chg_buf, sizeof(chg_buf), "+%d.%d%%", pct_x10 / 10, abs(pct_x10 % 10));
    } else {
        snprintf(chg_buf, sizeof(chg_buf), "%d.%d%%", pct_x10 / 10, abs(pct_x10 % 10));
    }

    lv_label_set_text(s_lbl_price, price_buf);
    lv_label_set_text(s_lbl_chg, chg_buf);
    lv_obj_set_style_text_color(s_lbl_price, quote_color, 0);
    lv_obj_set_style_text_color(s_lbl_chg, quote_color, 0);
}

static void stock_timer_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    lv_chart_set_next_value(s_chart, s_series, next_stock_value());
    update_quote_labels();
}

void hr_chart_ui_create(void)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, C_SCR_BG, 0);
    lv_obj_set_style_pad_all(scr, 0, 0);

    /* 顶栏 */
    lv_obj_t *header = lv_obj_create(scr);
    lv_obj_set_size(header, LCD_H_RES, HEADER_H);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, C_HEADER_BG, 0);
    lv_obj_set_style_border_width(header, 0, 0);
    lv_obj_remove_flag(header, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *lbl_code = lv_label_create(header);
    lv_label_set_text(lbl_code, "DEMO");
    lv_obj_set_style_text_color(lbl_code, C_TEXT, 0);
    lv_obj_set_style_text_font(lbl_code, &lv_font_montserrat_14, 0);
    lv_obj_align(lbl_code, LV_ALIGN_LEFT_MID, 10, -10);

    lv_obj_t *lbl_sub = lv_label_create(header);
    lv_label_set_text(lbl_sub, "MIN");
    lv_obj_set_style_text_color(lbl_sub, C_SUBTEXT, 0);
    lv_obj_set_style_text_font(lbl_sub, &lv_font_montserrat_14, 0);
    lv_obj_align(lbl_sub, LV_ALIGN_LEFT_MID, 10, 10);

    s_lbl_price = lv_label_create(header);
    lv_label_set_text(s_lbl_price, "50.0");
    lv_obj_set_style_text_color(s_lbl_price, C_UP, 0);
    lv_obj_set_style_text_font(s_lbl_price, &lv_font_montserrat_14, 0);
    lv_obj_align(s_lbl_price, LV_ALIGN_RIGHT_MID, -10, -10);

    s_lbl_chg = lv_label_create(header);
    lv_label_set_text(s_lbl_chg, "+0.0%");
    lv_obj_set_style_text_color(s_lbl_chg, C_UP, 0);
    lv_obj_set_style_text_font(s_lbl_chg, &lv_font_montserrat_14, 0);
    lv_obj_align(s_lbl_chg, LV_ALIGN_RIGHT_MID, -10, 10);

    /* 分隔线 */
    lv_obj_t *divider = lv_obj_create(scr);
    lv_obj_set_size(divider, LCD_H_RES, 1);
    lv_obj_align(divider, LV_ALIGN_TOP_MID, 0, HEADER_H);
    lv_obj_set_style_bg_color(divider, C_DIVIDER, 0);
    lv_obj_set_style_border_width(divider, 0, 0);
    lv_obj_set_style_pad_all(divider, 0, 0);
    lv_obj_remove_flag(divider, LV_OBJ_FLAG_SCROLLABLE);

    /* 图表面板 */
    const int panel_h = LCD_V_RES - HEADER_H - 14;
    lv_obj_t *panel = lv_obj_create(scr);
    lv_obj_set_size(panel, LCD_H_RES - 12, panel_h);
    lv_obj_align(panel, LV_ALIGN_BOTTOM_MID, 0, -6);
    lv_obj_set_style_bg_color(panel, C_PANEL_BG, 0);
    lv_obj_set_style_border_color(panel, C_PANEL_BORDER, 0);
    lv_obj_set_style_border_width(panel, 1, 0);
    lv_obj_set_style_radius(panel, 8, 0);
    lv_obj_set_style_pad_all(panel, 6, 0);
    lv_obj_remove_flag(panel, LV_OBJ_FLAG_SCROLLABLE);

    s_chart = lv_chart_create(panel);
    lv_obj_set_width(s_chart, lv_pct(100));
    lv_obj_set_height(s_chart, lv_pct(100));
    lv_chart_set_type(s_chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(s_chart, CHART_POINTS);
    lv_chart_set_axis_range(s_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    lv_chart_set_update_mode(s_chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_div_line_count(s_chart, 5, 10);

    lv_obj_set_style_bg_color(s_chart, C_PANEL_BG, 0);
    lv_obj_set_style_border_width(s_chart, 0, 0);
    lv_obj_set_style_pad_all(s_chart, 2, 0);
    lv_obj_set_style_radius(s_chart, 4, 0);
    lv_obj_set_style_line_color(s_chart, C_GRID, LV_PART_MAIN);
    lv_obj_set_style_line_width(s_chart, 1, LV_PART_MAIN);
    lv_obj_set_style_line_opa(s_chart, LV_OPA_60, LV_PART_MAIN);
    lv_obj_set_style_line_color(s_chart, C_TRACE, LV_PART_ITEMS);
    lv_obj_set_style_line_width(s_chart, 1, LV_PART_ITEMS);
    lv_obj_set_style_line_opa(s_chart, LV_OPA_COVER, LV_PART_ITEMS);
    lv_obj_set_style_size(s_chart, 0, 0, LV_PART_INDICATOR);
    lv_obj_remove_flag(s_chart, LV_OBJ_FLAG_SCROLLABLE);

    s_series = lv_chart_add_series(s_chart, C_TRACE, LV_CHART_AXIS_PRIMARY_Y);
    s_open_fp = s_price_fp;
    lv_chart_set_all_values(s_chart, s_series, s_price_fp / PRICE_SCALE);
    update_quote_labels();

    lv_timer_create(stock_timer_cb, TICK_MS, NULL);
}
