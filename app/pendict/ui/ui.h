/**
 * @file ui.h
 * @author TianShuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2023-04-20
 *
 * @copyright Copyright (c) 2021 - 2023  shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _POCKETDICTPEN_UI_H
#define _POCKETDICTPEN_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

#define printk printf

#include <stdio.h>
#include "ui_events.h"
#include "assets/assets_res.h"

enum ui_page_id_t {
    UI_PAGE_ID_NONE,
    UI_PAGE_ID_HOME,
    UI_PAGE_ID_OCR,
    UI_PAGE_ID_AUDIO_PLAY,
    UI_PAGE_ID_SETTING,
    UI_PAGE_ID_DICTIONARY,
    UI_PAGE_ID_DIALOGUE,
    UI_PAGE_ID_SPELLING,

    UI_PAGE_ID_MAX,
};

void ui_init(void);
int ui_app_get_current_appid(void);
int ui_app_set_current_appid(const int app_id);

#include "lv_drv_conf.h"
#define SCREEN_WIDTH SDL_HOR_RES//320
#define SCREEN_HEIGHT SDL_VER_RES//240

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
