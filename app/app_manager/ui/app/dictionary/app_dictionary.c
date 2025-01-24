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
#include "../../common/lisaui_app_common.h"
// #include "../utils/lv_img_utils.h"

// static lv_img_dsc_t img_gif5;
// INCBIN(img_gif5, "app/pendict/ui/assets/gif/00b44af.gif");

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

    // lv_page_set_scrl_layout(parent, LV_LAYOUT_PRETTY_TOP);
    lv_page_set_scrl_layout(parent, LV_LAYOUT_COLUMN_LEFT);
    // lv_obj_set_width_margin(parent, LV_DPX(100));
    lv_obj_set_width(parent, LV_HOR_RES - LV_DPX(100));
    // lv_page_set_scrl_height(parent, LV_VER_RES - LV_DPX(100));
    lv_page_set_scrl_width(parent, LV_HOR_RES);
    // lv_obj_set_width(parent,   300);

    extern const uint8_t example_gif_map[]; /*Use the example gif*/
    lv_obj_t *img = lv_gif_create_from_data(parent, example_gif_map);
    // lv_obj_set_pos(img, LV_DPX(40), LISAUI_STATUS_BAR_HEIGHT + LV_DPX(10));

    lv_disp_size_t disp_size = lv_disp_get_size_category(NULL);

    lv_coord_t grid_h_chart = lv_page_get_height_grid(parent, 1, 1);
    lv_coord_t grid_w_chart = lv_page_get_width_grid(parent, 1, 1);
    // lv_coord_t grid_w_chart = lv_page_get_width_grid(parent, disp_size <= LV_DISP_SIZE_LARGE ? 1 : 2, 1);
    // lv_obj_set_height_margin(parent, LV_DPX(10));

#if 1
    lv_obj_t *uiApp_Demo_TextResult = NULL;
    for (int i = 0; i < sizeof(explain_list) / sizeof(struct _explain_t); i++) {
        lv_obj_t *uiApp_DictionaryBtnStart1 = lv_btn_create(parent, NULL);
        lv_obj_set_size(uiApp_DictionaryBtnStart1, 120, 40);
        // lv_obj_set_x(uiApp_DictionaryBtnStart1, 400);
        lv_obj_set_x(uiApp_DictionaryBtnStart1, LV_DPX(40));
        _lisaui_lv_obj_set_btn_custom_style(uiApp_DictionaryBtnStart1);
        // lv_obj_add_flag(uiApp_DictionaryBtnStart1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
        // lv_obj_clear_flag(uiApp_DictionaryBtnStart1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags

        // lv_obj_add_style(uiApp_DictionaryBtnStart1, &style, 0);
        // lv_obj_add_style(uiApp_DictionaryBtnStart1, &style_pr, LV_STATE_PRESSED);
        // lv_obj_set_size(uiApp_DictionaryBtnStart1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

        lv_obj_t *ui_BtnTranslate = lv_label_create(uiApp_DictionaryBtnStart1, NULL);
        char text[20] = {0};
        _lisaui_lv_obj_set_default_style(ui_BtnTranslate);

        lv_label_set_text(ui_BtnTranslate, explain_list[i].tittle);
        // lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
        // lv_obj_set_style_text_color(ui_BtnTranslate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

        uiApp_Demo_TextResult = lv_label_create(parent, NULL);
        _lisaui_lv_obj_set_default_style(uiApp_Demo_TextResult);
        lv_obj_set_width_margin(uiApp_Demo_TextResult, grid_w_chart);
        lv_obj_set_height_margin(uiApp_Demo_TextResult, grid_h_chart);

        lv_obj_set_width(uiApp_Demo_TextResult, 300);
        // lv_obj_set_width(parent,   300);

        if (explain_list[i].description) {
            lv_label_set_text(uiApp_Demo_TextResult, explain_list[i].description);
            lv_label_set_long_mode(uiApp_Demo_TextResult, LV_LABEL_LONG_BREAK); /*Break the long lines*/
        }
        lv_label_set_recolor(uiApp_Demo_TextResult, true);
    }
#endif
    // lv_obj_t *ta1 = lv_textarea_create(parent, NULL);
    // // lv_obj_set_size(ta1, LV_DPX(100), 100);
    // lv_obj_set_size(ta1, lv_obj_get_width(parent), 200);
    // lv_obj_align(ta1, NULL, LV_ALIGN_CENTER, 0, 0);
    // _lisaui_lv_obj_set_default_style(ta1);
    // lv_textarea_set_text(ta1, UI_TEST_STR1); /*Set an initial text*/

    lv_obj_t *label1 = lv_label_create(parent, NULL);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK); /*Break the long lines*/
    // lv_label_set_recolor(label1, true);                  /*Enable re-coloring by commands in the text*/
    // lv_label_set_align(label1, LV_LABEL_ALIGN_CENTER);   /*Center aligned lines*/
    lv_label_set_text(label1, UI_TEST_STR1);
    lv_obj_set_width(label1, LV_HOR_RES);
    _lisaui_lv_obj_set_default_style(label1);
    // lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -30);
}

static lv_obj_t *img_gif = NULL;
lv_obj_t *lisaui_explain_panel_create(lv_obj_t *parent)
{
    if (!parent) {
        return NULL;
    }

#if 1
    lv_obj_t *base_panel = lv_page_create(parent, NULL);
    lv_obj_set_style_local_pad_all(base_panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 30);
    lv_obj_set_style_local_margin_all(base_panel, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 30);

    lv_obj_set_y(base_panel, LISAUI_STATUS_BAR_HEIGHT + LV_DPX(10));
    lv_obj_set_x(base_panel, LV_DPX(40));
    lv_obj_set_size(base_panel, LV_HOR_RES - LV_DPX(20), LV_VER_RES - LV_DPX(50));
    _lisaui_set_style_container(base_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    lv_page_set_scrollbar_mode(base_panel, LV_SCROLLBAR_MODE_OFF); // 隐藏滚动条

    lv_style_init(&style_box);
    lv_style_set_value_align(&style_box, LV_STATE_DEFAULT, LV_ALIGN_OUT_TOP_LEFT);
    lv_style_set_value_ofs_y(&style_box, LV_STATE_DEFAULT, -LV_DPX(10));
    lv_style_set_margin_top(&style_box, LV_STATE_DEFAULT, LV_DPX(30));

    visuals_tst_create(base_panel);
#endif

    return base_panel;
}

/* -------------------------------------------------------------------------- */
static lv_obj_t *g_app_dictionary = NULL;
lisaui_err_t app_dictionary_create(void *parent)
{
    if (g_app_dictionary != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_dictionary = lv_obj_create(parent, parent);
    // _lisaui_set_style_container(g_app_dictionary, lv_color_hex(0x1F1F1F), 255, lv_color_hex(0x000000), 0, 0);
    _lisaui_set_style_container(g_app_dictionary, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    lv_obj_set_style_local_pad_all(g_app_dictionary, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 30);
    lv_obj_set_style_local_margin_all(g_app_dictionary, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 30);

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
    .title = "词典",
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