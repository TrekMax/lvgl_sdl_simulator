/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif
#include "aweui_screen.h"
#include "aweui_resources.h"
#include "aweui_event_inc.h"

#include "aweui_screen_network.h"

static lv_obj_t *net_home = NULL;
static lv_obj_t *net_scan = NULL;
static lv_obj_t *introduce_obj = NULL;
static lv_obj_t *scan_btn = NULL;
static lv_obj_t *net_rlt = NULL;
static lv_obj_t *network_loaing = NULL;
static lv_obj_t *load_gif = NULL;
static lv_obj_t *scan_img = NULL;
static lv_obj_t *scan_cancel_btn = NULL;
static lv_obj_t *rlt_img = NULL;
static lv_obj_t *ssid_lable = NULL;
static lv_obj_t *wifi_disconnect_btn = NULL;

static lv_img_dsc_t desc = {0};

lv_obj_t *line_floor[8];
void ui_event_network(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    LV_LOG_USER("[%d:%s] event: %X\n", __LINE__, __func__, event_code);
    lv_obj_t *obj = lv_event_get_target(e);
    if (event_code == LV_EVENT_PRESSED)
    {
        if (obj == scan_btn)
        {
            aweui_set_pull_event(AWEUI_EVENT_WIFI_QRCODE_CONNECT_SCAN, NULL);
        }
        else if (obj == scan_cancel_btn) {
            aweui_set_pull_event(AWEUI_EVENT_WIFI_QRCODE_CONNECT_CANCEL, NULL);
        }
        else if (obj == wifi_disconnect_btn) {
            aweui_set_pull_event(AWEUI_EVENT_WIFI_DISCONNECT, NULL);
        }
    }
}
lv_obj_t *aweui_network_home_create(lv_obj_t *init_pg)
{
    net_home = lv_obj_create(init_pg);
    lv_obj_remove_style_all(net_home);
    lv_obj_clear_flag(net_home, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(net_home, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(net_home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(net_home, 320);  /// 1
    lv_obj_set_height(net_home, 240); /// 1

    // 提示文本
    introduce_obj = lv_textarea_create(net_home);
    lv_obj_set_size(introduce_obj, 160, 100);
    lv_obj_set_align(introduce_obj, LV_ALIGN_RIGHT_MID);
    lv_obj_set_x(introduce_obj, 0);
    lv_obj_set_y(introduce_obj, -10);
    lv_obj_set_style_text_font(introduce_obj, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_text(introduce_obj, "网络未连接，\n请使用手机扫描");
    lv_obj_set_style_text_color(introduce_obj, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_bg_color(introduce_obj, lv_color_black(), 0);

    static lv_style_t style_rlt;
    lv_style_init(&style_rlt);
    lv_style_set_bg_color(&style_rlt, lv_color_hex(0x000000));
    // lv_style_set_bg_opa(&style_home, LV_OPA_30); /* 50%透明 */
    lv_style_set_border_width(&style_rlt, 0);
    lv_obj_add_style(introduce_obj, &style_rlt, 0);
    lv_style_set_border_color(&style_rlt, lv_color_hex(0x000000));

    // 扫描按钮
    scan_btn = lv_btn_create(net_home);
    lv_obj_set_size(scan_btn, 130, 50);
    lv_obj_set_pos(scan_btn, -25, -20);
    lv_obj_set_align(scan_btn, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(scan_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(scan_btn, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_add_event_cb(scan_btn, ui_event_network, LV_EVENT_PRESSED, NULL);

    lv_obj_t *ui_BtnLaelCsps_word = lv_label_create(scan_btn);
    lv_label_set_text(ui_BtnLaelCsps_word, "已扫描");
    lv_obj_set_style_text_font(ui_BtnLaelCsps_word, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnLaelCsps_word);

    return net_home;
}

static lv_point_t lv_point_line_floor[8][2];
#define LV_POINT_X1 75
#define LV_POINT_Y1 30

lv_obj_t *aweui_screen_network_scan_create(lv_obj_t *init_pg)
{
    net_scan = lv_obj_create(init_pg);
    lv_obj_remove_style_all(net_scan);
    lv_obj_clear_flag(net_scan, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(net_scan, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(net_scan, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_width(net_scan, 320);  /// 1
    // lv_obj_set_height(net_scan, 240); /// 1
    lv_obj_set_size(net_scan, lv_pct(100), lv_pct(100));

    // 扫描摄像头显示和
    scan_img = lv_img_create(net_scan);
    lv_obj_set_pos(scan_img, 0, 0);
    lv_obj_set_size(scan_img, lv_pct(100), lv_pct(100));
    lv_obj_set_align(scan_img, LV_ALIGN_CENTER);

    // 关闭按钮
    scan_cancel_btn = lv_img_create(net_scan);
    lv_img_set_src(scan_cancel_btn, &btn_cross);
    lv_obj_set_pos(scan_cancel_btn, -30, -20);
    lv_obj_set_align(scan_cancel_btn, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(scan_cancel_btn, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(scan_cancel_btn, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    lv_obj_add_event_cb(scan_cancel_btn, ui_event_network, LV_EVENT_PRESSED, NULL);

    // 扫描框框
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_line_rounded(&style_line, true);
    for (uint8_t i = 0; i < 8; i++)
    {
        line_floor[i] = lv_line_create(net_scan);
        lv_obj_add_style(line_floor[i], &style_line, 0);
        lv_obj_set_style_line_color(line_floor[i], lv_color_hex(0xffffff), 0);
    }
    lv_point_line_floor[0][0].x = LV_POINT_X1;
    lv_point_line_floor[0][0].y = LV_POINT_Y1;
    lv_point_line_floor[0][1].x = 125;
    lv_point_line_floor[0][1].y = LV_POINT_Y1;

    lv_point_line_floor[1][0].x = 195;
    lv_point_line_floor[1][0].y = LV_POINT_Y1;
    lv_point_line_floor[1][1].x = 245;
    lv_point_line_floor[1][1].y = LV_POINT_Y1;

    lv_point_line_floor[2][0].x = 245;
    lv_point_line_floor[2][0].y = LV_POINT_Y1;
    lv_point_line_floor[2][1].x = 245;
    lv_point_line_floor[2][1].y = 80;

    lv_point_line_floor[3][0].x = 245;
    lv_point_line_floor[3][0].y = 140;
    lv_point_line_floor[3][1].x = 245;
    lv_point_line_floor[3][1].y = 210;

    lv_point_line_floor[4][0].x = 245;
    lv_point_line_floor[4][0].y = 210;
    lv_point_line_floor[4][1].x = 195;
    lv_point_line_floor[4][1].y = 210;

    lv_point_line_floor[5][0].x = 125;
    lv_point_line_floor[5][0].y = 210;
    lv_point_line_floor[5][1].x = LV_POINT_X1;
    lv_point_line_floor[5][1].y = 210;

    lv_point_line_floor[6][0].x = LV_POINT_X1;
    lv_point_line_floor[6][0].y = 210;
    lv_point_line_floor[6][1].x = LV_POINT_X1;
    lv_point_line_floor[6][1].y = 140;

    lv_point_line_floor[7][0].x = LV_POINT_X1;
    lv_point_line_floor[7][0].y = 80;
    lv_point_line_floor[7][1].x = LV_POINT_X1;
    lv_point_line_floor[7][1].y = LV_POINT_Y1;

    // 关闭按钮
    scan_cancel_btn = lv_img_create(net_scan);
    lv_img_set_src(scan_cancel_btn, &btn_cross);
    lv_obj_set_pos(scan_cancel_btn, -30, -20);
    lv_obj_set_align(scan_cancel_btn, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(scan_cancel_btn, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(scan_cancel_btn, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    lv_obj_add_event_cb(scan_cancel_btn, ui_event_network, LV_EVENT_PRESSED, NULL);

    for (uint8_t i = 0; i < 8; i++)
    {
        lv_line_set_points(line_floor[i], lv_point_line_floor[i], 2);
    }
    return net_scan;
}

void aweui_set_scan_img(void *data, int width, int height)
{

    lv_obj_set_size(scan_img, width, height);
    lv_obj_set_align(scan_img, LV_ALIGN_CENTER);
    lv_obj_set_pos(scan_img, 0, 0);
    lv_img_set_zoom(scan_img, 260);
    desc.header.always_zero = 0;
    desc.header.w = width;
    desc.header.h = height;
    desc.header.cf = LV_IMG_CF_TRUE_COLOR;
    desc.data_size = width * height * LV_COLOR_DEPTH / 8;
    desc.data = data;
    lv_img_set_src(scan_img, &desc);
}

lv_obj_t *aweui_network_loading_create(lv_obj_t *init_pg)
{
    network_loaing = lv_obj_create(init_pg);
    lv_obj_remove_style_all(network_loaing);
    lv_obj_clear_flag(network_loaing, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(network_loaing, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(network_loaing, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(network_loaing, 320);  /// 1
    lv_obj_set_height(network_loaing, 240); /// 1

    // 等待连接网络gif
    load_gif = lv_gif_create(network_loaing);
    lv_gif_set_src(load_gif, &anim_circle);
    lv_obj_set_align(load_gif, LV_ALIGN_CENTER);
    lv_obj_add_flag(load_gif, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(load_gif, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags

    return network_loaing;
}

lv_obj_t *aweui_network_result_create(lv_obj_t *init_pg)
{
    net_rlt = lv_obj_create(init_pg);
    lv_obj_remove_style_all(net_rlt);
    lv_obj_clear_flag(net_rlt, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(net_rlt, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(net_rlt, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(net_rlt, 320);  /// 1
    lv_obj_set_height(net_rlt, 240); /// 1

    // 显示网络连接成功图标
    rlt_img = lv_img_create(net_rlt);
    lv_img_set_src(rlt_img, &ic_tick);
    lv_obj_set_align(rlt_img, LV_ALIGN_CENTER);
    lv_obj_set_pos(rlt_img, 0, -30);
    lv_obj_add_flag(rlt_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(rlt_img, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    lv_obj_add_event_cb(rlt_img, ui_event_network, LV_EVENT_PRESSED, NULL);

    // wifi名称
    ssid_lable = lv_label_create(net_rlt);
    lv_obj_set_x(ssid_lable, 0);
    lv_obj_set_y(ssid_lable, 0);
    lv_obj_set_align(ssid_lable, LV_ALIGN_CENTER);
    lv_obj_set_style_text_font(ssid_lable, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ssid_lable, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_bg_color(ssid_lable, lv_color_black(), 0);
    lv_label_set_text(ssid_lable, "ssid");
    static lv_style_t style_rlt;
    lv_style_init(&style_rlt);
    lv_style_set_bg_color(&style_rlt, lv_color_hex(0x000000));
    lv_style_set_border_width(&style_rlt, 0);
    lv_obj_add_style(ssid_lable, &style_rlt, 0);
    lv_style_set_border_color(&style_rlt, lv_color_hex(0x000000));

    // 关闭WiFi连接按钮
    wifi_disconnect_btn = lv_btn_create(net_rlt);
    lv_obj_set_size(wifi_disconnect_btn, 90, 40);
    lv_obj_set_pos(wifi_disconnect_btn, 0, -20);
    lv_obj_set_align(wifi_disconnect_btn, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(wifi_disconnect_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_set_style_bg_color(wifi_disconnect_btn, lv_color_hex(0xC0C0C0), 0);
    lv_obj_clear_flag(wifi_disconnect_btn, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_add_event_cb(wifi_disconnect_btn, ui_event_network, LV_EVENT_PRESSED, NULL);

    lv_obj_t *ui_BtnLaelCsps_word = lv_label_create(wifi_disconnect_btn);
    lv_label_set_text(ui_BtnLaelCsps_word, "断开");
    lv_obj_set_style_text_font(ui_BtnLaelCsps_word, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnLaelCsps_word);
    return net_rlt;
}
