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
#include "ls_radio_group.h"

#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#define LOG_INF LV_LOG_USER
#endif
typedef struct {
    lv_obj_t *radio_bg;
    lv_obj_t *radio;
    uint16_t radio_id;
    lv_obj_t *tip_text;
    lv_event_cb_t event_cb;
    void *user_data;
} radio_group_t;

#define RADIO_GROUP_MAX 10

static lv_style_t style_radio;
static lv_style_t style_radio_chk;
static radio_group_t radio_group[RADIO_GROUP_MAX];
static uint16_t radio_group_index = 0;
// static uint16_t active_radio_id = 0;
// static uint16_t active_radio_id_old = 0;

lv_obj_t *ls_lv_radio_group_create(lv_obj_t *parent, lv_event_cb_t event_cb, void *user_data)
{
    radio_group_index = 0;
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
    return radio_group;
}

void radio_group_bg_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (LV_EVENT_CLICKED == code) {
        uint16_t radio_id = 0;
        radio_id = *(uint16_t *)lv_event_get_user_data(e);
        // TODO: 需要优化为选中与期待选择两个 id，不使用遍历方式
        for (int i = 0; i < radio_group_index; i++) {
            lv_obj_clear_state(radio_group[i].radio, LV_STATE_CHECKED);
        }
        lv_obj_add_state(radio_group[radio_id].radio, LV_STATE_CHECKED);
        if (radio_group[radio_id].event_cb) {
            radio_group[radio_id].event_cb(e);
        }
    }
}

int lv_lv_radio_group_set_active_id(lv_obj_t *group, uint16_t id)
{
    if (id >= radio_group_index) {
        return -1;
    }
    for (int i = 0; i < radio_group_index; i++) {
        lv_obj_clear_state(radio_group[i].radio, LV_STATE_CHECKED);
    }
    lv_obj_add_state(radio_group[id].radio, LV_STATE_CHECKED);
    return 0;
}

lv_obj_t *ls_lv_radio_group_add(lv_obj_t *group, const char *txt, const char *tips_text, lv_event_cb_t event_cb,
                                void *user_data)
{
    lv_obj_t *parent = group;
    lv_obj_t *radio_bg = lv_obj_create(group);
    lv_obj_set_size(radio_bg, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_border_width(radio_bg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(radio_bg, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_size(radio_bg, lv_pct(100), LV_SIZE_CONTENT);
    // lv_obj_set_flex_flow(radio_bg, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_bg_color(radio_bg, lv_color_hex(0x24242f), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *obj = lv_checkbox_create(radio_bg);

    radio_group[radio_group_index].radio_bg = radio_bg;
    radio_group[radio_group_index].radio = obj;
    radio_group[radio_group_index].radio_id = radio_group_index;
    radio_group[radio_group_index].event_cb = event_cb;
    lv_obj_add_event_cb(radio_bg, radio_group_bg_event_handler, LV_EVENT_CLICKED,
                        (void *)&radio_group[radio_group_index].radio_id);
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
    lv_obj_set_style_text_font(tip_text, &lv_font_notosans_cs_medium_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tip_text, lv_color_hex(0xBCBCBC), LV_PART_MAIN | LV_STATE_DEFAULT);

    radio_group[radio_group_index].tip_text = tip_text;
    radio_group_index++;
    return obj;
}

void ls_lv_radio_group_example(lv_obj_t *parent)
{
    lv_obj_t *radio_group = ls_lv_radio_group_create(parent, NULL, NULL);

    ls_lv_radio_group_add(radio_group, "Option 1", "This is option 1", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 2", "This is option 2. Option 2 is a long text", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 3", "This is option 3", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 4", "This is option 4. Option 4 is a long text and it is a long text",
                          NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 5", "This is option 5", NULL, NULL);
    ls_lv_radio_group_add(radio_group, "Option 6", "This is option 6", NULL, NULL);
}