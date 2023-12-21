/**
 * @file lv_100ask_boot_animation.h
 *
 */

#ifndef LV_100ASK_BOOT_ANIAMTION_H
#define LV_100ASK_BOOT_ANIAMTION_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask.h"

/*********************
 *      DEFINES
 *********************/
#define ACTIVE_TRACK_CNT        3
#define INTRO_TIME              100
#define BAR_COLOR1              lv_color_hex(0xe9dbfc)
#define BAR_COLOR2              lv_color_hex(0x6f8af6)
#define BAR_COLOR3              LV_COLOR_WHITE
#define BAR_COLOR1_STOP         80
#define BAR_COLOR2_STOP         100
#define BAR_COLOR3_STOP         (2 * LV_HOR_RES / 3)
#define BAR_CNT                 20
#define DEG_STEP                (180/BAR_CNT)
#define BAND_CNT                4
#define BAR_PER_BAND_CNT        (BAR_CNT / BAND_CNT)
#define LV_DEMO_LIST_CTRL_OVERLAP  (60)


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_100ask_boot_animation(uint32_t delay);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_100ASK_BOOT_ANIAMTION_H*/
