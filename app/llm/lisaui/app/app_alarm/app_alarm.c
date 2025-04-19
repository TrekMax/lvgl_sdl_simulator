/**
 * @file app_alarm.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_alarm.h"
#include "app_common/lisaui_app_common.h"
// #include "assets/assets_res.h"
#include "widgets_common.h"

static const char *TAG = "app_alarm";
static lv_obj_t *g_app_alarm = NULL;
static lv_obj_t *g_app_panel = NULL;

lv_obj_t *g_obj_alarm_list = NULL;
lv_obj_t *g_obj_alarm_create_view = NULL;
lv_obj_t *g_delete_alarm_menu = NULL;
static void app_alarm_delete_menu_destroy(lv_obj_t *menu)
{
    if (menu == NULL) {
        return;
    }
    lv_obj_del(menu);
    menu = NULL;
}

static void msgbox_event_handler(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_current_target(e);
    LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
    if (e->code == LV_EVENT_CLICKED) {
        LISAUI_LOGI(TAG, "Clicked");
        app_alarm_delete_menu_destroy(g_delete_alarm_menu);
    }
}

static lv_obj_t *app_alarm_delete_menu_create(lv_obj_t *parent)
{
    lv_obj_t *menu = lv_obj_create(parent);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(menu, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(menu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *tips_label = lv_label_create(menu);
    lv_label_set_text(tips_label, "是否删除该闹钟");
    lv_obj_align(tips_label, LV_ALIGN_CENTER, 0, -LV_DPX(60));
    lv_obj_set_style_text_color(tips_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(tips_label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(tips_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *apply_btn = lv_btn_create(menu);
    lv_obj_align(apply_btn, LV_ALIGN_BOTTOM_MID, LV_DPX(80), -LV_DPX(30));
    lv_obj_add_event_cb(apply_btn, msgbox_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_size(apply_btn, LV_DPX(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(apply_btn, lv_color_hex(0x24242d), 0);
    lv_obj_set_style_radius(apply_btn, 8, 0);
    lv_obj_set_style_shadow_width(apply_btn, 0, 0);
    lv_obj_set_style_border_width(apply_btn, 0, 0);
    lv_obj_set_style_outline_width(apply_btn, 0, 0);

    lv_obj_t *label;
    label = lv_label_create(apply_btn);
    lv_label_set_text(label, "删除");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(label);

    lv_obj_t *cancel_btn = lv_btn_create(menu);
    lv_obj_align(cancel_btn, LV_ALIGN_BOTTOM_MID, -LV_DPX(80), -LV_DPX(30));
    lv_obj_set_size(cancel_btn, LV_DPX(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(cancel_btn, lv_color_hex(0x24242d), 0);
    lv_obj_set_style_radius(cancel_btn, 8, 0);
    lv_obj_set_style_shadow_width(cancel_btn, 0, 0);
    lv_obj_set_style_border_width(cancel_btn, 0, 0);
    lv_obj_set_style_outline_width(cancel_btn, 0, 0);
    lv_obj_add_event_cb(cancel_btn, msgbox_event_handler, LV_EVENT_CLICKED, NULL);

    label = lv_label_create(cancel_btn);
    lv_label_set_text(label, "取消");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(label);

    return menu;
}

static void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    // setting_item_t *item = (setting_item_t *)lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED) {
        LISAUI_LOGI(TAG, "Clicked");
        g_delete_alarm_menu = app_alarm_delete_menu_create(lv_layer_sys());
    }
}

void app_alarm_create_alarm_list(lv_obj_t *parent)
{
    g_obj_alarm_list = ls_lv_list_create(parent);
    lv_obj_set_size(g_obj_alarm_list, LV_PCT(100), LV_PCT(100));
    // ls_lv_list_add_text(g_obj_alarm_list, "闹钟列表");
    ls_lv_list_add_btn(g_obj_alarm_list, "07:00", "Alarm1", event_handler, NULL);
    ls_lv_list_add_btn(g_obj_alarm_list, "08:00", "Alarm1", event_handler, NULL);
    ls_lv_list_add_btn(g_obj_alarm_list, "09:00", "Alarm1", event_handler, NULL);
    ls_lv_list_add_btn(g_obj_alarm_list, "09:00", "Alarm1", event_handler, NULL);
    // ls_lv_list_add_text(g_obj_alarm_list, "闹钟列表");
    ls_lv_list_add_btn(g_obj_alarm_list, "09:00", "Alarm1", event_handler, NULL);
    ls_lv_list_add_btn(g_obj_alarm_list, "09:00", "Alarm1", event_handler, NULL);
    ls_lv_list_add_btn(g_obj_alarm_list, "09:00", "Alarm1", event_handler, NULL);
}

lisaui_err_t lisaui_app_alarm_op_alarm_clear(void)
{
    LVGL_UI_LOCK();
    // app_alarm_delete_menu_destroy(g_delete_alarm_menu);
    if (g_obj_alarm_list != NULL) {
        // lv_obj_del(g_delete_alarm_menu);
        // g_delete_alarm_menu = NULL;
        lv_obj_clean(g_obj_alarm_list);
    }
    LVGL_UI_UNLOCK();
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_alarm_op_alarm_add(const char *time, const char *date)
{
    LVGL_UI_LOCK();
    if (g_obj_alarm_list) {
        ls_lv_list_add_btn(g_obj_alarm_list, time, date, event_handler, NULL);
        LVGL_UI_UNLOCK();
        return LISAUI_ERR_OK;
    }
    LVGL_UI_UNLOCK();
    return LISAUI_ERR_OK;
}

static lv_obj_t *_lisaui_app_alarm_create_alarm_view(lv_obj_t *parent, const char *alarm_time_text,
                                                     const char *alarm_date_text)
{
    lv_obj_t *alarm_page = lv_obj_create(parent);
    lv_obj_set_size(alarm_page, LV_PCT(100), LV_PCT(100));
    _lisaui_set_style_container(alarm_page, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    lv_obj_set_style_radius(alarm_page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(alarm_page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(alarm_page, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *tip_label = lv_label_create(alarm_page);
    lv_label_set_text(tip_label, "闹钟设置成功");
    lv_obj_align(tip_label, LV_ALIGN_TOP_MID, 0, LV_DPX(0));
    lv_obj_set_style_text_color(tip_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(tip_label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(tip_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(tip_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *alarm_label = lv_label_create(alarm_page);
    // lv_label_set_text(alarm_label, "07:00");
    lv_label_set_text(alarm_label, alarm_time_text);

    lv_obj_align(alarm_label, LV_ALIGN_CENTER, 0, -LV_DPX(20));
    lv_obj_set_style_text_color(alarm_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(alarm_label, &lv_font_rubik_bold_64, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(alarm_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(alarm_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *date_label = lv_label_create(alarm_page);
    // lv_label_set_text(date_label, "4 月 1 日 周四");
    lv_label_set_text(date_label, alarm_date_text);
    lv_obj_align(date_label, LV_ALIGN_BOTTOM_MID, 0, -LV_DPX(20));
    lv_obj_set_style_text_color(date_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(date_label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(date_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(date_label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_alarm_op_alarm_add_view(const char *alarm_time_text, const char *alarm_date_text)
{
    LVGL_UI_LOCK();
    if (g_app_panel) {
        if (g_obj_alarm_create_view != NULL) {
            lv_obj_del(g_obj_alarm_create_view);
            g_obj_alarm_create_view = NULL;
        }
        g_obj_alarm_create_view = _lisaui_app_alarm_create_alarm_view(g_app_panel, alarm_time_text, alarm_date_text);
    }
    LVGL_UI_UNLOCK();
    return LISAUI_ERR_OK;
}

lisaui_err_t app_alarm_create(void *parent)
{
    if (g_app_alarm != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_alarm = lv_obj_create(parent);
    _lisaui_set_style_container(g_app_alarm, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    g_app_panel = lv_obj_create(g_app_alarm);
    _lisaui_set_style_container(g_app_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    LISAUI_COMMON_SET_APP_VIEW_PANEL_SIZE(g_app_alarm, g_app_panel);

    app_alarm_create_alarm_list(g_app_panel);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_alarm_destroy(void)
{
    LVGL_OBJ_SAFE_DEL(g_app_alarm);

    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_alarm_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_alarm_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_alarm_get_page(void)
{
    return g_app_alarm;
}

static struct app_icon_t app_icon_res_alarm = {
    .title = "闹钟",
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = NULL, //&icon_img_app_store_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_alarm = {
    .create = app_alarm_create,
    .destroy = app_alarm_destroy,
    .enter = app_alarm_enter,
    .exit = app_alarm_exit,

    .get_root_view = app_alarm_get_page,
    .info =
        {
            .name = "Alarm",
            .package_name = "com.listenai.lisaui.alarm",
            .id = UI_APP_ID_ALARM,
        },
    .icon = &app_icon_res_alarm,
};

lisaui_err_t app_alarm_init(void)
{
    lisaui_app_register(&app_alarm);
    return LISAUI_ERR_OK;
}

LISAUI_REGISTER_APP(alarm, &app_alarm, app_alarm_init);