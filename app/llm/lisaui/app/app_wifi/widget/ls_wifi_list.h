/**
 * @file ls_wifi_list.h
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-20
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_WIDGET_LS_WIFI_LIST_H__
#define __LISAUI_WIDGET_LS_WIFI_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#elif CONFIG_LISAUI_ENV_ARCS_SDK
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

LV_FONT_DECLARE(lv_font_notosans_cs_medium_14);
LV_FONT_DECLARE(lv_font_chinese_18);

#define LISAUI_APP_WIFI_SSID_MAX_LEN 33
#define LISAUI_APP_WIFI_PWD_MAX_LEN 65
#define LISAUI_APP_WIFI_LIST_ITEM_MAX 10

typedef enum {
    WIFI_LIST_ITEM_STATUS_DISCONNECT = 0,
    WIFI_LIST_ITEM_STATUS_CONNECTING,
    WIFI_LIST_ITEM_STATUS_CONNECTED,
} wifi_list_item_status_t;
typedef enum {
    WIFI_LIST_ITEM_SECURITY_NONE = 0,
    WIFI_LIST_ITEM_SECURITY_WEP,
    WIFI_LIST_ITEM_SECURITY_WPA,
    WIFI_LIST_ITEM_SECURITY_WPA2,
    WIFI_LIST_ITEM_SECURITY_WPA3,
} wifi_list_item_security_t;

typedef struct _wifi_item_t {
    int id;
    const char SSID[LISAUI_APP_WIFI_SSID_MAX_LEN];
    const char PWD[LISAUI_APP_WIFI_PWD_MAX_LEN];
    int rssi;
    int security;
    int status;
    int is_connect;
} wifi_item_t;

lv_obj_t *ls_wifi_list_create(lv_obj_t *parent);
lv_obj_t *ls_wifi_list_add_text(lv_obj_t *list, const char *txt);

lv_obj_t *ls_wifi_list_add_btn(lv_obj_t *list, wifi_item_t wifi, lv_event_cb_t event_cb,
                             void *user_data);

const char *ls_wifi_list_get_btn_text(lv_obj_t *list, lv_obj_t *btn);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*__LISAUI_WIDGET_LS_WIFI_LIST_H__*/
