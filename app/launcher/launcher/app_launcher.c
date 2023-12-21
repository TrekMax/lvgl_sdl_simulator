/**
 * @file app_manager.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2021 - 2023 shenzhen tisilicon co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>
#include "../ui.h"
#include "app_launcher.h"

app_manager_t app_manager = {
    .apps = NULL,
    .app_count = 0,
    .bounds.left = 20,
};


lv_obj_t *launcher;
lv_obj_t *ui_launcher;
lv_obj_t *launcherContainer;
lv_obj_t *ui_launcherContainer;
static lv_style_t style;


#pragma pack(push, 1)
typedef struct {
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    uint8_t color_type;
    uint8_t compression;
    uint8_t filter;
    uint8_t interlace;
} IHDRChunk;
#pragma pack(pop)

#define SWAP_UINT32(x) (((x) >> 24) | \
                       (((x) & 0x00FF0000) >> 8) | \
                       (((x) & 0x0000FF00) << 8) | \
                       ((x) << 24))

/**
 * @brief 读取 PNG 图片信息,并判断 PNG 图片是否有效
 * 
 * @param src 
 * @param size 
 * @param header 
 * @return uint8_t 
 */
uint8_t img_png_decoder_get_info(const uint8_t * src, size_t size, lv_img_header_t * header)
{
     if (size < 8) {
        return 0;
    }

    const uint8_t png_signature[8] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };
    if (memcmp(src, png_signature, 8) != 0) {
        return 0; // 签名不匹配
    }

    src += 8;
    size -= 8;

    // 检查 IHDR 块
    if (size < 25) { // IHDR块的最小长度：4(长度) + 4(类型) + 13(IHDR数据) + 4(CRC)
        return 0; // 剩余数据太短，不足以包含完整的 IHDR 块
    }

    // 读取块长度
    uint32_t chunk_length = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];
    if (chunk_length != 13) {
        return 0; // IHDR块长度不正确
    }

    // 确认块类型是 "IHDR"
    if (src[4] != 'I' || src[5] != 'H' || src[6] != 'D' || src[7] != 'R') {
        return 0; // 块类型不是 IHDR
    }
    src += 8;
    IHDRChunk *ihdr;
    ihdr = (IHDRChunk *)src;
    // 大小端转换
    header->w = SWAP_UINT32(ihdr->width);
    header->h = SWAP_UINT32(ihdr->height);
    header->cf = LV_IMG_CF_RAW_ALPHA;
    header->always_zero = 0;
    return 1;
}

// 图像数据延迟加载,不能作为局部变量

