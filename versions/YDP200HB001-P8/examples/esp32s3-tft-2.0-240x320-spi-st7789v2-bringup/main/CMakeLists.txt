idf_component_register(SRCS "main.c" "st7789_lcd.c" "lvgl_port.c" "hr_chart_ui.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_lcd driver esp_lvgl_port)
