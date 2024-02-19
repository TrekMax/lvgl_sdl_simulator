/**
 * @file aweui_types.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-22
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __AWEUI_TYPES_H__
#define __AWEUI_TYPES_H__

#include <stdint.h>
#define AWEUI_ERR_INVALID_STATE -2
#define AWEUI_ERR_INVALID_PARAM -1
#define AWEUI_ERR_OK 0

/**
 * @brief LLM 交互模式
 * 
 */
typedef enum {
    AWEUI_LLM_MODE_ONESHOT  = 0,
    AWEUI_LLM_MODE_CONTINUE = 1,
} aweui_llm_mode_e;

/**
 * @brief UI 唤醒选项
 * 
 */
typedef enum _aweui_wakeup_option_t {
    AWEUI_WAKEUP_OPTION_NONE = 0,          // 无
    AWEUI_WAKEUP_OPTION_BUTTON,            // 按键唤醒
    AWEUI_WAKEUP_OPTION_VOICE_SINGLE_TURN, // 语音唤醒，单论对话
    AWEUI_WAKEUP_OPTION_VOICE_MULTI_TURN,  // 语音唤醒，多轮对话
} aweui_wakeup_option_t;

typedef struct _aweui_img_t {
    uint16_t width;
    uint16_t height;
    uint8_t *data;

    uint32_t len;
} aweui_img_t;


typedef enum _aweui_text_mode_t {
    AWEUI_TEXT_MODE_APPEND = 0,            // 追加
    AWEUI_TEXT_MODE_OVERWRITE,             // 覆盖
    AWEUI_TEXT_MODE_NONE = 0,          // 无
} aweui_text_mode_t;

/**
 * @brief LLM 状态
 * 
 */
typedef enum _awe_llm_status_t {
    AWEUI_LLM_STATUS_WAITING = 0,         // 等待
    AWEUI_LLM_STATUS_PROCESSING,           // 处理中
    AWEUI_LLM_STATUS_SUCCESS,              // 成功
    AWEUI_LLM_STATUS_FAIL,                 // 失败
    AWEUI_LLM_STATUS_CLOSE,                 // 关闭
} awe_llm_status_t;

/**
 * @brief 音频播放器状态
 * 
 */
typedef enum _aweui_audio_player_status_t {
    AWEUI_AUDIO_PLAYER_STATUS_IDLE = 0,    // 空闲
    AWEUI_AUDIO_PLAYER_STATUS_PLAYING,     // 播放中
    AWEUI_AUDIO_PLAYER_STATUS_PAUSED,      // 暂停
    AWEUI_AUDIO_PLAYER_STATUS_STOPPED,     // 停止
} aweui_audio_player_status_t;

/**
 * @brief UI 事件, 通过统一事件处理函数处理
 * 
 */
typedef enum _aweui_event_t {
    AWEUI_EVENT_NONE                    = (1UL<<0),
    AWEUI_EVENT_CAMERA_PREVIEW_ENTER    = (1UL<<1),     // 相机预览进入
    AWEUI_EVENT_CAMERA_PREVIEW_EXIT     = (1UL<<2),     // 相机预览退出
    AWEUI_EVENT_CAMERA_TAKE_PHOTO       = (1UL<<3),     // 拍照（定格，相机预览暂停）
    AWEUI_EVENT_CAMERA_QUICK_RECOGNIZE  = (1UL<<4),     // 快速识别

    AWEUI_EVENT_CAMERA_DIRECTION_SWITCH = (1UL<<5),     // 相机方向切换

    AWEUI_EVENT_VOICE_KEY_PRESS         = (1UL<<6),     // 语音键按下
    AWEUI_EVENT_VOICE_KEY_RELEASE       = (1UL<<7),     // 语音键释放

    AWEUI_EVENT_WAKEUP_OPTION_CHANGE        = (1UL<<8), // 唤醒选项变更

    AWEUI_EVENT_BACKLIGHT_BRIGHTNESS_CHANGE = (1UL<<9), // 背光亮度变更，范围 2-100%
    AWEUI_EVENT_VOLUME_CHANGE               = (1UL<<10),// 音量变更，范围 0-100%

    // AWEUI_EVENT_QRCODE_RECOGNIZE_START,      // 开始二维码识别
    // AWEUI_EVENT_QRCODE_RECOGNIZE_CANCEL,     // 取消二维码识别

    AWEUI_EVENT_WIFI_DISCONNECT             = (1UL<<11),    // WIFI 断开
    AWEUI_EVENT_WIFI_QRCODE_CONNECT_SCAN    = (1UL<<12),    // WIFI 二维码连接
    AWEUI_EVENT_WIFI_QRCODE_CONNECT_CANCEL  = (1UL<<13),    // WIFI 二维码连接取消

    AWEUI_EVENT_SCREEN_CHANGE_TO_STANDBY    = (1UL<<14),    // 切换到待机界面
    AWEUI_EVENT_SCREEN_CHANGE_TO_CAMERA     = (1UL<<15),    // 切换到相机界面
    AWEUI_EVENT_SCREEN_CHANGE_TO_CHAT       = (1UL<<16),    // 切换到聊天界面

    AWEUI_EVENT_HOME_BTN_CLICKED            = (1UL<<17),    // 切换到主界面

    AWEUI_EVENT_UNKNOWN,
} aweui_event_t;

