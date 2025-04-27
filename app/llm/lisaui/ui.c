/**
 * @file ui.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ui.h"
#include "app/app_common.h"
#include "app_common/lisaui_log.h"
#include "lisaui_app_common.h"
#include "lisaui_app_manager.h"

#if CONFIG_LVGL_ENV_SIMULATOR
#include <pthread.h>
#include <stdbool.h>
#else
#include "FreeRTOS.h"
#include "semphr.h"
#endif
static const char *TAG = "UI";

#if CONFIG_LVGL_ENV_SIMULATOR
pthread_mutex_t lvgl_mutex;
#else
SemaphoreHandle_t lvgl_mutex;
#endif

#define TEST_LISAUI_APP 1

#if TEST_LISAUI_APP
void test_lisaui_example(void);
#endif

void lisaui_ui_init(void)
{
#if CONFIG_LVGL_ENV_SIMULATOR
    if (pthread_mutex_init(&lvgl_mutex, NULL) != 0) {
        LISAUI_LOGE(TAG, "[%s] Failed to create lvgl_mutex", __FUNCTION__);
        return;
    }
#else
    lvgl_mutex = xSemaphoreCreateRecursiveMutex();
    if (lvgl_mutex == NULL) {
        LISAUI_LOGE(TAG, "[%s] Failed to create lvgl_mutex", __FUNCTION__);
        return;
    }
#endif

#if 0
    lv_disp_t *dispp = lv_disp_get_default();

    lv_theme_t *theme = LV_THEME_DEFAULT_INIT(
        lv_theme_get_color_primary(), lv_theme_get_color_secondary(), LV_THEME_MATERIAL_FLAG_DARK,
        lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
    lv_theme_set_act(theme);
#endif

#if CONFIG_LVGL_ENV_SIMULATOR
    // LISAUI_USE_APP(standby);
    LISAUI_USE_APP(launcher);
    LISAUI_USE_APP(taskbar);
    LISAUI_USE_APP(setting);

    LISAUI_USE_APP(weather);
    LISAUI_USE_APP(template);
    LISAUI_USE_APP(alarm);
    LISAUI_USE_APP(audio_player);
    LISAUI_USE_APP(wifi);

#endif
    lisaui_app_manager_init();
    // lisaui_app_manager_show_all_app_info();

    LISAUI_LOGI(TAG, "UI init done");

#if TEST_LISAUI_APP
    test_lisaui_example();
#endif
}

#if TEST_LISAUI_APP
#include "app_standby.h"
#include "app_weather.h"
#include "app_audio_player.h"
#include "app_alarm.h"
#include "app_setting.h"
#include "app_taskbar.h"
#include "common_widgets.h"
#include "app_wifi.h"


static int count = 0;
static int test_index = 0;

static metadata_weather_t weather = {
    .weather = "晴",
    .city = "深圳",
    // .location = "深圳",
    // .time = "2025-01-22 12:00",
    // .week = "星期二",
    .date = "04/18",
    // .title = "天气",
    .temperature = "25C",
    // .temperature = "25°C",
    // .temperature_range = "20°C - 30°C",
    .temperature_range = "20C ~ 30C",
    .description = "晴朗 天气优",
};

static metadata_music_song_t song = {
    .title = "稻香",
    .artist = "周杰伦",
};

// static lisaui_alarm_clock_list_t alarm_clock_list = {
//     .list = {
//         {.time_text = "07:00", .date_text = "4月1日"},
//         {.time_text = "08:00", .date_text = "4月2日"},
//         {.time_text = "09:00", .date_text = "4月3日"},
//         {.time_text = "10:00", .date_text = "4月4日"},
//     },
//     .count = sizeof(alarm_clocks) / sizeof(lisaui_alarm_clock_item_t),
// };

// int lisaui_app_alarm_handler(lisaui_alarm_item_t type, lisaui_alarm_op_t operation, void *param)
// {
//     LISAUI_LOGI(TAG, "[%s] type:%d operation:%d", __FUNCTION__, type, operation);
//     if (type == LISAUI_ALARM_ITEM_CLOCK_LIST) {
//         if (operation == LISAUI_ALARM_OP_GET_LIST) {
//             lisaui_alarm_clock_list_t *list = (lisaui_alarm_clock_list_t *)param;
//             list->list = alarm_clocks;
//             list->count = sizeof(alarm_clocks) / sizeof(lisaui_alarm_clock_item_t);
//         }
//     }
//     return 0;
// }

void lisaui_taskbar_event_handler(lisaui_taskbar_event_t event, void *param)
{
    LISAUI_LOGI(TAG, "[%s] event:%d", __FUNCTION__, event);
    switch (event) {
    case LISAUI_TASKBAR_EVENT_ENTER_SETTING:
        lisaui_app_enter(UI_APP_ID_SETTING);
        break;
    case LISAUI_TASKBAR_EVENT_ENTER_ALARM:
        lisaui_app_enter(UI_APP_ID_ALARM);
        break;
    case LISAUI_TASKBAR_EVENT_ENTER_AUDIO_PLAYER:
        lisaui_app_enter(UI_APP_ID_AUDIO_PLAYER);
        break;
    case LISAUI_TASKBAR_EVENT_ENTER_WEATHER:
        lisaui_app_enter(UI_APP_ID_WEATHER);
        break;
    case LISAUI_TASKBAR_EVENT_ENTER_STANDBY:
        lisaui_app_enter(UI_APP_ID_STANDBY);
        break;
    default:
        break;
    }
}

static void test_lisaui_app_timer_cb(lv_timer_t *timer)
{
    LISAUI_LOGI(TAG, "[%s] test_lisaui_app_timer_cb index:%d", __FUNCTION__, test_index);
    switch (test_index) {
    // case 1:
    //     lisaui_app_weather_del_weather_view();
    //     lisaui_app_enter(UI_APP_ID_TEMPLATE);
    //     break;
    // case 2:
    //     lisaui_app_enter(UI_APP_ID_WEATHER);
    //     lisaui_app_weather_set_weather_view(&weather);
    //     break;
    // case 3:
    //     lisaui_app_weather_del_weather_view();
    //     lisaui_app_enter(UI_APP_ID_SETTING);
    //     LISAUI_LOGI(TAG, "[%s] enter setting", __FUNCTION__);
    //     break;
    // case 4:
    //     lisaui_app_weather_del_weather_view();
    //     metadata_weather_t weather2 = {
    //         .weather = "晴",
    //         .city = "潮州",
    //         // .location = "深圳",
    //         // .time = "2025-01-22 12:00",
    //         // .week = "星期二",
    //         .date = "04/20",
    //         // .title = "天气",
    //         .temperature = "31C",
    //         // .temperature = "25°C",
    //         // .temperature_range = "20°C - 30°C",
    //         .temperature_range = "20C ~ 33C",
    //         .description = "晴朗 天气优",
    //     };
    //     lisaui_app_weather_set_weather_view(&weather2);
    //     break;
    case 5:
        lisaui_app_enter(UI_APP_ID_WEATHER);
        ls_llm_dialog_popup("Test");
        ls_llm_dialog_popup("Test233123");
        ls_llm_dialog_popup("Test2114141");
        break;
    case 6:
        lisaui_app_enter(UI_APP_ID_SETTING);
        ls_llm_dialog_popup("Test");
        break;
    case 7:
        lisaui_app_enter(UI_APP_ID_AUDIO_PLAYER);
        lisaui_app_audio_player_set_song_view(&song, LISAUI_APP_AUDIO_PLAYER_STATE_PLAY);
        LISAUI_LOGI(TAG, "[%s] enter setting", __FUNCTION__);
        break;
    case 8:
        lisaui_app_enter(UI_APP_ID_STANDBY);
        lisaui_app_standby_set_emoji(LISAUI_APP_STANDBY_EMOJI_TYPE_STANDBY);
        break;
    case 9:
        lisaui_app_enter(UI_APP_ID_STANDBY);
        lisaui_app_standby_set_emoji(LISAUI_APP_STANDBY_EMOJI_TYPE_LISTENING);
        break;
    case 10:
        lisaui_app_enter(UI_APP_ID_STANDBY);
        lisaui_app_standby_set_emoji(LISAUI_APP_STANDBY_EMOJI_TYPE_STANDBY);
        break;

    default:
        test_index = 0;
        break;
    }
    test_index++;
    // if (count++ > 10) {
    //     LISAUI_LOGI(TAG, "[%s] delete timer", __FUNCTION__);
    //     lv_timer_del(timer);
    // }
}
#endif

static wifi_metadata_t test_wifi_item_list[] = {
    {0, "SSID1 sadasdadas", "", "PWD1", -50, 0, LISAUI_WIFI_STATUS_CONNECTED},
    {3, "SSID4sdadasdasdasdssssd", "", "PWD4", -80, 3, LISAUI_WIFI_STATUS_CONNECTING},
    {1, "SSID2", "", "PWD2", 60, 1, LISAUI_WIFI_STATUS_CONNECTED},
    {2, "SSID3", "", "PWD3", -70, 2, LISAUI_WIFI_STATUS_DISCONNECT},
    {3, "SSID3", "", "PWD3", -70, 2, LISAUI_WIFI_STATUS_DISCONNECT},
    {4, "SSID4sdadasdasdasdssssd", "", "PWD4", -80, 3, LISAUI_WIFI_STATUS_DISCONNECT},
};

void test_lisaui_example(void)
{

    lisaui_app_enter(UI_APP_ID_STANDBY);
#if 0
    // lisaui_app_enter(UI_APP_ID_TEMPLATE);
    // lisaui_app_enter(UI_APP_ID_ALARM);
    // lisaui_app_enter(UI_APP_ID_SETTING);
    // lisaui_app_enter(UI_APP_ID_WEATHER);
    // lisaui_app_enter(UI_APP_ID_AUDIO_PLAYER);
    // lisaui_app_enter(UI_APP_ID_WIFI);

    // lisaui_app_alarm_register_handler(lisaui_app_alarm_handler);
    // lisaui_taskbar_register_event_handler(lisaui_taskbar_event_handler);
#endif



}