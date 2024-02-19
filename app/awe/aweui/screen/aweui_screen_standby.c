/**
 * '@file aweui_standby.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "aweui_screen.h"
#include "aweui_resources.h"
#include "aweui_types.h"
#include "aweui_event_inc.h"
#include "aweui_chat_btn_group.h"
#include "screen_switch.h"

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "core/lv_obj.h"
    #include "lvgl.h"
    #include <zephyr/posix/time.h>
    #include <zephyr/net/websocket.h>
    #include <zephyr/net/http/client.h>
    #include <zephyr/net/sntp.h>
    #include <zephyr/net/net_ip.h>
    #include <zephyr/net/socket.h>
    #include <zephyr/logging/log.h>
    LOG_MODULE_REGISTER(screen_standby, LOG_LEVEL_INF);
#else
    #include "lvgl/lvgl.h"
    #define LOG_INF LV_LOG_USER
#endif
lv_obj_t *screen_standby_obj;
lv_obj_t *network_tips_label = NULL;
lv_obj_t *network_tips_btn = NULL;
lv_obj_t *xiaolin_txt = NULL;
lv_obj_t *clock_label;

bool ui_init_flag = false;

void ui_event_blood_oxy(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    LV_UNUSED(obj);
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) // 上滑
    {
        LV_LOG_USER("[%d:%s] event: %X\n", __LINE__, __func__, event_code);
        lv_indev_wait_release(lv_indev_get_act());
        // lv_scr_load_anim(ui_blood_oxy_new, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0, false);
        // _ui_screen_change(&ui_blood_oxy_new, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) // 下滑
    {
        lv_indev_wait_release(lv_indev_get_act());
        LV_LOG_USER("[%d:%s] event: %X\n", __LINE__, __func__, event_code);
        // lv_scr_load_anim(ui_blood_oxy_new, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0, false);
        // _ui_screen_change(&ui_blood_oxy_new, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_watch_digital_screen_init);
    }
}
void network_tips_event(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        // LOG_INF("------->[%s:%d] event: %X\n", __FILE__, __LINE__, event_code);
        if (obj == network_tips_btn)
        {
            // LOG_INF("------->[%s:%d] event: %X\n", __FILE__, __LINE__, event_code);
            // aweui_setting_tabview_create(lv_scr_act());
            // aweui_set_pull_event(AWEUI_EVENT_SCREEN_CHANGE_TO_NETWORK, NULL);
            aweui_status_bar_home_btn_hide(true);
            lv_obj_t *page = aweui_setting_tabview_create(lv_scr_act());
            // lv_obj_t *page = aweui_setting_tabview_create(NULL);
            // _ui_screen_change(page, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
            // lv_scr_load_anim(page, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0, false);
        }
    }
}

void ui_event_home_camera(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    LOG_INF("[%d:%s] event: %X\n", __LINE__, __func__, event_code);
    lv_obj_t *obj = lv_event_get_target(e);
    // if (event_code == LV_EVENT_PRESSED)
    // {

    //     if (obj == xiaolin_txt)
    //     {
    //         // 跳转页面配网然后删除cb
    //     }
    // }
    // if (event_code == LV_EVENT_RELEASED) // 释放
    // {
    // }
    if (event_code == LV_EVENT_CLICKED) {
        if (obj == xiaolin_txt) {
            aweui_set_pull_event(AWEUI_EVENT_SCREEN_CHANGE_TO_CAMERA, NULL);
        }
    }
}

void ui_set_bg_color(uint32_t color) {}

lv_obj_t *aweui_screen_standby_create(lv_obj_t *parent)
{
    ui_init_flag = false;
    LOG_INF("aweui_screen_standby_create parent:%p", parent);
    screen_standby_obj = lv_obj_create(parent);
    lv_obj_add_event_cb(screen_standby_obj, ui_event_blood_oxy, LV_EVENT_ALL, NULL);
    // if (parent == NULL)
    // {
        lv_obj_set_size(screen_standby_obj, LV_HOR_RES, 200);
    // } else {
        // lv_obj_set_size(screen_standby_obj, lv_pct(100), lv_pct(100));
    // }
    lv_obj_set_style_bg_opa(screen_standby_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(home_btn, LV_OPA_60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(screen_standby_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(screen_standby_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(screen_standby_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(screen_standby_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(screen_standby_obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_clear_flag(screen_standby_obj, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(screen_standby_obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(screen_standby_obj, lv_color_hex(0x00bcbcbc), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(screen_standby_obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_event_cb(screen_standby_obj, ui_event_blood_oxy, LV_EVENT_ALL, NULL);
    lv_obj_set_style_pad_all(screen_standby_obj, 0, 0);


    network_tips_btn = lv_btn_create(screen_standby_obj);
    lv_obj_set_pos(network_tips_btn, lv_pct(5), 30);
    lv_obj_set_size(network_tips_btn, 120, 40);
    lv_obj_set_style_bg_color(network_tips_btn, lv_color_hex(0x000000), 0);
    // home_btn = lv_btn_create(status_bar);
    // lv_obj_align(network_tips_btn, LV_ALIGN_LEFT_MID, 10, 40);
    // lv_obj_add_flag(network_tips_btn, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_bg_opa(network_tips_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(network_tips_btn, LV_OPA_60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(network_tips_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(network_tips_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(network_tips_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(network_tips_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_all(home_btn, 0, 0);
    // lv_obj_add_event_cb(network_tips_btn, aweui_event_home_btn_handler, LV_EVENT_ALL, NULL);

    lv_obj_add_event_cb(network_tips_btn, network_tips_event, LV_EVENT_CLICKED, NULL);

    network_tips_label = lv_label_create(network_tips_btn);
    lv_label_set_text(network_tips_label, "设备未联网");
    lv_obj_set_style_text_font(network_tips_label, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(network_tips_label, lv_color_hex(0x7790c8), 0);
    lv_obj_set_style_bg_color(network_tips_label, lv_color_black(), 0);
    lv_obj_add_event_cb(network_tips_label, network_tips_event, LV_EVENT_ALL, NULL);

    // static lv_style_t style;
    // lv_style_init(&style);
    // lv_style_set_bg_opa(&style, LV_OPA_COVER);
    // lv_style_set_border_width(&style, 0);
    // lv_style_set_pad_all(&style, 10);
    // lv_style_set_text_decor(&style, LV_TEXT_DECOR_UNDERLINE);
    // lv_obj_add_style(network_tips_label, &style, 0);

    // 时钟
    clock_label = lv_label_create(screen_standby_obj);
    lv_label_set_text(clock_label, "00:00");
    lv_obj_set_pos(clock_label, lv_pct(5), lv_pct(40));
    lv_obj_set_style_text_font(clock_label, &lv_font_clock_word, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(clock_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_bg_color(clock_label, lv_color_black(), 0);

    xiaolin_txt = lv_label_create(screen_standby_obj);
    lv_label_set_text(xiaolin_txt, "请使用“小聆小聆”唤醒我");
    lv_obj_set_pos(xiaolin_txt, lv_pct(5), lv_pct(80));
    lv_obj_set_style_text_font(xiaolin_txt, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(xiaolin_txt, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_bg_color(xiaolin_txt, lv_color_black(), 0);
    lv_obj_add_event_cb(xiaolin_txt, ui_event_home_camera, LV_EVENT_PRESSED, NULL);

    aweui_add_chat_camera_ui(screen_standby_obj, UI_CAMERA);
    //     // 拍照
    // lv_obj_t *camera_img = lv_img_create(screen_standby_obj);
    // lv_img_set_src(camera_img, &btn_camera_active);
    // lv_obj_set_pos(camera_img, 0, 0);
    // lv_obj_set_align(camera_img, LV_ALIGN_TOP_RIGHT);
    // lv_obj_add_flag(camera_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    // lv_obj_clear_flag(camera_img, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    // // lv_obj_add_event_cb(camera_img, ui_camera_evt_handle, LV_EVENT_ALL, NULL);
    // // lv_obj_add_style(camera_img, &camera_style, 0);
    // // lv_style_init(&camera_style);
    // // lv_style_set_opa(&camera_style, LV_OPA_80);
    // lv_obj_refresh_style(camera_img, 0, LV_STYLE_PROP_ANY);
    // aweui_add_chat_camera_ui(ui_demo_screen, UI_CAMERA_LONG);
    ui_init_flag = true;
    return screen_standby_obj;
}


#ifdef __ZEPHYR__
#define UTC8_SEC            (8 * 3600)

int get_ntp_time(uint8_t *hour, uint8_t *min)
{ // 获取网络时间
    int rc;
    struct sntp_time sntp_time;
    // char time_str[sizeof("1970-01-01 00:00:00")];
    char *servers[] = {CONFIG_SNTP_SERVER1, CONFIG_SNTP_SERVER2, CONFIG_SNTP_SERVER3, CONFIG_SNTP_SERVER4, CONFIG_SNTP_SERVER5};
    int server_count = sizeof(servers) / sizeof(servers[0]);

    for (int i = 0; i < server_count; i++) {
        int cnt = 0;
        do {
            LOG_INF("Sending NTP request to %s:", servers[i]);
            rc = sntp_simple(servers[i], 200, &sntp_time);
            if (rc == 0) {
                time_t now = sntp_time.seconds + UTC8_SEC;
                struct tm now_tm;

                gmtime_r(&now, &now_tm);
                *hour = now_tm.tm_hour;
                *min = now_tm.tm_min;
                LOG_INF("  Acquired time: hour-%d, min-%d", *hour, *min);
                return 0;
            } else {
                LOG_ERR("  Failed to acquire SNTP from %s, code %d, attempt %d", servers[i], rc, cnt);
            }
            cnt++;
        } while (cnt < 3);
    }
    return 1;
}
int update_date(uint8_t month, uint8_t day)
{
    char date_str[30] = {0};
    snprintf(date_str, sizeof(date_str), "%02d月%02d日\n", month, day);
    LV_LOG_USER("date_str:%s", date_str);
    lv_obj_set_style_text_color(network_tips_label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_bg_color(network_tips_label, lv_color_black(), 0);
    lv_label_set_text(network_tips_label, date_str);
    return 0;
}
int updata_clock(uint8_t hour_, uint8_t min_)
{
    char time_str[30] = {0};
    sprintf(time_str, "%02d:%02d\n", hour_, min_);
    lv_label_set_text(clock_label, time_str);
    return 0;
}
#endif

static struct aweui_scr aweui_screen_main = {0};

static void aweui_src_standby_enter_handle(struct aweui_scr *from, struct aweui_scr *to)
{
	if (to == NULL) {
		return;
	}

	lv_obj_clear_flag(from->screen, LV_OBJ_FLAG_HIDDEN);
}

void aweui_src_standby_exit_handle(struct aweui_scr *from, struct aweui_scr *to)
{
	if (from == NULL) {
		return;
	}

	if (from->screen == NULL) {
		return;
	}

	lv_obj_add_flag(from->screen, LV_OBJ_FLAG_HIDDEN);
}

int aweui_screen_standby_init(void)
{
	aweui_screen_main.id = AWEUI_SCR_STANDBY;
	aweui_screen_main.enter = aweui_src_standby_enter_handle;
	aweui_screen_main.exit = aweui_src_standby_exit_handle;
    aweui_screen_main.screen = screen_standby_obj;

	aweui_scr_register(AWEUI_SCR_STANDBY, &aweui_screen_main);

	return 0;
}
