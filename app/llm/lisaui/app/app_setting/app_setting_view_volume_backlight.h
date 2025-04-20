/**
 * @file app_setting_view_volume_backlight.h
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-15
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_APP_SETTING_VIEW_VOLUME_BACKLIGHT_H__
#define __LISAUI_APP_SETTING_VIEW_VOLUME_BACKLIGHT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lisaui_app_common.h"

typedef int (*lisaui_app_setting_set_backlight_cb_t)(const uint8_t brightness);
typedef int (*lisaui_app_setting_set_volume_cb_t)(const uint8_t volume);
lisaui_err_t lisaui_app_setting_register_set_backlight_handler(lisaui_app_setting_set_backlight_cb_t handler);
lisaui_err_t lisaui_app_setting_register_set_volume_handler(lisaui_app_setting_set_backlight_cb_t handler);

lv_obj_t * private_lisaui_app_view_create_volume_backlight(lv_obj_t *parent);

#ifdef __cplusplus
}
#endif

#endif // __LISAUI_APP_SETTING_VIEW_VOLUME_BACKLIGHT_H__
