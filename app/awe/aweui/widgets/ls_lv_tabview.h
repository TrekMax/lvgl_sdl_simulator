/**
 * @file lv_templ.h
 *
 */

#ifndef LS_LV_TABVIEW_H
#define LS_LV_TABVIEW_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
// #include "../../../lvgl.h"
#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#define LV_USE_TABVIEW 1
#if LV_USE_TABVIEW

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_obj_t obj;
    char ** map;
    uint16_t tab_cnt;
    uint16_t tab_cur;
    lv_dir_t tab_pos;
} ls_lv_tabview_t;

extern const lv_obj_class_t ls_lv_tabview_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t * ls_lv_tabview_create(lv_obj_t * parent, lv_dir_t tab_pos, lv_coord_t tab_size);

lv_obj_t * ls_lv_tabview_add_tab(lv_obj_t * tv, const char * name);

void ls_lv_tabview_rename_tab(lv_obj_t * obj, uint32_t tab_id, const char * new_name);

lv_obj_t * ls_lv_tabview_get_content(lv_obj_t * tv);

lv_obj_t * ls_lv_tabview_get_tab_btns(lv_obj_t * tv);

void ls_lv_tabview_set_act(lv_obj_t * obj, uint32_t id, lv_anim_enable_t anim_en);

uint16_t ls_lv_tabview_get_tab_act(lv_obj_t * tv);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_TABVIEW*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LS_LV_TABVIEW_H*/
