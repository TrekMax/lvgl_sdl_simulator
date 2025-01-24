/**
 * @file app_common.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __APP_COMMON_H__
#define __APP_COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

enum lisaui_app_id_t {
    UI_APP_ID_LAUNCHER = 0,
    UI_APP_ID_TASKBAR = 1,

    UI_APP_ID_DEMO,

    UI_APP_ID_OCR,
    UI_APP_ID_DICTIONARY,
    UI_APP_ID_AUDIO_PLAYER,
    UI_APP_ID_SPELLING,
    UI_APP_ID_DIALOGUE,
    UI_APP_ID_SKETCHPAD,

    UI_APP_ID_SETTING,

    UI_APP_ID_VOICE,
    UI_APP_ID_DEMO2,
    UI_APP_ID_DEMO3,

    UI_APP_ID_BEZIER,

    UI_APP_ID_NONE,
    UI_APP_ID_MAX,
};

#ifdef __cplusplus
}
#endif

#endif /* __APP_COMMON_H__ */