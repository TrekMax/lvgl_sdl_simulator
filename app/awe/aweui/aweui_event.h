/**
 * @file aweui_event.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-18
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __AWEUI_EVENT_H__
#define __AWEUI_EVENT_H__

#include "aweui_types.h"
#ifdef __ZEPHYR__
#include "gcl_cb_list.h"


/**
 * @brief UI 事件处理函数
 * 
 * @param event 事件
 * @param param 参数
 * @return int 
 */
typedef int (*aweui_event_handler_t)(aweui_event_t event, void *param);

/**
 * @brief UI 事件初始化，必须在 aweui_event_register 之前调用
 * 
 */
int aweui_event_init(void);

/**
 * @brief 注册 UI 事件处理函数
 * 
 * @note 一个事件可以注册多个处理函数, 处理函数按注册顺序依次调用，处理函数请保证为非阻塞
 * 
 * @param event 
 * @param handler 
 * @return int 
 */
int aweui_register_event_handler(aweui_event_t event, gcl_event_cb_t handler);

/**
 * @brief 注销 UI 事件处理函数
 * 
 * @param event 
 * @param handler 
 * @return int 
 */
int aweui_unregister_event_handler(aweui_event_t event, gcl_event_cb_t handler);

#endif
/**
 * @brief 设置相机预览
 * 
 * @param img 
 * @return int 
 */
int aweui_set_camera_preview(const aweui_img_t img);

/**
 * @brief 设置用户 ASR 结果
 * 
 * @param text 
 * @param text_mode 
 * @return int 
 */
int aweui_set_user_asr_result_text(const awe_llm_status_t llm_ret_status, const char *text, aweui_text_mode_t text_mode);


/**
 * @brief 设置用户 LLM 响应结果
 * 
 * @param text 
 * @param text_mode 
 * @return int 
 */
// int aweui_set_user_llm_response_result_status(const char *text, aweui_text_mode_t text_mode);

int aweui_set_user_llm_response_result_text(const awe_llm_status_t llm_ret_status, const char *text, aweui_text_mode_t text_mode);

int aweui_set_user_llm_response_result_picture(const awe_llm_status_t llm_ret_status, const aweui_img_t img);

int aweui_set_user_llm_response_canvas_color(const awe_llm_status_t llm_ret_status, uint32_t color);

int aweui_set_audio_player_status(aweui_audio_player_status_t status);

int aweui_set_action(aweui_action_t action, void *param);

void aweui_set_llm_mode(aweui_llm_mode_e mode);

aweui_llm_mode_e aweui_get_llm_mode(void);

int aweui_event_cb_list_init(void);

#endif // __AWEUI_EVENT_H__

