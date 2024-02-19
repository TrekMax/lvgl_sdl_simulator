/**
 * @file aweui_status_bar.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-19
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __AWEUI_UI_PAGE_AWEUI_STATUS_BAR_H__
#define __AWEUI_UI_PAGE_AWEUI_STATUS_BAR_H__

#ifdef __ZEPHYR__
    // #include <zephyr.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif
#include "aweui_resources.h"


lv_obj_t *aweui_status_bar_create(lv_obj_t *parent);
lv_obj_t *aweui_setting_tabview_create(lv_obj_t *parent);

#endif // __AWEUI_UI_PAGE_AWEUI_STATUS_BAR_H__

