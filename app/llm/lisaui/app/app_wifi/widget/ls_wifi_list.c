/**
 * @file ls_wifi_list.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-04-20
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ls_wifi_list.h"
#include <src/widgets/lv_label.h>
#include "lv_img_utils.h"
#include "incbin.h"

static lv_img_dsc_t img_wifi_status;

#if CONFIG_LVGL_ENV_SIMULATOR
#define LISAUI_APP_LS_LLM_DIALOG_UI_RES_PERFIX_PATH(path) "app/llm/lisaui/app/app_wifi/" path
#else
#define LISAUI_APP_LS_LLM_DIALOG_UI_RES_PERFIX_PATH(path) "src/ui/lisaui/app/app_wifi/" path
// app/llm/lisaui/widgets/assets/gif/ani_talk.gif
// app/llm/lisaui/app/app_wifi/assets/png/ic_status_wifi0.png
#endif

UI_RES_IMG_NAME(wifi_status, LISAUI_APP_LS_LLM_DIALOG_UI_RES_PERFIX_PATH("assets/png/ic_status_wifi4.png"))
// UI_RES_IMG_NAME(ani_talk, LISAUI_APP_LS_LLM_DIALOG_UI_RES_PERFIX_PATH("assets/gif/ani_talk.gif"))

#define MV_CLASS &ls_wifi_list

const lv_obj_class_t ls_wifi_list_class = {
    .base_class = &lv_obj_class, .width_def = (LV_DPI_DEF * 3) / 2, .height_def = LV_DPI_DEF * 2};

const lv_obj_class_t ls_wifi_list_btn_class = {
    .base_class = &lv_obj_class,
};

const lv_obj_class_t ls_wifi_list_text_class = {
    .base_class = &lv_label_class,
};

lv_obj_t *ls_wifi_list_create(lv_obj_t *parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t *list_panel = lv_obj_create(parent);
    lv_obj_set_size(list_panel, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(list_panel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_border_width(list_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(list_panel, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(list_panel, 0, 0);
    // lv_obj_set_style_pad_all(parent, 0, 0);
    lv_obj_set_style_bg_color(list_panel, lv_color_hex(0x0F0000), LV_PART_MAIN | LV_STATE_DEFAULT);

    return list_panel;
}

lv_obj_t *ls_wifi_list_add_text(lv_obj_t *list, const char *txt)
{
    LV_LOG_INFO("begin");
    lv_obj_t *obj = lv_obj_class_create_obj(&ls_wifi_list_text_class, list);
    lv_obj_class_init_obj(obj);
    lv_label_set_text(obj, txt);
    lv_label_set_long_mode(obj, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(obj, LV_PCT(100));
    lv_obj_set_height(obj, LV_DPX(40));
    lv_obj_set_style_text_font(obj, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(obj, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    return obj;
}

lv_obj_t *ls_wifi_list_add_btn(lv_obj_t *list, wifi_metadata_t *wifi, lv_event_cb_t event_cb, void *user_data)
{
    LV_LOG_INFO("begin");
    lv_obj_t *item = lv_obj_create(list);
    lv_obj_set_size(item, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_border_width(item, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(item, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(item, lv_color_hex(0x24242f), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ssid_label = lv_label_create(item);
    lv_obj_set_size(ssid_label, LV_PCT(60), LV_SIZE_CONTENT);
    lv_obj_set_style_text_color(ssid_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ssid_label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(ssid_label, wifi->SSID);
    lv_label_set_long_mode(ssid_label, LV_LABEL_LONG_SCROLL_CIRCULAR);

    lv_obj_t *op_btn = lv_btn_create(item);
    lv_obj_set_size(op_btn, LV_PCT(20), LV_SIZE_CONTENT);
    lv_obj_align(op_btn, LV_ALIGN_RIGHT_MID, LV_DPX(0), 0);
    lv_obj_set_style_bg_color(op_btn, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(op_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(op_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(op_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(op_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(op_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(op_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(op_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(op_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_t *status_icon = lv_img_create(item);
    lv_img_png_src_init(UI_RES_IMG_PNG(wifi_status));
    lv_img_set_src(status_icon, &LV_IMG_DSC(wifi_status));
    lv_obj_add_flag(status_icon, LV_OBJ_FLAG_CLICKABLE);
    // lv_obj_set_size(status_icon, LV_DPX(40), LV_DPX(40));
    lv_obj_align(status_icon, LV_ALIGN_RIGHT_MID, LV_DPX(0), 0);
    lv_obj_set_style_radius(status_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(status_icon, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(status_icon, event_cb, LV_EVENT_CLICKED, user_data);


    lv_obj_t *op_label = lv_label_create(item);
    // lv_label_set_text(op_label, wifi->status ? "已连接" : "");
    if (wifi->status == LISAUI_WIFI_STATUS_CONNECTED) {
        lv_label_set_text(op_label, "已连接");
    } else if (wifi->status == LISAUI_WIFI_STATUS_CONNECTING) {
        lv_label_set_text(op_label, "连接中");
    } else if (wifi->status == LISAUI_WIFI_STATUS_DISCONNECT) {
        lv_label_set_text(op_label, "");
    } else {
        lv_label_set_text(op_label, "连接");
    }
    // lv_obj_set_height(op_label, LV_DPX(40));
    // lv_obj_align(op_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align_to(op_label, status_icon, LV_ALIGN_OUT_LEFT_MID, -LV_DPX(40), 0);
    lv_obj_set_style_text_font(op_label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(op_label, lv_color_hex(0x2BBDA0), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_align(op_label, LV_ALIGN_RIGHT_MID, LV_DPX(0), 0);


    // lv_obj_t *rssi_label = lv_label_create(item);
    // lv_obj_set_size(rssi_label, LV_PCT(20), LV_SIZE_CONTENT);
    // lv_obj_set_style_text_color(rssi_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(rssi_label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_label_set_text(rssi_label, wifi->rssi);
    // lv_label_set_long_mode(rssi_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    // lv_obj_align(rssi_label, LV_ALIGN_RIGHT_MID, LV_DPX(0), 0);

    return item;
}
