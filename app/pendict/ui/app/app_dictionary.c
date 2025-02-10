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
#include "../utils/lv_img_utils.h"

static lv_img_dsc_t img_gif5;
INCBIN(img_gif5, "app/pendict/ui/assets/img/00b44af.gif");
static lv_img_dsc_t img_png6;
INCBIN(img_png6, "app/pendict/ui/assets/img/logo-m2.png");

lv_obj_t * uiApp_Dictionary = NULL;
lv_obj_t * uiApp_DictionaryBtnStart = NULL;

lv_obj_t * lisaui_explain_label_create(lv_obj_t *parent)
{
    printk("[%d:%s] ---------------->enter\n", __LINE__, __func__);
    if (!parent) {
        return NULL;
    }
    lv_obj_t * base_panel = lv_obj_create(parent);

    lv_obj_t * img_gif;
    img_gif = lv_gif_create(parent);
    // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    lv_img_gif_src_init(&img_gif5, gimg_gif5Data, gimg_gif5Size);
    lv_gif_set_src(img_gif, &img_gif5);
    lv_obj_align(img_gif, LV_ALIGN_TOP_LEFT, 0, 30);
    
    lv_obj_set_height(base_panel, 700);
    lv_obj_set_width(base_panel, SCREEN_WIDTH-140);

    // lv_obj_set_width(base_panel, lv_obj_get_width(parent));
    lv_obj_set_scrollbar_mode(base_panel, LV_SCROLLBAR_MODE_OFF);
    // if (SCREEN_WIDTH > 320) {
    //     // lv_obj_set_size(base_panel, SCREEN_WIDTH-140, 700);
    //     lv_obj_set_scroll_dir(base_panel, LV_DIR_TOP | LV_DIR_BOTTOM); // 仅允许上下滑动
    // }
    lv_obj_set_scrollbar_mode(base_panel, LV_SCROLL_SNAP_NONE);
    lv_obj_set_style_border_side(base_panel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(base_panel, lv_color_hex(0x008000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(base_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * uiApp_Demo_TextResult = lv_label_create(base_panel);
    if (SCREEN_WIDTH > 320) {
        // lv_obj_set_size(panel1, SCREEN_WIDTH-140, 700);
        lv_obj_set_size(uiApp_Demo_TextResult, SCREEN_WIDTH-200, 100);
    } else {
        lv_obj_set_size(uiApp_Demo_TextResult, SCREEN_WIDTH-100, 100);
    }
    // lv_obj_set_pos(uiApp_Demo_TextResult, 20, 40);
    // lv_obj_t * img_gif;
    // img_gif = lv_gif_create(panel1);
    // // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    // lv_img_gif_src_init(&img_gif5, gimg_gif5Data, gimg_gif5Size);
    // lv_gif_set_src(img_gif, &img_gif5);
    // lv_obj_align(img_gif, LV_ALIGN_TOP_LEFT, 0, 0);

    // lv_obj_align_to(uiApp_Demo_TextResult, img_gif, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 20);
    // lv_obj_set_align(uiApp_Demo_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiApp_Demo_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_label_set_text(uiApp_Demo_TextResult, "这是一条中文测试用例");
    lv_label_set_text(uiApp_Demo_TextResult, "1.[介]《戴珍珠耳环的少女》（荷兰语：Het meisje met de parel），十七世纪荷兰画家扬·维米尔的作品。画作以少女戴着的珍珠耳环作为视角的焦点，现时画作存放在海牙的毛里茨住宅中。");

    lv_obj_set_style_text_color(uiApp_Demo_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiApp_Demo_TextResult, lv_color_hex(0x000010), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiApp_Demo_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    return base_panel;
}

int app_dictionary_create(lv_obj_t * parent)
{
    uiApp_Dictionary = lv_obj_create(parent);
    // uiApp_Dictionary = lv_obj_create(parent);
    lv_obj_clear_flag(uiApp_Dictionary, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiApp_Dictionary, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Dictionary, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(uiApp_Dictionary, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * uiApp_DictionaryBody;
    uiApp_DictionaryBody = lv_obj_create(uiApp_Dictionary);
    lv_obj_set_size(uiApp_DictionaryBody, SCREEN_WIDTH, 140);
    // lv_obj_set_pos(uiApp_DictionaryBody, 2, 1);
    lv_obj_set_align(uiApp_DictionaryBody, LV_ALIGN_TOP_LEFT);
    lv_obj_add_flag(uiApp_DictionaryBody, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(uiApp_DictionaryBody, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
                      LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(uiApp_DictionaryBody, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiApp_DictionaryBody, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiApp_DictionaryBody, lv_color_hex(0x800000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_DictionaryBody, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(uiApp_DictionaryBody, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiApp_DictionaryBody, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiApp_DictionaryBtnStart = lv_btn_create(uiApp_DictionaryBody);
    lv_obj_set_size(uiApp_DictionaryBtnStart, 100, SCREEN_WIDTH>320?100:60);
    lv_obj_set_pos(uiApp_DictionaryBtnStart, 0, 0);
    lv_obj_set_align(uiApp_DictionaryBtnStart, SCREEN_WIDTH>320?LV_ALIGN_RIGHT_MID:LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(uiApp_DictionaryBtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiApp_DictionaryBtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnTranslate = lv_label_create(uiApp_DictionaryBtnStart);
    lv_label_set_text(ui_BtnTranslate, "Demo");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * panel1 = lv_obj_create(uiApp_DictionaryBody);
    // lv_obj_set_height(panel1, LV_SIZE_CONTENT);
    lv_obj_set_width(panel1, SCREEN_WIDTH-140);
    lv_obj_set_scrollbar_mode(panel1, LV_SCROLLBAR_MODE_OFF);
    if (SCREEN_WIDTH > 320) {
        // lv_obj_set_size(panel1, SCREEN_WIDTH-140, 700);
        lv_obj_set_scroll_dir(panel1, LV_DIR_TOP | LV_DIR_BOTTOM); // 仅允许上下滑动
    }
    lv_obj_set_style_border_side(panel1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(panel1, lv_color_hex(0x000080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * explain1 = lisaui_explain_label_create(panel1);
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
    .name = "词典",
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
    return lisaui_app_register(&app_dictionary);
}