void _ui_app_add(lv_obj_t *parent, app_t *app)
{
    lv_obj_t *app_title;
    lv_obj_t *app_icon_bg;

    app->app_item = lv_obj_create(parent);
    lv_obj_set_size(app->app_item, 100, 140);
    lv_obj_set_pos(app->app_item, app_manager.bounds.left + app->margin.left + app->id*120, 0);
    lv_obj_set_style_bg_color(app->app_item, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(app->app_item, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    app_icon_bg = lv_btn_create(app->app_item);
    lv_obj_set_size(app_icon_bg, 100, 100);
    lv_obj_set_pos(app_icon_bg, 0, -10);
    lv_obj_set_align(app_icon_bg, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(app_icon_bg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(app_icon_bg, 150, LV_PART_MAIN | LV_STATE_DEFAULT);

    app->app_icon = lv_img_create(app_icon_bg);
    lv_obj_add_style(app_icon_bg, &style, 0);
    lv_obj_set_align(app->app_icon, LV_ALIGN_CENTER);
    lv_obj_add_flag(app->app_icon, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(app->app_icon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    if (app->icon.type == APP_ICON_TYPE_SYMBOL) {
        lv_img_set_src(app->app_icon, (lv_img_dsc_t *)app->icon.data);
    } else if (app->icon.type == APP_ICON_TYPE_JPEG) {
        lv_img_set_src(app->app_icon, (lv_img_dsc_t *)app->icon.data);
    } else if (app->icon.type == APP_ICON_TYPE_PNG) {
        app->icon_dsc.data_size = app->icon.size,
        app->icon_dsc.data = app->icon.data;
        uint8_t png_valid = img_png_decoder_get_info(app->icon_dsc.data, app->icon_dsc.data_size, &app->icon_dsc.header);
        lv_img_set_src(app->app_icon, &app->icon_dsc);
    } else {
        // lv_img_set_src(app_item, &ui_img_launcher_png);
    }

    // lv_obj_add_event_cb(app->app_icon, app->event_handler, LV_EVENT_CLICKED, app);

    app_title = lv_label_create(app->app_item);
    lv_obj_set_pos(app_title, 0, 0);
    lv_obj_set_align(app_title, LV_ALIGN_BOTTOM_MID);
#if 0
    char name[20] = {0};
    sprintf(name, "%d:%s", app->id, app->name);
    lv_label_set_text(app_title, name);
#else
    lv_label_set_text(app_title, app->name);
#endif
    lv_obj_set_style_text_color(app_title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(app_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(app_title, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    uint8_t app_count = app_manager.app_count<3?3:app_manager.app_count;
    lv_obj_set_size(launcherContainer, 120 * app_count + app_manager.bounds.right, 140);
}

app_t *ui_app_register(app_t *app) {
    app_manager.apps = realloc(app_manager.apps, (app_manager.app_count + 1) * sizeof(app_t));
    app_t *item = &app_manager.apps[app_manager.app_count];
    // printf("app_manager.app_count: %d\n", app_manager.app_count);
    memset(item, 0, sizeof(app_t));
    memcpy(item, app, sizeof(app_t));
    item->id = app_manager.app_count;
    app_manager.app_count++;

    _ui_app_add(launcherContainer, item);
    return item;
}

void ui_app_unregister(app_t *app) {
    app_t *item = NULL;
    for (int i = 0; i < app_manager.app_count; i++) {
        if (app_manager.apps[i].id == app->id) {
            item = &app_manager.apps[i];
            break;
        }
    }
    if (item == NULL) {
        return;
    }
    for (int i = item->id; i < app_manager.app_count - 1; i++) {
        app_manager.apps[i] = app_manager.apps[i + 1];
        app_manager.apps[i].id = i;
    }
    
    lv_obj_del(item->app_item);
    app_manager.app_count--;
    app_manager.apps = realloc(app_manager.apps, app_manager.app_count * sizeof(app_t));

    uint8_t app_count = app_manager.app_count<3?3:app_manager.app_count;
    lv_obj_set_size(launcherContainer, 120 * app_count + app_manager.bounds.right, 140);
}

void ui_screens_launcher_init(void)
{
    ui_launcherContainer = lv_obj_create(NULL);
    lv_obj_set_size(ui_launcherContainer, 320, 240);
    lv_obj_set_style_bg_color(ui_launcherContainer, lv_color_hex(0x212121), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_launcherContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(ui_launcherContainer,LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_launcherContainer, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    // lv_obj_set_scrollbar_mode(ui_launcher, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *title_bar = lv_obj_create(ui_launcherContainer);
    lv_obj_set_size(title_bar, 320, 50);
    lv_obj_set_style_bg_opa(title_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *title = lv_label_create(title_bar);
    lv_obj_set_pos(title, 10, 0);
    lv_obj_set_align(title, LV_ALIGN_LEFT_MID);
    lv_label_set_text(title, "ListenAi Demo");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(title, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_launcher = lv_obj_create(ui_launcherContainer);
    lv_obj_set_size(ui_launcher, 320, 150);
    lv_obj_set_style_bg_color(ui_launcher, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(ui_launcher, lv_color_hex(0x3212), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_launcher, 255*0.06, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_launcher, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(ui_launcher,LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_launcher, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_scrollbar_mode(ui_launcher, LV_SCROLLBAR_MODE_OFF);

    launcherContainer = lv_obj_create(ui_launcher);
    lv_obj_set_style_bg_opa(launcherContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_clear_flag(launcherContainer, LV_OBJ_FLAG_SCROLL_ELASTIC);

    lv_obj_t *launcher_page_tips = lv_obj_create(ui_launcherContainer);
    lv_obj_set_size(launcher_page_tips, 320, 40);
    lv_obj_set_style_bg_opa(launcher_page_tips, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(launcher_page_tips, lv_color_hex(0x393939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *launcher_page_tips_box = lv_obj_create(launcher_page_tips);
    lv_obj_add_style(launcher_page_tips_box, &style, 0);
    lv_obj_set_size(launcher_page_tips_box, 80, 12);
    lv_obj_set_y(launcher_page_tips_box, -4);
    lv_obj_set_align(launcher_page_tips_box, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(launcher_page_tips_box, lv_color_hex(0x393939), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(launcherContainer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


    app_manager.apps = NULL;
    app_manager.app_count = 0;
    app_manager.bounds.left = 20;
    app_manager.bounds.right = 30;

    lv_style_init(&style);
    lv_style_set_radius(&style, 12);
    lv_style_set_border_opa(&style, LV_OPA_TRANSP);
}

