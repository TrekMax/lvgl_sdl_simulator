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
lv_obj_t * uiPage_ScanOCR;
lv_obj_t * uiPage_ScanOCR_Body;
lv_obj_t * uiPageScanOCR_TextResult;
lv_obj_t * uiPage_ScanOCR_ImgOCRTips;
lv_obj_t * uiPage_ScanOCR_LabelOCRTips;
lv_obj_t * uiPage_ScanOCR_BtnStart;
lv_obj_t * uiPage_ScanOCR_BtnStop;


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


void app_ocr_create(lv_obj_t * parent)
{
    uiPage_ScanOCR = lv_obj_create(NULL);
    lv_obj_clear_flag(uiPage_ScanOCR, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiPage_ScanOCR, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPage_ScanOCR, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiPage_ScanOCR_Body = lv_obj_create(uiPage_ScanOCR);
    lv_obj_set_size(uiPage_ScanOCR_Body, SCREEN_WIDTH, 140);
    lv_obj_set_pos(uiPage_ScanOCR_Body, 2, 1);
    lv_obj_set_align(uiPage_ScanOCR_Body, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(uiPage_ScanOCR_Body, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(uiPage_ScanOCR_Body, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
                      LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(uiPage_ScanOCR_Body, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiPage_ScanOCR_Body, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiPage_ScanOCR_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPage_ScanOCR_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiPage_ScanOCR_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

#if 1
    uiPageScanOCR_TextResult = lv_textarea_create(uiPage_ScanOCR);
    lv_obj_set_size(uiPageScanOCR_TextResult, SCREEN_WIDTH-140, 120);
    lv_obj_set_pos(uiPageScanOCR_TextResult, 20, 40);
    lv_obj_set_align(uiPageScanOCR_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiPageScanOCR_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_textarea_set_placeholder_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    lv_textarea_set_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    lv_textarea_set_cursor_click_pos(uiPageScanOCR_TextResult, true);
    lv_obj_set_style_text_color(uiPageScanOCR_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiPageScanOCR_TextResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiPageScanOCR_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    uiPageScanOCR_TextResult = lv_label_create(uiPage_ScanOCR);
    lv_obj_set_size(uiPageScanOCR_TextResult, SCREEN_WIDTH-140, 100);
    lv_obj_set_pos(uiPageScanOCR_TextResult, 20, 40);
    lv_obj_set_align(uiPageScanOCR_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiPageScanOCR_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_textarea_set_placeholder_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    // lv_textarea_set_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    lv_label_set_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    // lv_textarea_set_cursor_click_pos(uiPageScanOCR_TextResult, true);
    lv_obj_set_style_text_color(uiPageScanOCR_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiPageScanOCR_TextResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiPageScanOCR_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
    uiPage_ScanOCR_BtnStart = lv_btn_create(uiPage_ScanOCR_Body);
    lv_obj_set_size(uiPage_ScanOCR_BtnStart, 100, SCREEN_WIDTH>320?100:60);
    lv_obj_set_pos(uiPage_ScanOCR_BtnStart, 0, 0);
    lv_obj_set_align(uiPage_ScanOCR_BtnStart, SCREEN_WIDTH>320?LV_ALIGN_RIGHT_MID:LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(uiPage_ScanOCR_BtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiPage_ScanOCR_BtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnTranslate = lv_label_create(uiPage_ScanOCR_BtnStart);
    lv_label_set_text(ui_BtnTranslate, "翻译");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnTranslate);

    lv_obj_add_event_cb(uiPage_ScanOCR_BtnStart, ui_event_BtnTranslateAction, LV_EVENT_CLICKED, NULL);
}

lv_obj_t * app_ocr_get_page(void)
{
    return uiPage_ScanOCR;
}


int ui_set_ocr_result_text(const char *result)
{
    if (uiPageScanOCR_TextResult == NULL || uiPage_ScanOCR == NULL)
    {
        return -1;
    }
    if (ui_app_get_current_appid() == UI_PAGE_ID_NONE) {
        return -1;
    }
    if (ui_app_get_current_appid() != UI_PAGE_ID_OCR) {
        ui_app_set_current_appid(UI_PAGE_ID_OCR);
        // lv_obj_set_parent(ui_StatusBar, uiPage_ScanOCR);
        // lv_obj_clear_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN); //显示 BackHome 按钮
        // lv_obj_add_flag(uiStatusBar_LabDate, LV_OBJ_FLAG_HIDDEN);   // 隐藏日期
        // _ui_screen_change(uiPage_ScanOCR, LV_SCR_LOAD_ANIM_OVER_LEFT, 0, 0);
        // lv_obj_set_style_text_font(uiPageScanOCR_TextResult, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // lv_textarea_set_text(uiPageScanOCR_TextResult, result);
    return 0;
}