/**
 * @brief 用于 UI 动作
 * 
 */
typedef enum _aweui_action_t {
    AWEUI_ACTION_WAKEUP = 0,           // 唤醒
    AWEUI_ACTION_IDLE,                 // 空闲
    AWEUI_ACTION_SLEEP,                // 休眠

    AWEUI_ACTION_VOICE_BUTTON_PRESS,       // 语音键按下
    AWEUI_ACTION_VOICE_BUTTON_LONG_PRESS,  // 语音键长按
    AWEUI_ACTION_VOICE_BUTTON_RELEASE,     // 语音键释放

    AWEUI_ACTION_CAMERA_BUTTON_PRESS,      // 拍照键按下
    AWEUI_ACTION_CAMERA_BUTTON_LONG_PRESS, // 拍照键长按
    AWEUI_ACTION_CAMERA_BUTTON_RELEASE,    // 拍照键释放

    AWEUI_ACTION_VOLUME_UP,           // 音量+
    AWEUI_ACTION_VOLUME_DOWN,         // 音量-
    AWEUI_ACTION_BACKLIGHT_UP,        // 背光+
    AWEUI_ACTION_BACKLIGHT_DOWN,      // 背光-

    AWEUI_ACTION_RECOGNIZE_START,     // 录音开始
    AWEUI_ACTION_RECOGNIZE_STOP,      // 录音结束
    AWEUI_ACTION_RECOGNIZE,           // 识别中

    AWEUI_ACTION_RECOGNIZE_FAIL,      // 识别失败
    AWEUI_ACTION_RECOGNIZE_SUCCESS,   // 识别成功

    AWEUI_ACTION_USER_QUESTION_ASR_RESULT, // 返回用户提问 ASR 结果
    AWEUI_ACTION_USER_QUESTION_LLM_RESULT, // 返回云端下发 LLM 结果

    // AWEUI_ACTION_QRCODE_RECOGNIZE_START, // 二维码识别开始
    // AWEUI_ACTION_QRCODE_RECOGNIZE,       // 二维码识别中
    AWEUI_ACTION_QRCODE_RECOGNIZE_STOP,  // 二维码识别结束(带参数: SSID)

    AWEUI_ACTION_AUDIO_PLAYER_IDLE,       // 音频播放空闲
    AWEUI_ACTION_AUDIO_PLAYER_START,      // 音频播放开始
    AWEUI_ACTION_AUDIO_PLAYER_PAUSE,      // 音频播放暂停
    AWEUI_ACTION_AUDIO_PLAYER_STOP,       // 音频播放结束

    AWEUI_ACTION_WIFI_DISCONNECT,         // WIFI 断开
    AWEUI_ACTION_WIFI_CONNECTING,         // WIFI 连接中
    AWEUI_ACTION_WIFI_CONNECTED,          // WIFI 连接成功

    // AWEUI_ACTION_NETWORK_DISCONNECT,      // 网络断开
    AWEUI_ACTION_NETWORK_CONNECTING,      // 网络连接中
    AWEUI_ACTION_NETWORK_CONNECTED,       // 网络连接成功
    AWEUI_ACTION_NETWORK_CONNECT_FAIL,    // 网络连接失败

    AWEUI_ACTION_UNKNOWN,
} aweui_action_t;


#endif // __AWEUI_TYPES_H__