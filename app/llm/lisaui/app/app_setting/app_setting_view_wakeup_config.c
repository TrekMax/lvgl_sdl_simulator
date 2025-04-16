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
#include "widgets_common.h"

static const char *TAG = "app_setting_view_wakeup_config";

void radio_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (LV_EVENT_CLICKED == code) {
        uint16_t radio_id = *(uint16_t *)lv_event_get_user_data(e);
    }
}

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

    uint8_t active = 0;
    lv_obj_t *page = ls_lv_radio_group_create(parent, NULL, NULL);
    ls_lv_radio_group_add(page, "按键唤醒", "通过开发板 K3 按键进行唤醒", radio_event_handler, NULL);
    ls_lv_radio_group_add(page, "语音唤醒（单轮对话）", "通过唤醒词“小美小美”唤醒，一次唤醒一轮对话",
                          radio_event_handler, NULL);
    ls_lv_radio_group_add(page, "语音唤醒（多轮对话）", "通过唤醒词“小美小美”唤醒，支持多轮对话", radio_event_handler,
                          NULL);
    lv_lv_radio_group_set_active_id(page, active);
    return setting_home;
}
