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
#include "../app_common/lisaui_app_common.h"
#include "../app_common/lisaui_type.h"
#include "../app_framework/lisaui_app_manager.h"
#include "../app_framework/lisaui_dbus.h"

#include "assets/assets_res.h" 
#include "app_taskbar.h"

#include "app_launcher.h"
#include <stdbool.h>

static const char *TAG = "app_launcher";

#define LISAUI_LV_HOR_PCT(x) (LV_HOR_RES * x / 100)
#define LISAUI_LV_VER_PCT(x) (LV_VER_RES * x / 100)

#define LISAUI_LAUNCHER_ICON_MARGIN      20
#define LISAUI_LAUNCHER_ICON_SPACING     40
#define LISAUI_LAUNCHER_ICON_PANEL_WIDTH LV_HOR_RES
#define LISAUI_LAUNCHER_ICON_SHOW_COUNT  5

#define LISAUI_LAUNCHER_ICON_WIDTH 72//(LISAUI_LAUNCHER_ICON_PANEL_WIDTH / LISAUI_LAUNCHER_ICON_SHOW_COUNT + 20)
#if 0
static void icon_event_click_handler(lv_obj_t *obj, lv_event_t e)
{
    if (e == LV_EVENT_CLICKED) {
        // LISAUI_LOGI(TAG, "icon_event_click_handler");
        struct lisaui_app_t *app = (struct lisaui_app_t *)obj->user_data;
        if (app == NULL) {
            LISAUI_LOGW(TAG, "app is NULL");
            return;
        }
        // LISAUI_LOGI(TAG, "app: %s", app->icon->title);
        // lisaui_app_show_info(app);
        lisaui_app_enter(app->info.id);

#if CONFIG_LISAUI_DBUS_ENABLE
        lisaui_dbus_t *_app_manager_bus;
        if (lisaui_get_app_manager_bus(&_app_manager_bus) != LISAUI_ERR_OK) {
            LISAUI_LOGE(TAG, "Failed to get app manager bus");
            return;
        }
        lisaui_dbus_publish(_app_manager_bus, LISAUI_DBUS_APP_LAUNCHER, app);
#endif
    }
}

void lisaui_launcher_add_app_icon(lv_obj_t *icon_panel, struct lisaui_app_t *app)
{
    if (icon_panel == NULL || app == NULL) {
        LISAUI_LOGE(TAG, "icon_panel or app is NULL");
        return;
    }
    if (app->hidden_icon) {
        return;
    }
    // lv_obj_set_style_local_bg_color(icon_panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x00000));
    int hidden_icon_count = lisaui_app_get_registered_count() - lisaui_app_get_unhidden_count();
    int icon_panel_index = (app->info.uuid);

    int icon_panel_width = lisaui_app_get_registered_count() * (LISAUI_LAUNCHER_ICON_WIDTH  + LISAUI_LAUNCHER_ICON_SPACING);
    icon_panel_width = icon_panel_width < LV_HOR_RES ? LV_HOR_RES+200 : icon_panel_width;
    int icon_offset_x = (icon_panel_index-hidden_icon_count) * (LISAUI_LAUNCHER_ICON_WIDTH  + LISAUI_LAUNCHER_ICON_SPACING) + LISAUI_LAUNCHER_ICON_MARGIN;
    
    lv_obj_set_width(icon_panel, icon_panel_width); // 更新 icon_panel 宽度
    
    lv_obj_t *m_app_icon = lv_img_create(icon_panel, NULL);
    if (app->icon->zoom) {
        lv_img_set_zoom(m_app_icon, app->icon->zoom);
    }
    m_app_icon->user_data = app;
    
    lv_obj_align(m_app_icon, icon_panel, LV_ALIGN_IN_LEFT_MID, 0, LISAUI_LAUNCHER_ICON_MARGIN);
    lv_img_set_src(m_app_icon, app->icon->icon);
    lv_obj_set_click(m_app_icon, true);       // 设置为可点击
    lv_obj_set_drag_parent(m_app_icon, true); // 设置为可拖动
    lv_obj_set_event_cb(m_app_icon, icon_event_click_handler);
    lv_obj_set_x(m_app_icon, icon_offset_x);
    LISAUI_LOGV(TAG, "hidden_icon_count: %d | index:%d icon_offset_x: %d, icon_panel_width: %d", 
            hidden_icon_count, icon_panel_index, icon_offset_x, icon_panel_width);

    // m_app_title
    lv_obj_t *m_app_title = lv_label_create(icon_panel, NULL);
    _lisaui_lv_obj_set_default_style(m_app_title);
    lv_obj_set_style_local_text_font(m_app_title, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_chinese_18);
    lv_obj_align(m_app_title, m_app_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 16);

    lv_label_set_text(m_app_title, app->icon->title);

}


