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

// static lv_img_dsc_t img_gif4;
// INCBIN(img_gif4, "app/pendict/ui/assets/img/00b44af.gif");

// Scan App
lv_obj_t * uiApp_ScanOCR;
lv_obj_t * uiApp_ScanOCR_Body;
lv_obj_t * uiAppScanOCR_TextResult;
lv_obj_t * uiApp_ScanOCR_ImgOCRTips;
lv_obj_t * uiApp_ScanOCR_LabelOCRTips;
lv_obj_t * uiApp_ScanOCR_BtnStart;
lv_obj_t * uiApp_ScanOCR_BtnStop;


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
    uiApp_ScanOCR = lv_obj_create(NULL);
    lv_obj_clear_flag(uiApp_ScanOCR, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiApp_ScanOCR, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_ScanOCR, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiApp_ScanOCR_Body = lv_obj_create(uiApp_ScanOCR);
    lv_obj_set_size(uiApp_ScanOCR_Body, SCREEN_WIDTH, 140);
    lv_obj_set_pos(uiApp_ScanOCR_Body, 2, 1);
    lv_obj_set_align(uiApp_ScanOCR_Body, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(uiApp_ScanOCR_Body, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(uiApp_ScanOCR_Body, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
                      LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(uiApp_ScanOCR_Body, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiApp_ScanOCR_Body, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiApp_ScanOCR_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_ScanOCR_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiApp_ScanOCR_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

#if 1
    uiAppScanOCR_TextResult = lv_textarea_create(uiApp_ScanOCR);
    lv_obj_set_size(uiAppScanOCR_TextResult, SCREEN_WIDTH-140, 120);
    lv_obj_set_pos(uiAppScanOCR_TextResult, 20, 40);
    lv_obj_set_align(uiAppScanOCR_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiAppScanOCR_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_textarea_set_placeholder_text(uiAppScanOCR_TextResult, UI_TEST_STR);
    lv_textarea_set_text(uiAppScanOCR_TextResult, UI_TEST_STR);
    lv_textarea_set_cursor_click_pos(uiAppScanOCR_TextResult, true);
    lv_obj_set_style_text_color(uiAppScanOCR_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiAppScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiAppScanOCR_TextResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiAppScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiAppScanOCR_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiAppScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    uiAppScanOCR_TextResult = lv_label_create(uiApp_ScanOCR);
    lv_obj_set_size(uiAppScanOCR_TextResult, SCREEN_WIDTH-140, 100);
    lv_obj_set_pos(uiAppScanOCR_TextResult, 20, 40);
    lv_obj_set_align(uiAppScanOCR_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiAppScanOCR_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_textarea_set_placeholder_text(uiAppScanOCR_TextResult, UI_TEST_STR);
    // lv_textarea_set_text(uiAppScanOCR_TextResult, UI_TEST_STR);
    lv_label_set_text(uiAppScanOCR_TextResult, UI_TEST_STR);
    // lv_textarea_set_cursor_click_pos(uiAppScanOCR_TextResult, true);
    lv_obj_set_style_text_color(uiAppScanOCR_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiAppScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiAppScanOCR_TextResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiAppScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiAppScanOCR_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiAppScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
    uiApp_ScanOCR_BtnStart = lv_btn_create(uiApp_ScanOCR_Body);
    lv_obj_set_size(uiApp_ScanOCR_BtnStart, 100, SCREEN_WIDTH>320?100:60);
    lv_obj_set_pos(uiApp_ScanOCR_BtnStart, 0, 0);
    lv_obj_set_align(uiApp_ScanOCR_BtnStart, SCREEN_WIDTH>320?LV_ALIGN_RIGHT_MID:LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(uiApp_ScanOCR_BtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiApp_ScanOCR_BtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnTranslate = lv_label_create(uiApp_ScanOCR_BtnStart);
    lv_label_set_text(ui_BtnTranslate, "翻译");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnTranslate);

    lv_obj_add_event_cb(uiApp_ScanOCR_BtnStart, ui_event_BtnTranslateAction, LV_EVENT_CLICKED, NULL);

    return 0;
}

lv_obj_t * app_ocr_get_page(void)
{
    return uiApp_ScanOCR;
}


int ui_set_ocr_result_text(const char *result)
{
    if (uiAppScanOCR_TextResult == NULL || uiApp_ScanOCR == NULL)
    {
        return -1;
    }
    if (ui_app_get_current_appid() == UI_APP_ID_NONE) {
        return -1;
    }
    if (ui_app_get_current_appid() != UI_APP_ID_OCR) {
        ui_app_set_current_appid(UI_APP_ID_OCR);
        // lv_obj_set_parent(ui_StatusBar, uiApp_ScanOCR);
        // lv_obj_clear_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN); //显示 BackHome 按钮
        // lv_obj_add_flag(uiStatusBar_LabDate, LV_OBJ_FLAG_HIDDEN);   // 隐藏日期
        // _ui_screen_change(uiApp_ScanOCR, LV_SCR_LOAD_ANIM_OVER_LEFT, 0, 0);
        // lv_obj_set_style_text_font(uiAppScanOCR_TextResult, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // lv_textarea_set_text(uiAppScanOCR_TextResult, result);
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
    .app_id = UI_APP_ID_OCR,
    .icon = &icon_ocr_scan,
};

int app_ocr_scan_init(void)
{
    app_ocr_scan.app_id = 0;
    
    return lisaui_app_register(&app_ocr_scan);
}
