/**
 * @file app_wifi.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_wifi.h"
#include "lisaui_app_common.h"
#include "assets/assets_res.h"
#include "widget/ls_wifi_list.h"

static const char *TAG = "app_wifi";
static lv_obj_t *g_app_wifi = NULL;
static lv_obj_t *g_app_panel = NULL;
lv_obj_t *g_obj_wifi_list = NULL;

static void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    // setting_item_t *item = (setting_item_t *)lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED) {
        LISAUI_LOGI(TAG, "Clicked");
        // g_delete_alarm_menu = app_alarm_delete_menu_create(lv_layer_sys());
    }
}

static wifi_item_t test_wifi_item_list[] = {
    {0, "SSID1 sadasdadas", "PWD1", -50, 0, 0, 0},
    {3, "SSID4sdadasdasdasdssssd", "PWD4", -80, 3, 3, 0},
    {1, "SSID2", "PWD2", -60, 1, 1, 0},
    {2, "SSID3", "PWD3", -70, 2, 2, 0},
    {3, "SSID4sdadasdasdasdssssd", "PWD4", -80, 3, 3, 0},
};

void app_wifi_create_wifi_list(lv_obj_t *parent)
{
    g_obj_wifi_list = ls_wifi_list_create(parent);
    lv_obj_set_size(g_obj_wifi_list, LV_PCT(100), LV_PCT(100));
    ls_wifi_list_add_text(g_obj_wifi_list, "WIFI 列表");
    ls_wifi_list_add_btn(g_obj_wifi_list, test_wifi_item_list[0], event_handler, NULL);
    ls_wifi_list_add_btn(g_obj_wifi_list, test_wifi_item_list[1], event_handler, NULL);
    ls_wifi_list_add_text(g_obj_wifi_list, "网络");
    ls_wifi_list_add_btn(g_obj_wifi_list, test_wifi_item_list[2], event_handler, NULL);
    ls_wifi_list_add_btn(g_obj_wifi_list, test_wifi_item_list[3], event_handler, NULL);
    ls_wifi_list_add_btn(g_obj_wifi_list, test_wifi_item_list[4], event_handler, NULL);
}


lisaui_err_t app_wifi_create(void *parent)
{
    if (g_app_wifi != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_wifi = lv_obj_create(parent);
    _lisaui_set_style_container(g_app_wifi, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    g_app_panel = lv_obj_create(g_app_wifi);
    _lisaui_set_style_container(g_app_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    LISAUI_COMMON_SET_APP_VIEW_PANEL_SIZE(g_app_wifi, g_app_panel);

    app_wifi_create_wifi_list(g_app_panel);
    // app_wifi_create_wifi_connect(g_app_panel);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_wifi_destroy(void)
{
    LVGL_OBJ_SAFE_DEL(g_app_wifi);

    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_wifi_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_wifi_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_wifi_get_view(void)
{
    return g_app_wifi;
}

static struct app_icon_t app_icon_res_wifi = {
    .title = "WIFI",
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = &icon_img_app_wifi_png,
    .zoom = APP_ICON_ZOOM(0),
};

lisaui_app_t app_wifi = {
    .create = app_wifi_create,
    .destroy = app_wifi_destroy,
    .enter = app_wifi_enter,
    .exit = app_wifi_exit,

    .get_app_view = app_wifi_get_view,
    .info =
        {
            .name = "Wifi",
            .package_name = "com.listenai.lisaui.wifi",
            .id = UI_APP_ID_WIFI,
        },
    .icon = &app_icon_res_wifi,
};

lisaui_err_t app_wifi_init(void)
{
    lisaui_app_register(&app_wifi);
    return LISAUI_ERR_OK;
}

LISAUI_REGISTER_APP(wifi, &app_wifi, app_wifi_init);
