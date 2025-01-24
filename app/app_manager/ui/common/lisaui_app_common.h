/**
 * @file app_common.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_APP_COMMON_H__
#define __LISAUI_APP_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LV_CONF_PATH
#define LV_CONF_PATH ../../../include/lv_conf.h
#endif

#include "lvgl/lvgl.h"
#include "lisaui_type.h"

#include "../app/app_common.h"
#include "../assets/assets_res.h"

#include "lisaui_app_manager.h"
#include "lisaui_view_manager.h"

#include "lisaui_dbus.h"

#include <stdlib.h>
#include <string.h>

// #define LOG_LEVEL         LOG_VERBOSE
// #define CONFIG_LOG_COLORS 1
// #define CONFIG_LOG_ENABLE 1
// #define CLOG_ENABLE       1

#include "utils_log.h"

#ifdef CONFIG_LOG_ENABLE
#ifdef CLOG_ENABLE
#define LISAUI_PRINTK(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define LISAUI_LOGE             LOGE
#define LISAUI_LOGW             LOGW
#define LISAUI_LOGI             LOGI
#define LISAUI_LOGD             LOGD
#define LISAUI_LOGV             LOGV
#else

#endif
#else
#define LISAUI_LOGE(TAG, fmt, ...) printf("E:" fmt, ##__VA_ARGS__)
#define LISAUI_LOGW(TAG, fmt, ...) printf("W:" fmt, ##__VA_ARGS__)
#define LISAUI_LOGI(TAG, fmt, ...) printf("I:" fmt, ##__VA_ARGS__)
#define LISAUI_LOGD(TAG, fmt, ...) printf("D:" fmt, ##__VA_ARGS__)
#define LISAUI_LOGV(TAG, fmt, ...) printf("V:" fmt, ##__VA_ARGS__)
#endif

#define LISAUI_LV_COLOR_RED   lv_color_hex(0xFF0000)
#define LISAUI_LV_COLOR_GREEN lv_color_hex(0x00FF00)
#define LISAUI_LV_COLOR_BLUE  lv_color_hex(0x0000FF)
#define LISAUI_LV_COLOR_WHITE lv_color_hex(0xFFFFFF)
#define LISAUI_LV_COLOR_BLACK lv_color_hex(0x000000)

#define lisaui_malloc malloc
#define lisaui_free   free

#define LISAUI_DBUS_APP_UPDATE   "app_update"
#define LISAUI_DBUS_APP_LAUNCHER "app_launcher"
#define LISAUI_DBUS_APP_ENTER    "app_enter"
#define LISAUI_DBUS_APP_EXIT     "app_exit"
#define RES_PERFIX_PATH(res)     "app/pendict/" res

#define LISAUI_STATUS_BAR_HEIGHT 30

lisaui_err_t _lisaui_set_style_container(lv_obj_t *obj, lv_color_t bg_color, lv_opa_t bg_opa, lv_color_t border_color,
                                         lv_coord_t border_width, lv_coord_t radius);
lisaui_err_t _lisaui_lv_obj_set_default_style(lv_obj_t *obj);
lisaui_err_t _lisaui_lv_obj_set_btn_custom_style(lv_obj_t *obj);

lisaui_err_t lisaui_app_create_toast(const char *message);

#ifdef __cplusplus
}
#endif

#endif /* __LISAUI_APP_COMMON_H__ */