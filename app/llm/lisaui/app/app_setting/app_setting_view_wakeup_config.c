/**
 * @file app_setting_view_wakeup_config.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-04-15
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_setting_view_wakeup_config.h"

#include "app_setting.h"
#include "assets/assets_res.h"
#include "lisaui_app_common.h"
#include "lv_img_utils.h"

// #include "base/ls_radio_group.h"
#include "widgets_common.h"

static const char *TAG = "app_setting_view_wakeup_config";

lv_obj_t *_lisaui_app_view_create_wakeup_config(lv_obj_t *parent)
{
    lv_obj_t *setting_home = lv_obj_create(parent);
    lv_obj_set_size(setting_home, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(setting_home, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(setting_home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(setting_home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(setting_home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(setting_home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(setting_home, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_add_flag(setting_home, LV_OBJ_FLAG_EVENT_BUBBLE);

    // setting_home = lv_obj_create(parent);
    // lv_obj_remove_style_all(setting_home);
    // lv_obj_clear_flag(setting_home, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    // // lv_obj_set_style_bg_color(setting_home, lv_color_hex(0x242430), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(setting_home, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(setting_home, 250, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_size(setting_home, LV_PCT(100), LV_PCT(100));

    ls_lv_radio_group_example(setting_home);
    return setting_home;
}
