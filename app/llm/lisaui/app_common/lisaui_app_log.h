/**
 * @file lisaui_app_log.h
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-04-14
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_APP_LOG_H__
#define __LISAUI_APP_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

// #define LOG_LEVEL         LOG_INFO
#define LOG_LEVEL         LOG_DEBUG
#define CONFIG_LOG_COLORS 1
#define CONFIG_LOG_ENABLE 1
// #define CLOG_ENABLE       1
#define LISAUI_PRINTF printf


#if CONFIG_LOG_ENABLE
#if defined(__LVGL_SIMULATOR__)
#include "utils_log.h"
#define LISAUI_PRINTK(fmt, ...) printf(fmt, ##__VA_ARGS__)
#define LISAUI_LOGE             LOGE
#define LISAUI_LOGW             LOGW
#define LISAUI_LOGI             LOGI
#define LISAUI_LOGD             LOGD
#define LISAUI_LOGV             LOGV
#else
#include "log_print.h"
#define LISAUI_PRINTK(fmt, ...)    printf(fmt, ##__VA_ARGS__)
#define LISAUI_LOGE(TAG, fmt, ...) CLOG("E:[%s:%d]" fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LISAUI_LOGW(TAG, fmt, ...) CLOG("W:" fmt, ##__VA_ARGS__)
#define LISAUI_LOGI(TAG, fmt, ...) CLOG("I:" fmt, ##__VA_ARGS__)
#define LISAUI_LOGD(TAG, fmt, ...) CLOG("D:[%s:%d]" fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#define LISAUI_LOGV(TAG, fmt, ...) CLOG("V:" fmt, ##__VA_ARGS__)
#endif
#else
#define LISAUI_PRINTK(fmt, ...)
#define LISAUI_LOGE(TAG, fmt, ...)
#define LISAUI_LOGW(TAG, fmt, ...)
#define LISAUI_LOGI(TAG, fmt, ...)
#define LISAUI_LOGD(TAG, fmt, ...)
#define LISAUI_LOGV(TAG, fmt, ...)
#endif


#ifdef __cplusplus
}
#endif

#endif /* __LISAUI_APP_LOG_H__ */
