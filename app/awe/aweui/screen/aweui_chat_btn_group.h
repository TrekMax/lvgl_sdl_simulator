/*
 * Copyright (c) 2023, LISTENAI
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
#include "ui.h"
#include "aweui_screen.h"
/**
 * @brief 创建录音以及拍照的UI
 * 
 * @param init_pg ：基于init_pg页面创建
 * @param home_flg ：是否是主页
 */
void aweui_add_chat_camera_ui(lv_obj_t *init_pg, chat_btn_group_type_t show_e);

/**
 * @brief 
 * 
 * @param camera_show 
 * @param voice_show 
 * @param camera_l_show 
 */
void aweui_set_show_chat_camera(bool camera_show, bool voice_show, bool camera_l_show);
/**
 * @brief 清除拍照按键的回调函数
 * 
 */
void clear_camera_cb(void);

/**
 * @brief 添加拍照按键的回调函数
 * 
 */
void add_camera_cb(void);

/**
 * @brief 清除录音按键的回调函数
 * 
 */
void clear_voice_cb(void);

/**
 * @brief 添加录音按键的回调函数
 * 
 */
void add_voice_cb(void);
#ifdef __cplusplus
}
#endif
