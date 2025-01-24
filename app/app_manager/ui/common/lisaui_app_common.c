/**
 * @file app_common.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-26
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lisaui_app_common.h"

static const char *TAG = "app_common";

lisaui_err_t _lisaui_set_style_container(lv_obj_t *obj, lv_color_t bg_color, lv_opa_t bg_opa, lv_color_t border_color,
                                         lv_coord_t border_width, lv_coord_t radius)
{
    if (obj == NULL) {
        return LISAUI_ERR_INVALID_PARAM;
    }
#if 0
    lv_obj_set_style_local_bg_color(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, bg_color);
    lv_obj_set_style_local_bg_opa(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, bg_opa);
    lv_obj_set_style_local_radius(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, radius);
    lv_obj_set_style_local_border_color(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, border_color);
    lv_obj_set_style_local_border_width(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, border_width);
    lv_obj_set_style_local_pad_all(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
#endif
    return LISAUI_ERR_OK;
}

static lv_style_t default_style;
static bool default_style_inited = false;

lisaui_err_t _lisaui_set_default_style(lv_style_t *style)
{
#if 0
    if (style != NULL) {
        lv_style_copy(&default_style, style);
    } else {
        lv_style_init(&default_style);
        lv_style_set_text_font(&default_style, LV_STATE_DEFAULT, &lv_font_chinese_18);
    }
#endif
    return LISAUI_ERR_OK;
}

lisaui_err_t _lisaui_lv_obj_set_default_style(lv_obj_t *obj)
{
    if (obj == NULL) {
        return LISAUI_ERR_INVALID_PARAM;
    }
#if 0
    // if (lv_debug_check_style(&default_style) != LV_RES_OK)
    // {
    //     _lisaui_set_default_style(NULL);
    // }
    if (!default_style_inited) {
        _lisaui_set_default_style(NULL);
        default_style_inited = true;
    }
    // lv_obj_set_style_local_text_font(obj, LV_OBJ_PART_MAIN, &default_style);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &default_style);
#endif
    return LISAUI_ERR_OK;
}

lisaui_err_t _lisaui_lv_obj_set_btn_custom_style(lv_obj_t *obj)
{
    if (obj == NULL) {
        return LISAUI_ERR_INVALID_PARAM;
    }
#if 0
    static lv_style_t style_btn;

    /*Create a simple button style*/
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, LV_STATE_DEFAULT, 6);

    /*Add a border*/
    // lv_style_set_border_opa(&style_btn, LV_STATE_DEFAULT, LV_OPA_70);
    lv_style_set_border_width(&style_btn, LV_STATE_DEFAULT, 0);

    /*Different border color in focused state*/
    // lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED, LV_COLOR_BLUE);
    lv_style_set_bg_color(&style_btn, LV_STATE_DEFAULT, lv_color_hex(0x1886EE));
    lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED, lv_color_hex(0x39BAFF));
    lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);

    lv_obj_add_style(obj, LV_BTN_PART_MAIN, &style_btn);
#endif
    return LISAUI_ERR_OK;
}
#if 0
#define TOAST_DURATION 800
static lv_coord_t obj_width = 200;
static lv_coord_t obj_height = 50;
#define TIME_STEP      50
lv_anim_t a1;
lv_anim_t a2;
static lv_obj_t *toast = NULL;
static lv_obj_t *toast_label = NULL;

static void obj_test_task_cb(lv_task_t *)
{
    LISAUI_LOGI(TAG, "obj_test_task_cb");
    lv_obj_set_hidden(toast, true);
}
#endif
lisaui_err_t lisaui_app_create_toast(const char *message)
{
    lv_obj_t *screen = lv_layer_sys();
#if 0
    if (toast == NULL) {
        toast = lv_obj_create(screen, NULL);
    }
    lv_obj_set_size(toast, 200, 50);
    // lv_obj_align(toast, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_align(toast, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -20);

    lv_obj_set_style_local_bg_opa(toast, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_90);
    lv_obj_set_style_local_bg_color(toast, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0xFFF4DE));
    lv_obj_set_style_local_outline_width(toast, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 1);
    lv_obj_set_style_local_border_width(toast, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
    // lv_obj_set_style_local_radius(toast, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 10);

    if (toast_label == NULL) {
        toast_label = lv_label_create(toast, NULL);
        lv_anim_init(&a1);
        lv_anim_set_var(&a1, toast);
        lv_anim_set_values(&a1, 100, obj_width);
        // lv_anim_set_early_apply(&a1, false);
        lv_anim_set_exec_cb(&a1, (lv_anim_exec_xcb_t)lv_obj_set_width);
        lv_anim_init(&a2);
        lv_anim_set_var(&a2, toast);
        lv_anim_set_values(&a2, 0, obj_height);
        // lv_anim_set_early_apply(&a2, false);
        lv_anim_set_exec_cb(&a2, (lv_anim_exec_xcb_t)lv_obj_set_height);
        // lv_anim_set_path_cb(&a2, lv_anim_path_ease_out);
        lv_anim_set_time(&a2, 300);
    }
    lv_label_set_text(toast_label, message);
    lv_obj_align(toast_label, toast, LV_ALIGN_CENTER, 0, 0);

    static lv_style_t style_toast_label;
    lv_style_set_text_font(&style_toast_label, LV_STATE_DEFAULT, &lv_font_chinese_18);
    lv_style_set_text_color(&style_toast_label, LV_STATE_DEFAULT, lv_color_hex(0x9d6531));
    lv_obj_add_style(toast_label, LV_OBJ_PART_MAIN, &style_toast_label);

    lv_anim_start(&a1);
    lv_anim_start(&a2);
    lv_task_t *pop_toast = lv_task_create(obj_test_task_cb, TOAST_DURATION, LV_TASK_PRIO_LOW, toast);
    lv_task_set_repeat_count(pop_toast, 1);
    lv_obj_set_hidden(toast, false);
#endif
    return LISAUI_ERR_OK;
}
