/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "aweui_screen.h"
#include "aweui_resources.h"
#include "aweui_event_inc.h"
#include "aweui_types.h"

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
    #include <zephyr/logging/log.h>
    LOG_MODULE_REGISTER(aweui_screen_bar_setting, LOG_LEVEL_INF);
#else
    #include "lvgl/lvgl.h"
    #define LOG_INF LV_LOG_USER
#endif

#include "../utils/lv_img_utils.h"

static lv_obj_t *setting_home;
static lv_obj_t *setting_btn;
static lv_obj_t *slider_voice;
static lv_obj_t *slider_luminance;
static lv_style_t style_setting;

static lv_point_t lv_setting_line_floor[2];
static lv_obj_t *line_setting_floor;

static lv_obj_t *icon_volume_min;
static lv_obj_t *icon_volume_max;
static lv_obj_t *icon_brightness_min;
static lv_obj_t *icon_brightness_max;
static lv_obj_t *icon_setting_btn;

lv_img_dsc_t icon_volume_min_png;
lv_img_dsc_t icon_volume_max_png;
lv_img_dsc_t icon_brightness_min_png;
lv_img_dsc_t icon_brightness_max_png;
lv_img_dsc_t icon_setting_btn_png;
#ifdef __ZEPHYR__
INCBIN(icon_volume_min_png, "app_ui/aweui/assets/png/ic_volume_low.png");
INCBIN(icon_volume_max_png, "app_ui/aweui/assets/png/ic_volume_high.png");
INCBIN(icon_brightness_min_png, "app_ui/aweui/assets/png/ic_brightness_low.png");
INCBIN(icon_brightness_max_png, "app_ui/aweui/assets/png/ic_brightness_high.png");
INCBIN(icon_setting_btn_png, "app_ui/aweui/assets/png/ic_launch_setting.png");
#else
INCBIN(icon_volume_min_png, "app/awe/aweui/assets/png/ic_volume_low.png");
INCBIN(icon_volume_max_png, "app/awe/aweui/assets/png/ic_volume_high.png");
INCBIN(icon_brightness_min_png, "app/awe/aweui/assets/png/ic_brightness_low.png");
INCBIN(icon_brightness_max_png, "app/awe/aweui/assets/png/ic_brightness_high.png");
INCBIN(icon_setting_btn_png, "app/awe/aweui/assets/png/ic_launch_setting.png");
#endif

static void slider_event_cb(lv_event_t *e)
{
	lv_obj_t *slider = lv_event_get_target(e);

	/*Refresh the text*/
	// lv_label_set_text_fmt(label, "%" LV_PRId32, lv_slider_get_value(slider_voice));
	if (slider == slider_voice)
	{

		LOG_INF("voice is %d ,luminance is %d", lv_slider_get_value(slider_voice), lv_slider_get_value(slider_luminance));
		aweui_set_pull_event(AWEUI_EVENT_VOLUME_CHANGE, (void *)lv_slider_get_value(slider_voice));
	}
	else if (slider == slider_luminance)
	{

		aweui_set_pull_event(AWEUI_EVENT_BACKLIGHT_BRIGHTNESS_CHANGE, (void *)lv_slider_get_value(slider_luminance));
		LOG_INF("voice is %d ,luminance is %d", lv_slider_get_value(slider_voice), lv_slider_get_value(slider_luminance));
	}
}

