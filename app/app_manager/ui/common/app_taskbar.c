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
#include "lisaui_app_common.h"
#include "lisaui_app_manager.h"

#include "assets/assets_res_taskbar.h"
#include "app_taskbar.h"
#include "lisaui_type.h"
#include <time.h>

#define LISAUI_TASKBAR_TIME_UPDATE_INTERVAL 500
#define LISAUI_TASKBAR_PAD_LEFT             (80)
#define LISAUI_TASKBAR_PAD_RIGHT            (-50)
#define LISAUI_TASKBAR_PAD_TOP              0
#define LISAUI_TASKBAR_PAD_BOTTOM           0

lv_obj_t *g_app_taskbar = NULL;
lv_obj_t *m_label_time = NULL;
lv_obj_t *m_label_date = NULL;
lv_obj_t *g_taskbar_btn_back = NULL;

static const char *TAG = "app_taskbar";

static void taskbar_label_date_update_cb(lv_task_t *task)
{
    time_t now = time(NULL);
    struct tm *tm = localtime(&now);
    char date_str[40];
    snprintf(date_str, sizeof(date_str), "%04d-%02d-%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
    lv_label_set_text(m_label_date, date_str);
}


static void _lisaui_taskbar_create_date_label(lv_obj_t *parent)
{
    m_label_date = lv_label_create(parent, NULL);
    lv_label_set_text(m_label_date, "2025-01-01");
    lv_obj_align(m_label_date, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPX(LISAUI_TASKBAR_PAD_LEFT), 0);
    _lisaui_lv_obj_set_default_style(m_label_date);
    lv_task_create(taskbar_label_date_update_cb, 1000, LV_TASK_PRIO_LOW, NULL);
}
static void taskbar_label_time_update_cb(lv_task_t *task)
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
    m_label_time = lv_label_create(parent, NULL);
    lv_label_set_text(m_label_time, "9:00 AM");
    lv_obj_align(m_label_time, NULL, LV_ALIGN_IN_TOP_MID, 0, 8);
    _lisaui_lv_obj_set_default_style(m_label_time);
    lv_task_create(taskbar_label_time_update_cb, 500, LV_TASK_PRIO_LOW, NULL);
}

static void back_btn_event_click_handler(lv_obj_t *obj, lv_event_t e)
{
    if (e == LV_EVENT_CLICKED) {
        // lisaui_app_enter(app->info.id);
        int app_id = lisaui_app_get_current_appid();
        if (app_id == UI_APP_ID_LAUNCHER) {
            lisaui_app_create_toast("Can't exit taskbar");
            return;
        }
        lisaui_app_exit(app_id);
    }
}

static void _lisaui_taskbar_create_back_btn(lv_obj_t *parent)
{
    g_taskbar_btn_back = lv_btn_create(parent, NULL);
    lv_obj_set_size(g_taskbar_btn_back, 50, 50);
    lv_obj_align(g_taskbar_btn_back, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPX(4), 0);
    lv_obj_set_click(g_taskbar_btn_back, true);
    lv_obj_set_event_cb(g_taskbar_btn_back, back_btn_event_click_handler);

    _lisaui_lv_obj_set_btn_custom_style(g_taskbar_btn_back);
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

static void _lisaui_taskbar_battery_update_cb(lv_task_t *task)
{
    // charging = !charging;
    static int count = 0;
    static uint8_t battery_charging_animation = 0;
    if (charging) {
        battery_charging_animation = (battery_charging_animation + 1) % 5;
        if (count % 10 == 0) {
            // LISAUI_LOGI(TAG, "battery charging status:%s", charging ? "true" : "false");
            battery_percent = (battery_percent + 1) % 100;
            lv_label_set_text_fmt(battery_label, "%d%%", battery_percent);
            battery_level = battery_percent / 20;
        }
    }
    lv_img_set_src(battery_icon, charging ? _lisaui_taskbar_battery_charging_icon[battery_charging_animation]
                                          : _lisaui_taskbar_battery_icon[battery_level]);
    count++;
}

static void _lisaui_taskbar_create_battery(lv_obj_t *parent)
{
    battery_icon = lv_img_create(parent, NULL);
    lv_img_set_src(battery_icon, _lisaui_taskbar_battery_icon[0]);
    lv_obj_align(battery_icon, NULL, LV_ALIGN_IN_RIGHT_MID, LISAUI_TASKBAR_PAD_RIGHT, 0);

    battery_label = lv_label_create(parent, NULL);
    lv_label_set_text(battery_label, "100%");
    lv_obj_align(battery_label, battery_icon, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    _lisaui_lv_obj_set_default_style(battery_label);

    lv_task_create(_lisaui_taskbar_battery_update_cb, 500, LV_TASK_PRIO_LOW, NULL);
}
static void _lisaui_app_enter_handler_cb(void* data)
{
    struct lisaui_app_t *app = (struct lisaui_app_t *)data;
    if (app == NULL) {
        LISAUI_LOGE(TAG, "app is NULL");
        return;
    }
    LISAUI_LOGI(TAG, "---------------->taskbar back app: %s", app->icon->title);
    // lisaui_app_show_info(app);
    // lisaui_app_create_toast(app->icon->title);
    // lisaui_app_enter(app->info.id);
    // lisaui_app_exit(app->info.id);
    // lisaui_app_enter(UI_APP_ID_TASKBAR);
}

lisaui_err_t app_taskbar_create(void *parent)
{
    LISAUI_LOGI(TAG, "[%d:%s]----------------> create\n", __LINE__, __func__);
    g_app_taskbar = lv_obj_create(lv_layer_sys(), NULL);
    lv_obj_set_size(g_app_taskbar, LV_HOR_RES, LISAUI_STATUS_BAR_HEIGHT);
    _lisaui_set_style_container(g_app_taskbar, lv_color_hex(0x000000), 0, lv_color_hex(0x000000), 0, 0);

    _lisaui_taskbar_create_date_label(g_app_taskbar);
    _lisaui_taskbar_create_time_label(g_app_taskbar);
    _lisaui_taskbar_create_battery(g_app_taskbar);
    _lisaui_taskbar_create_back_btn(g_app_taskbar);

#if CONFIG_LISAUI_DBUS_ENABLE
    lisaui_dbus_t *m_taskbar_bus;
    if (lisaui_get_taskbar_dbus(&m_taskbar_bus) != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "Failed to get app manager bus");
        return LISAUI_ERR_FAIL;
    }
    
    lisaui_dbus_subscribe(m_taskbar_bus, LISAUI_DBUS_APP_ENTER, _lisaui_app_enter_handler_cb);
    return LISAUI_ERR_OK;
#endif
}

void lisaui_taskbar_hide(bool hide)
{
    if (g_app_taskbar == NULL) {
        return;
    }
    if (hide) {
        lv_obj_set_hidden(g_app_taskbar, true);
    } else {
        lv_obj_set_hidden(g_app_taskbar, false);
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

void * app_taskbar_get_page(void)
{
    return g_app_taskbar;
}

static struct app_icon_t app_icon_res = {
    .title = "taskbar",
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = (const uint8_t *)&ui_img_icon_scanner_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_taskbar = {
    .create = app_taskbar_create,
    .destroy = app_taskbar_destroy,
    .enter = app_taskbar_enter,
    .exit = app_taskbar_exit,

    .get_root_view = app_taskbar_get_page,
    .info = {
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
    LISAUI_LOGW(TAG, "------------------->app_taskbar_init");
    app_taskbar_create(NULL);
    return LISAUI_ERR_OK;
}

REGISTER_LISAUI_APP(taskbar, &app_taskbar, app_taskbar_init);
