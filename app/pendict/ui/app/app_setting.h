/**
 * @file app_setting.h
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __APP_SETTING_H__
#define __APP_SETTING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../ui.h"

void app_setting_create(lv_obj_t * parent);
lv_obj_t * app_setting_get_page(void);


#ifdef __cplusplus
}
#endif

#endif // __APP_SETTING_H__
