/**
 * @file lv_100ask_demo.h
 *
 */

#ifndef LV_100ASK_DEMO_H
#define LV_100ASK_DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_100ask.h"


/*********************
 *      DEFINES
 *********************/
#define LV_100SK_DEMO_BG_BLACK           lv_color_hex(0xffffff)
#define LV_100SK_DEMO_BG_WHITE           lv_color_hex(0xffffff)
#define LV_100SK_DEMO_BG_LIGHT           lv_color_hex(0xf3f8fe)
#define LV_100SK_DEMO_BG_GRAY            lv_color_hex(0x8a8a8a)
#define LV_100SK_DEMO_BG_LIGHT_GRAY      lv_color_hex(0xc4c4c4)
#define LV_100SK_DEMO_BG_BLUE            lv_color_hex(0x2f3243) //006fb6
#define LV_100SK_DEMO_BG_GREEN           lv_color_hex(0x4cb242)
#define LV_100SK_DEMO_BG_RED             lv_color_hex(0xd51732)

/*Animations*/
#define LV_100SK_DEMO_ANIM_X 		       (LV_HOR_RES / 40)
#define LV_100SK_DEMO_ANIM_Y 		       (LV_VER_RES / 40)
#define LV_100SK_DEMO_ANIM_DELAY 	       (0)
#define LV_100SK_DEMO_ANIM_TIME  	       (0)

// SIZE
#define LV_100ASK_BOTTOM_MENU_W                    (LV_HOR_RES)
#define LV_100ASK_BOTTOM_MENU_H                    (76)
#define LV_100ASK_BOTTOM_MENU_ITEM_SIZE            (52)

// COLOR
#define LV_100ASK_BOTTOM_MENU_COLOR                (lv_color_hex(0xC9C9CE))
#define LV_100ASK_BOTTOM_MENU_ITEM_COUNT           (4)
#define LV_100ASK_MENU_ITEM_COUNT                  (9) 	/*12*/

/*Padding*/
#define LV_100SK_DEMO_TITLE_PAD          (8)
#define LV_100SK_DEMO_BACK_W             (30)
#define LV_100SK_DEMO_BACK_H             (30)
#define LV_100SK_DEMO_BACK_PAD           (10)
#define LV_100ASK_TABVIEW_NAVIGATION_SPACE         (10)

// TIME
#define LV_100ASK_HOME_OPEN_TIME                   (0)


/**********************
 *      TYPEDEFS
 **********************/


/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_100ask_demo(uint32_t delay);
void lv_100ask_demo_home(uint32_t delay);
void add_back(lv_obj_t * obj, lv_event_cb_t event_cb);	// 添加返回按钮
void lv_100ask_anim_out_all(lv_obj_t * obj, uint32_t delay);
lv_obj_t * add_title(lv_obj_t * obj_space, const char * txt);	// 添加标题
void ui_init( void );

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_100ASK_DEMO_H */
