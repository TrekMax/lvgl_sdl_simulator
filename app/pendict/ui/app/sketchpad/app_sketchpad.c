/**
 * @file app_sketchpad.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_sketchpad.h"

#include "../../ui.h"
#include "../../utils/lv_img_utils.h"
#include "lv_100ask_sketchpad.h"

// FIXME: INCBIN 之后 的 lv_obj_t * 不能为 static, 编译阶段提示 dwarf line number information for .data ignored
lv_obj_t * uiApp_Sketchpad = NULL;

/*=====================
 * Other functions
 *====================*/

/**********************
 *   STATIC FUNCTIONS
 **********************/

// static void event_handler(lv_event_t * e)
// {
//     lv_obj_t * sketchpad = lv_event_get_target(e);

//     void * canvas_buf = lv_canvas_get_buf(sketchpad);
//     lv_draw_buf_t * canvas_draw_buf = lv_canvas_get_draw_buf(sketchpad);

//     LV_LOG_USER("LV_EVENT_VALUE_CHANGED");

// }

#define SKETCHPAD_DEFAULT_WIDTH  SCREEN_WIDTH
#define SKETCHPAD_DEFAULT_HEIGHT SCREEN_HEIGHT

static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(SKETCHPAD_DEFAULT_WIDTH, SKETCHPAD_DEFAULT_HEIGHT)];

int app_sketchpad_create(lv_obj_t * parent)
{
    uiApp_Sketchpad = lv_obj_create(parent);
    lv_obj_clear_flag(uiApp_Sketchpad, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiApp_Sketchpad, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Sketchpad, 100, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_t *sketchpad = lv_100ask_sketchpad_create(uiApp_Sketchpad);

    lv_canvas_set_buffer(sketchpad, cbuf, SKETCHPAD_DEFAULT_WIDTH, SKETCHPAD_DEFAULT_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_obj_center(sketchpad);
    lv_canvas_fill_bg(sketchpad, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);
    return 0;
}

lv_obj_t * app_sketchpad_get_page(void)
{
    printk("[%d:%s] get page: %p\n", __LINE__, __func__, uiApp_Sketchpad);
    return uiApp_Sketchpad;
}


int app_sketchpad_destroy(void)
{
    printk("[%d:%s] destroy\n", __LINE__, __func__);
    if (uiApp_Sketchpad) {
        lv_obj_del(uiApp_Sketchpad);
        uiApp_Sketchpad = NULL;
    }
    return 0;
}

int app_sketchpad_enter(void)
{
    printk("[%d:%s] enter\n", __LINE__, __func__);
    return 0;
}

int app_sketchpad_exit(void)
{
    printk("[%d:%s] exit\n", __LINE__, __func__);
    return 0;
}

struct app_icon_t icon_sketchpad = {
    .name = "几何画板",
    .icon_width = LV_SIZE_CONTENT,
    .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img__launcher_fav_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_sketchpad = {
    .create = app_sketchpad_create,
    .destroy = app_sketchpad_destroy,
    .enter = app_sketchpad_enter,
    .exit = app_sketchpad_exit,

    .get_obj_handle = app_sketchpad_get_page,
    .app_id = UI_APP_ID_SKETCHPAD,
    .icon = &icon_sketchpad,
};

int app_sketchpad_init(void)
{
    return lisaui_app_register(&app_sketchpad);
}