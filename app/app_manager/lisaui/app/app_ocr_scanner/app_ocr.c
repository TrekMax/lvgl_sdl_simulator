/**
 * @file app_ocr.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_ocr.h"
#include "lisaui_app_common.h"
#include "../app_common.h"
#include "assets/assets_res.h"


static const char *TAG = "app_ocr";
lv_obj_t *g_app_ocr = NULL;
#if 0
static void event_handler(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED) {
        LISAUI_LOGI(TAG, "Clicked");
        // lisaui_memory_monitor(NULL);
        lisaui_app_close(UI_APP_ID_DICTIONARY);

    } else if (event == LV_EVENT_VALUE_CHANGED) {
        LISAUI_LOGI(TAG, "Open App Dictionary");
        lisaui_app_enter(UI_APP_ID_DICTIONARY);
    }
}
static void app_ocr_bg_task_handle_cb(lv_task_t *task)
{
    LISAUI_LOGI(TAG, "bg task tick");
}
#endif
lisaui_err_t app_ocr_create(void *parent)
{
    if (g_app_ocr != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_ocr = lv_obj_create(parent);
    _lisaui_set_style_container(g_app_ocr, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
#if 0
    lv_obj_t *label = lv_label_create(g_app_ocr, NULL);
    lv_label_set_text(label, "Hello ocr!");
    // lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    lv_obj_t *btn1 = lv_btn_create(g_app_ocr, NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, -160, 0);
    _lisaui_lv_obj_set_btn_custom_style(btn1);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Close App OCR");

    // lv_obj_t * btn2 = lv_btn_create(g_app_ocr, NULL);
    // lv_obj_set_event_cb(btn2, event_handler);
    // lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 200, 0);
    // lv_btn_set_checkable(btn2, true);
    // lv_btn_toggle(btn2);
    // lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);
    // _lisaui_lv_obj_set_btn_custom_style(btn2);

    // label = lv_label_create(btn2, NULL);
    // lv_label_set_text(label, "Open App Dictionary");

    lv_task_create(app_ocr_bg_task_handle_cb, 500, LV_TASK_PRIO_LOW, NULL);
    #endif
    LISAUI_LOGI(TAG, "[%d:%s] create", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_ocr_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_ocr_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_ocr_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_ocr_get_page(void)
{
    return g_app_ocr;
}

static struct app_icon_t app_icon_res = {
    #if CONFIG_LISAUI_FONT_LANGUAGE_ZH_CN_ENABLE
    .title = "扫描",
#else
    .title = "Scanner",
#endif
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img_icon_scanner_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_ocr = {
    .create = app_ocr_create,
    .destroy = app_ocr_destroy,
    .enter = app_ocr_enter,
    .exit = app_ocr_exit,

    .get_root_view = app_ocr_get_page,
    .info =
        {
            .name = "OCR",
            .package_name = "com.listenai.lisaui.ocr",
            .id = UI_APP_ID_OCR,
        },
    .icon = &app_icon_res,
};

lisaui_err_t app_ocr_init(void)
{
    lisaui_app_register(&app_ocr);
    return LISAUI_ERR_OK;
}

LISAUI_REGISTER_APP(ocr, &app_ocr, app_ocr_init);
