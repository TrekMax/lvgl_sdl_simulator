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

#if defined(__LVGL_SIMULATOR__)
#ifndef LV_CONF_PATH
#define LV_CONF_PATH ../../../include/lv_conf.h
#endif
#endif

#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#elif defined(__LVGL_SIMULATOR__)
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif

#include "incbin.h"
#include "lisaui_type.h"
#include "../widgets/assets/assets_res.h"

#include "lisaui_app_manager.h"
#include "lisaui_view_manager.h"
#include "lisaui_dbus.h"
#include "lisaui_log.h"

#if defined(__LVGL_SIMULATOR__)
#else
#include "FreeRTOS.h"
#include "semphr.h"
#endif
#include <stdlib.h>
#include <string.h>

#define CONFIG_LISAUI_FONT_LANGUAGE_ZH_CN_ENABLE 1

#define LISAUI_LV_COLOR_RED   lv_color_hex(0xFF0000)
#define LISAUI_LV_COLOR_GREEN lv_color_hex(0x00FF00)
#define LISAUI_LV_COLOR_BLUE  lv_color_hex(0x0000FF)
#define LISAUI_LV_COLOR_WHITE lv_color_hex(0xFFFFFF)
#define LISAUI_LV_COLOR_BLACK lv_color_hex(0x000000)

#define LISAUI_LV_COLOR_BG_BLACK           lv_color_hex(0x212429)
#define LISAUI_LV_COLOR_BG_ICON_BLACK      lv_color_hex(0x1f1f1f)
#define LISAUI_LV_COLOR_BG_ICON_GRAY       lv_color_hex(0x181818)
#define LISAUI_LV_COLOR_BG_ICON_GRAY_LIGHT lv_color_hex(0x2f2f2f)
#define LISAUI_LV_COLOR_BG_ICON_GRAY_DARK  lv_color_hex(0x0f0f0f)

#define LISAUI_LV_COLOR_GRAY_GREEN lv_color_hex(0x003000)
#define LISAUI_LV_COLOR_GRAY_BLUE  lv_color_hex(0x0000C0)

#define lisaui_malloc malloc
#define lisaui_free   free

#define LISAUI_DBUS_APP_UPDATE   "app_update"
#define LISAUI_DBUS_APP_LAUNCHER "app_launcher"
#define LISAUI_DBUS_APP_ENTER    "app_enter"
#define LISAUI_DBUS_APP_EXIT     "app_exit"
#define RES_PERFIX_PATH(res)     "app/app_manager/" res

#define LISAUI_STATUS_BAR_HEIGHT       40
#define CONFIG_LISAUI_EXEC_HOOK_ENABLE 1

#if defined(__LVGL_SIMULATOR__)
#define LVGL_UI_LOCK()                                                                                                 \
    do {                                                                                                               \
    } while (0)

#define LVGL_UI_UNLOCK()                                                                                               \
    do {                                                                                                               \
    } while (0)

#else
extern SemaphoreHandle_t lvgl_mutex;

#define LVGL_UI_LOCK()                                                                                                 \
    do {                                                                                                               \
        xSemaphoreTakeRecursive(lvgl_mutex, portMAX_DELAY);                                                            \
    } while (0)
#define LVGL_UI_UNLOCK()                                                                                               \
    do {                                                                                                               \
        xSemaphoreGiveRecursive(lvgl_mutex);                                                                           \
    } while (0)
#endif

#define LVGL_OBJ_SAFE_DEL(obj)                                                                                         \
    do {                                                                                                               \
        if (obj) {                                                                                                     \
            lv_obj_del(obj);                                                                                           \
            obj = NULL;                                                                                                \
        }                                                                                                              \
    } while (0)

lisaui_err_t _lisaui_set_style_container(lv_obj_t *obj, lv_color_t bg_color, lv_opa_t bg_opa, lv_color_t border_color,
                                         lv_coord_t border_width, lv_coord_t radius);
lisaui_err_t _lisaui_lv_obj_set_default_style(lv_obj_t *obj);
lisaui_err_t _lisaui_lv_obj_set_btn_custom_style(lv_obj_t *obj);

lisaui_err_t lisaui_popup_toast(const char *message);
void lisaui_memory_monitor(void *param);

#ifdef __cplusplus
}
#endif

#endif /* __LISAUI_APP_COMMON_H__ */