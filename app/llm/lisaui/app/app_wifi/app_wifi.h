/**
 * @file app_wifi.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_APP_WIFI_H__
#define __LISAUI_APP_WIFI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../app_common.h"
#include "lisaui_app_common.h"
#include "wifi_type.h"

lisaui_err_t app_wifi_init(void);
lisaui_err_t lisaui_app_add_wifi_list_item(wifi_metadata_t *wifi_item);

typedef lisaui_err_t (*app_wifi_event_handler_t)(lisaui_wifi_op_t op,
                                                 wifi_metadata_t *wifi_item);
lisaui_err_t lisaui_app_wifi_register_event_handler(app_wifi_event_handler_t handler);

static wifi_metadata_t test_wifi_item_list[] = {
    {0, "SSID1 sadasdadas", "PWD1", -50, 0, LISAUI_WIFI_STATUS_CONNECTED},
    {3, "SSID4sdadasdasdasdssssd", "PWD4", -80, 3, LISAUI_WIFI_STATUS_CONNECTING},
    {1, "SSID2", "PWD2", -60, 1, LISAUI_WIFI_STATUS_DISCONNECT},
    {2, "SSID3", "PWD3", -70, 2, LISAUI_WIFI_STATUS_DISCONNECT},
    {3, "SSID4sdadasdasdasdssssd", "PWD4", -80, 3, LISAUI_WIFI_STATUS_DISCONNECT},
};

#ifdef __cplusplus
}
#endif

#endif // __LISAUI_APP_WIFI_H__
