/**
 * @file app_dictionary.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-03-03
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_dictionary.h"
#include "../../app_common/lisaui_app_common.h"
#include "../assets/assets_res.h"
#include "../../utils/lv_img_utils.h"

static lv_img_dsc_t img_gif5;
INCBIN(img_gif5, RES_PERFIX_PATH("ui/assets/img/00b44af.gif"));

static lv_img_dsc_t img_favorite;
static lv_img_dsc_t img_book;
static lv_img_dsc_t img_voice;
INCBIN(img_favorite, RES_PERFIX_PATH("ui/assets/img/icons/favorite.png"));
INCBIN(img_book, RES_PERFIX_PATH("ui/assets/img/icons/books.png"));
INCBIN(img_voice, RES_PERFIX_PATH("ui/assets/img/icons/voice.png"));

static const char *TAG = "app_dictionary";
struct _explain_t {
    const char *tittle;
    const char *description;
};

#define DESCRIPTION_INDEX2                                                                                             \
    "〈动〉(1) (形声。从耳，令声。本义：细听) [3](2) 同本义 [hear]聆广乐之九奏兮。——张衡《思玄赋》\
    宝玉接过来，一面目视其文，耳聆其歌。——《红楼梦》\
    扣而聆之。——宋· 苏轼《石钟山记》\
    (3) 又如：聆偈(听经)；聆受(倾听并接受)；聆训(听受训教)；聆教(聆听教晦)；聆音察理(听到声音就能明察事理)\
    (4) 明了，清楚 [understand]\
    观读之者，晓然若盲之开目，聆然若聋之通耳。——汉· 王充《论衡》 [3]\
    (5) 又如：聆聆(明了，清楚) [1]"

static struct _explain_t explain_list[] = {
    {"[古籍释义]", "《广韵》《集韵》《韵会》𠀤余六切，音育。地之肥也。以其能生长万物，故从育从土地之肥也。以其能生长万"
                   "物，故从育从土以其能生长万物，故从育从土"},
    {"基本字义", "#0000ff 聆#líng ⒈ 听：聆听。聆取。聆教（jiào ）"},
    {"基本词义", DESCRIPTION_INDEX2},
    {"释义", "#0000ff 聆听#。#0000ff 聆取#。#00ff00 聆教（jiao）#"},
    {"同义词", "XXX"},
    {"反义词", "XXX"},
};

/* -------------------------------------------------------------------------- */

static lv_style_t style_box;
static void visuals_tst_create(lv_obj_t *parent)
{

}

