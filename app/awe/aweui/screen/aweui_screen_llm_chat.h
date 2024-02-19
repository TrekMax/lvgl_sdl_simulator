/*
 * Copyright (c) 2023, LISTENAI
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "aweui_types.h"

/**
 * @brief Create a chat page
 * 
 * @param parent 
 * @return lv_obj_t* 
 */
lv_obj_t *ui_chat_create(lv_obj_t *parent);

/**
 * @brief Create a chat result page
 * 
 * @param parent 
 * @return lv_obj_t* 
 */
lv_obj_t *aweui_chat_result_create(lv_obj_t *parent, aweui_llm_mode_e mode);

/**
 * @brief 开始录音
 * 
 * @param parent 
 * @return lv_obj_t* 
 */
void start_voice_recognition(void);

int aweui_screen_chat_result_text(const awe_llm_status_t llm_ret_status, const char *text, aweui_text_mode_t text_mode);
int aweui_screen_chat_result_picture(const awe_llm_status_t llm_ret_status, const aweui_img_t img);

#ifdef __cplusplus
}
#endif
