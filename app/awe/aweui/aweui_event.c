/**
 * @file aweui_event.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2024-02-18
 *
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(aweui_event, LOG_LEVEL_INF);
#else
#include "lvgl/lvgl.h"
#define LOG_INF LV_LOG_USER
#define LOG_WRN LV_LOG_WARN
#endif

#include "aweui_event.h"
#include "aweui_types.h"
#include "widgets/llm_dialog.h"

#include "screen/aweui_screen_network.h"
#include "screen/aweui_screen_llm_chat.h"
#include "screen/aweui_screen_camera.h"
static aweui_llm_mode_e aweui_llm_mode = AWEUI_LLM_MODE_ONESHOT;
#ifdef __ZEPHYR__
static uint8_t aweui_camera_image_buffer[240 * 320 * 2]
	__attribute__((section(".psram_section"))) = {0};
K_MUTEX_DEFINE(aweui_img_buffer_lock);
static gcl_cb_list_t aweui_cb_list = NULL;


int aweui_event_cb_list_init(void)
{
    aweui_cb_list = gcl_cb_list_create();
    if (aweui_cb_list == NULL) {
        LV_LOG_USER("aweui_event_cb_list_init failed, aweui_cb_list is NULL");
        return -1;
    }
    return AWEUI_ERR_OK;
}

int aweui_event_init(void)
{
    return aweui_event_cb_list_init();
}

/**
 * @brief 注册 UI 事件处理函数
 *
 * @param event
 * @param handler
 * @return int
 */
int aweui_register_event_handler(aweui_event_t event, gcl_event_cb_t handler)
{
    if (aweui_cb_list == NULL || handler == NULL) {
        return AWEUI_ERR_INVALID_PARAM;
    }
    
    int ret = AWEUI_ERR_OK;
    ret = gcl_cb_list_add_callback(aweui_cb_list, event, (gcl_event_cb_t)handler, NULL);

    return ret;
}

/**
 * @brief 注销 UI 事件处理函数
 *
 * @param event
 * @param handler
 * @return int
 */
int aweui_unregister_event_handler(aweui_event_t event, gcl_event_cb_t handler)
{
    if (aweui_cb_list == NULL || handler == NULL) {
        return AWEUI_ERR_INVALID_PARAM;
    }

    int ret = AWEUI_ERR_OK;
    ret = gcl_cb_list_remove_callback(aweui_cb_list, (gcl_event_cb_t)handler);

    return ret;
}
#endif
int aweui_event_handler(aweui_event_t event, void *param)
{
    LOG_INF("-->AWEUI event: 0x%X", event);
    // for (int i = 0; i < aweui_lv_event_dsc.event_dsc_cnt; i++) {
    //     // aweui_lv_event_dsc.event_dsc[i](event, param);
    //     if (event == aweui_lv_event_dsc.event_dsc[i].filter) {
    //         aweui_lv_event_dsc.event_dsc[i](event, param);
    //     }
    // }
    switch (event)
    {
    // case AWEUI_EVENT_CAMERA_PREVIEW_EXIT:
    //     // aweui_register_event_handler(AWEUI_EVENT_CAMERA_PREVIEW_ENTER, aweui_set_camera_preview1);
    //     // aweui_register_event_handler(AWEUI_EVENT_CAMERA_PREVIEW_EXIT, aweui_set_camera_preview2);

    //     break;

    // case AWEUI_EVENT_CAMERA_TAKE_PHOTO:
    //     break;

    // case AWEUI_EVENT_CAMERA_QUICK_RECOGNIZE:
    //     // 快速识别
    //     break;

    // case AWEUI_EVENT_CAMERA_DIRECTION_SWITCH:
    //     break;

    // case AWEUI_EVENT_VOICE_KEY_PRESS:
    //     // 开始录音
    //     break;

    // case AWEUI_EVENT_VOICE_KEY_RELEASE:
    //     break;

    // case AWEUI_EVENT_WAKEUP_OPTION_CHANGE:
    //     if (!param)
    //     {
    //         return AWEUI_ERR_INVALID_PARAM;
    //     }
    //     aweui_wakeup_option_t *option = (aweui_wakeup_option_t *)param;
    //     // 更新唤醒选项
    //     break;

    // case AWEUI_EVENT_WIFI_QRCODE_CONNECT_SCAN:
    //     // 开始二维码识别
    //     LV_LOG_USER("开始二维码识别");
    //     break;

    case AWEUI_EVENT_SCREEN_CHANGE_TO_CAMERA:
        LOG_INF("AWEUI_EVENT_SCREEN_CHANGE_TO_CAMERA");
        aweui_camera_create(lv_scr_act());
        break;

    default:
        break;
    }
#ifdef __ZEPHYR__
    return gcl_cb_event_dispatch(aweui_cb_list, event, param, 0);
#else
    return AWEUI_ERR_OK;
#endif
}

int aweui_set_pull_event(aweui_event_t event, void *param)
{
    return aweui_event_handler(event, param);
}

