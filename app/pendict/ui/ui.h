/**
 * @file ui.h
 * @author TianShuang Ke (dske@listenai.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2021 - 2023  shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _POCKETDICTPEN_UI_H
#define _POCKETDICTPEN_UI_H

#ifdef __cplusplus
extern "C" {
#endif

// #include "lvgl.h"
#include "lvgl/lvgl.h"

#include <stdio.h>
#define printk printf
#include "ui_events.h"

LV_IMG_DECLARE(ui_img__launcher_composition_png);    // assets\ launcher_composition.png
LV_IMG_DECLARE(ui_img__launcher_setting_png);    // assets\ launcher_setting.png
LV_IMG_DECLARE(ui_img__launcher_scan_png);    // assets\ launcher_scan.png
LV_IMG_DECLARE(ui_img__status_charging_5_png);    // assets\ status_charging_5.png
LV_IMG_DECLARE(ui_img__angle_left_double_png);    // assets\ angle_left_double.png
LV_IMG_DECLARE(ui_img__guide_scan_png);    // assets\ guide_scan.png
LV_IMG_DECLARE(ui_img__launcher_fav_png);    // assets\ guide_scan.png
LV_IMG_DECLARE(ui_img__launcher_practice_png);    // assets\ guide_scan.png

LV_IMG_DECLARE(ui_img__status_battery_1_png);    // assets\ status_battery_1.png
LV_IMG_DECLARE(ui_img__status_battery_2_png);    // assets\ status_battery_2.png
LV_IMG_DECLARE(ui_img__status_battery_3_png);    // assets\ status_battery_3.png
LV_IMG_DECLARE(ui_img__status_battery_4_png);    // assets\ status_battery_4.png
LV_IMG_DECLARE(ui_img__status_battery_5_png);    // assets\ status_battery_5.png

LV_IMG_DECLARE(ui_img__status_charging_1_png);    // assets\ status_charging_1.png
LV_IMG_DECLARE(ui_img__status_charging_2_png);    // assets\ status_charging_2.png
LV_IMG_DECLARE(ui_img__status_charging_3_png);    // assets\ status_charging_3.png
LV_IMG_DECLARE(ui_img__status_charging_4_png);    // assets\ status_charging_4.png

// LV_FONT_DECLARE(ui_font_PocketDictPenRegular);
LV_FONT_DECLARE(lv_font_chinese_18);

enum ui_screen_t {
    UI_SCREEN_NONE,
    UI_SCREEN_HOME,
    UI_SCREEN_OCR,
    UI_SCREEN_AUDIO_PLAY,
    UI_SCREEN_SETTING,
    UI_SCREEN_DICTIONARY,
    UI_SCREEN_DIALOGUE,
};

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
