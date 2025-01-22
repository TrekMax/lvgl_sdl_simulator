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

#include "incbin.h"

enum ui_app_id_t {

    UI_APP_ID_OCR,
    UI_APP_ID_DICTIONARY,
    UI_APP_ID_AUDIO_PLAY,
    UI_APP_ID_SPELLING,
    UI_APP_ID_SETTING,
    UI_APP_ID_DIALOGUE,

    UI_APP_ID_NONE,
    UI_APP_ID_LAUNCHER,
    UI_APP_ID_MAX,
};

void ui_init(void);
int ui_app_get_current_appid(void);
int ui_app_set_current_appid(const int app_id);


struct ui_app_t {
    const int id;
    const char *name;
    const lv_img_dsc_t *icon;
    uint16_t zoom;
    lv_obj_t *icon_canvas;
    uint16_t icon_width;
    uint16_t icon_height;
};

#include "lv_drv_conf.h"
#define SCREEN_WIDTH SDL_HOR_RES//320
#define SCREEN_HEIGHT SDL_VER_RES//240

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
