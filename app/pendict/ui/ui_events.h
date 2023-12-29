/**
 * @file ui_events.h
 * @author TianShuang Ke (dske@listenai.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2021 - 2023  shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _UI_EVENTS_H
#define _UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
// #include <zephyr/zephyr.h>

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

typedef int (*ui_get_timer_cb_t)(struct tm *tmer);
typedef int (*ui_get_battery_cb_t)(uint8_t *state, uint8_t *level);
typedef int (*ui_set_backlight_cb_t)(const uint8_t brightness);
typedef int (*ui_set_volume_cb_t)(const uint8_t volume);

typedef int (*ui_audio_player_action_cb_t)(const uint8_t action);
typedef int (*ui_wsp_action_cb_t)(const uint8_t action);
typedef int (*ui_translate_action_cb_t)(const uint8_t action);

// UI 事件处理注册
void ui_register_time_update_cb(ui_get_timer_cb_t update_handler);
void ui_register_battery_update_cb(ui_get_battery_cb_t update_handler);
void ui_register_set_backlight_cb(ui_set_backlight_cb_t update_handler);
void ui_register_set_volume_cb(ui_set_volume_cb_t update_handler);
void ui_register_wsp_action_cb(ui_wsp_action_cb_t update_handler);

void ui_register_audio_player_action_cb(ui_audio_player_action_cb_t update_handler);
void ui_register_translate_action_cb(ui_translate_action_cb_t update_handler);

// 用户主动触发 UI 更新操作
int ui_set_ocr_result_text(const char *result);
int ui_set_wsp_result_text(const char *result);
int ui_set_battery_state(const uint8_t state);
int ui_set_battery_level(const uint8_t level);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
