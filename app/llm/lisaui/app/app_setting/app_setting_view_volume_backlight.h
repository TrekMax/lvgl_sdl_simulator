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
#ifndef __APP_SETTING_VIEW_VOLUME_BACKLIGHT_H__
#define __APP_SETTING_VIEW_VOLUME_BACKLIGHT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lisaui_app_common.h"

typedef int (*ui_get_battery_cb_t)(uint8_t *state, uint8_t *level);
typedef int (*ui_set_backlight_cb_t)(const uint8_t brightness);
typedef int (*ui_set_volume_cb_t)(const uint8_t volume);

lv_obj_t * _lisaui_app_view_create_volume_backlight(lv_obj_t *parent);

void ui_register_set_backlight_cb(ui_set_backlight_cb_t update_handler);
void ui_register_set_volume_cb(ui_set_volume_cb_t update_handler);


#ifdef __cplusplus
}
#endif

#endif // __APP_SETTING_VIEW_VOLUME_BACKLIGHT_H__
