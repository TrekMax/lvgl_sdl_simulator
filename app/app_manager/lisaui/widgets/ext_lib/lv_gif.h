/**
 * @file lv_gif.h
 *
 */

#ifndef LV_GIF_H
#define LV_GIF_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include <lvgl/lvgl.h>
#endif
  
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * lv_gif_create_from_file(lv_obj_t * parent, const char * path);
lv_obj_t * lv_gif_create_from_data(lv_obj_t * parent, const void * data);
lv_obj_t * lv_gif_tes(lv_obj_t * parent, const void * data);


void lv_gif_repeat(lv_obj_t *gif, bool enable);
void lv_gif_restart(lv_obj_t * gif);

void lv_gif_pause(lv_obj_t * obj);
void lv_gif_resume(lv_obj_t * obj);

int lv_gif_get_frame_count(lv_obj_t * obj);
int lv_gif_get_repeat_count(lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_GIFDEC_H*/
