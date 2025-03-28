/**
 * @file app_launcher.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "../../app_common/lisaui_app_common.h"
#include "../../app_common/lisaui_type.h"
#include "../../app_framework/lisaui_app_manager.h"
#include "../../app_framework/lisaui_dbus.h"

#include "../assets/assets_res.h"
// #include "../app_taskbar.h"

#include "app_launcher.h"
#include <stdbool.h>

static const char *TAG = "app_launcher";

#define LISAUI_LAUNCHER_ICON_MARGIN      20
#define LISAUI_LAUNCHER_ICON_SPACING     40
#define LISAUI_LAUNCHER_ICON_PANEL_WIDTH LV_HOR_RES
#define LISAUI_LAUNCHER_ICON_SHOW_COUNT  5

#define LISAUI_LAUNCHER_ICON_WIDTH 72 //(LISAUI_LAUNCHER_ICON_PANEL_WIDTH / LISAUI_LAUNCHER_ICON_SHOW_COUNT + 20)
static void icon_event_click_handler(lv_event_t *event)
{
    // LISAUI_LOGI(TAG, "icon_event_click_handler");
    lv_event_code_t event_code = lv_event_get_code(event);
    lv_obj_t *target = lv_event_get_target(event);
    if (event_code == LV_EVENT_CLICKED) {
        struct lisaui_app_t *app = (struct lisaui_app_t *)lv_event_get_user_data(event);
        if (app == NULL) {
            LISAUI_LOGW(TAG, "app is NULL");
            return;
        }
        LISAUI_LOGI(TAG, "app: %s", app->icon->title);
        // lisaui_app_show_info(app);
        lisaui_app_enter(app->info.id);

#if CONFIG_LISAUI_DBUS_ENABLE
        lisaui_dbus_t *_app_manager_bus;
        if (lisaui_app_manager_get_bus(&_app_manager_bus) != LISAUI_ERR_OK) {
            LISAUI_LOGE(TAG, "Failed to get app manager bus");
            return;
        }
        lisaui_dbus_publish(_app_manager_bus, LISAUI_DBUS_APP_LAUNCHER, app);
#endif
    }
}

void lisaui_launcher_add_app_icon(lv_obj_t *icon_container, struct lisaui_app_t *app)
{
    if (icon_container == NULL || app == NULL) {
        LISAUI_LOGE(TAG, "icon_panel or app is NULL");
        return;
    }
    if (app->hidden_icon) {
        return;
    }

    lv_obj_t *icon_panel = lv_obj_create(icon_container);
    // lv_obj_center(icon_panel);
    lv_obj_set_height(icon_panel, LV_PCT(100));
    // lv_obj_align(icon_panel, LV_ALIGN_CENTER, 0, LV_DPX(20));
    // lv_obj_set_height(icon_panel, LV_SIZE_CONTENT);
    // lv_obj_align(icon_panel, LV_ALIGN_CENTER, 0, 50);
    // lv_obj_set_y(icon_panel, 10);
    _lisaui_set_style_container(icon_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
#if 0
    lv_obj_t * obj;
    lv_obj_t * label;

    /*Add items to the row*/
    obj = lv_btn_create(icon_panel);
    lv_obj_set_size(obj, 100, LV_PCT(100));

    label = lv_label_create(obj);
    lv_label_set_text_fmt(label, "Item: %"LV_PRIu32, app->info.id);
    lv_obj_center(label);

    // /*Add items to the column*/
    // obj = lv_btn_create(cont_col);
    // lv_obj_set_size(obj, LV_PCT(100), LV_SIZE_CONTENT);

    // label = lv_label_create(obj);
    // lv_label_set_text_fmt(label, "Item: %"LV_PRIu32, i);
    // lv_obj_center(label);
    #else
    lv_obj_t *m_app_icon = lv_img_create(icon_panel);
    lv_obj_align(m_app_icon, LV_ALIGN_CENTER, 0, -LV_DPX(20));
    lv_obj_add_flag(m_app_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(m_app_icon, icon_event_click_handler, LV_EVENT_CLICKED, app);
    lv_img_set_src(m_app_icon, app->icon->icon);
    if (app->icon->zoom) {
        lv_img_set_zoom(m_app_icon, app->icon->zoom);
    }

    lv_obj_t *m_app_title = lv_label_create(icon_panel);
    lv_label_set_text(m_app_title, app->icon->title);
    lv_obj_align(m_app_title, LV_ALIGN_BOTTOM_MID, 0, -LV_DPX(10));

    lv_obj_set_style_text_color(m_app_title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(m_app_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#if CONFIG_LISAUI_FONT_LANGUAGE_ZH_CN_ENABLE
    lv_obj_set_style_text_font(m_app_title, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    lv_obj_set_style_text_font(m_app_title, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
#endif
}

static lv_obj_t *g_app_launcher = NULL;
static lv_obj_t *g_icon_panel = NULL;

lisaui_err_t lisaui_launcher_register_app(struct lisaui_app_t *app)
{
    if (g_icon_panel == NULL | app == NULL) {
        LISAUI_LOGE(TAG, "g_icon_panel or app is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    // LISAUI_LOGD(TAG, "--->app: %s", app->icon->title);
    // lisaui_app_manager_show_app_info(app);
    lisaui_launcher_add_app_icon(g_icon_panel, app);
    return LISAUI_ERR_OK;
}
lisaui_err_t lisaui_launcher_update_app_icon(void)
{
    if (g_icon_panel == NULL) {
        LISAUI_LOGE(TAG, "g_icon_panel is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    lv_obj_clean(g_icon_panel);
    for (int i = 0; i < lisaui_app_manager_get_registered_count(); i++) {
        struct lisaui_app_t *app = NULL;
        if (lisaui_app_manager_get_app_by_uuid(i, &app) != LISAUI_ERR_OK) {
            // LISAUI_LOGE(TAG, "Failed to get app by uuid: %d", i);
            // return LISAUI_ERR_FAIL;
            continue;
        }
        if (app == NULL) {
            // LISAUI_LOGE(TAG, "app is NULL");
            continue;
            // return LISAUI_ERR_INVALID_PARAM;
        }
        lisaui_launcher_add_app_icon(g_icon_panel, app);
    }
    return LISAUI_ERR_OK;
}
lisaui_err_t lisaui_launcher_update_app(struct lisaui_app_t *app)
{
    if (g_icon_panel == NULL | app == NULL) {
        LISAUI_LOGE(TAG, "g_icon_panel or app is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    if (app == NULL) {
        LISAUI_LOGE(TAG, "app is NULL");
        return LISAUI_ERR_FAIL;
    }
    lisaui_app_manager_show_app_info(app);
    lisaui_launcher_add_app_icon(g_icon_panel, app);
    return LISAUI_ERR_OK;
}
#define LAUNCHER_ICON_ROW_NUM 4
lisaui_err_t app_launcher_create(void *parent)
{
    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    g_app_launcher = lv_obj_create(parent); // launcher 页面根容器
    _lisaui_set_style_container(g_app_launcher, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    lv_obj_set_size(g_app_launcher, LV_PCT(100), LV_PCT(100));

    // static lv_style_t style;
    // lv_style_init(&style);
    // lv_style_set_flex_flow(&style, LV_FLEX_FLOW_ROW_WRAP);
    // lv_style_set_flex_main_place(&style, LV_FLEX_ALIGN_SPACE_EVENLY);
    // lv_style_set_layout(&style, LV_LAYOUT_FLEX);
    
    g_icon_panel = lv_obj_create(g_app_launcher);
    lv_obj_set_size(g_icon_panel, LV_PCT(100), LV_PCT(70));
    lv_obj_set_y(g_icon_panel, LV_DPX(LISAUI_STATUS_BAR_HEIGHT+10));
    // lv_obj_set_height(m_icon_container, LV_PCT(60));
    // lv_obj_set_width(m_icon_container, LV_PCT(100));
    _lisaui_set_style_container(g_icon_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    
    // lv_obj_align(m_icon_container, LV_ALIGN_CENTER, 0, 5);
    lv_obj_set_flex_flow(g_icon_panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(g_icon_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    // lv_obj_center(g_icon_panel);
    lv_obj_set_scrollbar_mode(g_icon_panel, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_set_scroll_dir(page, LV_DIR_TOP | LV_DIR_BOTTOM); // 仅允许上下滑动

#if CONFIG_LISAUI_DBUS_ENABLE
    lisaui_dbus_t *_app_manager_bus;
    if (lisaui_app_manager_get_bus(&_app_manager_bus) != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "Failed to get app manager bus");
        return LISAUI_ERR_FAIL;
    }

    lisaui_dbus_subscribe(_app_manager_bus, LISAUI_DBUS_APP_UPDATE, _lisaui_bus_event_app_update_handler_cb);
    lisaui_dbus_subscribe(_app_manager_bus, LISAUI_DBUS_APP_LAUNCHER, _lisaui_bus_event_app_open_handler_cb);
#endif
    return LISAUI_ERR_OK;
}

lisaui_err_t app_launcher_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_launcher_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_launcher_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_launcher_get_page(void)
{
    return g_app_launcher;
}

static struct app_icon_t app_icon_res = {
#if CONFIG_LISAUI_FONT_LANGUAGE_ZH_CN_ENABLE
    .title = "启动器",
#else
    .title = "Launcher",
#endif
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img_icon_launcher_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_launcher = {
    .create = app_launcher_create,
    .destroy = app_launcher_destroy,
    .enter = app_launcher_enter,
    .exit = app_launcher_exit,

    .get_root_view = app_launcher_get_page,
    .info =
        {
            .name = "launcher",
            .package_name = "com.listenai.lisaui.launcher",
            .id = UI_APP_ID_LAUNCHER,
            .type = LISAUI_APP_TYPE_SYSTEM,
        },
    .icon = &app_icon_res,
    .hidden_icon = true,
};

lisaui_err_t app_launcher_init(void)
{
    lisaui_app_register(&app_launcher);
    lisaui_app_enter(UI_APP_ID_LAUNCHER);
    lisaui_app_manager_set_register_app_hook(lisaui_launcher_register_app);
    lisaui_app_manager_set_unregister_app_hook(lisaui_launcher_update_app);

    return LISAUI_ERR_OK;
}

LISAUI_REGISTER_APP(launcher, &app_launcher, app_launcher_init);
