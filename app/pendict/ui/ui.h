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

#define RES_PERFIX_PATH(res)     "app/pendict/" res

#define printk printf

#include <stdio.h>
#include "ui_events.h"
#include "assets/assets_res.h"

#include "incbin.h"

enum ui_app_id_t {

    UI_APP_ID_OCR,
    UI_APP_ID_DICTIONARY,
    UI_APP_ID_AUDIO_PLAYER,
    UI_APP_ID_SPELLING,
    UI_APP_ID_SETTING,
    UI_APP_ID_DIALOGUE,

    UI_APP_ID_SKETCHPAD,
    UI_APP_ID_DEMO,
    UI_APP_ID_DEMO1,
    UI_APP_ID_DEMO2,
    UI_APP_ID_DEMO3,

    UI_APP_ID_BEZIER,
    
    UI_APP_ID_NONE,
    UI_APP_ID_LAUNCHER,
    UI_APP_ID_MAX,
};

void ui_init(void);
int ui_app_get_current_appid(void);
int ui_app_set_current_appid(const int app_id);


struct app_icon_t {
    const char *name;
    const lv_img_dsc_t *icon;
    uint16_t zoom;
    lv_obj_t *icon_canvas;
    uint16_t icon_width;
    uint16_t icon_height;
};

struct app_info_t {
    const char *name;
    const char *package_name;

    const int id;
    int uuid;
};

#define APP_ICON_ZOOM(x)    (x*256)
#include "lv_drv_conf.h"
#define SCREEN_WIDTH SDL_HOR_RES//320
#define SCREEN_HEIGHT SDL_VER_RES//240

struct lisaui_app_t {
    int (*create)(lv_obj_t * parent);
    int (*destroy)(void);
    int (*enter)(void);
    int (*exit)(void);

    lv_obj_t * (*get_obj_handle)(void);

    struct app_info_t info;
    struct app_icon_t *icon;
};

int lisaui_app_register(struct lisaui_app_t *app);
int lisaui_app_unregister(struct lisaui_app_t *app);
void lisaui_app_enter(const int app_id);

typedef struct {
    const char *app_name;
    int (*app_init_func)(void);
} lvgl_app_t;

#define LISAUI_APP_SECTION __attribute__((used, section(".lisaui_apps")))

#define REGISTER_LISAUI_APP(name, init_func) \
    LISAUI_APP_SECTION \
    static const lvgl_app_t lisaui_app_##name = { \
        .app_name = #name, \
        .app_init_func = init_func, \
    };


#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