#if CONFIG_LISAUI_DBUS_ENABLE
static void _lisaui_bus_event_app_open_handler_cb(void *data)
{
    struct lisaui_app_t *app = (struct lisaui_app_t *)data;
    if (app == NULL) {
        LISAUI_LOGE(TAG, "app is NULL");
        return;
    }
    lisaui_app_show_info(app);
    lisaui_app_enter(app->info.id);
    LISAUI_LOGI(TAG, "%s: %s", __func__, app->icon->title);

    lisaui_dbus_t *m_taskbar_bus;
    if (lisaui_get_taskbar_dbus(&m_taskbar_bus) != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "Failed to get app manager bus");
        return;
    }
    LISAUI_LOGI(TAG, "lisaui_dbus_publish");
    lisaui_dbus_publish(m_taskbar_bus, LISAUI_DBUS_APP_ENTER, app);
}

static void _lisaui_bus_event_app_update_handler_cb(void *data)
{
    lisaui_launcher_update_app(NULL);
}
#endif
#else
void lisaui_launcher_add_app_icon(lv_obj_t *icon_container, struct lisaui_app_t *app)
{

    if (icon_container == NULL || app == NULL) {
        LISAUI_LOGE(TAG, "icon_panel or app is NULL");
        return;
    }
    if (app->hidden_icon) {
        return;
    }


    // uint32_t i;
    // for(i = 0; i < 15; i++) {
    //     lv_obj_t * obj = lv_obj_create(m_icon_container);
    //     lv_obj_align(obj, LV_ALIGN_CENTER, 0, 5);
    //     // lv_obj_set_size(obj, icon_panel_width, LV_SIZE_CONTENT);
    //     lv_obj_set_size(obj, icon_panel_width, icon_panel_width);

    //     lv_obj_t * label = lv_label_create(obj);
    //     lv_label_set_text_fmt(label, "%"LV_PRIu32, i);
    //     lv_obj_center(label);
    // }
    lv_obj_t * icon_panel = lv_obj_create(icon_container);
    lv_obj_align(icon_panel, LV_ALIGN_CENTER, 0, 5);

    // lv_obj_set_style_local_bg_color(icon_panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x00000));
    int hidden_icon_count = lisaui_app_get_registered_count() - lisaui_app_get_unhidden_count();
    int icon_panel_index = (app->info.uuid);

    int icon_panel_width = lisaui_app_get_registered_count() * (LISAUI_LAUNCHER_ICON_WIDTH  + LISAUI_LAUNCHER_ICON_SPACING);
    icon_panel_width = icon_panel_width < LV_HOR_RES ? LV_HOR_RES+200 : icon_panel_width;
    int icon_offset_x = (icon_panel_index-hidden_icon_count) * (LISAUI_LAUNCHER_ICON_WIDTH  + LISAUI_LAUNCHER_ICON_SPACING) + LISAUI_LAUNCHER_ICON_MARGIN;
    
    lv_obj_set_width(icon_panel, icon_panel_width); // 更新 icon_panel 宽度
    
    lv_obj_t *m_app_icon = lv_img_create(icon_panel);
    if (app->icon->zoom) {
        lv_img_set_zoom(m_app_icon, app->icon->zoom);
    }
    m_app_icon->user_data = app;
    
    // lv_obj_align(m_app_icon, icon_panel, LV_ALIGN_IN_LEFT_MID, 0, LISAUI_LAUNCHER_ICON_MARGIN);
    lv_img_set_src(m_app_icon, app->icon->icon);
    // lv_obj_set_click(m_app_icon, true);       // 设置为可点击
    // lv_obj_set_drag_parent(m_app_icon, true); // 设置为可拖动
    // lv_obj_set_event_cb(m_app_icon, icon_event_click_handler);
    lv_obj_set_x(m_app_icon, icon_offset_x);
    LISAUI_LOGV(TAG, "hidden_icon_count: %d | index:%d icon_offset_x: %d, icon_panel_width: %d", 
            hidden_icon_count, icon_panel_index, icon_offset_x, icon_panel_width);

    // m_app_title
    lv_obj_t *m_app_title = lv_label_create(icon_panel);
    // _lisaui_lv_obj_set_default_style(m_app_title);
    // lv_obj_set_style_local_text_font(m_app_title, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_chinese_18);
    // lv_obj_align(m_app_title, m_app_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 16);

    lv_label_set_text(m_app_title, app->icon->title);

}

#endif

