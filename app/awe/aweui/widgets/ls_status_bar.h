/**
 * @file ls_status_bar.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * @note: listenai 自定义任务栏实现，功能如下：
 *      1. 任务栏分为三部分，左中右
 *          1.1. 左侧：导航按钮
 *          1.2. 中间：通知信息/当前页面标题
 *          1.3. 右侧：通知icon/通知数量/当前时间
 *      2. 支持手势上/下拉收起/展开任务栏面板(PanelHolder)
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LS_STATUS_BAR_H__
#define __LS_STATUS_BAR_H__


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#define LS_STATUS_BAR 1

#define LS_STATUS_BAR_HEIGHT 40

#if LS_STATUS_BAR

typedef struct {
    lv_obj_t obj;
    lv_obj_t * home_btn_enable;
} ls_status_bar_t;

extern const lv_obj_class_t ls_status_bar_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t *ls_status_bar_create(lv_obj_t *parent);

lv_obj_t * ls_status_bar_set_home_icon(lv_obj_t * bar, bool hide);
lv_obj_t * ls_status_bar_get_header(lv_obj_t * win);
lv_obj_t * ls_status_bar_add_title(lv_obj_t * win, const char * txt);
lv_obj_t * ls_status_bar_add_btn(lv_obj_t * win, const void * icon, lv_coord_t btn_w);

#endif

#ifdef __cplusplus
}
#endif

#endif // __LS_STATUS_BAR_H__