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
#include "app/app_standby/app_standby.h"
#include "app/app_weather/app_weather.h"

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

#define TEST_LISAUI_APP 0

#if TEST_LISAUI_APP
static int count = 0;
static int test_index = 0;
static void test_lisaui_app_timer_cb(lv_timer_t *timer)
{
    LISAUI_LOGI(TAG, "[%s] test_lisaui_app_timer_cb index:%d", __FUNCTION__, test_index);
    switch (test_index++) {
    case 0:
        lisaui_app_weather_del_weather_view();
        lisaui_app_enter(UI_APP_ID_TEMPLATE);
        break;
    case 1:
        //     lisaui_app_standby_set_emoji(LISAUI_APP_STANDBY_EMOJI_TYPE_STANDBY);
        //     lisaui_app_enter(UI_APP_ID_STANDBY);
        metadata_weather_t weather = {
            .type = 0,
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
        lisaui_app_weather_set_weather_view(&weather);
        break;

    case 2:
        lisaui_app_weather_del_weather_view();
        lisaui_app_enter(UI_APP_ID_SETTING);
        LISAUI_LOGI(TAG, "[%s] enter setting", __FUNCTION__);
        break;

    case 3:
        lisaui_app_weather_del_weather_view();
        metadata_weather_t weather2 = {
            .type = 0,
            .city = "潮州",
            // .location = "深圳",
            // .time = "2025-01-22 12:00",
            // .week = "星期二",
            .date = "04/20",
            // .title = "天气",
            .temperature = "31C",
            // .temperature = "25°C",
            // .temperature_range = "20°C - 30°C",
            .temperature_range = "20C ~ 33C",
            .description = "晴朗 天气优",
        };
        lisaui_app_weather_set_weather_view(&weather2);
        break;
    //     lisaui_app_standby_set_emoji(LISAUI_APP_STANDBY_EMOJI_TYPE_RECOGNITION);
    // //     lisaui_app_enter(UI_APP_ID_LAUNCHER);
    //     break;
    case 5:
        lisaui_app_enter(UI_APP_ID_SETTING);

        extern int ls_llm_dialog_popup(const char *text);
        ls_llm_dialog_popup("Test");

        break;
    default:
        test_index = 0;
        break;
    }

    if (count++ > 10) {
        LISAUI_LOGI(TAG, "[%s] delete timer", __FUNCTION__);
        lv_timer_del(timer);
    }
}
#endif

void lisaui_ui_init(void)
{
#if CONFIG_LVGL_ENV_SIMULATOR
    if (pthread_mutex_init(&lvgl_mutex, NULL) != 0) {
        LISAUI_LOGE(TAG, "[%s] Failed to create lvgl_mutex", __FUNCTION__);
        return;
    }
#else
    lvgl_mutex = xSemaphoreCreateMutex();
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
    LISAUI_USE_APP(standby);
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

    // lisaui_app_enter(UI_APP_ID_TEMPLATE);
    // lisaui_app_enter(UI_APP_ID_ALARM);
    // lisaui_app_enter(UI_APP_ID_SETTING);
    // lisaui_app_enter(UI_APP_ID_WEATHER);
    // lisaui_app_enter(UI_APP_ID_AUDIO_PLAYER);
    // lisaui_app_enter(UI_APP_ID_WIFI);
#if TEST_LISAUI_APP

    lv_timer_t *timer = lv_timer_create(test_lisaui_app_timer_cb, 1000, NULL);
    if (timer == NULL) {
        LISAUI_LOGE(TAG, "[%s] Failed to create timer", __FUNCTION__);
        return;
    }
    // lv_timer_set_repeat_count(timer, LV_TIMER_REPEAT_INFINITE);
    // lv_timer_set_period(timer, 1000);
    // lv_timer_ready(timer);

    // test_lisaui_dbus_example1();
#endif
}