static lv_obj_t *img_gif = NULL;
static void lisaui_img_event_cb(lv_event_t *e)
{
    static bool is_pause = false;
    // printk("gif event code : %d\n", e->code);
    if (e->code == LV_EVENT_CLICKED) {
        lv_obj_t *img_gif = lv_event_get_target(e);
        if (is_pause) {
            lv_gif_resume(img_gif);
        } else {
            lv_gif_pause(img_gif);
        }
        is_pause = !is_pause;
    }
}
lv_obj_t *lisaui_explain_panel_create(lv_obj_t *parent)
{
    if (!parent) {
        return NULL;
    }

    lv_obj_t *base_panel = lv_obj_create(parent);




    // 设置 Flex 布局和对齐方式
    lv_obj_set_layout(base_panel, LV_LAYOUT_FLEX); // 设置为Flex布局
    lv_obj_set_flex_flow(base_panel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_border_width(base_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(base_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(base_panel, LV_OBJ_FLAG_SCROLL_ELASTIC);

    lv_obj_set_width(base_panel, LV_PCT(100));
    lv_obj_set_height(base_panel,  LV_PCT(100) - 20);

    lv_obj_set_scrollbar_mode(base_panel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(base_panel, LV_DIR_TOP | LV_DIR_BOTTOM); // 仅允许上下滑动
    lv_obj_set_scrollbar_mode(base_panel, LV_SCROLL_SNAP_NONE);
    lv_obj_set_style_border_side(base_panel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(base_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(base_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(base_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(base_panel, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(base_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *img_container = lv_obj_create(base_panel);
    // lv_obj_set_size(img_container, SCREEN_WIDTH - 100, 100);
    lv_obj_set_width(img_container,  LV_PCT(100) - 100);
    lv_obj_set_height(img_container, LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(img_container, LV_SCROLL_SNAP_NONE);
    lv_obj_set_style_border_side(img_container, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(img_container, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(img_container, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *img_gif = lv_gif_create(img_container);
    // lv_gif_set_src(img2, LV_SYMBOL_GIF_FILE_PATH_2);
    lv_img_gif_src_init(&img_gif5, gimg_gif5Data, gimg_gif5Size);
    lv_gif_set_src(img_gif, &img_gif5);
    lv_obj_align(img_gif, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_add_flag(img_gif, LV_OBJ_FLAG_CLICKABLE);
    
    lv_obj_add_event_cb(img_gif, lisaui_img_event_cb, LV_EVENT_ALL, NULL);

    lv_obj_t *uiDictionary_pingyinBtn = lv_btn_create(img_container);
    lv_obj_set_size(uiDictionary_pingyinBtn, 80, 40);
    lv_obj_align_to(uiDictionary_pingyinBtn, img_gif, LV_ALIGN_OUT_TOP_RIGHT, 120, 40);

    lv_obj_t *uiDictionary_pingyin = lv_label_create(uiDictionary_pingyinBtn);
    lv_label_set_text(uiDictionary_pingyin, "/yu/");
    lv_obj_set_style_text_font(uiDictionary_pingyin, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(uiDictionary_pingyin, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_align_to(uiDictionary_pingyin, img_gif, LV_ALIGN_OUT_TOP_RIGHT, 100, 40);

    lv_obj_t *uiDictionary_explain = lv_label_create(img_container);
    lv_label_set_text(uiDictionary_explain, "#FFFFFF 释义：# #FFFF00 肥沃的土地#");
    lv_label_set_recolor(uiDictionary_explain, true); /*Enable re-coloring by commands in the text*/
    // lv_label_set_text(uiDictionary_explain, "释义：肥沃的土地");
    // lv_label_set_text(uiDictionary_explain, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label, align the lines to
    // the center "
    //     "and wrap long text automatically.");
    lv_obj_set_style_text_font(uiDictionary_explain, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(uiDictionary_explain, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(uiDictionary_explain, uiDictionary_pingyin, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 20);

    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, 3);

    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_grad_color(&style, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_dir(&style, LV_GRAD_DIR_VER);

    lv_style_set_border_opa(&style, LV_OPA_40);
    lv_style_set_border_width(&style, 2);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_GREY));

    // lv_style_set_shadow_width(&style, 8);
    // lv_style_set_shadow_color(&style, lv_palette_main(LV_PALETTE_GREY));
    // lv_style_set_shadow_ofs_y(&style, 8);

    lv_style_set_outline_opa(&style, LV_OPA_COVER);
    lv_style_set_outline_color(&style, lv_palette_main(LV_PALETTE_BLUE));

    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_pad_all(&style, 10);

    /*Init the pressed style*/
    static lv_style_t style_pr;
    lv_style_init(&style_pr);

    /*Add a large outline when pressed*/
    lv_style_set_outline_width(&style_pr, 30);
    lv_style_set_outline_opa(&style_pr, LV_OPA_TRANSP);

    lv_style_set_translate_y(&style_pr, 5);
    lv_style_set_shadow_ofs_y(&style_pr, 3);
    lv_style_set_bg_color(&style_pr, lv_palette_darken(LV_PALETTE_BLUE, 2));
    lv_style_set_bg_grad_color(&style_pr, lv_palette_darken(LV_PALETTE_BLUE, 4));

    /*Add a transition to the outline*/
    static lv_style_transition_dsc_t trans;
    static lv_style_prop_t props[] = {LV_STYLE_OUTLINE_WIDTH, LV_STYLE_OUTLINE_OPA, 0};
    lv_style_transition_dsc_init(&trans, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_set_transition(&style_pr, &trans);

    lv_obj_t *uiApp_Demo_TextResult = NULL;
    for (int i = 0; i < sizeof(explain_list) / sizeof(struct _explain_t); i++) {
        lv_obj_t *uiApp_DictionaryBtnStart1 = lv_btn_create(base_panel);
        lv_obj_set_size(uiApp_DictionaryBtnStart1, 120, 40);
        lv_obj_set_x(uiApp_DictionaryBtnStart1, 20);
        lv_obj_align_to(uiApp_DictionaryBtnStart1, img_gif, LV_ALIGN_OUT_BOTTOM_LEFT, 30, 20 + i * 100);
        lv_obj_add_flag(uiApp_DictionaryBtnStart1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
        lv_obj_clear_flag(uiApp_DictionaryBtnStart1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
        lv_obj_remove_style_all(uiApp_DictionaryBtnStart1); /*Remove the style coming from the theme*/
        lv_obj_add_style(uiApp_DictionaryBtnStart1, &style, 0);
        lv_obj_add_style(uiApp_DictionaryBtnStart1, &style_pr, LV_STATE_PRESSED);
        lv_obj_set_size(uiApp_DictionaryBtnStart1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_t *ui_BtnTranslate = lv_label_create(uiApp_DictionaryBtnStart1);
        char text[20] = {0};
        // snprintf(&text[0], sizeof(text), explain_list[i].tittle);
        lv_label_set_text(ui_BtnTranslate, explain_list[i].tittle);
        lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(ui_BtnTranslate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

        uiApp_Demo_TextResult = lv_label_create(base_panel);
        // if (SCREEN_WIDTH > 320) {
            lv_obj_set_width(uiApp_Demo_TextResult, LV_PCT(100) - 120);
            lv_obj_set_height(uiApp_Demo_TextResult, LV_SIZE_CONTENT);
        // } else {
        //     lv_obj_set_size(uiApp_Demo_TextResult, SCREEN_WIDTH - 100, 100);
        // }

        lv_obj_align_to(uiApp_Demo_TextResult, img_gif, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 20 + i * 100 + 50);
        lv_obj_set_style_text_font(uiApp_Demo_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_label_set_text(uiApp_Demo_TextResult, explain_list[i].description);
        lv_label_set_recolor(uiApp_Demo_TextResult, true);
        lv_obj_set_style_text_color(uiApp_Demo_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(uiApp_Demo_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(uiApp_Demo_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
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
    lv_obj_add_style(uiApp_DictionaryBtnStart1, &style, 0);
    lv_obj_add_style(uiApp_DictionaryBtnStart1, &style_pr, LV_STATE_PRESSED);

    lv_obj_t *ui_BtnTranslate = lv_label_create(uiApp_DictionaryBtnStart1);
    lv_label_set_text(ui_BtnTranslate, "详细解释");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *uiApp_Demo_Text = lv_textarea_create(base_panel);
    lv_obj_align_to(uiApp_Demo_Text, uiApp_Demo_TextResult, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 100);
    lv_obj_set_size(uiApp_Demo_Text, LV_PCT(100) - 80, LV_SIZE_CONTENT);
    lv_obj_set_style_text_font(uiApp_Demo_Text, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(uiApp_Demo_Text, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_text(uiApp_Demo_Text, UI_TEST_STR1);

    lv_obj_set_style_text_color(uiApp_Demo_Text, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiApp_Demo_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiApp_Demo_Text, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Demo_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiApp_Demo_Text, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiApp_Demo_Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(uiApp_Demo_Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    return base_panel;
}

/* -------------------------------------------------------------------------- */
static lv_obj_t *g_app_dictionary = NULL;
lisaui_err_t app_dictionary_create(void *parent)
{
    if (g_app_dictionary != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_dictionary = lv_obj_create(parent);
    // // _lisaui_set_style_container(g_app_dictionary, lv_color_hex(0x1F1F1F), 255, lv_color_hex(0x000000), 0, 0);
    // _lisaui_set_style_container(g_app_dictionary, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    // lv_obj_set_style_local_pad_all(g_app_dictionary, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 30);
    // lv_obj_set_style_local_margin_all(g_app_dictionary, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 30);

    lisaui_explain_panel_create(g_app_dictionary);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_dictionary_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_dictionary_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_dictionary_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_dictionary_get_page(void)
{
    return g_app_dictionary;
}

static struct app_icon_t app_icon_res = {
#if CONFIG_LISAUI_FONT_LANGUAGE_ZH_CN_ENABLE
    .title = "词典",
#else
    .title = "Dictionary",
#endif

    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = (const uint8_t *)&ui_img_icon_fav_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_dictionary = {
    .create = app_dictionary_create,
    .destroy = app_dictionary_destroy,
    .enter = app_dictionary_enter,
    .exit = app_dictionary_exit,

    .get_root_view = app_dictionary_get_page,
    .info =
        {
            .name = "Dictionary",
            .package_name = "com.listenai.lisaui.dictionary",
            .id = UI_APP_ID_DICTIONARY,
        },
    .icon = &app_icon_res,
};

lisaui_err_t app_dictionary_init(void)
{
    lisaui_app_register(&app_dictionary);
    return LISAUI_ERR_OK;
}

REGISTER_LISAUI_APP(dictionary, &app_dictionary, app_dictionary_init);