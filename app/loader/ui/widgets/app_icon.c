/**
 * @file app_icon.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2021 - 2023 shenzhen co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_icon.h"

#if LV_USE_APP_ICON != 0

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS &lv_app_icon_class

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_app_icon_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_app_icon_event(lv_obj_t * obj, lv_event_t e);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t lv_app_icon_class = {
    .base_class = &lv_obj_class,
    .instance_size = sizeof(lv_app_icon_t),
    .constructor_cb = lv_app_icon_constructor,
    .event_cb = lv_app_icon_event,
};


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_obj_t * lv_app_icon_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void lv_app_icon_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    lv_app_icon_t * icon = (lv_app_icon_t *)obj;
    lv_memset_00(icon, sizeof(lv_app_icon_t));
}


#endif /*LV_USE_APP_ICON != 0*/