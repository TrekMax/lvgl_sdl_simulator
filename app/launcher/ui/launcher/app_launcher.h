/**
 * @file app_manger.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2021 - 2023 shenzhen tisilicon co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __APP_MANAGER_H__
#define __APP_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _icon_type_t
{
    APP_ICON_TYPE_NONE = 0,
    APP_ICON_TYPE_SYMBOL,
    APP_ICON_TYPE_RAW,
    APP_ICON_TYPE_PNG,
    APP_ICON_TYPE_JPEG,
    APP_ICON_TYPE_BMP,
    APP_ICON_TYPE_GIF,
    APP_ICON_TYPE_FILE,
} icon_type_t;

typedef struct _app_icon_t
{
    icon_type_t type;
    uint16_t width;
    uint16_t height;
    uint8_t *data;
    unsigned int size;
    // const lv_img_dsc_t *data;
} app_icon_t;

typedef struct {
    uint16_t left;
    uint16_t right;
    uint16_t top;
    uint16_t bottom;
} app_margin_t, app_bounds_t;

typedef struct _app_t app_t;
typedef void (*app_event_handler_t)(app_t *app_handler, lv_event_t * e);

struct _app_t
{
    app_t *handle;
    char *name;
    char *version;
    int id;

    app_icon_t icon;
    lv_obj_t *app_item;
    lv_obj_t *app_icon;
    lv_img_dsc_t icon_dsc;
    
    void (*init)(void);
    app_event_handler_t event_handler;
    app_margin_t margin;
};

typedef struct _app_manager_t
{
    app_t *apps;
    size_t app_count;
    app_bounds_t bounds;
} app_manager_t;

void ui_app_manager_init(void);
app_t *ui_app_register(const app_t app);
void ui_app_unregister(app_t *app);

LV_FONT_DECLARE(lv_font_chinese_18);
#ifdef __cplusplus
}
#endif

#endif // __APP_MANAGER_H__

