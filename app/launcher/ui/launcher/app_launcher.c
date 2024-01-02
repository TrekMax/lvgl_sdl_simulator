/**
 * @file app_manager.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-12-18
 *
 * @copyright Copyright (c) 2021 - 2023 shenzhen co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <stdlib.h>

#include "../ui.h"

#include "img_utils.h"
#include "app_launcher.h"

app_manager_t app_manager = {
    .apps = NULL,
    .app_count = 0,
    .bounds.left = 20,
    .bounds.right = 30,
};

lv_obj_t *launcher;
lv_obj_t *launcherContainer;
lv_obj_t *ui_launcher;
lv_obj_t *ui_launcherContainer;
static lv_style_t icon_bg_style;

lv_obj_t *screen_app_loading_page;

lv_obj_t *iconContainerBg;
lv_obj_t *app_loading = NULL;

lv_anim_t anim;

int set_app_loading_progress(int progress)
{
    if (app_loading == NULL)
    {
        return -1;
    }
    char text[32] = {0};
    sprintf(text, "应用正在加载中...(%d%%)", progress);
    lv_label_set_text(app_loading, text);
    return 0;
}

void _ui_screen_change(lv_obj_t **target, lv_scr_load_anim_t fademode, int spd, int delay, void (*target_init)(void))
{
    if (*target == NULL)
        target_init();
    lv_scr_load_anim(*target, fademode, spd, delay, false);
}

void icon_event(lv_event_t *event)
{
    lv_event_code_t event_code = lv_event_get_code(event);

    if (event_code == LV_EVENT_CLICKED)
    {
        int *p_app_id = (int *)lv_event_get_user_data(event);
        int app_id = *p_app_id;
        app_t *app = ui_app_get(app_id);
        _ui_screen_change(&screen_app_loading_page, LV_SCR_LOAD_ANIM_FADE_ON, 120, 0, &ui_screens_app_loading_init);
        if (app && app->run)
        {
            // printf("app[%d]: name: %s\n", app->id, app->name);
            app->run(app, event);
        }
        _ui_app_loading(iconContainerBg, app);
        lv_anim_start(&anim);
    }
}

void _ui_app_add(lv_obj_t *parent, app_t *app)
{
    lv_obj_t *app_title;
    lv_obj_t *app_icon_bg;
    lv_obj_t *app_item = lv_obj_create(parent);

    app->app_item = app_item;
    lv_obj_set_size(app_item, 100, 140);
    lv_obj_set_pos(app_item, app_manager.bounds.left + app->margin.left + app->id * 120, 0);
    lv_obj_set_style_bg_color(app_item, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(app_item, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    app_icon_bg = lv_btn_create(app_item);
    lv_obj_set_size(app_icon_bg, 100, 100);
    lv_obj_set_pos(app_icon_bg, 0, -10);
    lv_obj_set_align(app_icon_bg, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(app_icon_bg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(app_icon_bg, 150, LV_PART_MAIN | LV_STATE_DEFAULT);

    app->app_icon = lv_img_create(app_icon_bg);
    lv_obj_add_style(app_icon_bg, &icon_bg_style, 0);
    lv_obj_set_align(app->app_icon, LV_ALIGN_CENTER);
    lv_obj_add_flag(app->app_icon, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(app->app_icon, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    if (app->icon.type == APP_ICON_TYPE_SYMBOL)
    {
        lv_img_set_src(app->app_icon, (lv_img_dsc_t *)app->icon.data);
    }
    else if (app->icon.type == APP_ICON_TYPE_JPEG)
    {
        // lv_img_set_src(app->app_icon, (lv_img_dsc_t *)app->icon.data);
    }
    else if (app->icon.type == APP_ICON_TYPE_PNG)
    {
        app->icon_dsc.data_size = app->icon.size,
        app->icon_dsc.data = app->icon.data;
        img_header_t header;
        uint8_t png_valid = img_png_get_info(app->icon_dsc.data, app->icon_dsc.data_size, &header);
        if (png_valid)
        {
            app->icon_dsc.header.w = header.width;
            app->icon_dsc.header.h = header.height;
            app->icon_dsc.header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
            // app->icon_dsc.header.always_zero = 0;
            lv_img_set_src(app->app_icon, &app->icon_dsc);
        }
    }
    else
    {
        // lv_img_set_src(app_item, &ui_img_launcher_png);
    }
    lv_obj_add_event_cb(app->app_icon, icon_event, LV_EVENT_ALL, &app->id);

    app_title = lv_label_create(app_item);
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
}

app_t *ui_app_register(const app_t app)
{
    if (app_manager.app_count >= APP_MAX_COUNT)
    {
        printf("app_manager.app_count >= APP_MAX_COUNT(%d)\n", APP_MAX_COUNT);
        return NULL;
    }
    app_t *p_app_list = realloc(app_manager.apps, (app_manager.app_count + 1) * sizeof(app_t));
    if (p_app_list == NULL)
    {
        return NULL;
    }
    app_manager.apps = p_app_list;
    app_t *item = &app_manager.apps[app_manager.app_count];
    // printf("app_manager.app_count: %d\n", app_manager.app_count);
    memset(item, 0, sizeof(app_t));
    memcpy(item, &app, sizeof(app_t));
    item->id = app_manager.app_count;
    app_manager.app_count++;
    item->handle = item;
    _ui_app_add(launcherContainer, item);

    uint8_t app_count = app_manager.app_count < 3 ? 3 : app_manager.app_count;
    lv_obj_set_size(launcherContainer, 120 * app_count + app_manager.bounds.right, 140);
    return item;
}

void ui_app_unregister(app_t *app)
{
    app_t *item = NULL;
    for (int i = 0; i < app_manager.app_count; i++)
    {
        if (app_manager.apps[i].id == app->id)
        {
            item = &app_manager.apps[i];
            break;
        }
    }
    if (item == NULL)
    {
        return;
    }
    for (int i = item->id; i < app_manager.app_count - 1; i++)
    {
        app_manager.apps[i] = app_manager.apps[i + 1];
        app_manager.apps[i].id = i;
    }

    lv_obj_del(item->app_item);
    app_manager.app_count--;
    app_manager.apps = realloc(app_manager.apps, app_manager.app_count * sizeof(app_t));

    uint8_t app_count = app_manager.app_count < 3 ? 3 : app_manager.app_count;
    lv_obj_set_size(launcherContainer, 120 * app_count + app_manager.bounds.right, 140);
}

app_t *ui_app_get(int id)
{
    app_t *item = NULL;
    for (int i = 0; i < app_manager.app_count; i++)
    {
        if (app_manager.apps[i].id == id)
        {
            item = &app_manager.apps[i];
            break;
        }
    }
    return item;
}

static void anim_progress_load(void* obj, int32_t v) {
    lv_bar_set_start_value(obj, v, LV_ANIM_ON);
    lv_bar_set_value(obj, 20 + v, LV_ANIM_ON);
}

void _ui_app_loading(lv_obj_t *parent, app_t *app)
{
    lv_obj_t *app_title;
    lv_obj_t *app_icon_bg;
    lv_obj_t *app_item = lv_obj_create(parent);
    // lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_ROW);

    app->app_item = app_item;
    lv_obj_set_size(app_item, 100, 140);
    lv_obj_set_pos(app_item, app_manager.bounds.left, 10);
    lv_obj_set_style_bg_color(app_item, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(app_item, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    app_icon_bg = lv_btn_create(app_item);
    lv_obj_set_size(app_icon_bg, 80, 80);
    lv_obj_set_pos(app_icon_bg, 0, -10);
    lv_obj_set_align(app_icon_bg, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_bg_color(app_icon_bg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(app_icon_bg, 150, LV_PART_MAIN | LV_STATE_DEFAULT);

    app->app_icon = lv_img_create(app_icon_bg);
    lv_obj_add_style(app_icon_bg, &icon_bg_style, 0);
    lv_obj_set_align(app->app_icon, LV_ALIGN_CENTER);
    lv_obj_add_flag(app->app_icon, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST); /// Flags
    lv_obj_clear_flag(app->app_icon, LV_OBJ_FLAG_SCROLLABLE);                        /// Flags
    if (app->icon.type == APP_ICON_TYPE_SYMBOL)
    {
        lv_img_set_src(app->app_icon, (lv_img_dsc_t *)app->icon.data);
    }
    else if (app->icon.type == APP_ICON_TYPE_JPEG)
    {
        // lv_img_set_src(app->app_icon, (lv_img_dsc_t *)app->icon.data);
    }
    else if (app->icon.type == APP_ICON_TYPE_PNG)
    {
        app->icon_dsc.data_size = app->icon.size,
        app->icon_dsc.data = app->icon.data;
        img_header_t header;
        uint8_t png_valid = img_png_get_info(app->icon_dsc.data, app->icon_dsc.data_size, &header);
        if (png_valid)
        {
            app->icon_dsc.header.w = header.width;
            app->icon_dsc.header.h = header.height;
            app->icon_dsc.header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
            // app->icon_dsc.header.always_zero = 0;
            lv_img_set_src(app->app_icon, &app->icon_dsc);
        }
    }
    else
    {
        // lv_img_set_src(app_item, &ui_img_launcher_png);
    }
    // lv_obj_add_event_cb(app->app_icon, icon_event, LV_EVENT_ALL, &app->id);

    app_icon_bg = lv_btn_create(parent);
    // lv_obj_set_flex_flow(app_icon_bg, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_align(app_icon_bg, LV_ALIGN_RIGHT_MID);
    lv_obj_set_size(app_icon_bg, 200, 130);
    // lv_obj_set_pos(app_icon_bg, 0, -10);
    lv_obj_set_x(app_icon_bg, -10);
    // lv_obj_set_align(app_icon_bg, LV_ALIGN_LEFT_MID);
    // lv_obj_set_style_bg_color(app_icon_bg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(app_icon_bg, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    app_title = lv_label_create(app_icon_bg);
    lv_obj_set_y(app_title, 20);
    lv_obj_set_align(app_title, LV_ALIGN_TOP_LEFT);
    char name[20] = {0};
    sprintf(name, "%d:%s", app->id, app->name);
    lv_label_set_text(app_title, name);
    lv_label_set_text(app_title, app->name);
    lv_obj_set_style_text_color(app_title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(app_title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(app_title, &lv_font_chinese_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    app_loading = lv_label_create(app_icon_bg);
    lv_obj_set_y(app_loading, 70);
    lv_label_set_text(app_loading, app->name);
    // lv_label_set_text(app_loading, "App loading...(100%)");
    lv_label_set_text(app_loading, "应用正在加载中...(0%)");
    lv_obj_set_style_text_color(app_loading, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(app_loading, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(app_loading, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(app_loading, &lv_font_chinese_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(app_loading, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);


}

void ui_screens_launcher_init(void)
{
    ui_launcherContainer = lv_obj_create(NULL);
    lv_obj_set_size(ui_launcherContainer, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_bg_color(ui_launcherContainer, lv_color_hex(0x212121), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_launcherContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(ui_launcherContainer, LV_FLEX_FLOW_COLUMN);
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
    lv_obj_set_style_bg_opa(ui_launcher, 255 * 0.06, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_launcher, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(ui_launcher, LV_FLEX_FLOW_COLUMN);
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
    lv_obj_add_style(launcher_page_tips_box, &icon_bg_style, 0);
    lv_obj_set_size(launcher_page_tips_box, 80, 12);
    lv_obj_set_y(launcher_page_tips_box, -4);
    lv_obj_set_align(launcher_page_tips_box, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(launcher_page_tips_box, lv_color_hex(0x393939), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_style_init(&icon_bg_style);
    lv_style_set_radius(&icon_bg_style, 12);
    lv_style_set_border_opa(&icon_bg_style, LV_OPA_TRANSP);
}

void ui_screens_app_loading_init(void)
{
    screen_app_loading_page = lv_obj_create(NULL);
    lv_obj_set_size(screen_app_loading_page, 320, 240);

    lv_obj_set_style_bg_color(screen_app_loading_page, lv_color_hex(0x212121), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(screen_app_loading_page, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(screen_app_loading_page, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(screen_app_loading_page, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    lv_obj_t *title_bar = lv_obj_create(screen_app_loading_page);
    lv_obj_set_size(title_bar, 320, 50);
    lv_obj_set_style_bg_opa(title_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_t *title = lv_label_create(title_bar);
    lv_obj_set_pos(title, 10, 0);
    lv_obj_set_align(title, LV_ALIGN_LEFT_MID);
    lv_label_set_text(title, "ListenAi Demo");
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_26, LV_PART_MAIN | LV_STATE_DEFAULT);

    iconContainerBg = lv_obj_create(screen_app_loading_page);
    lv_obj_set_size(iconContainerBg, 320, 150);
    lv_obj_set_style_bg_color(iconContainerBg, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(iconContainerBg, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_flex_flow(iconContainerBg,LV_FLEX_FLOW_COLUMN);
    // lv_obj_set_flex_align(iconContainerBg, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    // lv_obj_set_scrollbar_mode(iconContainerBg, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_t *launcher_page_tips_box = lv_obj_create(screen_app_loading_page);
    // lv_obj_set_size(launcher_page_tips_box, 320, 4);
    // lv_obj_set_align(launcher_page_tips_box, LV_ALIGN_CENTER);
    // lv_obj_set_style_bg_color(launcher_page_tips_box, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(launcher_page_tips_box, 100, LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_anim_init(&anim);
    lv_obj_t* bar = lv_bar_create(screen_app_loading_page);
    lv_obj_set_y(bar, 150);
    lv_anim_set_var(&anim, bar);
    // lv_obj_t* bar = lv_bar_create(lv_scr_act());
    lv_bar_set_mode(bar, LV_BAR_MODE_RANGE);
    static lv_style_t style_bg;
    static lv_style_t style_indic;
    lv_style_init(&style_bg);
    // lv_style_set_border_color(&style_bg, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_color(&style_bg, lv_color_hex(0xFFFFFF));
    lv_style_set_border_width(&style_bg, 1);
    lv_style_set_pad_all(&style_bg, 6);
    // lv_style_set_radius(&style_bg, 6);
    lv_style_set_anim_time(&style_bg, 1000);
    lv_style_init(&style_indic);
    lv_style_set_bg_opa(&style_indic, LV_OPA_COVER);
    // lv_style_set_bg_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_color(&style_indic, lv_color_hex(0xFFFFFF));
    lv_style_set_radius(&style_indic, 3);
    lv_obj_remove_style_all(bar);
    lv_obj_add_style(bar, &style_bg, 0);
    lv_obj_add_style(bar, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(bar, 320, 20);

    lv_anim_set_exec_cb(&anim, anim_progress_load);
    lv_anim_set_values(&anim, 0, 80);
    lv_anim_set_path_cb(&anim, lv_anim_path_linear);
    lv_anim_set_time(&anim, 1500);
    lv_anim_set_delay(&anim, 0);

    lv_anim_set_playback_time(&anim, 1500);
    lv_anim_set_repeat_count(&anim, LV_ANIM_REPEAT_INFINITE);
}
