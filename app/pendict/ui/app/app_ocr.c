/**
 * @file app_ocr.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_ocr.h"
#include "../ui.h"

// Scan App
lv_obj_t * uiOCR_panel;
lv_obj_t * uiOCR_ResultText;

static ui_translate_action_cb_t ui_translate_action_cb = NULL;
void ui_register_translate_action_cb(ui_translate_action_cb_t update_handler)
{
    ui_translate_action_cb = update_handler;
}

void ui_event_BtnTranslateAction(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // printk("[%d:%s] event: %d\n", __LINE__, __func__, event_code);
    lv_obj_t * obj = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        if (ui_translate_action_cb) {
            ui_translate_action_cb(0);
        }
    }
}


int app_ocr_create(lv_obj_t * parent)
{
    lv_obj_t * uiOCR_translateBtn;
    uiOCR_panel = lv_obj_create(parent);
    lv_obj_clear_flag(uiOCR_panel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiOCR_panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiOCR_panel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(uiOCR_panel, LV_PCT(100), LV_PCT(100));

    uiOCR_ResultText = lv_textarea_create(uiOCR_panel);
    lv_obj_set_size(uiOCR_ResultText, SCREEN_WIDTH-140,  LV_PCT(90));
    lv_obj_set_pos(uiOCR_ResultText, 20, 40);
    lv_obj_set_align(uiOCR_ResultText, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiOCR_ResultText, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_placeholder_text(uiOCR_ResultText, "请扫描文本");
    lv_textarea_set_text(uiOCR_ResultText, UI_TEST_STR);

    lv_textarea_set_cursor_click_pos(uiOCR_ResultText, true);
    lv_obj_set_style_text_color(uiOCR_ResultText, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiOCR_ResultText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiOCR_ResultText, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiOCR_ResultText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiOCR_ResultText, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiOCR_ResultText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiOCR_translateBtn = lv_btn_create(uiOCR_panel);
    lv_obj_set_size(uiOCR_translateBtn, 100, SCREEN_WIDTH>320?100:60);
    lv_obj_set_pos(uiOCR_translateBtn, -10, 40);
    lv_obj_set_align(uiOCR_translateBtn, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(uiOCR_translateBtn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiOCR_translateBtn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnTranslate = lv_label_create(uiOCR_translateBtn);
    lv_label_set_text(ui_BtnTranslate, "翻译");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnTranslate);

    lv_obj_add_event_cb(uiOCR_translateBtn, ui_event_BtnTranslateAction, LV_EVENT_CLICKED, NULL);

    return 0;
}

lv_obj_t * app_ocr_get_page(void)
{
    return uiOCR_panel;
}


int ui_set_ocr_result_text(const char *result)
{
    if (uiOCR_ResultText == NULL || uiOCR_panel == NULL)
    {
        return -1;
    }
    if (ui_app_get_current_appid() == UI_APP_ID_NONE) {
        return -1;
    }
    if (ui_app_get_current_appid() != UI_APP_ID_OCR) {
        ui_app_set_current_appid(UI_APP_ID_OCR);
        // lv_obj_set_parent(ui_StatusBar, uiOCR_panel);
        // lv_obj_clear_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN); //显示 BackHome 按钮
        // lv_obj_add_flag(uiStatusBar_LabDate, LV_OBJ_FLAG_HIDDEN);   // 隐藏日期
        // _ui_screen_change(uiOCR_panel, LV_SCR_LOAD_ANIM_OVER_LEFT, 0, 0);
        // lv_obj_set_style_text_font(uiOCR_ResultText, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // lv_textarea_set_text(uiOCR_ResultText, result);
    return 0;
}


int app_ocr_scan_destroy(void)
{
    printk("[%d:%s] destroy\n", __LINE__, __func__);
    return 0;
}

int app_ocr_scan_enter(void)
{
    printk("[%d:%s] enter\n", __LINE__, __func__);
    return 0;
}

int app_ocr_scan_exit(void)
{
    printk("[%d:%s] exit\n", __LINE__, __func__);
    return 0;
}

struct app_icon_t icon_ocr_scan = {
    .name = "扫描",
    .icon_width = LV_SIZE_CONTENT,
    .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img__launcher_scan_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_ocr_scan = {
    .create = app_ocr_create,
    .destroy = app_ocr_scan_destroy,
    .enter = app_ocr_scan_enter,
    .exit = app_ocr_scan_exit,

    .get_obj_handle = app_ocr_get_page,

    .info = {
        .name = "OCR",
        .package_name = "com.listenai.lisaui.ocr",
        .id = UI_APP_ID_OCR,
    },
    .icon = &icon_ocr_scan,
};

int app_ocr_scan_init(void)
{
    return lisaui_app_register(&app_ocr_scan);
}

REGISTER_LISAUI_APP(lisaui_ocr, app_ocr_scan_init);

void printk_app_ocr_info(void)
{
//     printk("app_demo_info\n");
//     printk("app_demo address: %p\n", &app_ocr);
}