static lv_obj_t *g_app_launcher = NULL;
static lv_obj_t *g_icon_panel = NULL;

lisaui_err_t lisaui_launcher_update_app(struct lisaui_app_t *app)
{
    if (g_icon_panel == NULL) {
        LISAUI_LOGE(TAG, "g_icon_panel is NULL");
        return LISAUI_ERR_FAIL;
    }
    if (app == NULL) {
        LISAUI_LOGE(TAG, "app is NULL");
        return LISAUI_ERR_FAIL;
    }
    lisaui_app_show_info(app);
    lisaui_launcher_add_app_icon(g_icon_panel, app);
}
#define LAUNCHER_ICON_ROW_NUM 4


lisaui_err_t app_launcher_create(void *parent)
{
    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    g_app_launcher = lv_obj_create(parent); // launcher 页面根容器
    _lisaui_set_style_container(g_app_launcher, lv_color_hex(0x3f0000), 255, lv_color_hex(0x000000), 0, 0);
    lv_obj_set_size(g_app_launcher, LV_PCT(100), LV_PCT(100));

    int icon_panel_width = lv_obj_get_width(g_app_launcher)/(LAUNCHER_ICON_ROW_NUM+1);

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_flex_flow(&style, LV_FLEX_FLOW_ROW_WRAP);
    // lv_style_set_flex_main_place(&style, LV_FLEX_ALIGN_SPACE_EVENLY);
    lv_style_set_layout(&style, LV_LAYOUT_FLEX);

    lv_obj_t * m_icon_container = lv_obj_create(g_app_launcher);
    lv_obj_set_size(m_icon_container,  LV_PCT(100), LV_PCT(80));
    // lv_obj_center(m_icon_container);
    // lv_obj_add_style(m_icon_container, &style, 0);
    lv_obj_align(m_icon_container, LV_ALIGN_CENTER, 0, 5);
    lv_obj_set_flex_flow(m_icon_container, LV_FLEX_FLOW_ROW);
    _lisaui_set_style_container(m_icon_container, lv_color_hex(0x003f00), 255, lv_color_hex(0x000000), 0, 0);

    g_icon_panel = m_icon_container;
#if 0
    g_app_launcher = lv_obj_create(parent, parent); // launcher 页面根容器
    _lisaui_set_style_container(g_app_launcher, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    lv_obj_set_size(g_app_launcher, LISAUI_LV_HOR_PCT(100), LISAUI_LV_HOR_PCT(100));

    lv_obj_t *m_icon_container = lv_page_create(g_app_launcher, NULL);
    lv_obj_set_size(m_icon_container, LISAUI_LV_HOR_PCT(100), LV_VER_RES);
    _lisaui_set_style_container(m_icon_container, lv_color_hex(0x000000), 200, lv_color_hex(0x000000), 0, 0);
    lv_page_set_scrollbar_mode(m_icon_container, LV_SCROLLBAR_MODE_OFF); // 隐藏滚动条
    lv_obj_align(m_icon_container, parent, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_page_set_edge_flash(m_icon_container, false); // 关闭边缘闪光

    g_icon_panel = lv_obj_create(m_icon_container, NULL);
    lv_obj_align(g_icon_panel, m_icon_container, LV_ALIGN_IN_TOP_LEFT, 0, LISAUI_STATUS_BAR_HEIGHT);
    lv_obj_set_size(g_icon_panel, lv_obj_get_width(m_icon_container), LV_VER_RES - LISAUI_STATUS_BAR_HEIGHT);

    // lv_page_set_scrollbar_mode(g_icon_panel, LV_SCROLLBAR_MODE_DRAG);
    lv_obj_set_drag_parent(g_icon_panel, true); // 设置为可拖动
    _lisaui_set_style_container(g_icon_panel, lv_color_hex(0x000000), 120, lv_color_hex(0x000000), 0, 0);
#endif
#if CONFIG_LISAUI_DBUS_ENABLE
    lisaui_dbus_t *_app_manager_bus;
    if (lisaui_get_app_manager_bus(&_app_manager_bus) != LISAUI_ERR_OK) {
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
    .icon = (const uint8_t *)&ui_img_icon_launcher_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_launcher = {
    .create = app_launcher_create,
    .destroy = app_launcher_destroy,
    .enter = app_launcher_enter,
    .exit = app_launcher_exit,

    .get_root_view = app_launcher_get_page,
    .info = {
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
    lisaui_app_set_app_register_hook(lisaui_launcher_update_app);

    return LISAUI_ERR_OK;
}

REGISTER_LISAUI_APP(launcher, &app_launcher, app_launcher_init);

