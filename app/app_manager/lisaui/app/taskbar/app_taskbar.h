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

#include "../../app_common/lisaui_type.h"
#include "../../app_common/lisaui_app_common.h"

lisaui_err_t lisaui_taskbar(lv_obj_t *parent);
void lisaui_taskbar_hide(bool hide);
lisaui_err_t lisaui_get_taskbar_dbus(lisaui_dbus_t **dbus);
lisaui_err_t lisaui_taskbar_set_battery_percent(int percent);
lisaui_err_t lisaui_taskbar_set_battery_charging(bool is_charging);

#ifdef __cplusplus
}
#endif

#endif /* __LISAUI_APP_TASKBAR_H__ */
