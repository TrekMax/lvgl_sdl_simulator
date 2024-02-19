/**
 * @file llm_dialog.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LLM_DIALOG_H__
#define __LLM_DIALOG_H__

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

typedef enum {
    LLM_DIALOG_TYPE_INFO,
    LLM_DIALOG_TYPE_WARN,
    LLM_DIALOG_TYPE_ERROR,
    LLM_DIALOG_TYPE_SUCCESS,
    LLM_DIALOG_TYPE_CONFIRM,
    LLM_DIALOG_TYPE_INPUT,
} llm_dialog_type_t;

typedef enum {
    LLM_DIALOG_EMOJI_STATE_STANDBY = 0,
    LLM_DIALOG_EMOJI_STATE_THINKING,
    LLM_DIALOG_EMOJI_STATE_LISTENING,
} llm_dialog_emoji_state_t;

int ls_lv_llm_dialog_popup(const char *text);
int ls_lv_llm_dialog_set_emoji_state(const llm_dialog_emoji_state_t state);
int ls_lv_llm_dialog_popup_with_mode(const awe_llm_status_t llm_ret_status, const char *text, aweui_text_mode_t text_mode);
void ls_llm_dialog_example(void);

#ifdef __cplusplus
}
#endif

#endif // __LLM_DIALOG_H__