/**
 * @file app_demo.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_demo.h"
#include "../ui.h"
#include "../utils/lv_img_utils.h"

static lv_img_dsc_t img_gif4;
INCBIN(img_gif4, "app/pendict/ui/assets/img/00b44af.gif");


// Scan App
lv_obj_t * uiApp_Demo;
lv_obj_t * uiApp_Demo_Body;
lv_obj_t * uiApp_Demo_TextResult;
lv_obj_t * uiApp_Demo_ImgOCRTips;
lv_obj_t * uiApp_Demo_LabelOCRTips;
lv_obj_t * uiApp_Demo_BtnStart;
lv_obj_t * uiApp_Demo_BtnStop;

int app_demo_create(lv_obj_t * parent)
{
    uiApp_Demo = lv_obj_create(parent);
    lv_obj_clear_flag(uiApp_Demo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiApp_Demo, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Demo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiApp_Demo_Body = lv_obj_create(uiApp_Demo);
    lv_obj_set_size(uiApp_Demo_Body, SCREEN_WIDTH, 140);
    lv_obj_set_pos(uiApp_Demo_Body, 2, 1);
    lv_obj_set_align(uiApp_Demo_Body, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(uiApp_Demo_Body, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(uiApp_Demo_Body, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
                      LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(uiApp_Demo_Body, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiApp_Demo_Body, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiApp_Demo_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Demo_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiApp_Demo_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiApp_Demo_TextResult = lv_label_create(uiApp_Demo);
    lv_obj_set_size(uiApp_Demo_TextResult, SCREEN_WIDTH-140, 100);
    lv_obj_set_pos(uiApp_Demo_TextResult, 20, 40);
    lv_obj_set_align(uiApp_Demo_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiApp_Demo_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(uiApp_Demo_TextResult, "这是一条中文测试用例");
    lv_obj_set_style_text_color(uiApp_Demo_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiApp_Demo_TextResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiApp_Demo_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiApp_Demo_BtnStart = lv_btn_create(uiApp_Demo_Body);
    lv_obj_set_size(uiApp_Demo_BtnStart, 100, SCREEN_WIDTH>320?100:60);
    lv_obj_set_pos(uiApp_Demo_BtnStart, 0, 0);
    lv_obj_set_align(uiApp_Demo_BtnStart, SCREEN_WIDTH>320?LV_ALIGN_RIGHT_MID:LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(uiApp_Demo_BtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiApp_Demo_BtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnTranslate = lv_label_create(uiApp_Demo_BtnStart);
    lv_label_set_text(ui_BtnTranslate, "Demo");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_center(ui_BtnTranslate);

    lv_obj_t * img_gif;
    img_gif = lv_gif_create(uiApp_Demo);
    // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    lv_img_gif_src_init(&img_gif4, gimg_gif4Data, gimg_gif4Size);
    lv_gif_set_src(img_gif, &img_gif4);
    lv_obj_align(img_gif, LV_ALIGN_LEFT_MID, 260+120, 0);
    return 0;
}

lv_obj_t * app_demo_get_page(void)
{
    return uiApp_Demo;
}


int app_demo_destroy(void)
{
    printk("[%d:%s] destroy\n", __LINE__, __func__);
    return 0;
}

int app_demo_enter(void)
{
    printk("[%d:%s] enter\n", __LINE__, __func__);
    return 0;
}

int app_demo_exit(void)
{
    printk("[%d:%s] exit\n", __LINE__, __func__);
    return 0;
}

struct app_icon_t icon_demo = {
    .name = "Demo",
    .icon_width = LV_SIZE_CONTENT,
    .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img__launcher_fav_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_demo = {
    .create = app_demo_create,
    .destroy = app_demo_destroy,
    .enter = app_demo_enter,
    .exit = app_demo_exit,

    .get_obj_handle = app_demo_get_page,
    .app_id = UI_APP_ID_DEMO,
    .icon = &icon_demo,
};

int app_demo_init(void)
{
    return lisaui_app_register(&app_demo);
}
