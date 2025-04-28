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
#include "app_wifi/wifi_type.h"
#include "lisaui_app_common.h"
#include "assets/assets_res.h"
#include "widget/ls_wifi_list.h"

#include "lv_img_utils.h"
#include <src/core/lv_obj_pos.h>
#include <src/misc/lv_area.h>

static const char *TAG = "app_wifi";
static lv_obj_t *g_app_wifi = NULL;
static lv_obj_t *g_app_panel = NULL;
lv_obj_t *g_obj_wifi_list = NULL;
static lv_img_dsc_t img_gif_anim_circle;

#if CONFIG_LVGL_ENV_SIMULATOR
#define LISAUI_APP_LS_LLM_DIALOG_UI_RES_PERFIX_PATH(path) "app/llm/lisaui/app/app_wifi/" path
#else
#define LISAUI_APP_LS_LLM_DIALOG_UI_RES_PERFIX_PATH(path) "src/ui/lisaui/app/app_wifi/" path
// app/llm/lisaui/app/app_wifi/assets/gif/anim_circle.gif
#endif

UI_RES_IMG_NAME(anim_circle, LISAUI_APP_LS_LLM_DIALOG_UI_RES_PERFIX_PATH("assets/gif/anim_circle_24x24.gif"))
UI_RES_IMG_NAME(wifi_refresh_icon, LISAUI_APP_LS_LLM_DIALOG_UI_RES_PERFIX_PATH("assets/png/ic_refresh.png"))
lv_obj_t *LV_OBJ_ICON(refresh_static);
lv_obj_t *refresh_icon = NULL;

static app_wifi_event_handler_t g_app_wifi_event_handler = NULL;
lisaui_err_t lisaui_app_wifi_register_event_handler(app_wifi_event_handler_t handler)
{
    if (handler == NULL) {
        LISAUI_LOGE(TAG, "handler is NULL");
        return LISAUI_ERR_FAIL;
    }
    g_app_wifi_event_handler = handler;
    return LISAUI_ERR_OK;
}

static lv_obj_t *g_apply_btn = NULL;
static lv_obj_t *g_cancel_btn = NULL;
static lv_obj_t *password = NULL;
static lv_obj_t *g_wifi_connect_msgbox = NULL;

static void app_wifi_destroy_connect_ap_view(lv_obj_t *menu)
{
    if (menu == NULL) {
        return;
    }
    lv_obj_del(menu);
    menu = NULL;
}

static void msgbox_event_handler(lv_event_t *event)
{
    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t event_code = lv_event_get_code(event);
    LISAUI_LOGI(TAG, "button clicked");

    if (event_code == LV_EVENT_CLICKED) {
        if (g_apply_btn && g_apply_btn == obj) {
            LISAUI_LOGI(TAG, "button apply clicked");
            wifi_metadata_t *wifi_item = (wifi_metadata_t *)lv_event_get_user_data(event);
            if (wifi_item == NULL) {
                LISAUI_LOGE(TAG, "item is NULL");
                return;
            }
            if (password) {
                const char *psw = lv_textarea_get_text(password);
                if (strlen(psw) < 8) {
                    // LISAUI_LOGE(TAG, "password is too short");
                    lisaui_popup_toast("密码长度至少8位");
                    return;
                }
                strncpy(wifi_item->PWD, psw, LISAUI_APP_WIFI_PWD_MAX_LEN);
            }
            if (g_app_wifi_event_handler) {
                g_app_wifi_event_handler(LISAUI_WIFI_ITEM_AP, LISAUI_WIFI_OP_CONNECT, wifi_item);
            }
            app_wifi_destroy_connect_ap_view(g_wifi_connect_msgbox);
        }
        if (g_cancel_btn && g_cancel_btn == obj) {
            app_wifi_destroy_connect_ap_view(g_wifi_connect_msgbox);
        }
    }
}

