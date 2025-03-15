/**
 * @file ui.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ui.h"
#include "app_user/app_common.h"
#include "app_common/lisaui_app_common.h"
#include "app_framework/lisaui_app_manager.h"
static const char *TAG = "UI";

void lisaui_ui_init(void)
{
    // lv_disp_t *dispp = lv_disp_get_default();

    // lv_theme_t *theme = LV_THEME_DEFAULT_INIT(
    //     lv_theme_get_color_primary(), lv_theme_get_color_secondary(), LV_THEME_MATERIAL_FLAG_DARK,
    //     lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
    // lv_theme_set_act(theme);

    LISAUI_USE_APP(demo);
    // LISAUI_USE_APP(ocr);
    // LISAUI_USE_APP(audio_player);
    LISAUI_USE_APP(dictionary);
    // LISAUI_USE_APP(setting);
    // LISAUI_USE_APP(voice);

    LISAUI_USE_APP(taskbar);
    LISAUI_USE_APP(launcher);

    lisaui_app_manager_init();
    // lisaui_app_enter(UI_APP_ID_DICTIONARY);
    lisaui_app_show_all_info();

    LISAUI_LOGI(TAG, "UI init done");
    LISAUI_LOGI(TAG, "[%d:%s] init done", __LINE__, __func__);
    LISAUI_LOGI(TAG, "[%s:%d] init done", __FILE__, __LINE__);
}