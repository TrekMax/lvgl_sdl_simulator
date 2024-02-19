/**
 * @file ls_status_bar.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

/*********************
 *      INCLUDES
 *********************/
#include "ls_status_bar.h"
#include "aweui_resources.h"
#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#if LS_STATUS_BAR

// #include "../../../misc/lv_assert.h"

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS    &ls_status_bar_class

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void ls_status_bar_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void ls_status_bar_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void ls_status_bar_event(const lv_obj_class_t * class_p, lv_event_t * e);
static void btns_value_changed_event_cb(lv_event_t * e);
static void cont_scroll_end_event_cb(lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/
const lv_obj_class_t ls_status_bar_class = {
    .constructor_cb = ls_status_bar_constructor,
    .destructor_cb = ls_status_bar_destructor,
    .event_cb = ls_status_bar_event,
    .width_def = LV_PCT(100),
    .height_def = LV_PCT(100),
    .base_class = &lv_obj_class,
    .instance_size = sizeof(ls_status_bar_t)
};

lv_obj_t * home_btn;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * ls_status_bar_create(lv_obj_t * parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(&ls_status_bar_class, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

lv_obj_t * ls_status_bar_add_title(lv_obj_t * win, const char * txt)
{
    lv_obj_t * header = ls_status_bar_get_header(win);
    lv_obj_t * title = lv_label_create(header);
    lv_label_set_long_mode(title, LV_LABEL_LONG_DOT);
    lv_label_set_text(title, txt);
    lv_obj_set_flex_grow(title, 1);
    return title;
}

lv_obj_t * ls_status_bar_set_home_icon(lv_obj_t * bar, bool hide)
{
    lv_obj_t * header = ls_status_bar_get_header(bar);
    // home_btn = lv_obj_get_child(header, 0);
	lv_obj_t *home_btn = lv_img_create(header);
	// lv_img_png_src_init(&icon_nav_home, icon_nav_home_png_data, icon_nav_home_png_size);
	lv_img_set_src(home_btn, &ic_nav_home);
	// lv_obj_align(home_btn, LV_ALIGN_LEFT_MID, -STATUS_BAR_ICON_WIDTH + 10, 0);
    lv_obj_set_flex_grow(home_btn, 1);
    if (hide) {
        // lv_obj_set_hidden(home_btn, true);
        lv_obj_add_flag(home_btn, LV_OBJ_FLAG_HIDDEN); // 显示对象
    } else {
        lv_obj_clear_flag(home_btn, LV_OBJ_FLAG_HIDDEN); // 显示对象
    }
    return home_btn;
}
// {
//     lv_obj_t * header = ls_status_bar_get_header(bar);
//     lv_obj_t * title = lv_label_create(header);
//     lv_label_set_long_mode(title, LV_LABEL_LONG_DOT);
//     lv_label_set_text(title, txt);
//     lv_obj_set_flex_grow(title, 1);
//     return title;
// }

lv_obj_t * ls_status_bar_add_btn(lv_obj_t * win, const void * icon, lv_coord_t btn_w)
{
    lv_obj_t * header = ls_status_bar_get_header(win);
    lv_obj_t * btn = lv_btn_create(header);
    lv_obj_set_size(btn, btn_w, LV_PCT(100));

    lv_obj_t * img = lv_img_create(btn);
    lv_img_set_src(img, icon);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    

    return btn;
}

lv_obj_t * ls_status_bar_get_header(lv_obj_t * win)
{
    return lv_obj_get_child(win, 0);
}

lv_obj_t * ls_status_bar_get_content(lv_obj_t * win)
{
    return lv_obj_get_child(win, 1);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void ls_status_bar_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{
    LV_UNUSED(class_p);
    lv_obj_t * parent = lv_obj_get_parent(obj);
    lv_obj_set_size(obj, lv_obj_get_width(parent), lv_obj_get_height(parent));
    lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);

    lv_obj_t * header = lv_obj_create(obj);
    lv_obj_set_size(header, LV_PCT(100), LV_PCT(100));
    lv_obj_set_flex_flow(header, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(header, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_t * cont = lv_obj_create(obj);
    lv_obj_set_flex_grow(cont, 1);
    lv_obj_set_width(cont, LV_PCT(100));
}

static void ls_status_bar_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj)
{

}

static void ls_status_bar_event(const lv_obj_class_t * class_p, lv_event_t * e)
{

}
#endif
