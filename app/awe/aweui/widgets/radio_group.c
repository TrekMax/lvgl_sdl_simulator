/**
 * @file radio_group.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "radio_group.h"

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#include "aweui_resources.h"

static lv_style_t style_radio;
static lv_style_t style_radio_chk;
static lv_event_cb_t radio_group_event_cb;

static uint32_t active_index_1 = 0;
static uint32_t active_index_2 = 0;

static void radio_group_event_handler(lv_event_t * e)
{
    uint32_t * active_id = lv_event_get_user_data(e);
    lv_obj_t * cont = lv_event_get_current_target(e);
    lv_obj_t * act_cb = lv_event_get_target(e);
    LV_LOG_USER("active_id: %d", *active_id);
    lv_obj_t * old_cb = lv_obj_get_child(cont, *active_id);
    /*Do nothing if the container was clicked*/
    if(act_cb == cont) return;

    lv_obj_clear_state(old_cb, LV_STATE_CHECKED);   /*Uncheck the previous radio button*/
    lv_obj_add_state(act_cb, LV_STATE_CHECKED);     /*Uncheck the current radio button*/


    *active_id = lv_obj_get_index(act_cb);

    LV_LOG_USER("Selected radio buttons: %d, %d", (int)active_index_1, (int)active_index_2);
    if (radio_group_event_cb) {
        radio_group_event_cb(e);
    }
}


lv_obj_t * ls_lv_radio_group_create(lv_obj_t * parent, lv_event_cb_t event_cb, void * user_data)
{
    lv_style_init(&style_radio);
    lv_style_set_radius(&style_radio, LV_RADIUS_CIRCLE);

    lv_obj_t *radio_group = lv_obj_create(parent);
    lv_obj_set_size(radio_group, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_flow(radio_group, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_border_width(radio_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(radio_group, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(radio_group, 0, 0);
    lv_obj_set_style_pad_all(parent, 0, 0);
    lv_obj_set_style_bg_color(radio_group, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_top(parent, 10, 0);

    // radio_group_event_cb = event_cb;
    // lv_obj_add_event_cb(radio_group, radio_event_handler, LV_EVENT_CLICKED, &active_index_1);
    // lv_obj_set_style_text_font(radio_group, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(radio_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    return radio_group;
}


static void radio_event_handler(lv_event_t * e)
{
    uint32_t * active_id = lv_event_get_user_data(e);
    LV_LOG_USER("active_id: %d", *active_id);
    lv_obj_t * cont = lv_event_get_current_target(e);
    lv_obj_t * act_cb = lv_event_get_target(e);
    lv_obj_t * old_cb = lv_obj_get_child(lv_obj_get_child(cont, *active_id), 0);

    /*Do nothing if the container was clicked*/
    if(act_cb == cont) return;

    lv_obj_clear_state(old_cb, LV_STATE_CHECKED);   /*Uncheck the previous radio button*/
    lv_obj_add_state(act_cb, LV_STATE_CHECKED);     /*Uncheck the current radio button*/

    *active_id = lv_obj_get_index(act_cb);

    LV_LOG_USER("Selected radio buttons: %d, %d", (int)active_index_1, (int)active_index_2);
}
lv_obj_t * parent = NULL;

void radio_group_bg_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (LV_EVENT_CLICKED == code) {
        lv_obj_t * obj = lv_event_get_user_data(e);
        // lv_obj_add_state(lv_obj_get_child(lv_obj_get_child(parent, 0), 0), LV_STATE_CHECKED);
        if (lv_obj_get_state(obj) & LV_STATE_CHECKED) {
            // LV_LOG_USER("lv_obj_clear_state, LV_STATE_CHECKED");
            lv_obj_clear_state(obj, LV_STATE_CHECKED);
        } else {
            // LV_LOG_USER("lv_obj_add_state, LV_STATE_CHECKED");
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
    }
}
static uint16_t radio_group_index = 0;

lv_obj_t * ls_lv_radio_group_add(lv_obj_t * group, const char * txt,
    const char * tips_text, lv_event_cb_t event_cb, void * user_data)
{
    lv_obj_t * radio_bg = lv_obj_create(group);
    parent = group;
    lv_obj_set_size(radio_bg, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_border_width(radio_bg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(radio_bg, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_size(radio_bg, lv_pct(100), LV_SIZE_CONTENT);
    // lv_obj_set_flex_flow(radio_bg, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_bg_color(radio_bg, lv_color_hex(0x24242f), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t * obj = lv_checkbox_create(radio_bg);

    lv_obj_add_event_cb(radio_bg, radio_group_bg_event_handler, LV_EVENT_ALL, (void *)obj);

    lv_obj_set_style_text_color(radio_bg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(obj, lv_pct(80), LV_SIZE_CONTENT);

    lv_checkbox_set_text(obj, txt);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_style(obj, &style_radio, LV_PART_INDICATOR);
    lv_obj_add_style(obj, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *tip_text = lv_label_create(radio_bg);

    lv_obj_align_to(tip_text, obj, LV_ALIGN_BOTTOM_LEFT, 30, 25);
    lv_obj_set_size(tip_text, lv_pct(80), LV_SIZE_CONTENT);

    lv_label_set_text(tip_text, tips_text);
    lv_obj_set_style_text_font(tip_text, &lv_font_chinese_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tip_text, lv_color_hex(0xBCBCBC), LV_PART_MAIN | LV_STATE_DEFAULT);
    return obj;
}


void ls_lv_radio_group_example(lv_obj_t * parent)
{
    lv_obj_t * radio_group = ls_lv_radio_group_create(parent, NULL, NULL);

    ls_lv_radio_group_add(radio_group, "Option 1", "This is option 1", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 2", "This is option 2. Option 2 is a long text", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 3", "This is option 3", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 4", "This is option 4. Option 4 is a long text and it is a long text", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 5", "This is option 5", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 6", "This is option 6", NULL, NULL);
}