/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
    #include <zephyr/logging/log.h>
    LOG_MODULE_REGISTER(aweui_char_btn_group, LOG_LEVEL_INF);
#else
    #include "lvgl/lvgl.h"
    #define LOG_INF LV_LOG_USER
#endif

#include "aweui_screen.h"
#include "aweui_resources.h"
#include "aweui_event_inc.h"
#include "aweui_chat_btn_group.h"
#include "screen_switch.h"

static lv_obj_t *voice_img;
static lv_obj_t *camera_img;
static lv_obj_t *camera_long_img;
static lv_style_t camera_style;
static lv_style_t voice_style;
static lv_style_t camera_l_style;

static void ui_camera_evt_handle(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (LV_EVENT_CLICKED == event_code) {
		LOG_INF("ui camera button clicked");
		aweui_scr_switch_to_id(AWEUI_SCR_CAMERA_IMAGE_PREVIEW);
	}
}

static void ui_voice_btn_evt_handle(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	if (LV_EVENT_PRESSED == event_code) {
		LOG_INF("ui voice button pressed");
		aweui_set_pull_event(AWEUI_EVENT_VOICE_KEY_PRESS, NULL);
	}else if (LV_EVENT_RELEASED == event_code) {
		LOG_INF("ui voice button released");
		aweui_set_pull_event(AWEUI_EVENT_VOICE_KEY_RELEASE, NULL);
    }
}

void ui_event_chat_camera(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);

	lv_obj_t *obj = lv_event_get_target(e);

	if (LV_EVENT_CLICKED == event_code) {
		LOG_INF("[%d:%s] event: %X\n", __LINE__, __func__, event_code);
		if (obj == camera_long_img) {
			aweui_set_pull_event(AWEUI_EVENT_CAMERA_PREVIEW_ENTER, NULL);
		}
	}
}

void aweui_set_show_chat_camera(bool camera_show, bool voice_show, bool camera_l_show)
{
    if (camera_show)
    {
        lv_obj_clear_flag(camera_img, LV_OBJ_FLAG_HIDDEN); // 显示对象
    }
    else
    {
        lv_obj_add_flag(camera_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
    }
    if (voice_show)
    {
        lv_obj_clear_flag(voice_img, LV_OBJ_FLAG_HIDDEN); // 显示对象
    }
    else
    {
        lv_obj_add_flag(voice_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
    }
    if (camera_l_show)
    {
        lv_obj_clear_flag(camera_long_img, LV_OBJ_FLAG_HIDDEN); // 显示对象
    }
    else
    {
        lv_obj_add_flag(camera_long_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
    }
    // lv_obj_add_flag(camera_img_l, LV_OBJ_FLAG_HIDDEN); // 显示对象
    // lv_obj_add_flag(camera_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
    // lv_obj_add_flag(voice_img, LV_OBJ_FLAG_HIDDEN);  // 隐藏对象

    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN); // 显示对象
}

void aweui_add_chat_camera_ui(lv_obj_t *parent, chat_btn_group_type_t btn_type)
{
    // 拍照
    camera_img = lv_img_create(parent);
    lv_img_set_src(camera_img, &btn_camera_active);
    lv_obj_set_pos(camera_img, -10, 0);
    lv_obj_set_align(camera_img, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(camera_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(camera_img, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    lv_obj_add_event_cb(camera_img, ui_camera_evt_handle, LV_EVENT_ALL, NULL);
    lv_obj_add_style(camera_img, &camera_style, 0);
    lv_style_init(&camera_style);
    lv_style_set_opa(&camera_style, LV_OPA_80);
    lv_obj_refresh_style(camera_img, 0, LV_STYLE_PROP_ANY);

	lv_obj_set_style_pad_all(parent, 0, 0);
    // 录音
    voice_img = lv_img_create(parent);
    lv_img_set_src(voice_img, &btn_voice_active);
    lv_obj_align_to(voice_img, camera_img, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 4);
    lv_obj_add_flag(voice_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(voice_img, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    lv_obj_add_event_cb(voice_img, ui_voice_btn_evt_handle, LV_EVENT_ALL, NULL);
    lv_obj_add_style(voice_img, &voice_style, 0);
    lv_style_init(&voice_style);
    lv_style_set_opa(&voice_style, LV_OPA_80);
    lv_obj_refresh_style(voice_img, 0, LV_STYLE_PROP_ANY);

    // 拍照 long
    camera_long_img = lv_img_create(parent);
    lv_img_set_src(camera_long_img, &btn_camera_l_active);
    lv_obj_set_pos(camera_img, -10, 0);
    lv_obj_set_align(camera_long_img, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(camera_long_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(camera_long_img, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    lv_obj_add_event_cb(camera_long_img, ui_event_chat_camera, LV_EVENT_ALL, NULL);
    lv_obj_add_style(camera_long_img, &camera_l_style, 0);
    lv_style_init(&camera_l_style);
    lv_style_set_opa(&camera_l_style, LV_OPA_80);
    // lv_obj_refresh_style(camera_long_img, 0, LV_STYLE_PROP_ANY);

    switch (btn_type)
    {
    case UI_CAMERA:
        lv_obj_add_flag(camera_long_img, LV_OBJ_FLAG_HIDDEN); // 显示对象
        lv_obj_clear_flag(camera_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
        lv_obj_clear_flag(voice_img, LV_OBJ_FLAG_HIDDEN);  // 隐藏对象
        break;
    case UI_CAMERA_LONG:
        lv_obj_clear_flag(camera_long_img, LV_OBJ_FLAG_HIDDEN); // 显示对象
        lv_obj_add_flag(camera_img, LV_OBJ_FLAG_HIDDEN);     // 隐藏对象
        lv_obj_add_flag(voice_img, LV_OBJ_FLAG_HIDDEN);      // 隐藏对象
        break;
    case UI_NOT_SHOW:
        lv_obj_add_flag(camera_img, LV_OBJ_FLAG_HIDDEN);   // 隐藏对象
        lv_obj_add_flag(voice_img, LV_OBJ_FLAG_HIDDEN);    // 隐藏对象
        lv_obj_add_flag(camera_long_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
        break;
    default:
        break;
    }
}