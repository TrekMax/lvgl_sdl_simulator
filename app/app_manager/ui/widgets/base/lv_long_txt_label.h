/***********
 * @file lv_long_txt_label.h
 * 描述： 
 * @author 徐华振-hzxu2@iflytek.com
 * @date 2023-06-29 21:33 
***********/
#include "lvgl.h"
#include "ui_base.h"
#ifndef _LV_LONG_TXT_LABEL_H_
#define _LV_LONG_TXT_LABEL_H_
#ifdef __cplusplus
extern "C" {
#endif


typedef void (*long_txt_label_item_click)(lv_obj_t * obj, int index);

typedef struct {
    long_txt_label_item_click event;
}lv_long_txt_label_ext_t;

lv_obj_t * lv_long_txt_label_create(lv_obj_t * par, lv_obj_t *label, char *src, int w);
bool lv_obj_is_lv_long_txt_label(lv_obj_t * obj);

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /*_LV_LONG_TXT_LABEL_H_*/