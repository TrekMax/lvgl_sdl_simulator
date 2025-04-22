/**
 * @file app_setting.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_setting.h"
#include "lisaui_app_common.h"
#include "../app_common.h"
#include "assets/assets_res.h"
#include "app_setting_view_volume_backlight.h"
#include "app_setting_view_wakeup_config.h"
#include "lisaui_app_manager.h"
#include "lisaui_log.h"
#include "lisaui_type.h"
#include "common_widgets.h"
#include "../app_weather/app_weather.h"

#include "lv_img_utils.h"

static const char *TAG = "app_setting";
lv_obj_t *g_app_setting = NULL;
lv_obj_t *g_app_panel = NULL;
lv_obj_t *g_settings_panel = NULL;

typedef struct _setting_item_t {
    const int id;
    const char *name;
    const lv_img_dsc_t *icon;
} setting_item_t;

UI_RES_IMG_NAME(alarm, LISAUI_APP_SETTING_UI_RES_PERFIX_PATH("assets/png/ic_setting_alarm.png"))
UI_RES_IMG_NAME(regular, LISAUI_APP_SETTING_UI_RES_PERFIX_PATH("assets/png/ic_setting_regular.png"))
UI_RES_IMG_NAME(wake, LISAUI_APP_SETTING_UI_RES_PERFIX_PATH("assets/png/ic_setting_wake.png"))
UI_RES_IMG_NAME(wifi, LISAUI_APP_SETTING_UI_RES_PERFIX_PATH("assets/png/ic_setting_wifi.png"))

static setting_item_t setting_items[] = {
    {LISAUI_APP_SETTING_ITEM_ID_REGULAR, "基础设置", &LV_IMG_DSC(regular)},
    {LISAUI_APP_SETTING_ITEM_ID_ALARM, "闹钟设置", &LV_IMG_DSC(alarm)},
    {LISAUI_APP_SETTING_ITEM_ID_WAKE, "唤醒交互", &LV_IMG_DSC(wake)},
    {LISAUI_APP_SETTING_ITEM_ID_WIFI, "网络设置", &LV_IMG_DSC(wifi)},
};

static lv_obj_t *temp_setting_item_view = NULL;

static void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    setting_item_t *item = (setting_item_t *)lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED) {
        LISAUI_LOGI(TAG, "Open setting: %s", item->name);
        switch (item->id) {
        case LISAUI_APP_SETTING_ITEM_ID_REGULAR:
            temp_setting_item_view = private_lisaui_app_view_create_volume_backlight(g_app_panel);
            break;

        case LISAUI_APP_SETTING_ITEM_ID_ALARM:
            lisaui_app_enter(UI_APP_ID_ALARM);
            break;

        case LISAUI_APP_SETTING_ITEM_ID_WAKE:
            temp_setting_item_view = private_lisaui_app_view_create_wakeup_config(g_app_panel);
            break;

        case LISAUI_APP_SETTING_ITEM_ID_WIFI:
            lisaui_app_enter(UI_APP_ID_WIFI);
            break;

        case LISAUI_APP_SETTING_ITEM_ID_WEATHER:
            lisaui_app_enter(UI_APP_ID_WEATHER);
            break;

        case LISAUI_APP_SETTING_ITEM_ID_AUDIO_PLAYER:
            lisaui_app_enter(UI_APP_ID_AUDIO_PLAYER);
            break;

        default:
            break;
        }
    }
}

lv_obj_t *app_settings_create_item_page(lv_obj_t *parent)
{
    g_settings_panel = lv_obj_create(parent);
    _lisaui_set_style_container(g_settings_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    lv_obj_set_size(g_settings_panel, LV_PCT(100), LV_PCT(100));
    lv_obj_center(g_settings_panel);

    lv_obj_set_layout(g_settings_panel, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(g_settings_panel, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_pad_row(g_settings_panel, 12, 0);
    lv_obj_set_style_pad_column(g_settings_panel, 12, 0);
    lv_obj_set_style_pad_all(g_settings_panel, 10, 0);

    lv_img_png_src_init(UI_RES_IMG_PNG(alarm));
    lv_img_png_src_init(UI_RES_IMG_PNG(regular));
    lv_img_png_src_init(UI_RES_IMG_PNG(wake));
    lv_img_png_src_init(UI_RES_IMG_PNG(wifi));

    for (int i = 0; i < sizeof(setting_items) / sizeof(setting_items[0]); i++) {
        lv_obj_t *btn = lv_btn_create(g_settings_panel);
        lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, (void *)&(setting_items[i]));
        lv_obj_set_size(btn, LV_PCT(45), 60);
        // lv_obj_set_size(btn, LV_PCT(48), LV_DPX(80));
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x24242d), 0);
        lv_obj_set_style_radius(btn, 10, 0);
        lv_obj_set_style_shadow_width(btn, 0, 0);
        lv_obj_set_style_border_width(btn, 0, 0);
        lv_obj_set_style_outline_width(btn, 0, 0);

        lv_obj_set_layout(btn, LV_LAYOUT_FLEX);
        lv_obj_set_flex_flow(btn, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(btn, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

        lv_obj_t *icon = lv_img_create(btn);
        lv_img_set_src(icon, setting_items[i].icon);
        // lv_obj_align(icon, LV_ALIGN_LEFT_MID, LV_DPX(10), 0);

        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, setting_items[i].name);
        // lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        // // lv_obj_set_size(label, LV_PCT(90), LV_DPX(100));
        // lv_obj_set_width(label, LV_PCT(80));
        // lv_obj_set_height(label, LV_DPX(30));
        lv_obj_align_to(label, icon, LV_ALIGN_OUT_RIGHT_MID, LV_DPX(20), 0);
        lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    return g_settings_panel;
}

lisaui_err_t lisaui_app_setting_enter_item_panel(void)
{
    LVGL_UI_LOCK();

    // lisaui_app_enter(UI_APP_ID_STANDBY);
    if (g_app_panel == NULL) {
        LISAUI_LOGE(TAG, "g_app_panel is NULL");
        LVGL_UI_UNLOCK();
        return LISAUI_ERR_FAIL;
    }
    if (temp_setting_item_view) {
        // lisaui_app_enter(UI_APP_ID_SETTING);
        // LVGL_OBJ_SAFE_DEL(temp_setting_item_view);
        lv_obj_del(g_settings_panel);
        app_settings_create_item_page(g_app_panel);
        temp_setting_item_view = NULL;
    } else {
        lisaui_app_enter(UI_APP_ID_STANDBY);
        LVGL_UI_UNLOCK();
        return LISAUI_ERR_OK;
    }

    // if (g_settings_panel) {
    //     lv_obj_del(g_settings_panel);
    //     app_settings_create_item_page(g_app_panel);
    // }
    LVGL_UI_UNLOCK();

    return LISAUI_ERR_OK;
}

lisaui_err_t app_setting_create(void *parent)
{
    if (g_app_setting != NULL) {
        return LISAUI_ERR_OK;
    }

    g_app_setting = lv_obj_create(NULL);
    lv_obj_clear_flag(g_app_setting, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(g_app_setting, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(g_app_setting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(g_app_setting, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_pad_all(g_app_setting, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    g_app_panel = lv_obj_create(g_app_setting);
    _lisaui_set_style_container(g_app_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    LISAUI_COMMON_SET_APP_VIEW_PANEL_SIZE(g_app_setting, g_app_panel);

    app_settings_create_item_page(g_app_panel);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_setting_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy", __LINE__, __func__);
    LVGL_OBJ_SAFE_DEL(g_app_panel);
    LVGL_OBJ_SAFE_DEL(g_app_setting);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_setting_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_setting_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_setting_get_page(void)
{
    return g_app_setting;
}

static struct app_icon_t app_icon_res = {
    // .title = "Setting",
    .title = "设置",
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img_icon_setting_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_setting = {
    .create = app_setting_create,
    .destroy = app_setting_destroy,
    .enter = app_setting_enter,
    .exit = app_setting_exit,

    .get_root_view = app_setting_get_page,
    .info =
        {
            .name = "Setting",
            .package_name = "com.listenai.lisaui.setting",
            .id = UI_APP_ID_SETTING,
        },
    .icon = &app_icon_res,
};

lisaui_err_t app_setting_init(void)
{
    lisaui_app_register(&app_setting);
    return LISAUI_ERR_OK;
}

LISAUI_REGISTER_APP(setting, &app_setting, app_setting_init);
