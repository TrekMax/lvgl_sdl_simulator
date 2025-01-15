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

LV_IMG_DECLARE(ui_img__launcher_composition_png);
LV_IMG_DECLARE(ui_img__launcher_setting_png);
LV_IMG_DECLARE(ui_img__launcher_scan_png);
LV_IMG_DECLARE(ui_img__status_charging_5_png);
LV_IMG_DECLARE(ui_img__angle_left_double_png);
LV_IMG_DECLARE(ui_img__guide_scan_png);
LV_IMG_DECLARE(ui_img__launcher_fav_png);
LV_IMG_DECLARE(ui_img__launcher_practice_png);

LV_IMG_DECLARE(ui_img__status_battery_1_png);
LV_IMG_DECLARE(ui_img__status_battery_2_png);
LV_IMG_DECLARE(ui_img__status_battery_3_png);
LV_IMG_DECLARE(ui_img__status_battery_4_png);
LV_IMG_DECLARE(ui_img__status_battery_5_png);

LV_IMG_DECLARE(ui_img__status_charging_1_png);
LV_IMG_DECLARE(ui_img__status_charging_2_png);
LV_IMG_DECLARE(ui_img__status_charging_3_png);
LV_IMG_DECLARE(ui_img__status_charging_4_png);

// LV_FONT_DECLARE(ui_font_PocketDictPenRegular);
LV_FONT_DECLARE(lv_font_chinese_18);

enum ui_page_id_t {
    UI_PAGE_ID_NONE,
    UI_PAGE_ID_HOME,
    UI_PAGE_ID_OCR,
    UI_PAGE_ID_AUDIO_PLAY,
    UI_PAGE_ID_SETTING,
    UI_PAGE_ID_DICTIONARY,
    UI_PAGE_ID_DIALOGUE,
    UI_PAGE_ID_SPELLING,
};

void ui_init(void);

#define UI_TEST_STR "支持更大容量的高速和片外，支持用户配置数据缓存与指令缓存。带宽；\
其低功耗蓝牙子系统支持可通过与广播扩展实现远距离通信。它还支持 2 Mbps PHY，\
用于提高传输速度和数据吞吐量。ESP32-S3 的 Wi-Fi 和 Bluetooth LE 射频性能优越，在高温下也能稳定工作。\
其低功耗蓝牙子系统支持可通过与广播扩展实现远距离通信。它还支持 2 Mbps PHY，\
用于提高传输速度和数据吞吐量。ESP32-S3 的 Wi-Fi 和 Bluetooth LE 射频性能优越，在高温下也能稳定工作。\
其低功耗蓝牙子系统支持可通过与广播扩展实现远距离通信。它还支持 2 Mbps PHY，\
用于提高传输速度和数据吞吐量。ESP32-S3 的 Wi-Fi 和 Bluetooth LE 射频性能优越，在高温下也能稳定工作。\
其低功耗蓝牙子系统支持可通过与广播扩展实现远距离通信。它还支持 2 Mbps PHY，\
用于提高传输速度和数据吞吐量。ESP32-S3 的 Wi-Fi 和 Bluetooth LE 射频性能优越，在高温下也能稳定工作。."

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