int aweui_set_action(aweui_action_t action, void *param)
{
    switch (action)
    {
    case AWEUI_ACTION_WAKEUP: // 唤醒
        break;
    case AWEUI_ACTION_IDLE: // 空闲
        break;
    case AWEUI_ACTION_SLEEP: // 休眠
        break;
    case

        AWEUI_ACTION_VOICE_BUTTON_PRESS: // 语音键按下
        break;
    case AWEUI_ACTION_VOICE_BUTTON_LONG_PRESS: // 语音键长按
        break;
    case AWEUI_ACTION_VOICE_BUTTON_RELEASE: // 语音键释放
        break;
    case

        AWEUI_ACTION_CAMERA_BUTTON_PRESS: // 拍照键按下
        break;
    case AWEUI_ACTION_CAMERA_BUTTON_LONG_PRESS: // 拍照键长按
        break;
    case AWEUI_ACTION_CAMERA_BUTTON_RELEASE: // 拍照键释放
        break;
    case

        AWEUI_ACTION_VOLUME_UP: // 音量+
        break;
    case AWEUI_ACTION_VOLUME_DOWN: // 音量-
        break;
    case AWEUI_ACTION_BACKLIGHT_UP: // 背光+
        break;
    case AWEUI_ACTION_BACKLIGHT_DOWN: // 背光-
        break;
    case

        AWEUI_ACTION_RECOGNIZE_START: // 录音开始
        break;
    case AWEUI_ACTION_RECOGNIZE_STOP: // 录音结束
        break;
    case AWEUI_ACTION_RECOGNIZE: // 识别中
        break;
    case

        AWEUI_ACTION_RECOGNIZE_FAIL: // 识别失败
        break;
    case AWEUI_ACTION_RECOGNIZE_SUCCESS: // 识别成功
        break;
    case

        AWEUI_ACTION_USER_QUESTION_ASR_RESULT: // 返回用户提问 ASR 结果
        break;
    case AWEUI_ACTION_USER_QUESTION_LLM_RESULT: // 返回云端下发 LLM 结果
        break;
    // case AWEUI_ACTION_QRCODE_RECOGNIZE_START: // 二维码识别开始
    // break;
    // case AWEUI_ACTION_QRCODE_RECOGNIZE:       // 二维码识别中
    // break;
    case AWEUI_ACTION_QRCODE_RECOGNIZE_STOP: // 二维码识别结束(带参数: SSID)
        break;
    case

        AWEUI_ACTION_AUDIO_PLAYER_IDLE: // 音频播放空闲
        break;
    case AWEUI_ACTION_AUDIO_PLAYER_START: // 音频播放开始
        break;
    case AWEUI_ACTION_AUDIO_PLAYER_PAUSE: // 音频播放暂停
        break;
    case AWEUI_ACTION_AUDIO_PLAYER_STOP: // 音频播放结束
        break;
    case AWEUI_ACTION_WIFI_DISCONNECT: // WIFI 断开
        break;
    case AWEUI_ACTION_WIFI_CONNECTING: // WIFI 连接中
        break;
    case AWEUI_ACTION_WIFI_CONNECTED: // WIFI 连接成功
        aweui_network_result_create(lv_scr_act());
        break;
        // case AWEUI_ACTION_NETWORK_DISCONNECT:      // 网络断开
        // break;
    case AWEUI_ACTION_NETWORK_CONNECTING: // 网络连接中
        break;
    case AWEUI_ACTION_NETWORK_CONNECTED: // 网络连接成功
        break;
    case AWEUI_ACTION_NETWORK_CONNECT_FAIL: // 网络连接失败
        break;

    default:
        break;
    }
    return AWEUI_ERR_OK;
}

void aweui_set_llm_mode(aweui_llm_mode_e mode)
{
    aweui_llm_mode = mode;
}

aweui_llm_mode_e aweui_get_llm_mode(void)
{
    return aweui_llm_mode;
}

int aweui_set_camera_preview(const aweui_img_t img)
{
#ifdef __ZEPHYR__
	if (img.len > sizeof(aweui_camera_image_buffer)) {
		LOG_ERR("invalid camera image size:%d", img.len);
		return AWEUI_ERR_INVALID_PARAM;
	}

	k_mutex_lock(&aweui_img_buffer_lock, K_FOREVER);
	memcpy(aweui_camera_image_buffer, img.data, img.len);
	k_mutex_unlock(&aweui_img_buffer_lock);

	aweui_set_camera(aweui_camera_image_buffer, img.width, img.height);
#endif
	return AWEUI_ERR_OK;
}

int aweui_set_user_asr_result_text(const awe_llm_status_t llm_ret_status, const char *text, aweui_text_mode_t text_mode)
{
    ls_lv_llm_dialog_popup_with_mode(llm_ret_status, text, text_mode);
    return AWEUI_ERR_OK;
}

int aweui_set_user_llm_response_result_text(const awe_llm_status_t llm_ret_status, const char *text, aweui_text_mode_t text_mode)
{
    return aweui_screen_chat_result_text(llm_ret_status, text, text_mode);
}

int aweui_set_user_llm_response_result_picture(const awe_llm_status_t llm_ret_status, const aweui_img_t img)
{
    aweui_screen_chat_result_picture(llm_ret_status, img);
    return AWEUI_ERR_OK;
}

int aweui_set_user_llm_response_canvas_color(const awe_llm_status_t llm_ret_status, uint32_t color)
{
    LOG_WRN("Not implemented yet(use aweui_screen_chat_result_picture)");
    return AWEUI_ERR_OK;
}

int aweui_set_audio_player_status(aweui_audio_player_status_t status)
{

    return AWEUI_ERR_OK;
}

// void aweui_event_task(void *p1, void *p2, void *p3)
// {
//     while (1)
//     {
//         k_sleep(K_MSEC(30));
//     }
// }
// #ifdef __ZEPHYR__
// K_THREAD_DEFINE(aweui_event_task_id, 2 * 1024, aweui_event_task, NULL, NULL, NULL,
// 		2, 0, 0);
// #else

// #endif
