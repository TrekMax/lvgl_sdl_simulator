/**
 * @file lisaui_type.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief 
 * @version 0.1
 * @date 2025-02-24
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_TYPE_H__
#define __LISAUI_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#if defined(__LVGL_SIMULATOR__)
    #ifndef LV_CONF_PATH
        #define LV_CONF_PATH ../../../include/lv_conf.h
    #endif
#endif

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#elif defined(__LVGL_SIMULATOR__)
    #include "lvgl/lvgl.h"
#else
    #include "lvgl.h"
#endif


#define LISAUI_ERR_OK   (0)
#define LISAUI_ERR_FAIL (-1)

#define LISAUI_ERR_UNKNOW                   (-1)
#define LISAUI_ERR_INVALID_PARAM            (-2)
#define LISAUI_ERR_NO_MEMORY                (-3)


#define LISAUI_ERR_APP_OK                   (LISAUI_ERR_OK)
#define LISAUI_ERR_APP_UNKNOW_FAILED        (-1000)
#define LISAUI_ERR_APP_NOT_REGISTERED       (-1001)
#define LISAUI_ERR_APP_ALREADY_REGISTERED   (-1002)
#define LISAUI_ERR_APP_CREATE_FAILED        (-1003)
#define LISAUI_ERR_APP_ENTER_FAILED         (-1004)
#define LISAUI_ERR_APP_ID_INVALID           (-1005)
#define LISAUI_ERR_APP_FULL                 (-1006)
#define LISAUI_ERR_APP_NOT_FOUND            (-1007)
#define LISAUI_ERR_APP_EXIT_FAILED          (-1008)
#define LISAUI_ERR_APP_DESTROY_FAILED       (-1009)
#define LISAUI_ERR_APP_NOT_INIT             (-1010)

#define LISAUI_ERR_APP_LOCKED               (-1011)
#define LISAUI_ERR_APP_ALREADY_IN           (-1012)


#define LISAUI_VIEW_OBJ_T lv_obj_t
#define LISAUI_ICON_RES_T const lv_img_dsc_t

#ifndef LISAUI_VIEW_OBJ_T 
#define LISAUI_VIEW_OBJ_T uint32_t
#endif
#ifndef LISAUI_ICON_RES_T
    #define LISAUI_ICON_RES_T const uint8_t *
#endif

typedef int lisaui_err_t;
typedef lisaui_err_t lisaui_view_err_t;

typedef LISAUI_VIEW_OBJ_T lisaui_view_t;
typedef LISAUI_ICON_RES_T lisaui_icon_res_t;
typedef struct _lisaui_view_stack_t lisaui_view_stack_t;
typedef struct _lisaui_view_page_t lisaui_view_page_t;

#ifdef __cplusplus
}
#endif

#endif /* __LISAUI_TYPE_H__ */