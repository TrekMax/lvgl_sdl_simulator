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

static lv_img_dsc_t img_favorite;
INCBIN(img_favorite, "app/pendict/ui/assets/img/icons/favorite.png");
static lv_img_dsc_t img_book;
INCBIN(img_book, "app/pendict/ui/assets/img/icons/books.png");
static lv_img_dsc_t img_voice;
INCBIN(img_voice, "app/pendict/ui/assets/img/icons/voice.png");

lv_obj_t *uiApp_Dictionary = NULL;
lv_obj_t *uiApp_DictionaryBtnStart = NULL;

lv_obj_t *lisaui_explain_label_create(lv_obj_t *parent)
{
    // printk("[%d:%s] ---------------->enter\n", __LINE__, __func__);
    if (!parent) {
        return NULL;
    }

    lv_obj_clear_flag(parent, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_t *base_panel = lv_obj_create(parent);
    lv_obj_set_pos(base_panel, 0, -10);

    lv_obj_set_style_border_width(base_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(base_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(base_panel, LV_OBJ_FLAG_SCROLL_ELASTIC);

    lv_obj_t *img_gif;
    img_gif = lv_gif_create(base_panel);
    // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    lv_img_gif_src_init(&img_gif5, gimg_gif5Data, gimg_gif5Size);
    lv_gif_set_src(img_gif, &img_gif5);
    lv_obj_align(img_gif, LV_ALIGN_TOP_LEFT, 0, 0);

    // lv_obj_set_height(base_panel, 600);
    // lv_obj_set_height(base_panel, LV_SIZE_CONTENT);
    lv_obj_set_width(base_panel, SCREEN_WIDTH - 100);

    // lv_obj_set_width(base_panel, lv_obj_get_width(parent));
    lv_obj_set_scrollbar_mode(base_panel, LV_SCROLLBAR_MODE_OFF);
    // if (SCREEN_WIDTH > 320) {
    //     // lv_obj_set_size(base_panel, SCREEN_WIDTH-140, 700);
    lv_obj_set_scroll_dir(base_panel, LV_DIR_TOP | LV_DIR_BOTTOM); // 仅允许上下滑动
    // }
    lv_obj_set_scrollbar_mode(base_panel, LV_SCROLL_SNAP_NONE);
    lv_obj_set_style_border_side(base_panel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(base_panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(base_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *uiDictionary_pingyin = lv_label_create(base_panel);
    lv_label_set_text(uiDictionary_pingyin, "/yu[四声]/");
    lv_obj_set_style_text_font(uiDictionary_pingyin, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(uiDictionary_pingyin, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(uiDictionary_pingyin, img_gif, LV_ALIGN_OUT_TOP_RIGHT, 100, 40);

    lv_obj_t *uiDictionary_explain = lv_label_create(base_panel);
    lv_label_set_text(uiDictionary_explain, "释义：肥沃的土地");
    lv_obj_set_style_text_font(uiDictionary_explain, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(uiDictionary_explain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(uiDictionary_explain, uiDictionary_pingyin, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

    lv_obj_t *uiApp_Demo_TextResult = NULL;
    for (int i = 0; i < 10; i++) {
        lv_obj_t *uiApp_DictionaryBtnStart1 = lv_btn_create(base_panel);
        lv_obj_set_size(uiApp_DictionaryBtnStart1, 100, 40);
        lv_obj_align_to(uiApp_DictionaryBtnStart1, img_gif, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 20 + i * 100);
        lv_obj_add_flag(uiApp_DictionaryBtnStart1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
        lv_obj_clear_flag(uiApp_DictionaryBtnStart1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags

        lv_obj_t *ui_BtnTranslate = lv_label_create(uiApp_DictionaryBtnStart1);
        char text[20] = {0};
        snprintf(&text[0], sizeof(text), "释义 %d", i);
        lv_label_set_text(ui_BtnTranslate, text);
        lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

        uiApp_Demo_TextResult = lv_label_create(base_panel);
        if (SCREEN_WIDTH > 320) {
            // lv_obj_set_size(panel1, SCREEN_WIDTH-140, 700);
            // lv_obj_set_size(uiApp_Demo_TextResult, SCREEN_WIDTH-200, 100);
            lv_obj_set_width(uiApp_Demo_TextResult, SCREEN_WIDTH - 200);
            lv_obj_set_height(uiApp_Demo_TextResult, LV_SIZE_CONTENT);
        } else {
            lv_obj_set_size(uiApp_Demo_TextResult, SCREEN_WIDTH - 100, 100);
        }

        lv_obj_align_to(uiApp_Demo_TextResult, img_gif, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 20 + i * 100 + 50);
        // lv_obj_set_align(uiApp_Demo_TextResult, LV_ALIGN_TOP_LEFT);
        lv_obj_set_style_text_font(uiApp_Demo_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        // lv_label_set_text(uiApp_Demo_TextResult, "这是一条中文测试用例");
        lv_label_set_text(uiApp_Demo_TextResult,
                          "1.[古籍释义]《广韵》《集韵》《韵会》𠀤余六切，音育。地之肥也。以其能生长万物，故从育从土");

        lv_obj_set_style_text_color(uiApp_Demo_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(uiApp_Demo_TextResult, lv_color_hex(0x000010), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(uiApp_Demo_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(uiApp_Demo_TextResult, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    lv_obj_t *uiApp_DictionaryBtnStart1 = lv_btn_create(base_panel);
    lv_obj_set_size(uiApp_DictionaryBtnStart1, 100, 40);
    lv_obj_align_to(uiApp_DictionaryBtnStart1, uiApp_Demo_TextResult, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 40);
    lv_obj_add_flag(uiApp_DictionaryBtnStart1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(uiApp_DictionaryBtnStart1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags

    lv_obj_t *ui_BtnTranslate = lv_label_create(uiApp_DictionaryBtnStart1);
    // char text[20] = {0};
    // snprintf(&text[0], sizeof(text), "释义 %d", i);
    lv_label_set_text(ui_BtnTranslate, "详细解释");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *uiApp_Demo_Text = lv_textarea_create(base_panel);
    // lv_obj_align_to(uiApp_Demo_Text, img_gif, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 20+10*100+40);
    lv_obj_align_to(uiApp_Demo_Text, uiApp_Demo_TextResult, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 100);
    lv_obj_set_size(uiApp_Demo_Text, SCREEN_WIDTH - 200, 240);
    // lv_obj_set_align(uiApp_Demo_Text, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiApp_Demo_Text, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_label_set_text(uiApp_Demo_Text, "这是一条中文测试用例");
    lv_textarea_set_text(uiApp_Demo_Text, "《诗经·小雅·信南山》中有这样一句：\
    “信彼南山，维禹甸之。畇畇原隰，曾孙田之。我疆我理，南东其亩。” \
    其中“畇畇原隰”中的“畇畇”形容田地平坦整齐，而“原隰”则指高平之地和低湿之地，整体描绘了土地的肥沃和平整，虽然没有直接使用“堉”字，但表达了类似的意思。 \
    另外，古代农书如《齐民要术》中也有关于土地耕作和土壤肥沃的描述，可能会间接涉及到“堉”的概念。 \
    如果你对某个具体文献或古文有兴趣，可以进一步查阅相关资料。");

    lv_obj_set_style_text_color(uiApp_Demo_Text, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiApp_Demo_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiApp_Demo_Text, lv_color_hex(0x000010), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Demo_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiApp_Demo_Text, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiApp_Demo_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(uiApp_Demo_Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    return base_panel;
}

int app_dictionary_create(lv_obj_t *parent)
{
    uiApp_Dictionary = lv_obj_create(parent);
    // uiApp_Dictionary = lv_obj_create(parent);
    lv_obj_clear_flag(uiApp_Dictionary, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(uiApp_Dictionary, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Dictionary, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(uiApp_Dictionary, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *uiApp_DictionaryBody;
    uiApp_DictionaryBody = lv_obj_create(uiApp_Dictionary);
    lv_obj_set_size(uiApp_DictionaryBody, SCREEN_WIDTH, 140);
    // lv_obj_set_size(uiApp_DictionaryBody, SCREEN_WIDTH, 440);
    lv_obj_set_pos(uiApp_DictionaryBody, 0, 30);
    lv_obj_set_align(uiApp_DictionaryBody, LV_ALIGN_TOP_LEFT);
    lv_obj_add_flag(uiApp_DictionaryBody, LV_OBJ_FLAG_SCROLL_ONE); /// Flags
    lv_obj_clear_flag(uiApp_DictionaryBody,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE); /// Flags
    lv_obj_set_scrollbar_mode(uiApp_DictionaryBody, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiApp_DictionaryBody, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiApp_DictionaryBody, lv_color_hex(0x008000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_DictionaryBody, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(uiApp_DictionaryBody, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiApp_DictionaryBody, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_scroll_bounce(uiApp_DictionaryBody, false);  // 禁用回弹效果
    lv_obj_clear_flag(uiApp_DictionaryBody, LV_OBJ_FLAG_SCROLL_ELASTIC);

    // uiApp_DictionaryBtnStart = lv_btn_create(uiApp_DictionaryBody);
    // lv_obj_set_size(uiApp_DictionaryBtnStart, 40, SCREEN_WIDTH>320?80:60);
    // lv_obj_set_pos(uiApp_DictionaryBtnStart, 0, 0);
    // // lv_obj_set_align(uiApp_DictionaryBtnStart, SCREEN_WIDTH>320?LV_ALIGN_TOP_RIGHT:LV_ALIGN_BOTTOM_RIGHT);
    // lv_obj_align(uiApp_DictionaryBtnStart, SCREEN_WIDTH>320?LV_ALIGN_TOP_RIGHT:LV_ALIGN_BOTTOM_RIGHT, 0, 20);
    // lv_obj_add_flag(uiApp_DictionaryBtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    // lv_obj_clear_flag(uiApp_DictionaryBtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    // lv_obj_t * ui_BtnTranslate = lv_label_create(uiApp_DictionaryBtnStart);
    // lv_label_set_text(ui_BtnTranslate, "De");
    // lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_set_scroll_dir(uiApp_DictionaryBody, LV_DIR_TOP | LV_DIR_BOTTOM); // 仅允许上下滑动

    lv_obj_t *uiIcon_Book = lv_img_create(uiApp_DictionaryBody);
    lv_img_png_src_init(&img_book, gimg_bookData, gimg_bookSize);
    lv_img_set_src(uiIcon_Book, &img_book);
    lv_obj_set_size(uiIcon_Book, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiIcon_Book, 0, 0);
    lv_obj_set_align(uiIcon_Book, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(uiIcon_Book, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(uiIcon_Book, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *uiIcon_Voice = lv_img_create(uiApp_DictionaryBody);
    lv_img_png_src_init(&img_voice, gimg_voiceData, gimg_voiceSize);
    lv_img_set_src(uiIcon_Voice, &img_voice);
    lv_obj_set_size(uiIcon_Voice, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiIcon_Voice, 0, 40);
    lv_obj_set_align(uiIcon_Voice, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(uiIcon_Voice, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(uiIcon_Voice, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *uiIcon_Favorite = lv_img_create(uiApp_DictionaryBody);
    lv_img_png_src_init(&img_favorite, gimg_favoriteData, gimg_favoriteSize);
    lv_img_set_src(uiIcon_Favorite, &img_favorite);
    lv_obj_set_size(uiIcon_Favorite, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiIcon_Favorite, 0, 80);
    lv_obj_set_align(uiIcon_Favorite, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(uiIcon_Favorite, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(uiIcon_Favorite, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *explain1 = lisaui_explain_label_create(uiApp_DictionaryBody);

    return 0;
}

lv_obj_t *app_dictionary_get_page(void)
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