static void ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED) {
        if (lv_indev_get_type(lv_indev_get_act()) != LV_INDEV_TYPE_KEYPAD) {
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_set_style_max_height(kb, LV_HOR_RES * 2 / 3, 0);
            lv_obj_update_layout(g_wifi_connect_msgbox); /*Be sure the sizes are recalculated*/
            lv_obj_set_height(g_wifi_connect_msgbox, LV_VER_RES - lv_obj_get_height(kb));
            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
        }
    } else if (code == LV_EVENT_DEFOCUSED) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_set_height(g_wifi_connect_msgbox, LV_VER_RES);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_indev_reset(NULL, ta);

    } else if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_set_height(g_wifi_connect_msgbox, LV_VER_RES);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta); /*To forget the last clicked object to make it focusable again*/
    }
}

static lv_obj_t *app_wifi_create_connect_ap_view(lv_obj_t *parent, wifi_metadata_t *wifi_item)
{
    lv_obj_t *menu = lv_obj_create(parent);
    lv_obj_set_size(menu, LV_PCT(100), LV_PCT(100));
    lv_obj_set_style_bg_color(menu, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(menu, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(menu, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *tips_label = lv_label_create(menu);
    lv_label_set_text_fmt(tips_label, "连接到 %s", wifi_item->SSID);
    lv_obj_align(tips_label, LV_ALIGN_CENTER, 0, -LV_DPX(80));
    lv_obj_set_style_text_color(tips_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(tips_label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(tips_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Create a keyboard*/
    lv_obj_t *kb = lv_keyboard_create(lv_scr_act());
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    password = lv_textarea_create(menu);
    lv_obj_align(password, LV_ALIGN_CENTER, LV_PCT(0), LV_DPX(0));
    // lv_obj_align(password, LV_ALIGN_CENTER, -LV_PCT(20), LV_DPX(0));
    // lv_obj_set_width(password, LV_PCT(60));
    lv_textarea_set_one_line(password, true);
    lv_textarea_set_password_mode(password, true);
    lv_textarea_set_placeholder_text(password, "Min. 8 chars.");
    lv_obj_add_event_cb(password, ta_event_cb, LV_EVENT_ALL, kb);
    lv_textarea_set_text(password, wifi_item->PWD);
    LISAUI_LOGI(TAG, "password:%s", wifi_item->PWD);

    lv_obj_t *password_show_btn = lv_btn_create(menu);
    lv_obj_set_size(password_show_btn, LV_DPX(40), LV_DPX(40));
    lv_obj_align_to(password_show_btn, password, LV_ALIGN_OUT_RIGHT_MID, LV_DPX(10), 0);
    lv_obj_set_style_bg_color(password_show_btn, lv_color_hex(0x24242d), 0);
    lv_obj_set_style_radius(password_show_btn, 8, 0);
    lv_obj_set_style_shadow_width(password_show_btn, 0, 0);
    lv_obj_set_style_border_width(password_show_btn, 0, 0);
    lv_obj_set_style_outline_width(password_show_btn, 0, 0);
    lv_obj_set_style_bg_opa(password_show_btn, 0, 0);
    lv_obj_set_style_border_opa(password_show_btn, 0, 0);
    lv_obj_set_style_outline_opa(password_show_btn, 0, 0);
    lv_obj_set_style_pad_all(password_show_btn, 0, 0);

    g_apply_btn = lv_btn_create(menu);
    // lv_obj_align(g_apply_btn, LV_ALIGN_BOTTOM_MID, LV_DPX(80), -LV_DPX(30));
    lv_obj_align_to(g_apply_btn, password, LV_ALIGN_OUT_BOTTOM_MID, LV_DPX(80), LV_DPX(30));
    lv_obj_add_event_cb(g_apply_btn, msgbox_event_handler, LV_EVENT_CLICKED, (void *)wifi_item);
    lv_obj_set_size(g_apply_btn, LV_DPX(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(g_apply_btn, lv_color_hex(0x5078D0), 0);
    lv_obj_set_style_radius(g_apply_btn, 8, 0);
    lv_obj_set_style_shadow_width(g_apply_btn, 0, 0);
    lv_obj_set_style_border_width(g_apply_btn, 0, 0);
    lv_obj_set_style_outline_width(g_apply_btn, 0, 0);

    lv_obj_t *label;
    label = lv_label_create(g_apply_btn);
    lv_label_set_text(label, "连接");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(label);

    g_cancel_btn = lv_btn_create(menu);
    // lv_obj_align(g_cancel_btn, LV_ALIGN_BOTTOM_MID, -LV_DPX(80), -LV_DPX(30));
    lv_obj_align_to(g_cancel_btn, password, LV_ALIGN_OUT_BOTTOM_MID, -LV_DPX(80), LV_DPX(30));
    lv_obj_set_size(g_cancel_btn, LV_DPX(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(g_cancel_btn, lv_color_hex(0x24242d), 0);
    lv_obj_set_style_radius(g_cancel_btn, 8, 0);
    lv_obj_set_style_shadow_width(g_cancel_btn, 0, 0);
    lv_obj_set_style_border_width(g_cancel_btn, 0, 0);
    lv_obj_set_style_outline_width(g_cancel_btn, 0, 0);
    lv_obj_add_event_cb(g_cancel_btn, msgbox_event_handler, LV_EVENT_CLICKED, (void *)wifi_item);

    label = lv_label_create(g_cancel_btn);
    lv_label_set_text(label, "取消");
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(label);

    return menu;
}

static void wifi_item_event_handler(lv_event_t *event)
{
    lv_event_code_t code = lv_event_get_code(event);
    lv_obj_t *obj = lv_event_get_target(event);
    if (code == LV_EVENT_CLICKED) {
        wifi_metadata_t *wifi_item = (wifi_metadata_t *)lv_event_get_user_data(event);
        if (wifi_item == NULL) {
            LISAUI_LOGE(TAG, "item is NULL");
            return;
        }
        g_wifi_connect_msgbox = app_wifi_create_connect_ap_view(lv_layer_top(), wifi_item);
    }
}

lisaui_err_t lisaui_app_add_wifi_list_item(wifi_metadata_t *wifi_item)
{
    if (g_obj_wifi_list == NULL) {
        g_obj_wifi_list = ls_wifi_list_create(g_app_panel);
        lv_obj_set_size(g_obj_wifi_list, LV_PCT(100), LV_PCT(100));
    }
    ls_wifi_list_add_btn(g_obj_wifi_list, wifi_item, wifi_item_event_handler, (void *)wifi_item);
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_del_wifi_list(void)
{
    if (g_obj_wifi_list == NULL) {
        return LISAUI_ERR_OK;
    }

    // FIXME：销毁旧的列表
    return LISAUI_ERR_OK;
}


static void btn_refresh_event_handler(lv_event_t *event)
{
    lv_event_code_t code = lv_event_get_code(event);
    lv_obj_t *obj = lv_event_get_target(event);
    if (code == LV_EVENT_CLICKED) {
        LISAUI_LOGI(TAG, "button refresh clicked");
        if (g_app_wifi_event_handler) {
            g_app_wifi_event_handler(LISAUI_WIFI_ITEM_NONE, LISAUI_WIFI_OP_SCAN, NULL);
            lv_obj_add_flag(LV_OBJ_ICON(refresh_static), LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(refresh_icon, LV_OBJ_FLAG_HIDDEN);
        }
    }
}

lv_obj_t *app_wifi_create_panel_wifi_list(lv_obj_t *parent)
{

    lv_obj_t *wifi_list_panel = lv_obj_create(parent);
    _lisaui_set_style_container(wifi_list_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    lv_obj_t *refresh_btn = lv_btn_create(wifi_list_panel);
    lv_obj_set_width(refresh_btn, LV_DPX(200));
    // lv_obj_align(refresh_btn, LV_ALIGN_BOTTOM_MID, LV_DPX(80), -LV_DPX(30));
    // lv_obj_align_to(refresh_btn, password, LV_ALIGN_OUT_BOTTOM_MID, LV_DPX(80), LV_DPX(30));
    // lv_obj_add_event_cb(refresh_btn, msgbox_event_handler, LV_EVENT_CLICKED, (void *)wifi_item);
    // lv_obj_set_size(refresh_btn, LV_DPX(100), LV_SIZE_CONTENT);
    lv_obj_align(refresh_btn, LV_ALIGN_TOP_LEFT, LV_DPX(20), LV_DPX(LISAUI_STATUS_BAR_HEIGHT));
    // lv_obj_set_style_bg_color(refresh_btn, lv_color_hex(0x24242d), 0);
    lv_obj_set_style_bg_color(refresh_btn, lv_color_hex(0xff0000), 0);
    lv_obj_set_style_radius(refresh_btn, 8, 0);
    lv_obj_set_style_shadow_width(refresh_btn, 0, 0);
    lv_obj_set_style_border_width(refresh_btn, 0, 0);
    lv_obj_set_style_outline_width(refresh_btn, 0, 0);
    lv_obj_set_style_pad_all(refresh_btn, 4, 0);
    lv_obj_add_event_cb(refresh_btn, btn_refresh_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t *label;
    label = lv_label_create(refresh_btn);
    lv_label_set_text(label, "刷新");
    lv_obj_set_width(label, LV_PCT(50));
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    refresh_icon = lv_gif_create(refresh_btn);
    lv_img_gif_src_init(&img_gif_anim_circle, gfile_anim_circleData, gfile_anim_circleSize);
    lv_gif_set_src(refresh_icon, &img_gif_anim_circle);
    lv_obj_align_to(refresh_icon, label, LV_ALIGN_RIGHT_MID, LV_DPX(0), 0);
    lv_obj_add_flag(refresh_icon, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_t *refresh_icon_static
    LV_OBJ_ICON(refresh_static) = lv_img_create(refresh_btn);
    lv_img_png_src_init(UI_RES_IMG_PNG(wifi_refresh_icon));
    lv_img_set_src(LV_OBJ_ICON(refresh_static), &LV_IMG_DSC(wifi_refresh_icon));
    lv_obj_align_to(LV_OBJ_ICON(refresh_static), label, LV_ALIGN_RIGHT_MID, LV_DPX(0), 0);
    // lv_obj_add_flag(refresh_icon, LV_OBJ_FLAG_HIDDEN);

    g_app_panel = lv_obj_create(wifi_list_panel);
    _lisaui_set_style_container(g_app_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    // LISAUI_COMMON_SET_APP_VIEW_PANEL_SIZE(wifi_list_panel, g_app_panel, NULL);
    lv_coord_t offset_y = 40;
    lv_obj_set_y(g_app_panel, LV_DPX(LISAUI_STATUS_BAR_HEIGHT + offset_y));
    lv_coord_t height = lv_obj_get_height(wifi_list_panel) - LV_DPX(LISAUI_STATUS_BAR_HEIGHT + offset_y);
    lv_obj_set_size(g_app_panel, LV_PCT(100), height);
    return wifi_list_panel;
}


lisaui_err_t lisaui_app_wifi_update_wifi_list(lisaui_wifi_list_t *wifi_list)
{
    lv_obj_clear_flag(LV_OBJ_ICON(refresh_static), LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(refresh_icon, LV_OBJ_FLAG_HIDDEN);

    for (int i = 0; i < wifi_list->count; i++) {
        // FIXME: 检测是否重复，这里通过遍历进行过滤 O(n), 需使用 hash 表等数据结构进行优化
        bool is_duplicate = false;
        for (int j = 0; j < i; j++) {
            if (strncmp(wifi_list->list[i].SSID, wifi_list->list[j].SSID, LISAUI_APP_WIFI_SSID_MAX_LEN) == 0) {
                is_duplicate = true;
                break;
            }
        }
        if (is_duplicate) {
            continue;
        }
        wifi_metadata_t *ap = (wifi_metadata_t *)lisaui_malloc(sizeof(wifi_metadata_t));
        if (ap == NULL) {
            LISAUI_LOGE(TAG, "malloc failed");
            return LISAUI_ERR_NO_MEMORY;
        }
        // LISAUI_LOGI(TAG, "Add wifi ap %d: %s, %s, %s", i, wifi_list->list[i].SSID, wifi_list->list[i].BSSID,
        //             wifi_list->list[i].PWD);

        strncpy(ap->SSID, wifi_list->list[i].SSID, LISAUI_APP_WIFI_SSID_MAX_LEN);
        strncpy(ap->BSSID, wifi_list->list[i].BSSID, LISAUI_APP_WIFI_BSSID_MAX_LEN);
        strncpy(ap->PWD, wifi_list->list[i].PWD, LISAUI_APP_WIFI_PWD_MAX_LEN);
        ap->security = wifi_list->list[i].security;
        ap->status = wifi_list->list[i].status;
        ap->id = wifi_list->list[i].id;
        ap->rssi = wifi_list->list[i].rssi;
        lisaui_app_add_wifi_list_item(ap);
    }
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_update_state(LISAUI_WIFI_STATE_e state, lisaui_wifi_list_t *hotspot_list)
{
    lisaui_app_del_wifi_list();

    LISAUI_LOGI(TAG, "[%s %d]Update wifi list:%p, state:%d,count:%d", __FUNCTION__, __LINE__, hotspot_list, state,
                hotspot_list->count);
    lisaui_wifi_list_t *wifi_list =
        lisaui_malloc(sizeof(lisaui_wifi_list_t) + sizeof(wifi_metadata_t) * LISAUI_APP_WIFI_LIST_ITEM_MAX);
    if (wifi_list == NULL) {
        LISAUI_LOGE(TAG, "[%s %d]no memory!", __FUNCTION__, __LINE__);
        return LISAUI_ERR_NO_MEMORY;
    }
    memset(wifi_list, 0, sizeof(lisaui_wifi_list_t) + sizeof(wifi_metadata_t) * LISAUI_APP_WIFI_LIST_ITEM_MAX);
    wifi_list->count =
        hotspot_list->count > LISAUI_APP_WIFI_LIST_ITEM_MAX ? LISAUI_APP_WIFI_LIST_ITEM_MAX : hotspot_list->count;

    for (int i = 0; i < wifi_list->count; i++) {
        LISAUI_LOGI(TAG, "Wifi[%d],bssid:%20s, pwd:%12s,rssi:%5d, status:%d,ssid:%20s", i, hotspot_list->list[i].BSSID,
                    hotspot_list->list[i].PWD, hotspot_list->list[i].rssi, hotspot_list->list[i].status,
                    hotspot_list->list[i].SSID);

        if (strlen(hotspot_list->list[i].SSID) == 0) {
            // LISAUI_LOGV(TAG, "SSID is empty");
            continue;
        }
        strncpy(wifi_list->list[i].SSID, hotspot_list->list[i].SSID, LISAUI_APP_WIFI_SSID_MAX_LEN);
        strncpy(wifi_list->list[i].BSSID, hotspot_list->list[i].BSSID, LISAUI_APP_WIFI_BSSID_MAX_LEN);
        strncpy(wifi_list->list[i].PWD, hotspot_list->list[i].PWD, LISAUI_APP_WIFI_PWD_MAX_LEN);
        wifi_list->list[i].rssi = hotspot_list->list[i].rssi;
        wifi_list->list[i].status = hotspot_list->list[i].status;
    }
    lisaui_app_wifi_update_wifi_list(wifi_list);
    lisaui_free(wifi_list);
    return 0;
}

lisaui_err_t app_wifi_create(void *parent)
{

    if (g_app_wifi != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_wifi = app_wifi_create_panel_wifi_list(parent);
    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);

    if (g_app_wifi_event_handler) {
        g_app_wifi_event_handler(LISAUI_WIFI_ITEM_NONE, LISAUI_WIFI_OP_SCAN, NULL);
        lv_obj_add_flag(LV_OBJ_ICON(refresh_static), LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(refresh_icon, LV_OBJ_FLAG_HIDDEN);
    }
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

    if (g_app_wifi_event_handler) {
        lisaui_wifi_list_t *wifi_list =
            lisaui_malloc(sizeof(lisaui_wifi_list_t) + sizeof(wifi_metadata_t) * LISAUI_APP_WIFI_LIST_ITEM_MAX);
        if (wifi_list == NULL) {
            LISAUI_LOGE(TAG, "[%s %d]no memory!", __FUNCTION__, __LINE__);
            return LISAUI_ERR_NO_MEMORY;
        }
        memset(wifi_list, 0, sizeof(lisaui_wifi_list_t) + sizeof(wifi_metadata_t) * LISAUI_APP_WIFI_LIST_ITEM_MAX);
        wifi_list->count = LISAUI_APP_WIFI_LIST_ITEM_MAX;
        g_app_wifi_event_handler(LISAUI_WIFI_ITEM_AP_LIST, LISAUI_WIFI_OP_GET_AP_LIST, (void *)wifi_list);
        lisaui_app_wifi_update_wifi_list(wifi_list);
        lisaui_free(wifi_list);
    }
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
