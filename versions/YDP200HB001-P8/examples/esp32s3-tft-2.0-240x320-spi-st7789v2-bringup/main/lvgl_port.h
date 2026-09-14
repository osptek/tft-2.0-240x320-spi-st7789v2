#pragma once

#include "esp_err.h"
#include "lvgl.h"

esp_err_t lvgl_port_init_all(void);
lv_display_t *lvgl_port_get_display(void);
