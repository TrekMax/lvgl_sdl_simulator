/**
 * @file aweui_status_bar.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-19
 *
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifdef __ZEPHYR__
    #include "zephyr/logging/log.h"
    #include "zephyr/sys/printk.h"
    #include <zephyr/kernel.h>
    #include "lvgl.h"
    #include <zephyr/logging/log.h>
    LOG_MODULE_REGISTER(screen_status_bar, LOG_LEVEL_INF);
#else
    #include "lvgl/lvgl.h"
    #define LOG_INF LV_LOG_USER
    #define printk LV_LOG_USER
#endif

#include "aweui_screen.h"
#include "../utils/lv_img_utils.h"

#define STATUS_BAR_HEIGHT 40
#define STATUS_BAR_ICON_WIDTH 60

#include "aweui_types.h"
#include "aweui_event_inc.h"
#include "widgets/radio_group.h"
#include "aweui_screen_network.h"

#ifdef __ZEPHYR__
INCBIN(icon_nav_home_png, "app_ui/aweui/assets/png/ic_nav_home.png");
INCBIN(icon_status_wifi_png, "app_ui/aweui/assets/png/ic_status_wifi1.png");
#else
INCBIN(icon_nav_home_png, "app/awe/aweui/assets/png/ic_nav_home.png");
INCBIN(icon_status_wifi_png, "app/awe/aweui/assets/png/ic_status_wifi1.png");
#endif


lv_img_dsc_t icon_nav_home;
lv_img_dsc_t icon_wifi;
lv_obj_t *home_btn;
lv_obj_t * status_line_obj;
lv_obj_t *homt_btn_img_obj;

lv_obj_t *status_bar;
void aweui_status_bar_home_btn_hide(bool hide);

lv_obj_t *aweui_screen_setting_interactive_page_create(lv_obj_t *parent)
{
	// lv_obj_t *page = lv_obj_create(parent);
	lv_obj_t *page = ls_lv_radio_group_create(parent, NULL, NULL);
	// lv_obj_set_style_border_width(page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	// lv_obj_set_style_outline_width(page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_all(page, 0, 0);
	
	ls_lv_radio_group_add(page, "按键唤醒", "通过开发板 K3 按键进行唤醒", NULL, NULL);
	ls_lv_radio_group_add(page, "语音唤醒（单轮对话）", "通过唤醒词“小L小L”唤醒，一次唤醒一轮对话", NULL, NULL);
	ls_lv_radio_group_add(page, "语音唤醒（多轮对话）", "通过唤醒词“小L小L”唤醒，支持多轮对话", NULL, NULL);
	return page;
}

void ui_event_scan_btn_handler(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	lv_obj_t *target = lv_event_get_target(e);
	LV_UNUSED(target);
	if (event_code == LV_EVENT_CLICKED)
	{
		// _ui_screen_change( ui_main_menu, LV_SCR_LOAD_ANIM_FADE_ON, 100, 200);
		aweui_set_pull_event(AWEUI_EVENT_WIFI_QRCODE_CONNECT_SCAN, NULL);
	}
}

lv_obj_t * aweui_screen_setting_network_page_create(lv_obj_t *parent)
{
    lv_obj_t *page = lv_obj_create(parent);
    lv_obj_remove_style_all(page);
    lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));


    lv_obj_t *wifi_icon = lv_img_create(page);
    lv_img_set_src(wifi_icon, &wifi_tool_qrcode);
    // lv_obj_set_align(wifi_icon, LV_ALIGN_CENTER);
    lv_obj_align(wifi_icon, LV_ALIGN_LEFT_MID, LV_PCT(10), 0);
    // lv_obj_align(wifi_icon, LV_ALIGN_RIGHT_MID, 50, 0);
    lv_obj_set_style_border_width(wifi_icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(wifi_icon, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(wifi_icon, 0, 0);
    lv_obj_set_style_pad_all(parent, 0, 0);
    lv_obj_set_style_bg_color(wifi_icon, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *tips_label = lv_label_create(page);
    lv_label_set_text(tips_label, "网络未连接，\n请使用手机扫描二维码配置网络");
    lv_obj_align_to(tips_label, wifi_icon, LV_ALIGN_OUT_RIGHT_MID, 10, -50);
    lv_obj_set_width(tips_label, LV_PCT(40));
    lv_obj_set_height(tips_label, LV_PCT(40));

    lv_obj_set_style_text_font(tips_label, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tips_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *scan_btn = lv_btn_create(page);
    lv_obj_set_size(scan_btn, 100, 40);
    // lv_obj_align(scan_btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_align_to(scan_btn, tips_label, LV_ALIGN_BOTTOM_MID, -10, 50);
    lv_obj_t *scan_label = lv_label_create(scan_btn);
    lv_label_set_text(scan_label, "扫描二维码");
    lv_obj_set_style_text_font(scan_label, &lv_font_chinese_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(scan_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(scan_btn, ui_event_scan_btn_handler, LV_EVENT_ALL, NULL);
    return page;
}

lv_obj_t * aweui_screen_setting_about_page_create(lv_obj_t *parent)
{
    // lv_obj_t *page = lv_obj_create(parent);
    // lv_obj_remove_style_all(page);
    // lv_obj_set_size(page, LV_PCT(100), LV_PCT(100));

    // lv_obj_t *label = lv_label_create(page);
    // lv_label_set_text(label, "Setting Interactive Page3");
    // lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_t *page  = ui_camera_create(parent);
    lv_obj_t *page  = aweui_screen_network_scan_create(parent);

    return page;
}

void aweui_event_home_btn_handler(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    LV_UNUSED(target);
    if (event_code == LV_EVENT_CLICKED)
    {
        LOG_INF("home btn clicked\n");
        printk("[%d:%s] home btn clicked\n", __LINE__, __func__);
        aweui_status_bar_home_btn_hide(true);

        lv_obj_t *page = aweui_screen_standby_create(NULL);
        // _ui_screen_change(page, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
        lv_scr_load_anim(page, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0, false);
        // aweui_set_pull_event(AWEUI_EVENT_HOME_BTN_CLICKED, NULL);
    }
}
lv_obj_t * tabview_home_btn;
lv_obj_t * tabview_home_btn_img;
lv_obj_t *aweui_setting_tabview_create(lv_obj_t *parent)
{
    aweui_status_bar_home_btn_hide(false);
    lv_obj_t *page = lv_obj_create(lv_scr_act());
    lv_obj_remove_style_all(page);
    lv_obj_set_size(page, 320, 240);
    lv_obj_t *status_bar_tabview = lv_tabview_create(page, LV_DIR_TOP, 45);
    lv_obj_set_size(status_bar_tabview, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(status_bar_tabview, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_t *status_bar_tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 45);
    lv_obj_set_style_text_font(status_bar_tabview, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *tab_btns = lv_tabview_get_tab_btns(status_bar_tabview);
    lv_obj_clear_flag(tab_btns, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_left(tab_btns, STATUS_BAR_ICON_WIDTH, 0);
    lv_obj_set_style_pad_right(tab_btns, STATUS_BAR_ICON_WIDTH*2, 0);
    lv_obj_set_style_bg_color(tab_btns, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(tab_btns, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(tab_btns, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    tabview_home_btn = lv_btn_create(tab_btns);
    lv_obj_align(tabview_home_btn, LV_ALIGN_LEFT_MID, 10, 0);
    lv_obj_add_flag(tabview_home_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_bg_opa(tabview_home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(home_btn, LV_OPA_60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(tabview_home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(tabview_home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(tabview_home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(tabview_home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_all(home_btn, 0, 0);
    lv_obj_add_event_cb(tabview_home_btn, aweui_event_home_btn_handler, LV_EVENT_ALL, NULL);
    
        tabview_home_btn_img = lv_img_create(tabview_home_btn);
    lv_img_png_src_init(&icon_nav_home, icon_nav_home_png_data, icon_nav_home_png_size);
    lv_img_set_src(tabview_home_btn_img, &icon_nav_home);
    lv_obj_set_style_bg_opa(tabview_home_btn_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(tabview_home_btn_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(tabview_home_btn_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(tabview_home_btn_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_t *logo = lv_img_create(tab_btns);
    // lv_img_png_src_init(&icon_nav_home, icon_nav_home_png_data, icon_nav_home_png_size);
    // lv_img_set_src(logo, &icon_nav_home);
    // lv_obj_align(logo, LV_ALIGN_LEFT_MID, -STATUS_BAR_ICON_WIDTH + 10, 0);
    // lv_obj_add_event_cb(logo, aweui_event_home_btn_handler, LV_EVENT_ALL, NULL);

    // lv_obj_t *wifi_icon = lv_img_create(tab_btns);
    // lv_img_png_src_init(&icon_wifi, icon_status_wifi_png_data, icon_status_wifi_png_size);
    // lv_img_set_src(wifi_icon, &icon_wifi);
    // lv_obj_align(wifi_icon, LV_ALIGN_RIGHT_MID, 50, 0);

    lv_obj_t *music_state_icon = lv_img_create(tab_btns);
    lv_img_png_src_init(&icon_nav_home, icon_nav_home_png_data, icon_nav_home_png_size);
    lv_img_set_src(music_state_icon, &icon_nav_home);
    lv_obj_align(music_state_icon, LV_ALIGN_LEFT_MID, -STATUS_BAR_ICON_WIDTH*2 + 10, 0);
    
    lv_obj_t *tab1 = lv_tabview_add_tab(status_bar_tabview, "唤醒");
    lv_obj_t *tab2 = lv_tabview_add_tab(status_bar_tabview, "网络");
    lv_obj_t *tab3 = lv_tabview_add_tab(status_bar_tabview, "QR");
    lv_obj_remove_event_cb(status_bar_tabview, LV_EVENT_SCROLL_END);

    aweui_screen_setting_interactive_page_create(tab1);
    aweui_screen_setting_network_page_create(tab2);
    aweui_screen_setting_about_page_create(tab3);
    return page;

}

void aweui_status_bar_home_btn_hide(bool hide)
{
    if (home_btn == NULL)
    {
        return;
    }
    if (hide)
    {
        lv_obj_add_flag(status_line_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(home_btn, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_del_delayed(status_bar, 0);
        // lv_obj_set_height(status_bar, 0);
    }
    else
    {
        lv_obj_clear_flag(status_line_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(home_btn, LV_OBJ_FLAG_HIDDEN);
        // lv_obj_set_height(status_bar, STATUS_BAR_HEIGHT);
    }
}


lv_obj_t *aweui_status_bar_create(lv_obj_t *parent)
{
    status_bar = lv_obj_create(parent);
    lv_obj_clear_flag(status_bar, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_remove_style_all(status_bar);
    lv_obj_set_size(status_bar, LV_PCT(100), STATUS_BAR_HEIGHT);
    lv_obj_set_style_bg_color(status_bar, lv_color_hex(0x00ff00), LV_PART_MAIN | LV_STATE_DEFAULT);

    home_btn = lv_btn_create(status_bar);
    lv_obj_align(home_btn, LV_ALIGN_LEFT_MID, 10, 0);
    lv_obj_add_flag(home_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_bg_opa(home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(home_btn, LV_OPA_60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(home_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_all(home_btn, 0, 0);
    lv_obj_add_event_cb(home_btn, aweui_event_home_btn_handler, LV_EVENT_ALL, NULL);
    homt_btn_img_obj = lv_img_create(home_btn);
    lv_img_png_src_init(&icon_nav_home, icon_nav_home_png_data, icon_nav_home_png_size);
    lv_img_set_src(homt_btn_img_obj, &icon_nav_home);
    lv_obj_set_style_bg_opa(homt_btn_img_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(homt_btn_img_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(homt_btn_img_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(homt_btn_img_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_t *wifi_icon = lv_img_create(status_bar);
    lv_img_png_src_init(&icon_wifi, icon_status_wifi_png_data, icon_status_wifi_png_size);
    lv_img_set_src(wifi_icon, &icon_wifi);
    lv_obj_align(wifi_icon, LV_ALIGN_RIGHT_MID, -10, 0);

    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_line_color(&style, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_line_width(&style, 1);
    lv_style_set_line_rounded(&style, true);
    lv_style_set_line_opa(&style, LV_OPA_30);

    /*Create an object with the new style*/
    status_line_obj = lv_line_create(status_bar);
    lv_obj_add_style(status_line_obj, &style, 0);

    static lv_point_t p[] = {{10, 38}, {310, 38}};
    lv_line_set_points(status_line_obj, p, 2);

    lv_obj_add_flag(status_line_obj, LV_OBJ_FLAG_HIDDEN);

    return status_bar;
}

