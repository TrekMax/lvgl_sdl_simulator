/**
 * '@file aweui_standby.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-22
 *
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __AWEUI_SCREEN_STANDBY_H__
#define __AWEUI_SCREEN_STANDBY_H__

#ifdef __ZEPHYR__
	#include <zephyr/kernel.h>
	#include "lvgl.h"
#else
	#include "lvgl/lvgl.h"
#endif
#include "aweui_resources.h"

typedef enum
{
    UI_CAMERA = 0,//显示拍照以及录音
    UI_CAMERA_LONG,//显示和长拍照图
    UI_NOT_SHOW,//都不显示
    UI_NOT_SET,//不设置
} chat_btn_group_type_t;

lv_obj_t *aweui_screen_bar_setting_create(lv_obj_t *parent);
lv_obj_t *aweui_screen_standby_create(lv_obj_t *parent);

void aweui_status_bar_home_btn_hide(bool hide);

#endif // __AWEUI_SCREEN_STANDBY_H__