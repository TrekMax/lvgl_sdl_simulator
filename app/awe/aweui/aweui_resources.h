/**
 * @file aweui_resources.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __AWEUI_RESOURCES_H__
#define __AWEUI_RESOURCES_H__

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

LV_FONT_DECLARE(lv_font_chinese_14);
LV_FONT_DECLARE(lv_font_notosans_cs_medium_18);
// LV_FONT_DECLARE(lv_font_chinese_26);

LV_FONT_DECLARE(lv_font_clock_word);
LV_FONT_DECLARE(lv_font_screen_word);

LV_IMG_DECLARE( xiaoling_listening_s);
LV_IMG_DECLARE( xiaoling_standby_s);
LV_IMG_DECLARE( xiaoling_thinking_s);

LV_IMG_DECLARE( wifi_tool_qrcode);
LV_IMG_DECLARE( anim_music);

LV_IMG_DECLARE( btn_camera_active);
LV_IMG_DECLARE( btn_voice_active);
LV_IMG_DECLARE( btn_camera_l_active);

LV_IMG_DECLARE( btn_flipcamera);
LV_IMG_DECLARE( btn_takephoto_48);
LV_IMG_DECLARE( btn_takephoto_56);
LV_IMG_DECLARE( btn_tick_48);
LV_IMG_DECLARE( btn_tick_56);

LV_IMG_DECLARE( screen_word);
LV_IMG_DECLARE( clock_word);
LV_IMG_DECLARE( btn_cross);
LV_IMG_DECLARE( btn_flipcamera);
LV_IMG_DECLARE( btn_takephoto_48);
LV_IMG_DECLARE( btn_takephoto_56);
LV_IMG_DECLARE( btn_tick_48);
LV_IMG_DECLARE( btn_tick_56);
LV_IMG_DECLARE( btn_withdraw);
LV_IMG_DECLARE( ic_brightness_high);
LV_IMG_DECLARE( ic_brightness_low);
LV_IMG_DECLARE( ic_cross);
LV_IMG_DECLARE( ic_filpcamera);
LV_IMG_DECLARE( ic_launch_camera);
LV_IMG_DECLARE( ic_launch_setting);
LV_IMG_DECLARE( ic_launch_voice);
LV_IMG_DECLARE( ic_nav_home);
LV_IMG_DECLARE( ic_radio_off);
LV_IMG_DECLARE( ic_radio_on);
LV_IMG_DECLARE( ic_status_wifi0);
LV_IMG_DECLARE( ic_status_wifi1);
LV_IMG_DECLARE( ic_tick);
LV_IMG_DECLARE( ic_volumn_high);
LV_IMG_DECLARE( ic_volumn_low);
LV_IMG_DECLARE( ic_warning);
LV_IMG_DECLARE( ic_withdraw);
LV_IMG_DECLARE( anim_loading);
LV_IMG_DECLARE( anim_speak);
LV_IMG_DECLARE( btn_camera_active);
LV_IMG_DECLARE( btn_voice_active);
LV_IMG_DECLARE( btn_camera_l_active);
LV_IMG_DECLARE( anim_circle);

#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX
#include "incbin.h"

lv_obj_t *aweui_get_ui_base(void);

#endif // __AWEUI_RESOURCES_H__
