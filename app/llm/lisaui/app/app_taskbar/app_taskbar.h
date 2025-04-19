/**
 * @file app_taskbar.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-25
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_APP_TASKBAR_H__
#define __LISAUI_APP_TASKBAR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lisaui_app_common.h"

#define CONFIG_LISAUI_APP_TASKBAR_TOOLKIT_ENABLE 0

lisaui_err_t app_taskbar_init(void);

lisaui_err_t lisaui_taskbar_hide(bool hide);
lisaui_err_t lisaui_get_taskbar_dbus(lisaui_dbus_t **dbus);
lisaui_err_t lisaui_taskbar_set_battery_percent(int percent);
lisaui_err_t lisaui_taskbar_set_battery_charging(bool is_charging);

#ifdef __cplusplus
}
#endif

#endif /* __LISAUI_APP_TASKBAR_H__ */
