/**
 * @file app_alarm.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __APP_ALARM_H__
#define __APP_ALARM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../app_common.h"
#include "lisaui_app_common.h"

lisaui_err_t app_alarm_init(void);
lisaui_err_t lisaui_app_alarm_op_alarm_add_view(const char *alarm_time_text, const char *alarm_date_text);

typedef struct {
    char *alarm_time_text;
    char *alarm_date_text;
    uint64_t timestamp;
} lisaui_alarm_clock_item_t;

typedef struct {
    lisaui_alarm_clock_item_t *list;
    int count;
} lisaui_alarm_clock_list_t;

typedef enum  {
    LISAUI_ALARM_ITEM_CLOCK = 0,
    LISAUI_ALARM_ITEM_CLOCK_LIST,
} lisaui_alarm_item_t;

typedef enum {
    LISAUI_ALARM_OP_GET = 0,
    LISAUI_ALARM_OP_SET,

    LISAUI_ALARM_OP_GET_LIST,
    // LISAUI_ALARM_OP_SET_LIST,
    // LISAUI_ALARM_OP_GET_LIST_COUNT,

    // LISAUI_ALARM_OP_ADD,
    // LISAUI_ALARM_OP_MODIFY,
    LISAUI_ALARM_OP_DELETE,
    // LISAUI_ALARM_OP_CLEAR,

} lisaui_alarm_op_t;

typedef int (*lisaui_app_alarm_handler_t)(lisaui_alarm_item_t type, lisaui_alarm_op_t operation, void *param);
lisaui_err_t lisaui_app_alarm_register_handler(lisaui_app_alarm_handler_t handler);

lisaui_err_t lisaui_app_alarm_op_alarm_add(const char *time, const char *date);

#ifdef __cplusplus
}
#endif

#endif // __APP_ALARM_H__
