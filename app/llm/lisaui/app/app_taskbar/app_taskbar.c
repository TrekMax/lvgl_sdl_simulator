/**
 * @file app_taskbar.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "app_taskbar.h"
#include "../app_common.h"
#include "lisaui_app_common.h"
#include "assets/assets_res.h"

#include <stdio.h>
#include <time.h>

#define LISAUI_TASKBAR_TIME_UPDATE_INTERVAL 500
#define LISAUI_TASKBAR_PAD_LEFT             (80)
#define LISAUI_TASKBAR_PAD_RIGHT            (50)
#define LISAUI_TASKBAR_PAD_TOP              0
#define LISAUI_TASKBAR_PAD_BOTTOM           0

lv_obj_t *g_app_taskbar = NULL;
lv_obj_t *m_label_time = NULL;
lv_obj_t *g_taskbar_btn_back = NULL;
lv_obj_t *g_taskbar_btn_close = NULL;
lv_obj_t *g_taskbar_btn_home = NULL;

static const char *TAG = "app_taskbar";
#if 1

static void taskbar_label_time_update_cb(lv_timer_t *timer)
{
    static bool dot_hide_flag = false;
    dot_hide_flag = !dot_hide_flag;
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char time_str[10];
    snprintf(time_str, sizeof(time_str), "%02d%s%02d %s", tm->tm_hour, dot_hide_flag ? ":" : " ", tm->tm_min,
             tm->tm_hour < 12 ? "AM" : "PM");
    lv_label_set_text(m_label_time, time_str);
}

static void _lisaui_taskbar_create_time_label(lv_obj_t *parent)
{
    m_label_time = lv_label_create(parent);
    lv_label_set_text(m_label_time, "9:00 AM");
    lv_obj_align(m_label_time, LV_ALIGN_CENTER, LV_DPX(20), 0);

    lv_obj_set_style_text_color(m_label_time, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(m_label_time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(m_label_time, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_timer_t *timer = lv_timer_create(taskbar_label_time_update_cb, 500, m_label_time);
}

lv_obj_t *m_label_date = NULL;
static void taskbar_label_date_update_cb(lv_timer_t *timer)
{
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char date_str[40];
    snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    lv_label_set_text(m_label_date, date_str);
}

static void _lisaui_taskbar_create_date_label(lv_obj_t *parent)
{
    m_label_date = lv_label_create(parent);
    lv_obj_set_size(m_label_date, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    // lv_obj_align(m_label_date, LV_ALIGN_LEFT_MID, LV_DPX(68), 0);
    lv_obj_align_to(m_label_date, g_taskbar_btn_home, LV_ALIGN_OUT_RIGHT_MID, LV_DPX(6), 0);

    lv_label_set_text(m_label_date, "2025/1/22");
    lv_obj_set_style_text_color(m_label_date, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(m_label_date, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(m_label_date, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_timer_t *timer = lv_timer_create(taskbar_label_date_update_cb, 900, m_label_date);
}

static void back_btn_event_click_handler(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        int app_id = lisaui_app_manager_get_current_appid();
        struct lisaui_app_t *app = NULL;
        if (lisaui_app_manager_get_app_by_id(app_id, &app) != LISAUI_ERR_OK) {
            LISAUI_LOGE(TAG, "Failed to get app by id: %d", app_id);
            return;
        }
        if (app->info.type == LISAUI_APP_TYPE_LAUNCHER) {
            lisaui_popup_toast("Can't exit or close launcher");
            return;
        }
        if (lisaui_app_get_lock_state()) {
            lisaui_popup_toast("App view is locked");
            return;
        }
        if (target == g_taskbar_btn_back) {
            lisaui_app_exit(app_id);
        } else if (target == g_taskbar_btn_close) {
            lisaui_app_close(app_id);
        } else if (target == g_taskbar_btn_home) {
            lisaui_app_enter(UI_APP_ID_LAUNCHER);
        }
    }
}

static void _lisaui_taskbar_create_back_btn(lv_obj_t *parent)
{
    g_taskbar_btn_back = lv_btn_create(parent);
    lv_obj_set_size(g_taskbar_btn_back, LV_DPX(50), LV_DPX(LISAUI_STATUS_BAR_HEIGHT-10));
    lv_obj_align(g_taskbar_btn_back, LV_ALIGN_LEFT_MID, LV_DPX(4), 0);
    lv_obj_add_event_cb(g_taskbar_btn_back, back_btn_event_click_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_radius(g_taskbar_btn_back, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label = lv_label_create(g_taskbar_btn_back);
    lv_label_set_text(label, LV_SYMBOL_LEFT);
    // _lisaui_lv_obj_set_default_style(label);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    g_taskbar_btn_close = lv_btn_create(parent);
    lv_obj_set_size(g_taskbar_btn_close, LV_DPX(50), LV_DPX(LISAUI_STATUS_BAR_HEIGHT-10));
    lv_obj_align_to(g_taskbar_btn_close, g_taskbar_btn_back, LV_ALIGN_OUT_RIGHT_MID, LV_DPX(2), 0);
    lv_obj_add_event_cb(g_taskbar_btn_close, back_btn_event_click_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_radius(g_taskbar_btn_close, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label_close = lv_label_create(g_taskbar_btn_close);
    lv_label_set_text(label_close, LV_SYMBOL_CLOSE);
    lv_obj_align(label_close, LV_ALIGN_CENTER, 0, 0);

    g_taskbar_btn_home = lv_btn_create(parent);
    lv_obj_set_size(g_taskbar_btn_home, LV_DPX(50), LV_DPX(LISAUI_STATUS_BAR_HEIGHT-10));
    lv_obj_align_to(g_taskbar_btn_home, g_taskbar_btn_close, LV_ALIGN_OUT_RIGHT_MID, LV_DPX(2), 0);
    lv_obj_add_event_cb(g_taskbar_btn_home, back_btn_event_click_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_radius(g_taskbar_btn_home, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *label_home = lv_label_create(g_taskbar_btn_home);
    lv_label_set_text(label_home, LV_SYMBOL_HOME);
    lv_obj_align(label_home, LV_ALIGN_CENTER, 0, 0);
}

static const lv_img_dsc_t *_lisaui_taskbar_battery_charging_icon[5] = {
    &ui_img__status_charging_1_png, &ui_img__status_charging_2_png, &ui_img__status_charging_3_png,
    &ui_img__status_charging_4_png, &ui_img__status_charging_5_png,
};

static const lv_img_dsc_t *_lisaui_taskbar_battery_icon[5] = {
    &ui_img__status_battery_1_png, &ui_img__status_battery_2_png, &ui_img__status_battery_3_png,
    &ui_img__status_battery_4_png, &ui_img__status_battery_5_png,
};

static int battery_level = 0;
static int battery_percent = 0;
static bool charging = true;
static lv_obj_t *battery_icon = NULL;
static lv_obj_t *battery_label = NULL;

lisaui_err_t lisaui_taskbar_set_battery_percent(int percent)
{
    battery_percent = percent;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_taskbar_set_battery_charging(bool is_charging)
{
    charging = is_charging;
    LISAUI_LOGI(TAG, "lisaui_taskbar_set_battery_charging status:%s", is_charging ? "true" : "false");
    return LISAUI_ERR_OK;
}

static void _lisaui_taskbar_battery_update_cb(lv_timer_t *timer)
{
    // charging = !charging;
    static int count = 0;
    static uint8_t battery_charging_animation = 0;
    if (charging) {
        battery_charging_animation = (battery_charging_animation + 1) % 5;
        if (count % 10 == 0) {
            // LISAUI_LOGI(TAG, "battery charging status:%s", charging ? "true" : "false");
            battery_percent = (battery_percent + 1) % 100;
            if (battery_label) {
                lv_label_set_text_fmt(battery_label, "%d%%", battery_percent);
            }
            battery_level = battery_percent / 20;
        }
    }
    lv_img_set_src(battery_icon, charging ? _lisaui_taskbar_battery_charging_icon[battery_charging_animation]
                                          : _lisaui_taskbar_battery_icon[battery_level]);
    count++;
}

static void _lisaui_taskbar_create_battery(lv_obj_t *parent)
{
    if (lv_obj_get_width(g_app_taskbar) > 400) {
        battery_label = lv_label_create(parent);
        lv_label_set_text(battery_label, "100%");
        lv_obj_align(battery_label, LV_ALIGN_RIGHT_MID, -LV_DPX(20), 0);
        // _lisaui_lv_obj_set_default_style(battery_label);
        lv_obj_set_style_text_color(battery_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(battery_label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(battery_label, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    battery_icon = lv_img_create(parent);
    lv_img_set_src(battery_icon, _lisaui_taskbar_battery_icon[0]);
    if (lv_obj_get_width(g_app_taskbar) > 400) {
        lv_obj_align_to(battery_icon, battery_label, LV_ALIGN_OUT_LEFT_MID, 0, 0);
    } else {
        lv_obj_align(battery_icon, LV_ALIGN_RIGHT_MID, -LV_DPX(20), 0);
    }
    // lv_img_set_zoom(battery_icon, 255*1.2);
    lv_timer_t *timer = lv_timer_create(_lisaui_taskbar_battery_update_cb, 500, battery_icon);
}
static void _lisaui_app_enter_handler_cb(void *data)
{
    struct lisaui_app_t *app = (struct lisaui_app_t *)data;
    if (app == NULL) {
        LISAUI_LOGE(TAG, "app is NULL");
        return;
    }
    LISAUI_LOGI(TAG, "taskbar back app: %s", app->icon->title);
    // lisaui_app_show_info(app);
    // lisaui_popup_toast(app->icon->title);
    // lisaui_app_enter(app->info.id);
    // lisaui_app_exit(app->info.id);
    // lisaui_app_enter(UI_APP_ID_TASKBAR);
}

#endif

static void event_handler_app_panel(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    LV_UNUSED(obj);

    if (event_code == LV_EVENT_GESTURE)
    {
        // lisaui_popup_toast("Gesture");
        LISAUI_LOGI(TAG, "Gesture");
        if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
            lv_indev_wait_release(lv_indev_get_act());
        }
    }
    else if (event_code == LV_EVENT_CLICKED) {
        // lisaui_popup_toast("Clicked");
        LISAUI_LOGI(TAG, "Clicked");
    }
    else if (event_code == LV_EVENT_PRESSED) {
        // lisaui_popup_toast("Pressed");
        LISAUI_LOGI(TAG, "Pressed");
    }
    else if (event_code == LV_EVENT_RELEASED) {
        // lisaui_popup_toast("Released");
        LISAUI_LOGI(TAG, "Released");
    }
}

lisaui_err_t app_taskbar_create(void *parent)
{
    g_app_taskbar = lv_obj_create(lv_layer_sys());
    lv_obj_set_size(g_app_taskbar, LV_PCT(100), LV_DPX(LISAUI_STATUS_BAR_HEIGHT));
    _lisaui_set_style_container(g_app_taskbar, lv_color_hex(0x000000), 0, lv_color_hex(0x000000), 0, 0);

    _lisaui_taskbar_create_back_btn(g_app_taskbar);
    if (lv_obj_get_width(g_app_taskbar) > 400) {
        _lisaui_taskbar_create_date_label(g_app_taskbar);
    }
    _lisaui_taskbar_create_time_label(g_app_taskbar);
    _lisaui_taskbar_create_battery(g_app_taskbar);

    lv_obj_add_event_cb(g_app_taskbar, event_handler_app_panel, LV_EVENT_ALL, NULL);

#if CONFIG_LISAUI_DBUS_ENABLE
    lisaui_dbus_t *m_taskbar_bus;
    if (lisaui_get_taskbar_dbus(&m_taskbar_bus) != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "Failed to get app manager bus");
        return LISAUI_ERR_FAIL;
    }

    lisaui_dbus_subscribe(m_taskbar_bus, LISAUI_DBUS_APP_ENTER, _lisaui_app_enter_handler_cb);
#endif
    return LISAUI_ERR_OK;
}

void lisaui_taskbar_hide(bool hide)
{
    if (g_app_taskbar == NULL) {
        return;
    }
    if (hide) {
        // lv_obj_set_hidden(g_app_taskbar, true);
    } else {
        // lv_obj_set_hidden(g_app_taskbar, false);
    }
}

#if CONFIG_LISAUI_DBUS_ENABLE
static lisaui_dbus_t *_dbus_taskbar = NULL;

lisaui_err_t lisaui_get_taskbar_dbus(lisaui_dbus_t **dbus)
{
    if (dbus == NULL) {
        LISAUI_LOGE(TAG, "dbus is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    if (_dbus_taskbar == NULL) {
        // LISAUI_LOGE(TAG, "App manager bus is NULL(App manager not initialized)");
        // return LISAUI_ERR_FAIL;
        _dbus_taskbar = lisaui_dbus_create();
        if (!_dbus_taskbar) {
            LISAUI_LOGE(TAG, "Failed to create event bus");
            return LISAUI_ERR_FAIL;
        }
        LISAUI_LOGI(TAG, "Event bus created");
    }
    *dbus = _dbus_taskbar;
    return LISAUI_ERR_OK;
}
#endif

lisaui_err_t app_taskbar_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    g_app_taskbar = NULL;
    return LISAUI_ERR_OK;
}

lisaui_err_t app_taskbar_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_taskbar_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_taskbar_get_page(void)
{
    return g_app_taskbar;
}

static struct app_icon_t app_icon_res = {
#if CONFIG_LISAUI_FONT_LANGUAGE_ZH_CN_ENABLE
    .title = "任务栏",
#else
    .title = "taskbar",
#endif
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = NULL,//&ui_img_icon_taskbar_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_taskbar = {
    .create = app_taskbar_create,
    .destroy = app_taskbar_destroy,
    .enter = app_taskbar_enter,
    .exit = app_taskbar_exit,

    .get_root_view = app_taskbar_get_page,
    .info =
        {
            .name = "taskbar",
            .package_name = "com.listenai.lisaui.taskbar",
            .id = UI_APP_ID_TASKBAR,
            .type = LISAUI_APP_TYPE_SYSTEM,
        },
    .icon = &app_icon_res,
    .hidden_icon = true,
};

lisaui_err_t app_taskbar_init(void)
{
    lisaui_app_register(&app_taskbar);
    app_taskbar_create(NULL);
    return LISAUI_ERR_OK;
}

LISAUI_REGISTER_APP(taskbar, &app_taskbar, app_taskbar_init);
