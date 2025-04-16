/**
 * @file app_setting.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __APP_SETTING_H__
#define __APP_SETTING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lisaui_app_common.h"

#if CONFIG_LVGL_ENV_SIMULATOR
    #define APP_SETTING_UI_RES_PERFIX_PATH(path) "app/llm/lisaui/app/app_setting/" path
#else
    #define APP_SETTING_UI_RES_PERFIX_PATH(path) "src/ui/lisaui/app/app_setting/" path
#endif


#define APP_SETTING_ITEM_ID_REGULAR 0
#define APP_SETTING_ITEM_ID_ALARM 1
#define APP_SETTING_ITEM_ID_WAKE 2
#define APP_SETTING_ITEM_ID_WIFI 3
#define APP_SETTING_ITEM_ID_WEATHER 4
#define APP_SETTING_ITEM_ID_AUDIO_PLAYER 5

#define UI_SILDER_BACKLIGHT_BRIGHTNESS_MAX_VALUE  (100)
#define UI_SILDER_BACKLIGHT_BRIGHTNESS_MIN_VALUE  (0)
#define UI_SILDER_VOLUME_MAX_VALUE                (10)
#define UI_SILDER_VOLUME_MIN_VALUE                (0)

enum ui_audio_play_state {
    UI_AUDIO_PLAY_STATE_IDLE,
    UI_AUDIO_PLAY_STATE_PLAYING,
    UI_AUDIO_PLAY_STATE_PAUSED,
};

enum ui_audio_play_action {
    UI_AUDIO_PLAY_ACTION_PLAY,
    UI_AUDIO_PLAY_ACTION_PAUSE,
    UI_AUDIO_PLAY_ACTION_RESUME,
    UI_AUDIO_PLAY_ACTION_STOP,
};

enum ui_battery_state {
    UI_BATTERY_STATE_CHARGING,
    UI_BATTERY_STATE_DISCHARGING,
    UI_BATTERY_STATE_FULL,
};

lisaui_err_t app_setting_init(void);
lisaui_err_t lisaui_app_setting_enter_item_panel(void);

#ifdef __cplusplus
}
#endif

#endif // __APP_SETTING_H__
