/**
 * @file ui.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-19
 *
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ui.h"
#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
// #include "lv_theme_ultra_marine.h"
#include "aweui_event.h"
#include "screen/aweui_screen.h"
#include "screen/aweui_status_bar.h"

lv_disp_t *dispp;
lv_obj_t *base = NULL;

lv_obj_t *aweui_get_ui_base(void)
{
	if (base == NULL) {
		base = lv_scr_act();
		lv_obj_remove_style_all(base);
		lv_obj_set_style_pad_all(base, 0, 0);
		lv_obj_clear_flag(base, LV_OBJ_FLAG_SCROLLABLE);
		// lv_obj_set_size(base, LV_PCT(100), LV_PCT(100));
		lv_obj_set_size(base, LV_HOR_RES, LV_VER_RES);
	}
	return base;
}

void ui_init()
{
	LV_LOG_USER("UI_Init");
#ifdef __ZEPHYR__
	aweui_event_init();
#endif

	dispp = lv_disp_get_default();
	lv_theme_t *theme =
		lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE),
				      lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);

	lv_disp_set_theme(dispp, theme);
	lv_obj_t *scr = lv_scr_act();
	lv_obj_remove_style_all(scr);
	// lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
	lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

	// aweui_status_bar_create(lv_layer_top());
	// aweui_screen_bar_setting_create(lv_layer_top());
	aweui_screen_standby_create(scr);

	extern int aweui_screen_standby_init(void);
	aweui_screen_standby_init();

	extern int aweui_screen_camera_init(void);
	aweui_screen_camera_init();

	extern int aweui_screen_chat_init(void);
	aweui_screen_chat_init();

    // aweui_set_user_asr_result_text(AWEUI_LLM_STATUS_SUCCESS, "Hello, world!", AWEUI_TEXT_MODE_OVERWRITE);
    // aweui_set_user_asr_result_text(AWEUI_LLM_STATUS_SUCCESS, "111Hello, world!11111", AWEUI_TEXT_MODE_APPEND);
    // aweui_set_user_asr_result_text(AWEUI_LLM_STATUS_SUCCESS, "222Hello, world!222", AWEUI_TEXT_MODE_APPEND);
    // aweui_set_user_llm_response_result_text(AWEUI_LLM_STATUS_SUCCESS, "星火大模型", AWEUI_TEXT_MODE_OVERWRITE);
    // aweui_set_user_llm_response_result_text(AWEUI_LLM_STATUS_SUCCESS, "，聆思科技", AWEUI_TEXT_MODE_APPEND);
}
