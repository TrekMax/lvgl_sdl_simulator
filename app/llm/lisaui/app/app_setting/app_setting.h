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

#include "../../app_common/lisaui_app_common.h"


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

int app_setting_init(void);

#ifdef __cplusplus
}
#endif

#endif // __APP_SETTING_H__
