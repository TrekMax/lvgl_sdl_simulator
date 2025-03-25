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

#include "../app_common/lisaui_app_common.h"
#include "assets/assets_res.h"

enum lisaui_app_id_t {
    UI_APP_ID_LAUNCHER = 0,
    UI_APP_ID_TASKBAR = 1,

    UI_APP_ID_DEMO,

    UI_APP_ID_OCR,
    UI_APP_ID_OCR_DICT,
    UI_APP_ID_OCR_CALIBRATION,
    UI_APP_ID_OCR_PAGE_TIPS,
    UI_APP_ID_OCR_PAGE_SCANNER_TRANSLATOR,

    UI_APP_ID_DICTIONARY,
    UI_APP_ID_AUDIO_PLAYER,
    UI_APP_ID_SPELLING,
    UI_APP_ID_DIALOGUE,
    UI_APP_ID_SKETCHPAD,
    UI_APP_ID_SENTENCE_EVA,

    UI_APP_ID_SETTING,

    UI_APP_ID_VOICE,
    UI_APP_ID_DEMO2,
    UI_APP_ID_DEMO3,

    UI_APP_ID_BEZIER,

    UI_APP_ID_TEMPLATE,

    UI_APP_ID_NONE,
    UI_APP_ID_MAX,
};

typedef enum _lisaui_textarea_mode_t {
    LISAUI_TEXT_MODE_APPEND = 0, // 追加
    LISAUI_TEXT_MODE_OVERWRITE,  // 覆盖

    LISAUI_TEXT_MODE_NORMAL, // 默认
} lisaui_textarea_mode_t;

#define LISAUI_APP_INIT_CHECK(app_id, obj, err, ret)                                                                   \
    if (obj == NULL) {                                                                                                 \
        struct lisaui_app_t *app = lisaui_app_manager_get_app(app_id);                                                 \
        if (app == NULL) {                                                                                             \
            LISAUI_LOGE(TAG, "[%s] %d not registered", __FUNCTION__, app_id);                                          \
            return err;                                                                                                \
        }                                                                                                              \
        if (lisaui_app_enter(app_id) != LISAUI_ERR_OK) {                                                               \
            LISAUI_LOGE(TAG, "[%s] %s not init", __FUNCTION__, app->info.name);                                        \
            return err;                                                                                                \
        }                                                                                                              \
        obj = app->get_root_view();                                                                                    \
        if (obj == NULL) {                                                                                             \
            return err;                                                                                                \
        }                                                                                                              \
    }
#ifdef __cplusplus
}
#endif

#endif /* __APP_COMMON_H__ */