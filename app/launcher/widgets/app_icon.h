/**
 * @file app_icon.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2021 - 2023 shenzhen co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __APP_ICON_H__
#define __APP_ICON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#define LV_USE_APP_ICON 1

#if LV_USE_APP_ICON != 0


/**********************
 *      TYPEDEFS
 **********************/
/*Data of app icon*/
typedef struct {
    lv_obj_t * obj;
} lv_app_icon_t;



/**
 * @brief Create an app icon object
 * 
 * @param parent 
 * @return lv_obj_t* 
 */
lv_obj_t * lv_app_icon_create(lv_obj_t *parent);

#endif // LV_USE_APP_ICON


#ifdef __cplusplus
}
#endif

#endif // __APP_ICON_H__