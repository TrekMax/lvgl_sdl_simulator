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

// #include "unity.h"

#if CONFIG_LVGL_SIMULATOR
#include <pthread.h>
#include <stdbool.h>
#else
#include "FreeRTOS.h"
#include "semphr.h"
#endif
static const char *TAG = "UI";

#if CONFIG_LVGL_SIMULATOR
pthread_mutex_t lvgl_mutex;
#else
SemaphoreHandle_t lvgl_mutex;
#endif

static void tset_lisaui_app_timer__cb(lv_timer_t *timer)
{
    static int count = 0;
    static int index = 0;
    switch (index++) {
        case 0:
            lisaui_app_enter(UI_APP_ID_TEMPLATE);
            break;
        case 1:
            lisaui_app_standby_set_emoji(LISAUI_APP_STANDBY_EMOJI_TYPE_STANDBY);
            lisaui_app_enter(UI_APP_ID_STANDBY);
            break;
        case 2:
            lisaui_app_standby_set_emoji(LISAUI_APP_STANDBY_EMOJI_TYPE_RECOGNITION);
        //     lisaui_app_enter(UI_APP_ID_LAUNCHER);
            break;
        case 3:
            lisaui_app_enter(UI_APP_ID_SETTING);
            break;
        default:
            index = 0;
            break;
    }
    
    if (count++ > 10) {
        LISAUI_LOGI(TAG, "[%s] delete timer", __FUNCTION__);
        lv_timer_del(timer);
    }
}

void lisaui_ui_init(void)
{
#if CONFIG_LVGL_SIMULATOR
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
    // lv_disp_t *dispp = lv_disp_get_default();

    // lv_theme_t *theme = LV_THEME_DEFAULT_INIT(
    //     lv_theme_get_color_primary(), lv_theme_get_color_secondary(), LV_THEME_MATERIAL_FLAG_DARK,
    //     lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
    // lv_theme_set_act(theme);

#if CONFIG_LVGL_SIMULATOR
    LISAUI_USE_APP(template);
    LISAUI_USE_APP(standby);
    // LISAUI_USE_APP(launcher);
    // LISAUI_USE_APP(launcher2);
    LISAUI_USE_APP(taskbar);

    // LISAUI_USE_APP(demo);
    // LISAUI_USE_APP(ocr);
    // LISAUI_USE_APP(audio_player);
    // LISAUI_USE_APP(dictionary);
    LISAUI_USE_APP(setting);
    // LISAUI_USE_APP(thermography);
    // LISAUI_USE_APP(lvgl_demo);
    // LISAUI_USE_APP(voice);
#endif
    lisaui_app_manager_init();
    // lisaui_app_manager_show_all_app_info();
    // lisaui_app_enter(UI_APP_ID_TEMPLATE);
    lv_timer_t *timer = lv_timer_create(tset_lisaui_app_timer__cb, 1000, NULL);
    if (timer == NULL) {
        LISAUI_LOGE(TAG, "[%s] Failed to create timer", __FUNCTION__);
        return;
    }
    // lv_timer_set_repeat_count(timer, LV_TIMER_REPEAT_INFINITE);
    // lv_timer_set_period(timer, 1000);
    // lv_timer_ready(timer);

    LISAUI_LOGI(TAG, "UI init done");
    LISAUI_LOGI(TAG, "[%s:%d] init done", __func__, __LINE__);
    LISAUI_LOGI(TAG, "[%s:%d] init done", __FILE__, __LINE__);

    test_lisaui_dbus_example1();
}