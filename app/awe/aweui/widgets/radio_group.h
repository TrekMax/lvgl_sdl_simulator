/**
 * @file radio_group.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __RADIO_GROUP_H__
#define __RADIO_GROUP_H__

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

LV_FONT_DECLARE(lv_font_chinese_14);
LV_FONT_DECLARE(lv_font_chinese_18);
LV_FONT_DECLARE(lv_font_chinese_26);

lv_obj_t * ls_lv_radio_group_create(lv_obj_t * parent, lv_event_cb_t event_cb, void * user_data);
lv_obj_t * ls_lv_radio_group_add(lv_obj_t * group, const char * txt,
    const char * tips_text, lv_event_cb_t event_cb, void * user_data);


void ls_lv_radio_group_example(lv_obj_t * parent);



#endif // __RADIO_GROUP_H__
