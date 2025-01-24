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
INCBIN(img_gif4, RES_PERFIX_PATH("ui/assets/img/00b44af.gif"));

static lv_img_dsc_t img_jpg1;
INCBIN(img_jpg1, RES_PERFIX_PATH("ui/assets/img/Het_meisje_met_de_parel.jpg"));

lv_obj_t *uiApp_Demo;
lv_obj_t *uiApp_Demo_Body;
lv_obj_t *uiApp_Demo_TextResult;
lv_obj_t *uiApp_Demo_ImgOCRTips;
lv_obj_t *uiApp_Demo_LabelOCRTips;
lv_obj_t *uiApp_Demo_BtnStart;
lv_obj_t *uiApp_Demo_BtnStop;

static lv_style_t style_title;
static lv_style_t style_text_muted;

int app_demo_create(lv_obj_t *parent)
{
    uiApp_Demo = lv_obj_create(parent);
    lv_obj_clear_flag(uiApp_Demo, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(uiApp_Demo, lv_color_hex(0x0FF000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Demo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // uiApp_Demo_Body = lv_obj_create(uiApp_Demo);
    // // lv_obj_set_size(uiApp_Demo_Body, SCREEN_WIDTH, 140);
    lv_obj_set_size(uiApp_Demo, LV_PCT(100), LV_PCT(96));
    lv_obj_set_pos(uiApp_Demo, 10, 30);
    // lv_obj_set_align(uiApp_Demo_Body, LV_ALIGN_LEFT_MID);
    // lv_obj_add_flag(uiApp_Demo_Body, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    // lv_obj_clear_flag(uiApp_Demo_Body, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
    //                   LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    // lv_obj_set_scrollbar_mode(uiApp_Demo_Body, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_set_scroll_dir(uiApp_Demo_Body, LV_DIR_HOR);
    // lv_obj_set_style_bg_color(uiApp_Demo_Body, lv_color_hex(0x000FF0), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(uiApp_Demo_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_side(uiApp_Demo_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiApp_Demo_BtnStart = lv_btn_create(uiApp_Demo);
    lv_obj_set_size(uiApp_Demo_BtnStart, 100, SCREEN_WIDTH > 320 ? 100 : 60);
    lv_obj_set_pos(uiApp_Demo_BtnStart, -10, 40);
    lv_obj_set_align(uiApp_Demo_BtnStart, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(uiApp_Demo_BtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(uiApp_Demo_BtnStart, LV_OBJ_FLAG_SCROLLABLE);    /// Flags

    lv_obj_t *ui_BtnTranslate = lv_label_create(uiApp_Demo_BtnStart);
    lv_label_set_text(ui_BtnTranslate, "Demo");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *panel1 = lv_obj_create(uiApp_Demo);
    // lv_obj_set_height(panel1, LV_SIZE_CONTENT);
    lv_obj_set_size(panel1, LV_PCT(80), LV_PCT(86));
    lv_obj_set_pos(panel1, 10, 30);
    lv_obj_set_scrollbar_mode(panel1, LV_SCROLLBAR_MODE_OFF);
    if (SCREEN_WIDTH > 320) {
        // lv_obj_set_size(panel1, SCREEN_WIDTH-140, 700);
        lv_obj_set_scroll_dir(panel1, LV_DIR_TOP | LV_DIR_BOTTOM); // 仅允许上下滑动
    }
    lv_obj_set_style_border_side(panel1, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(panel1, lv_color_hex(0x00000F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *img_gif;
    img_gif = lv_gif_create(panel1);
    // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    lv_img_gif_src_init(&img_gif4, gimg_gif4Data, gimg_gif4Size);
    lv_gif_set_src(img_gif, &img_gif4);
    lv_obj_align(img_gif, LV_ALIGN_LEFT_MID, 10, 0);
    // lv_obj_set_size(img_gif, 100, 100);

#if 1
    uiApp_Demo_TextResult = lv_label_create(panel1);
    if (SCREEN_WIDTH > 320) {
        // lv_obj_set_size(panel1, SCREEN_WIDTH-140, 700);
        lv_obj_set_size(uiApp_Demo_TextResult, SCREEN_WIDTH - 300, 100);
    } else {
        lv_obj_set_size(uiApp_Demo_TextResult, SCREEN_WIDTH - 100, 100);
    }
    // lv_obj_set_pos(uiApp_Demo_TextResult, 20, 40);
    lv_obj_align_to(uiApp_Demo_TextResult, img_gif, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    lv_obj_set_align(uiApp_Demo_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiApp_Demo_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_label_set_text(uiApp_Demo_TextResult, "这是一条中文测试用例");
    lv_label_set_text(uiApp_Demo_TextResult, "《戴珍珠耳环的少女》（荷兰语：Het meisje met de "
                                             "parel），十七世纪荷兰画家扬·维米尔的作品。画作以少女戴着的珍珠耳环作为视"
                                             "角的焦点，现时画作存放在海牙的毛里茨住宅中。");

    lv_obj_set_style_text_color(uiApp_Demo_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiApp_Demo_TextResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiApp_Demo_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *uiTest_Textarea = lv_textarea_create(panel1);
    lv_obj_set_size(uiTest_Textarea, SCREEN_WIDTH - 160, 700);
    lv_obj_set_pos(uiTest_Textarea, 20, 40);
    // lv_obj_set_align(uiTest_Textarea, LV_ALIGN_TOP_LEFT);

    lv_obj_set_style_text_font(uiTest_Textarea, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_textarea_set_placeholder_text(uiTest_Textarea, UI_TEST_STR);
    lv_textarea_set_text(uiTest_Textarea, UI_TEST_STR UI_TEST_STR UI_TEST_STR UI_TEST_STR);
    lv_obj_align_to(uiTest_Textarea, img_gif, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    // lv_label_set_text(uiTest_Textarea, UI_TEST_STR);
    // lv_textarea_set_cursor_click_pos(uiTest_Textarea, true);
    lv_obj_set_style_text_color(uiTest_Textarea, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiTest_Textarea, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiTest_Textarea, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiTest_Textarea, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiTest_Textarea, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiTest_Textarea, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_center(ui_BtnTranslate);
#endif
    lv_obj_t *img_jpg;
    img_jpg = lv_img_create(panel1);
    // lv_gif_set_src(img, LV_SYMBOL_GIF_FILE_PATH_1);
    lv_img_jpg_src_init(&img_jpg1, gimg_jpg1Data, gimg_jpg1Size);
    lv_img_set_src(img_jpg, &img_jpg1);
    // lv_obj_set_size(img_jpg, 100, 100);
    // lv_obj_set_height(img_jpg, 100);
    // lv_img_set_zoom(img_jpg, 256);
    lv_obj_align_to(img_jpg, img_gif, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);

    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title, &lv_font_montserrat_18);
    lv_style_init(&style_text_muted);
    lv_style_set_text_opa(&style_text_muted, LV_OPA_50);
#if 1
    /*Create the second panel*/
    lv_obj_t *panel2 = lv_obj_create(panel1);
    // lv_obj_set_height(panel2, LV_SIZE_CONTENT);
    // lv_obj_set_size(panel2, SCREEN_WIDTH-140, 140);
    lv_obj_set_height(panel2, 140);
    lv_obj_set_width(panel2, LV_PCT(100));
    lv_obj_align_to(panel2, uiTest_Textarea, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
    lv_obj_set_style_bg_color(panel2, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *panel2_title = lv_label_create(panel2);
    lv_label_set_text(panel2_title, "Your profile");
    lv_obj_add_style(panel2_title, &style_title, 0);

    lv_obj_t *user_name_label = lv_label_create(panel2);
    lv_label_set_text(user_name_label, "User name");
    lv_obj_add_style(user_name_label, &style_text_muted, 0);

    lv_obj_t *user_name = lv_textarea_create(panel2);
    lv_textarea_set_one_line(user_name, true);
    lv_textarea_set_placeholder_text(user_name, "Your name");
    // lv_obj_add_event_cb(user_name, ta_event_cb, LV_EVENT_ALL, kb);

    lv_obj_t *password_label = lv_label_create(panel2);
    lv_label_set_text(password_label, "Password");
    // lv_obj_add_style(password_label, &style_text_muted, 0);

    lv_obj_t *password = lv_textarea_create(panel2);
    lv_textarea_set_one_line(password, true);
    lv_textarea_set_password_mode(password, true);
    lv_textarea_set_placeholder_text(password, "Min. 8 chars.");
    // lv_obj_add_event_cb(password, ta_event_cb, LV_EVENT_ALL, kb);

    lv_obj_t *gender_label = lv_label_create(panel2);
    lv_label_set_text(gender_label, "Gender");
    // lv_obj_add_style(gender_label, &style_text_muted, 0);

    lv_obj_t *gender = lv_dropdown_create(panel2);
    lv_dropdown_set_options_static(gender, "Male\nFemale\nOther");

    lv_obj_t *birthday_label = lv_label_create(panel2);
    lv_label_set_text(birthday_label, "Birthday");
    // lv_obj_add_style(birthday_label, &style_text_muted, 0);

    lv_obj_t *birthdate = lv_textarea_create(panel2);
    lv_textarea_set_one_line(birthdate, true);

    static lv_coord_t grid_2_col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t grid_2_row_dsc[] = {LV_GRID_CONTENT, /*Title*/
                                          5,               /*Separator*/
                                          LV_GRID_CONTENT, /*Box title*/
                                          30,              /*Boxes*/
                                          5,               /*Separator*/
                                          LV_GRID_CONTENT, /*Box title*/
                                          30,              /*Boxes*/
                                          LV_GRID_TEMPLATE_LAST};
    // lv_obj_add_event_cb(birthdate, birthday_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_grid_cell(panel2, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_dsc_array(panel2, grid_2_col_dsc, grid_2_row_dsc);
    lv_obj_set_grid_cell(panel2_title, LV_GRID_ALIGN_START, 0, 2, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_set_grid_cell(user_name, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_CENTER, 3, 1);
    lv_obj_set_grid_cell(user_name_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 2, 1);
    lv_obj_set_grid_cell(password, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_CENTER, 3, 1);
    lv_obj_set_grid_cell(password_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_START, 2, 1);
    lv_obj_set_grid_cell(birthdate, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_CENTER, 6, 1);
    lv_obj_set_grid_cell(birthday_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_START, 5, 1);
    lv_obj_set_grid_cell(gender, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_CENTER, 6, 1);
    lv_obj_set_grid_cell(gender_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 5, 1);
#endif
    return 0;
}

lv_obj_t *app_demo_get_page(void)
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
    .info = {
        .name = "Demo",
        .package_name = "com.listenai.lisaui.demo",
        .id = UI_APP_ID_DEMO,
    },
    .icon = &icon_demo,
};
int app_demo_init(void)
{
    lisaui_app_register(&app_demo);
    return 0;
}

REGISTER_LISAUI_APP(lisaui_demo, app_demo_init);

void printk_app_demo_info(void)
{
}
