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
#include "../app_common/lisaui_app_common.h"
#include "../assets/assets_res.h"

static const char *TAG = "app_setting";
lv_obj_t *g_app_setting = NULL;

static lv_obj_t *slider_label;
static void slider_event_cb(lv_obj_t *slider, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED) {
        static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
        snprintf(buf, 4, "%u", lv_slider_get_value(slider));
        lv_label_set_text(slider_label, buf);
    }
}

lisaui_err_t app_setting_create(void *parent)
{
    if (g_app_setting != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_setting = lv_obj_create(parent, parent);
    _lisaui_set_style_container(g_app_setting, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    lv_obj_t *mui_label_backlight = lv_label_create(g_app_setting, NULL);
    lv_label_set_text(mui_label_backlight, "亮度配置");
    lv_obj_align(mui_label_backlight, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPX(30), -15);
    lv_obj_set_style_local_text_font(mui_label_backlight, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_chinese_18);

    lv_obj_t *mui_label_volume = lv_label_create(g_app_setting, NULL);
    lv_label_set_text(mui_label_volume, "音量配置");
    lv_obj_align(mui_label_volume, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPX(30), 35);
    lv_obj_set_style_local_text_font(mui_label_volume, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_chinese_18);

    /* Create a slider in the center of the display */
    lv_obj_t *slider = lv_slider_create(g_app_setting, NULL);
    lv_obj_set_width(slider, LV_DPI * 3);
    lv_obj_align(slider, NULL, LV_ALIGN_CENTER, LV_DPX(40), -15);
    lv_obj_set_event_cb(slider, slider_event_cb);
    lv_slider_set_range(slider, 0, 100);

    /* Create a label below the slider */
    slider_label = lv_label_create(g_app_setting, NULL);
    lv_label_set_text(slider_label, "0");
    lv_obj_set_auto_realign(slider_label, true);
    lv_obj_align(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, -30);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_setting_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
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
    .icon = (const uint8_t *)&ui_img_icon_setting_png,
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
            .name = "setting",
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

REGISTER_LISAUI_APP(setting, &app_setting, app_setting_init);
