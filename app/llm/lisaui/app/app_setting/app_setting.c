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
#include "../app_common.h"
#include "lisaui_app_common.h"
#include "assets/assets_res.h"
#include "app_setting_view_volume_backlight.h"

static const char *TAG = "app_setting";
lv_obj_t *g_app_setting = NULL;

lisaui_err_t app_setting_create(void *parent)
{
    if (g_app_setting != NULL) {
        return LISAUI_ERR_OK;
    }

    g_app_setting = lv_obj_create(NULL);
    lv_obj_clear_flag(g_app_setting, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(g_app_setting, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(g_app_setting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(g_app_setting, LV_PCT(100), 180);

    _lisaui_app_view_create_volume_backlight(g_app_setting);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_setting_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy", __LINE__, __func__);
    // uiAppSetting_LabelBacklight = NULL;
    // uiAppSetting_LabelVolume = NULL;
    // uiAppSetting_SliderBacklight = NULL;
    // uiAppSetting_SliderVolume = NULL;
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
