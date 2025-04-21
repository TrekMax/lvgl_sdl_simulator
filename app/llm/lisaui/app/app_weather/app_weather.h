/**
 * @file app_weather.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __APP_WEATHER_H__
#define __APP_WEATHER_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _metadata_weather_t {
    int type;   // 天气类型
    char *city; // 城市
    char *date; // 日期
    char *icon_path; // 天气图标路径
    // char *location;     // 天气位置
    // char *time;         // 时间
    // char *week;         // 星期
    // char *title;        // 天气标题
    char *temperature;       // 温度
    char *temperature_range; // 温度范围
    char *description;       // 天气描述
} metadata_weather_t;

#include "../app_common.h"
#include "lisaui_app_common.h"

#if CONFIG_LVGL_ENV_SIMULATOR
#define APP_WEATHER_UI_RES_PERFIX_PATH(path) "app/llm/lisaui/app/app_weather/" path
#else
#define APP_WEATHER_UI_RES_PERFIX_PATH(path) "src/ui/lisaui/app/app_weather/" path
#endif

lisaui_err_t app_weather_init(void);

lisaui_err_t lisaui_app_weather_set_weather_view(metadata_weather_t *weather);
lisaui_err_t lisaui_app_weather_del_weather_view(void);

#ifdef __cplusplus
}
#endif

#endif // __APP_WEATHER_H__
