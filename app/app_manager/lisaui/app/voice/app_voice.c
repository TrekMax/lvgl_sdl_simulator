/**
 * @file app_voice.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_voice.h"
#include "app_common/lisaui_app_common.h"
#include "assets/assets_res.h"

static const char *TAG = "app_voice";
static lv_obj_t *g_app_voice = NULL;

// 声明[模板]应用需要实现的接口
LISAUI_DECLARE_APP_FUNC(voice, create, destroy, enter, exit, get_page);
// 定义[模板]应用
LISAUI_DEFINE_APP(voice, UI_APP_ID_VOICE, "语音", "Voice", &ui_img_icon_voice_png, {});

// App 模板宏原型在 common/lisaui_app_manager.h 中定义
// 定义[模板]应用功能实现, 用于创建、销毁、进入、退出、获取页面
#define LISAUI_APP_ENTITY_VOICE                                                                                     \
    {                                                                                                                  \
        if (g_app_voice != NULL) {                                                                                  \
            return LISAUI_ERR_OK;                                                                                      \
        }                                                                                                              \
        g_app_voice = lv_obj_create(parent);                                                                        \
        _lisaui_set_style_container(g_app_voice, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);        \
                                                                                                                       \
        lv_obj_t *label = lv_label_create(g_app_voice);                                                             \
        lv_label_set_text(label, "Hello LisaUI!");                                                                     \
        lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);                       \
        lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);                   \
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);                                                                    \
                                                                                                                       \
        return LISAUI_ERR_OK;                                                                                          \
    }
lisaui_err_t LISAUI_DEFINE_APP_FUNC(voice, create, void *parent, {LISAUI_APP_ENTITY_VOICE});
lisaui_err_t LISAUI_DEFINE_APP_FUNC(voice, destroy, void, {
    LVGL_OBJ_SAFE_DEL(g_app_voice);
    return LISAUI_ERR_OK;
});
lisaui_err_t LISAUI_DEFINE_APP_FUNC(voice, enter, void, { return LISAUI_ERR_OK; });
lisaui_err_t LISAUI_DEFINE_APP_FUNC(voice, exit, void, { return LISAUI_ERR_OK; });
void *LISAUI_DEFINE_APP_FUNC(voice, get_page, void, { return g_app_voice; });