void ui_event_setting(lv_event_t *e)
{
	lv_event_code_t event_code = lv_event_get_code(e);
	LOG_INF("[%d:%s] event: %X\n", __LINE__, __func__, event_code);
	lv_obj_t *obj = lv_event_get_target(e);
	if (event_code == LV_EVENT_PRESSED)
	{
		if (obj == setting_btn)
		{
			lv_style_set_opa(&style_setting, LV_OPA_100);
			lv_obj_refresh_style(setting_btn, 0, 0);
		}
	}
	if (LV_EVENT_RELEASED == event_code) // 释放
	{
		if (obj == setting_btn)
		{
			lv_style_set_opa(&style_setting, LV_OPA_80);
			lv_obj_refresh_style(setting_btn, 0, 0);
		}
	}
}
lv_obj_t *aweui_screen_bar_setting_create(lv_obj_t *parent)
{
	setting_home = lv_obj_create(parent);
	lv_obj_remove_style_all(setting_home);
	lv_obj_clear_flag(setting_home, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_style_bg_color(setting_home, lv_color_hex(0x404040), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(setting_home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_size(setting_home, LV_PCT(100), LV_PCT(70));

	icon_setting_btn = lv_img_create(setting_home);
	lv_img_png_src_init(&icon_setting_btn_png, icon_setting_btn_png_data, icon_setting_btn_png_size);
	lv_img_set_src(icon_setting_btn, &icon_setting_btn_png);
	lv_obj_set_pos(icon_setting_btn, 30, 15);
	lv_obj_set_align(icon_setting_btn, LV_ALIGN_TOP_LEFT);
	lv_obj_add_flag(icon_setting_btn, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
	lv_obj_clear_flag(icon_setting_btn, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_event_cb(icon_setting_btn, ui_event_setting, LV_EVENT_RELEASED, NULL);
	lv_obj_add_event_cb(icon_setting_btn, ui_event_setting, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(icon_setting_btn, &style_setting, 0);
	lv_style_init(&style_setting);
	lv_style_set_opa(&style_setting, LV_OPA_80);
	lv_obj_refresh_style(icon_setting_btn, 0, 0);

	// 亮度滑块
	slider_luminance = lv_slider_create(setting_home);
	lv_obj_set_style_bg_color(slider_luminance, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(slider_luminance, lv_color_hex(0xb0b0b0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(slider_luminance, lv_color_hex(0xa0a0a0), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_opa(slider_luminance, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_align(slider_luminance, LV_ALIGN_TOP_MID);
	lv_obj_set_style_bg_opa(slider_luminance, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_pos(slider_luminance, 30, 12);
	lv_obj_set_width(slider_luminance, LV_PCT(60)); /*Set the width*/
	lv_obj_set_height(slider_luminance, 60);
	lv_obj_set_style_width(slider_luminance, 1, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(slider_luminance, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(slider_luminance, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(slider_luminance, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(slider_luminance, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(slider_luminance, 10, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(slider_luminance, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(slider_luminance, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_add_event_cb(slider_luminance, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL); /*Assign an event function*/
	lv_slider_set_value(slider_luminance, 50, LV_ANIM_OFF);
	lv_slider_set_range(slider_luminance, 2, 100);

	// 音量滑块
	slider_voice = lv_slider_create(setting_home);
	lv_obj_set_style_bg_color(slider_voice, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(slider_voice, lv_color_hex(0xb0b0b0), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(slider_voice, lv_color_hex(0xF0F0F0), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_opa(slider_voice, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(slider_voice, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_align(slider_voice, LV_ALIGN_TOP_MID);
	lv_obj_set_pos(slider_voice, 0, 80);
	lv_obj_set_width(slider_voice, LV_PCT(80)); /*Set the width*/
	lv_obj_set_height(slider_voice, 60);
	lv_obj_set_style_pad_top(slider_voice, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(slider_voice, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(slider_voice, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(slider_voice, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(slider_voice, 10, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(slider_voice, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(slider_voice, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_add_event_cb(slider_voice, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL); /*Assign an event function*/
	lv_slider_set_value(slider_voice, 50, LV_ANIM_OFF);

	// 图标
	icon_brightness_min = lv_img_create(slider_luminance);
	lv_img_png_src_init(&icon_brightness_min_png, icon_brightness_min_png_data, icon_brightness_min_png_size);
	lv_img_set_src(icon_brightness_min, &icon_brightness_min_png);
	lv_obj_align(icon_brightness_min, LV_ALIGN_LEFT_MID, 20, 0);
	lv_obj_add_flag(icon_brightness_min, LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_clear_flag(icon_brightness_min, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_event_cb(icon_brightness_min, ui_event_setting, LV_EVENT_RELEASED, NULL);
	lv_obj_add_event_cb(icon_brightness_min, ui_event_setting, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(icon_brightness_min, &style_setting, 0);
	lv_style_init(&style_setting);
	lv_style_set_opa(&style_setting, LV_OPA_80);
	lv_obj_refresh_style(icon_brightness_min, 0, 0);

	icon_brightness_max = lv_img_create(slider_luminance);
	lv_img_png_src_init(&icon_brightness_max_png, icon_brightness_max_png_data, icon_brightness_max_png_size);
	lv_img_set_src(icon_brightness_max, &icon_brightness_max_png);
	lv_obj_align(icon_brightness_max, LV_ALIGN_RIGHT_MID, -20, 0);
	lv_obj_add_flag(icon_brightness_max, LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_clear_flag(icon_brightness_max, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_event_cb(icon_brightness_max, ui_event_setting, LV_EVENT_RELEASED, NULL);
	lv_obj_add_event_cb(icon_brightness_max, ui_event_setting, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(icon_brightness_max, &style_setting, 0);
	lv_style_init(&style_setting);
	lv_style_set_opa(&style_setting, LV_OPA_80);
	lv_obj_refresh_style(icon_brightness_max, 0, 0);

	icon_volume_min = lv_img_create(slider_voice);
	lv_img_png_src_init(&icon_volume_min_png, icon_volume_min_png_data, icon_volume_min_png_size);
	lv_img_set_src(icon_volume_min, &icon_volume_min_png);
	lv_obj_align(icon_volume_min, LV_ALIGN_LEFT_MID, 20, 0);
	lv_obj_add_flag(icon_volume_min, LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_clear_flag(icon_volume_min, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_event_cb(icon_volume_min, ui_event_setting, LV_EVENT_RELEASED, NULL);
	lv_obj_add_event_cb(icon_volume_min, ui_event_setting, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(icon_volume_min, &style_setting, 0);
	lv_style_init(&style_setting);
	lv_style_set_opa(&style_setting, LV_OPA_80);
	lv_obj_refresh_style(icon_volume_min, 0, 0);

	icon_volume_max = lv_img_create(slider_voice);
	lv_img_png_src_init(&icon_volume_max_png, icon_volume_max_png_data, icon_volume_max_png_size);
	lv_img_set_src(icon_volume_max, &icon_volume_max_png);
	lv_obj_align(icon_volume_max, LV_ALIGN_RIGHT_MID, -20, 0);
	lv_obj_add_flag(icon_volume_max, LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_clear_flag(icon_volume_max, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_event_cb(icon_volume_max, ui_event_setting, LV_EVENT_RELEASED, NULL);
	lv_obj_add_event_cb(icon_volume_max, ui_event_setting, LV_EVENT_PRESSED, NULL);
	lv_obj_add_style(icon_volume_max, &style_setting, 0);
	lv_style_init(&style_setting);
	lv_style_set_opa(&style_setting, LV_OPA_80);
	lv_obj_refresh_style(icon_volume_max, 0, 0);

	static lv_style_t style_line;
	lv_style_init(&style_line);
	lv_style_set_line_width(&style_line, 2);
	lv_style_set_line_color(&style_line, lv_palette_main(LV_PALETTE_BLUE));
	lv_style_set_line_rounded(&style_line, true);

	line_setting_floor = lv_line_create(setting_home);
	lv_obj_add_style(line_setting_floor, &style_line, 0);
	lv_obj_set_style_line_color(line_setting_floor, lv_color_hex(0xaaaaaa), 0);

	lv_setting_line_floor[0].x = 140;
	lv_setting_line_floor[0].y = 160;
	lv_setting_line_floor[1].x = 180;
	lv_setting_line_floor[1].y = 160;

	lv_line_set_points(line_setting_floor, lv_setting_line_floor, 2);
	return setting_home;
}