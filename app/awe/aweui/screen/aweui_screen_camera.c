/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
    #include <zephyr/logging/log.h>
    LOG_MODULE_REGISTER(aweui_screen_bar_camera, LOG_LEVEL_INF);
#else
    #include "lvgl/lvgl.h"
    #define LOG_INF LV_LOG_USER
#endif

#include "aweui_screen.h"
#include "aweui_resources.h"
#include "aweui_event_inc.h"
#include "aweui_chat_btn_group.h"
#include "screen_switch.h"

static bool photo_flag = false;
lv_obj_t *setting_ui;
lv_style_t style_clock;
lv_obj_t *camera_home = NULL;
// static lv_obj_t *camera_bg = NULL;
// static lv_style_t style_home;

static lv_obj_t *obj_camera = NULL;
static lv_style_t style_camera;

static lv_obj_t *obj_filpcamera = NULL;
static lv_style_t style_filpcamera;

static lv_obj_t *obj_withdraw = NULL;
static lv_style_t style_withdraw;

static lv_obj_t *obj_ok = NULL;
static lv_style_t style_ok;

// static lv_obj_t *obj_wifi = NULL;
// static lv_style_t style_wifi;

static lv_obj_t *test_img = NULL;
static lv_img_dsc_t desc = {0};

static lv_obj_t *wait_img = NULL;
static lv_obj_t *err_img = NULL;
static lv_obj_t *camera_result = NULL;
static bool camera_flag = false;
void set_camera_status(uint8_t status)
{
	camera_flag = status;
	if (camera_flag)
	{
		lv_obj_add_flag(test_img, LV_OBJ_FLAG_HIDDEN);	   // 隐藏对象
		lv_obj_add_flag(wait_img, LV_OBJ_FLAG_HIDDEN);	   // 隐藏对象
		lv_obj_clear_flag(camera_result, LV_OBJ_FLAG_HIDDEN); // 显示对象
	}
	else
	{
		lv_obj_add_flag(wait_img, LV_OBJ_FLAG_HIDDEN);	// 隐藏对象
		lv_obj_clear_flag(err_img, LV_OBJ_FLAG_HIDDEN); // 显示对象
	}
}
void ui_event_camera_screen(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	if (event_code == LV_EVENT_PRESSED)
	{
		if (obj == obj_camera)
		{
			photo_flag = true;
			lv_obj_clear_flag(obj_ok, LV_OBJ_FLAG_HIDDEN);		 // 显示对象
			lv_obj_clear_flag(obj_withdraw, LV_OBJ_FLAG_HIDDEN); // 显示对象
			lv_obj_add_flag(obj_camera, LV_OBJ_FLAG_HIDDEN);	 // 隐藏对象
			lv_obj_add_flag(obj_filpcamera, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
			aweui_set_pull_event(AWEUI_EVENT_CAMERA_TAKE_PHOTO, NULL);
		}
		if (obj == obj_ok)
		{
			lv_img_set_zoom(test_img, 100);
			lv_obj_set_pos(test_img, -30, -10);
			lv_obj_add_flag(obj_ok, LV_OBJ_FLAG_HIDDEN);		 // 隐藏对象
			lv_obj_add_flag(obj_withdraw, LV_OBJ_FLAG_HIDDEN);	 // 隐藏对象
			lv_obj_add_flag(obj_camera, LV_OBJ_FLAG_HIDDEN);	 // 隐藏对象
			lv_obj_add_flag(obj_filpcamera, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
			lv_obj_clear_flag(wait_img, LV_OBJ_FLAG_HIDDEN);	 // 显示对象
			aweui_set_show_chat_camera(1, 1, 0);
			// aweui_set_pull_event(AWEUI_EVENT_CAMERA_PREVIEW_EXIT, NULL);
			aweui_set_pull_event(AWEUI_EVENT_CAMERA_QUICK_RECOGNIZE, NULL);
		}
		if (obj == obj_filpcamera)
		{
			aweui_set_pull_event(AWEUI_EVENT_CAMERA_DIRECTION_SWITCH, NULL);
		}
		if (obj == obj_withdraw)
		{
			photo_flag = false;
			lv_obj_clear_flag(obj_camera, LV_OBJ_FLAG_HIDDEN);	   // 显示对象
			lv_obj_clear_flag(obj_filpcamera, LV_OBJ_FLAG_HIDDEN); // 显示对象
			lv_obj_add_flag(obj_ok, LV_OBJ_FLAG_HIDDEN);		   // 隐藏对象
			lv_obj_add_flag(obj_withdraw, LV_OBJ_FLAG_HIDDEN);	   // 隐藏对象
			aweui_set_pull_event(AWEUI_EVENT_CAMERA_PREVIEW_ENTER, NULL);
		}
	}
}
void ui_create_photo(lv_obj_t *parent)
{
	test_img = lv_img_create(parent);
	lv_obj_set_pos(test_img, 0, 0);
	lv_obj_set_align(test_img, LV_ALIGN_CENTER);
}

lv_obj_t *aweui_camera_create(lv_obj_t *parent)
{
	LOG_INF("[%d:%s] \n", __LINE__, __func__);
	// 创建home页面

	aweui_status_bar_home_btn_hide(false);
	camera_home = lv_obj_create(parent);
	lv_obj_remove_style_all(camera_home);
	lv_obj_clear_flag(camera_home, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_bg_color(camera_home, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(camera_home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	// lv_obj_set_width(camera_home, 320);	 /// 1
	// lv_obj_set_height(camera_home, 240); /// 1
	lv_obj_set_size(camera_home, lv_pct(100), lv_pct(100));
	static lv_style_t style_home;
	lv_style_init(&style_home);
	lv_style_set_bg_color(&style_home, lv_color_hex(0x000000));
	// lv_style_set_bg_opa(&style_home, LV_OPA_30); /* 50%透明 */
	lv_style_set_border_width(&style_home, 0);
	lv_obj_add_style(camera_home, &style_home, 0);
	lv_style_set_border_color(&style_home, lv_color_hex(0x000000));

	// 创建摄像头图像显示
	test_img = lv_img_create(camera_home);
	lv_obj_set_pos(test_img, 0, 0);
	lv_obj_set_size(test_img, lv_pct(100), lv_pct(100));
	lv_obj_set_align(test_img, LV_ALIGN_CENTER);
	// 拍照
	obj_camera = lv_img_create(test_img);
	lv_img_set_src(obj_camera, &btn_takephoto_56);
	lv_obj_set_pos(obj_camera, -20, 0);
	lv_obj_set_align(obj_camera, LV_ALIGN_RIGHT_MID);
	lv_obj_add_flag(obj_camera, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
	lv_obj_clear_flag(obj_camera, LV_OBJ_FLAG_SCROLLABLE);						  /// Flags
	lv_obj_add_event_cb(obj_camera, ui_event_camera_screen, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(obj_camera, &style_camera, 0);
	lv_style_init(&style_camera);
	// lv_style_set_opa(&style_camera, LV_OPA_60);
	lv_obj_refresh_style(obj_camera, 0, 0);

	// 确认按键
	obj_ok = lv_img_create(test_img);
	lv_img_set_src(obj_ok, &btn_tick_56);
	lv_obj_set_pos(obj_ok, -20, 0);
	lv_obj_set_align(obj_ok, LV_ALIGN_RIGHT_MID);
	lv_obj_add_flag(obj_ok, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
	lv_obj_clear_flag(obj_ok, LV_OBJ_FLAG_SCROLLABLE);						  /// Flags
	lv_obj_add_event_cb(obj_ok, ui_event_camera_screen, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(obj_ok, &style_ok, 0);
	lv_style_init(&style_ok);
	// lv_style_set_opa(&style_ok, LV_OPA_60);
	lv_obj_refresh_style(obj_ok, 0, 0);
	// lv_obj_clear_flag(ui_AppBtn_stop5, LV_OBJ_FLAG_HIDDEN); // 显示对象
	lv_obj_add_flag(obj_ok, LV_OBJ_FLAG_HIDDEN); // 隐藏对象

	// 转换方向按键
	obj_filpcamera = lv_img_create(test_img);
	lv_img_set_src(obj_filpcamera, &btn_flipcamera);
	lv_obj_set_pos(obj_filpcamera, -20, -30);
	lv_obj_set_align(obj_filpcamera, LV_ALIGN_BOTTOM_RIGHT);
	lv_obj_add_flag(obj_filpcamera, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
	lv_obj_clear_flag(obj_filpcamera, LV_OBJ_FLAG_SCROLLABLE);						  /// Flags
	lv_obj_add_event_cb(obj_filpcamera, ui_event_camera_screen, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(obj_filpcamera, &style_filpcamera, 0);
	lv_style_init(&style_filpcamera);
	// lv_style_set_opa(&style_filpcamera, LV_OPA_60);
	lv_obj_refresh_style(obj_filpcamera, 0, 0);
	// lv_obj_clear_flag(ui_AppBtn_stop5, LV_OBJ_FLAG_HIDDEN); // 显示对象
	// lv_obj_add_flag(obj_filpcamera, LV_OBJ_FLAG_HIDDEN); // 隐藏对象

	// 取消
	obj_withdraw = lv_img_create(test_img);
	lv_img_set_src(obj_withdraw, &btn_withdraw);
	lv_obj_set_pos(obj_withdraw, -20, -30);
	lv_obj_set_align(obj_withdraw, LV_ALIGN_BOTTOM_RIGHT);
	lv_obj_add_flag(obj_withdraw, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
	lv_obj_clear_flag(obj_withdraw, LV_OBJ_FLAG_SCROLLABLE);						/// Flags
	lv_obj_add_event_cb(obj_withdraw, ui_event_camera_screen, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(obj_withdraw, &style_withdraw, 0);
	lv_style_init(&style_withdraw);
	// lv_style_set_opa(&style_withdraw, LV_OPA_60);
	lv_obj_refresh_style(obj_withdraw, 0, 0);
	// lv_obj_clear_flag(ui_AppBtn_stop5, LV_OBJ_FLAG_HIDDEN); // 显示对象
	lv_obj_add_flag(obj_withdraw, LV_OBJ_FLAG_HIDDEN); // 隐藏对象

	// 等待gif
	wait_img = lv_gif_create(camera_home);
	lv_gif_set_src(wait_img, &anim_loading);
	lv_obj_set_pos(wait_img, -20, -20);
	lv_obj_set_align(wait_img, LV_ALIGN_BOTTOM_MID);
	lv_obj_add_flag(wait_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
	lv_obj_clear_flag(wait_img, LV_OBJ_FLAG_SCROLLABLE);						/// Flags
	lv_obj_add_event_cb(wait_img, ui_event_camera_screen, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(wait_img, &style_withdraw, 0);
	lv_style_init(&style_withdraw);
	// lv_style_set_opa(&style_withdraw, LV_OPA_60);
	lv_obj_refresh_style(wait_img, 0, 0);
	lv_obj_add_flag(wait_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象

	// 错误提示
	err_img = lv_img_create(camera_home);
	lv_img_set_src(err_img, &ic_warning);
	lv_obj_set_pos(err_img, -20, -20);
	lv_obj_set_align(err_img, LV_ALIGN_BOTTOM_MID);
	lv_obj_add_flag(err_img, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
	lv_obj_clear_flag(err_img, LV_OBJ_FLAG_SCROLLABLE);						   /// Flags
	lv_obj_add_event_cb(err_img, ui_event_camera_screen, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(err_img, &style_withdraw, 0);
	lv_style_init(&style_withdraw);
	// lv_style_set_opa(&style_withdraw, LV_OPA_60);
	lv_obj_refresh_style(err_img, 0, 0);
	lv_obj_add_flag(err_img, LV_OBJ_FLAG_HIDDEN); // 隐藏对象

	// result
	camera_result = lv_textarea_create(camera_home);
	lv_obj_set_x(camera_result, 0);
	lv_obj_set_y(camera_result, 0);
	lv_obj_set_style_text_font(camera_result, &lv_font_notosans_cs_medium_18, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(camera_result, lv_color_hex(0xffffff), 0);
	lv_obj_set_style_bg_color(camera_result, lv_color_black(), 0);
	lv_obj_add_flag(camera_result, LV_OBJ_FLAG_HIDDEN); // 隐藏对象
	lv_textarea_set_text(camera_result, "11111");
	aweui_add_chat_camera_ui(camera_home, UI_NOT_SHOW);
	// aweui_set_show_chat_camera(0,0);
	return camera_home;
}

void aweui_set_camera(void *data, int width, int height)
{
	if (photo_flag == true)
	{
		// set_camera_status(1);
	}
	else
	{
		lv_obj_set_size(test_img, width, height);
		lv_obj_set_align(test_img, LV_ALIGN_CENTER);
		lv_obj_set_pos(test_img, 0, 0);
		lv_img_set_zoom(test_img, 260);
		desc.header.always_zero = 0;
		desc.header.w = width;
		desc.header.h = height;
		desc.header.cf = LV_IMG_CF_TRUE_COLOR;
		desc.data_size = width * height * LV_COLOR_DEPTH / 8;
		desc.data = data;
		lv_img_set_src(test_img, &desc);
	}
}

static struct aweui_scr aweui_screen_camera = {0};

static void aweui_src_standby_enter_handle(struct aweui_scr *from, struct aweui_scr *to)
{
	if (to == NULL) {
		return;
	}

	if (to->screen == NULL) {
		to->screen = aweui_camera_create(lv_scr_act());
	}

	if (to->screen == NULL) {
		return;
	}

	lv_obj_clear_flag(to->screen, LV_OBJ_FLAG_HIDDEN);
	aweui_set_pull_event(AWEUI_EVENT_CAMERA_PREVIEW_ENTER, NULL);
}

static void aweui_src_standby_exit_handle(struct aweui_scr *from, struct aweui_scr *to)
{
	if (from == NULL) {
		return;
	}

	if (from->screen == NULL) {
		return;
	}

	lv_obj_add_flag(from->screen, LV_OBJ_FLAG_HIDDEN);
}

int aweui_screen_camera_init(void)
{
	aweui_screen_camera.id = AWEUI_SCR_CAMERA_IMAGE_PREVIEW;
	aweui_screen_camera.enter = aweui_src_standby_enter_handle;
	aweui_screen_camera.exit = aweui_src_standby_exit_handle;
	aweui_screen_camera.screen = camera_home;

	aweui_scr_register(AWEUI_SCR_CAMERA_IMAGE_PREVIEW, &aweui_screen_camera);

	return 0;
}