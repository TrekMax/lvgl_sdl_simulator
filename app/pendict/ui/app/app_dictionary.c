/**
 * @file app_dictionary.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_dictionary.h"

#include "../ui.h"

static lv_img_dsc_t gif5;
// INCBIN(gif5, "app/pendict/ui/assets/img/00b44af.gif");

static lv_obj_t * uiApp_Dictionary;

int app_dictionary_create(lv_obj_t * parent)
{
    uiApp_Dictionary = lv_obj_create(NULL);
    lv_obj_clear_flag(uiApp_Dictionary, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiApp_Dictionary, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Dictionary, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_t * img_gif;
    // img_gif = lv_gif_create(uiApp_Dictionary);
    // // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    // lv_img_gif_src_init(&img_gif_1, gimg_gif_1Data, gimg_gif_1Size);
    // lv_gif_set_src(img_gif, &img_gif_1);
    // lv_obj_align(img_gif, LV_ALIGN_LEFT_MID, 260+120, 0);

    return 0;
}

lv_obj_t * app_dictionary_get_page(void)
{
    return uiApp_Dictionary;
}


int app_dictionary_destroy(void)
{
    printk("[%d:%s] destroy\n", __LINE__, __func__);
    return 0;
}

int app_dictionary_enter(void)
{
    printk("[%d:%s] enter\n", __LINE__, __func__);
    return 0;
}

int app_dictionary_exit(void)
{
    printk("[%d:%s] exit\n", __LINE__, __func__);
    return 0;
}

struct app_icon_t icon_dictionary = {
    .name = "拼读",
    .icon_width = LV_SIZE_CONTENT,
    .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img__launcher_fav_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_dictionary = {
    .create = app_dictionary_create,
    .destroy = app_dictionary_destroy,
    .enter = app_dictionary_enter,
    .exit = app_dictionary_exit,

    .get_obj_handle = app_dictionary_get_page,
    .app_id = UI_APP_ID_DICTIONARY,
    .icon = &icon_dictionary,
};

int app_dictionary_init(void)
{
    app_dictionary.app_id = UI_APP_ID_DICTIONARY;
    return lisaui_app_register(&app_dictionary);
}