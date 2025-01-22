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

#include "../ui.h"
#include "../utils/lv_img_utils.h"


// FIXME: INCBIN 之后 的 lv_obj_t * 不能为 static, 编译阶段提示 dwarf line number information for .data ignored
lv_obj_t * uiApp_Sketchpad = NULL;

int app_sketchpad_create(lv_obj_t * parent)
{
    uiApp_Sketchpad = lv_obj_create(parent);
    lv_obj_clear_flag(uiApp_Sketchpad, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiApp_Sketchpad, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Sketchpad, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_t * img_gif;
    // lv_obj_t * lv_img_logo;
    // // img_gif = lv_gif_create(uiApp_Sketchpad);
    // // // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    // // lv_img_gif_src_init(&img_gif_1, gimg_gif_1Data, gimg_gif_1Size);
    // // lv_gif_set_src(img_gif, &img_gif_1);
    // // lv_obj_align(img_gif, LV_ALIGN_LEFT_MID, 260+120, 0);
    // lv_img_logo = lv_img_create(parent);
    // // lv_img_set_src(lv_img_logo, LV_SYMBOL_PNG_FILE_PATH);
    // lv_img_png_src_init(&img_png6, gimg_png6Data, gimg_png6Size);
    // lv_img_set_src(lv_img_logo, &img_png6);

    return 0;
}

lv_obj_t * app_sketchpad_get_page(void)
{
    return uiApp_Sketchpad;
}


int app_sketchpad_destroy(void)
{
    printk("[%d:%s] destroy\n", __LINE__, __func__);
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