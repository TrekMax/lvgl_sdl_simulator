/**
 * @file ui.c
 * @author TianShuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2023-04-20
 *
 * @copyright Copyright (c) 2021 - 2023  shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ui.h"
#include "ui_helpers.h"
#include "app/app_spelling.h"
#include "app/app_ocr.h"
#include "app/app_setting.h"
#include "app/app_audio_player.h"
#include "app/app_spelling.h"
#include "app/app_dictionary.h"
#include "app/app_demo.h"
#include "app/sketchpad/app_sketchpad.h"



lv_obj_t * uiAppLauncher;
lv_obj_t * uiAppLauncher_BodyBase;
lv_obj_t * uiAppLauncher_Body;

// 状态栏
lv_obj_t * ui_StatusBar;
lv_obj_t * uiStatusBar_BtnBackHome;
lv_obj_t * uiStatusBar_LabDate;
lv_obj_t * uiStatusBar_LabTime;
lv_obj_t * uiStatusBar_IconBatteryState;
lv_obj_t * uiStatusBar_LabBatteryLevel;

/**********************************************************/
void lisaui_launcher_add_app(struct lisaui_app_t *app);
static struct lisaui_app_t *lisaui_app_lists[UI_APP_ID_MAX] = {NULL};
static int app_registered_count = 0;

static uint8_t m_current_appid = UI_APP_ID_NONE;

int ui_app_get_current_appid(void)
{
    return m_current_appid;
}

int ui_app_set_current_appid(const int app_id)
{
    if (UI_APP_ID_MAX <= app_id) {
        printk("[ui] invalid app id: %d\n", app_id);
        return -1;
    }
    m_current_appid = app_id;
    return 0;
}

#if 1

int lisaui_app_register(struct lisaui_app_t *app)
{
    if (app->app_id >= UI_APP_ID_MAX) {
        printk("[ui] invalid app id: %d\n", app->app_id);
        return -1;
    }
    if (lisaui_app_lists[app->app_id] != NULL) {
        printk("[ui] app already registered\n");
        return -1;
    }
    app_registered_count++;
    lisaui_app_lists[app->app_id] = app;
    lisaui_launcher_add_app(app);
    printk("[%d:%s] app(%d:%s) register successful\r\n", 
        __LINE__, __func__, app->app_id, app->icon->name);
    return 0;
}

int lisaui_app_unregister(struct lisaui_app_t *app)
{
    if (app->app_id >= UI_APP_ID_MAX) {
        printk("[ui] invalid app id: %d\n", app->app_id);
        return -1;
    }
    if (lisaui_app_lists[app->app_id] == NULL) {
        printk("[ui] app not registered\n");
        return -1;
    }
    lisaui_app_lists[app->app_id] = NULL;
    app_registered_count--;
    return 0;
}

void lisaui_app_enter(const int app_id)
{
    if (app_id >= UI_APP_ID_MAX) {
        printk("[ui] invalid app id: %d\n", app_id);
        return;
    }
    struct lisaui_app_t *app = lisaui_app_lists[app_id];
    if (app == NULL) {
        printk("[ui] app not registered\n");
        return;
    }
    printk("[ui] open app: %d, %s\n", app_id, app->icon->name);
    if (app->get_obj_handle() == NULL) {
        if (app->create(NULL) != 0) {
            printk("[ui] app(%s) create failed\n", app->icon->name);
            return;
        }
        printk("[ui] app(%s) create success\n", app->icon->name);
    } 
    if (app->enter) {
        if (app->enter()) {
            printk("[ui] app enter failed\n");
            return;
        }
        {
            if (ui_StatusBar, app->get_obj_handle()!=NULL) {
                m_current_appid = app_id;
                lv_obj_set_parent(ui_StatusBar, app->get_obj_handle());
                _ui_screen_change(app->get_obj_handle(), LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
            }
        }
    }
}

void lisaui_app_exit(const int app_id)
{
    if (app_id >= UI_APP_ID_MAX) {
        printk("[ui] invalid app id: %d\n", app_id);
        return;
    }
    struct lisaui_app_t *app = lisaui_app_lists[app_id];
    if (app == NULL) {
        printk("[ui] app not registered\n");
        return;
    }
    printk("[ui] close app: %d, %s\n", app_id, app->icon->name);
    if (app->exit) {
        if (app->exit()) {
            printk("[ui] app exit failed\n");
            return;
        }
    }
    if (app->destroy) {
        if (app->destroy()) {
            printk("[ui] app destroy failed\n");
            return;
        }
    }
}
#endif

/******************************************************************************/
void ui_event_OpenApp(lv_event_t * event);
void ui_event_StatusBar_BtnBackHome(lv_event_t * e);

void lisaui_launcher_add_app(struct lisaui_app_t *app)
{
    if (app->app_id >= UI_APP_ID_MAX) {
        printk("[ui] invalid app id: %d\n", app->app_id);
        return;
    }
    // if (lisaui_app_lists[app->app_id] != NULL) {
    //     printk("[ui] app already registered\n");
    //     return;
    // }
    lv_obj_t * ui_AppName;
    lv_obj_t *ui_AppIcon;
    int app_icon_width = SCREEN_WIDTH/6+40;
    ui_AppIcon = lv_img_create(uiAppLauncher_Body);
    lv_img_set_src(ui_AppIcon, app->icon->icon);
    if (app->icon->zoom) {
        lv_img_set_zoom(ui_AppIcon, app->icon->zoom);
    }
    printk("app_registered_count: %d\n", app_registered_count);
    lv_obj_set_size(uiAppLauncher_Body, app_icon_width*app_registered_count, 120);
    lv_obj_set_x(ui_AppIcon, app_icon_width*(app_registered_count-1));
    lv_obj_add_flag(ui_AppIcon, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_AppIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_AppIcon, ui_event_OpenApp, LV_EVENT_ALL, (void *)&app->app_id);
    lv_obj_set_size(ui_AppIcon, app->icon->icon_width, app->icon->icon_height);
    lv_obj_set_style_bg_color(ui_AppIcon, lv_color_hex(0xFFFF00), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_AppName = lv_label_create(uiAppLauncher_Body);
    lv_label_set_text(ui_AppName, app->icon->name);
    lv_obj_set_size(ui_AppName, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_AppName, ui_AppIcon, LV_ALIGN_OUT_BOTTOM_MID, -10, 4);

    lv_obj_set_style_text_color(ui_AppName, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_AppName, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_AppName, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ui_event_OpenApp(lv_event_t * event)
{
    lv_event_code_t event_code = lv_event_get_code(event);
    lv_obj_t * target = lv_event_get_target(event);
    int *param = lv_event_get_user_data(event);
    int app_id = (int)*param;
    LV_UNUSED(target);

    if(event_code == LV_EVENT_CLICKED) {
        lv_obj_clear_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN); //显示 BackHome 按钮
        lv_obj_add_flag(uiStatusBar_LabDate, LV_OBJ_FLAG_HIDDEN);   // 隐藏日期

        lisaui_app_enter(app_id);
    }
}

void ui_event_StatusBar_BtnBackHome(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    LV_UNUSED(target);
    if(event_code == LV_EVENT_CLICKED) {
        lv_obj_set_parent(ui_StatusBar, uiAppLauncher);
        lv_obj_add_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN); // 隐藏 BackHome 按钮
        lv_obj_clear_flag(uiStatusBar_LabDate, LV_OBJ_FLAG_HIDDEN);   // 显示日期
        _ui_screen_change(uiAppLauncher, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
        lisaui_app_exit(m_current_appid);
        m_current_appid = UI_APP_ID_LAUNCHER;

    }
}

static ui_get_battery_cb_t battery_update_cb = NULL;
void ui_register_battery_update_cb(ui_get_battery_cb_t update_handler)
{
    battery_update_cb = update_handler;
}

static void ui_event_BatteryUpdate(lv_event_t *e)
{
    uint8_t battery_level = 0;
    uint8_t battery_status = 0;

    if (uiStatusBar_LabBatteryLevel == NULL) {
        return;
    }
    if (battery_update_cb) {
        battery_update_cb(&battery_status, &battery_level);
        lv_label_set_text_fmt(uiStatusBar_LabBatteryLevel, "%d%%", battery_level);
        // TODO: update battery icon according to battery status
    }
}

#define UI_BATTERY_UPDATE_INTERVAL 20
static lv_timer_t * ui_timer_date;
static ui_get_timer_cb_t ui_timer_update_cb = NULL;
void ui_timer_date_cb(lv_timer_t * timer)
{
    static uint8_t time_dot = 1;
    static uint8_t time_cnt = UI_BATTERY_UPDATE_INTERVAL;
    struct tm t;
    if (ui_timer_update_cb) {
        if (!ui_timer_update_cb(&t)) {
            lv_label_set_text_fmt(uiStatusBar_LabTime, time_dot?"%02d:%02d:%02d":"%02d:%02d %02d", t.tm_hour, t.tm_min, t.tm_sec);
            lv_label_set_text_fmt(uiStatusBar_LabDate, "%04d/%02d/%02d", t.tm_year+1900, t.tm_mon, t.tm_mday);
            time_dot = !time_dot;
        }
    }

    if(++time_cnt >= UI_BATTERY_UPDATE_INTERVAL) {
        time_cnt = 0;
        ui_event_BatteryUpdate(NULL);
    }
}

void ui_register_time_update_cb(ui_get_timer_cb_t update_handler)
{
    ui_timer_update_cb = update_handler;
}

void ui_timer_date_init(void)
{
    ui_timer_date = lv_timer_create(ui_timer_date_cb, 500, NULL);
}


static uint8_t _battery_level = 0;
int ui_set_battery_level(const uint8_t level)
{
    if (uiStatusBar_LabBatteryLevel == NULL) {
        return -1;
    }
    _battery_level = level;
    lv_label_set_text_fmt(uiStatusBar_LabBatteryLevel, "%d%%", _battery_level);
    return 0;
}

static const lv_img_dsc_t* _uiStatusBar_BatteryStateChargingIcon[5] = {
    &ui_img__status_charging_1_png,
    &ui_img__status_charging_2_png,
    &ui_img__status_charging_3_png,
    &ui_img__status_charging_4_png,
    &ui_img__status_charging_5_png,
};

static const lv_img_dsc_t* _uiStatusBar_BatteryStateNormalIcon[5] = {
    &ui_img__status_battery_1_png,
    &ui_img__status_battery_2_png,
    &ui_img__status_battery_3_png,
    &ui_img__status_battery_4_png,
    &ui_img__status_battery_5_png,
};


int ui_set_battery_state(const uint8_t state)
{
    if (uiStatusBar_IconBatteryState == NULL) {
        return -1;
    }
    uint8_t level = _battery_level/20;
    printk("[ui] battery level: %d, state: %d\n", level, state);
    if (state == UI_BATTERY_STATE_CHARGING) {
        lv_img_set_src(uiStatusBar_IconBatteryState, _uiStatusBar_BatteryStateChargingIcon[level]);
    } else {
        lv_img_set_src(uiStatusBar_IconBatteryState, _uiStatusBar_BatteryStateNormalIcon[level]);
    }
    return 0;
}

void uiStatusBar_init(lv_obj_t *parent)
{
    ui_StatusBar = lv_obj_create(parent);
    lv_obj_set_size(ui_StatusBar, SCREEN_WIDTH, 30);
    lv_obj_set_pos(ui_StatusBar, 0, 0);

    lv_obj_set_align(ui_StatusBar, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_StatusBar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_StatusBar, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_StatusBar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_side(ui_StatusBar, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_StatusBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_StatusBar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiStatusBar_LabBatteryLevel = lv_label_create(ui_StatusBar);
    lv_obj_set_size(uiStatusBar_LabBatteryLevel, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiStatusBar_LabBatteryLevel, -24, -10);

    lv_obj_set_align(uiStatusBar_LabBatteryLevel, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(uiStatusBar_LabBatteryLevel, "100%");
    lv_obj_set_style_text_color(uiStatusBar_LabBatteryLevel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiStatusBar_LabBatteryLevel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(uiStatusBar_LabBatteryLevel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);


    uiStatusBar_LabTime = lv_label_create(ui_StatusBar);
    lv_obj_set_size(uiStatusBar_LabTime, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiStatusBar_LabTime, 0, -10);

    lv_obj_set_align(uiStatusBar_LabTime, LV_ALIGN_TOP_MID);
    lv_label_set_text(uiStatusBar_LabTime, "10:00:00");
    lv_obj_set_style_text_color(uiStatusBar_LabTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiStatusBar_LabTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(uiStatusBar_LabTime, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiStatusBar_IconBatteryState = lv_img_create(ui_StatusBar);
    lv_img_set_src(uiStatusBar_IconBatteryState, &ui_img__status_charging_5_png);
    lv_obj_set_size(uiStatusBar_IconBatteryState, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiStatusBar_IconBatteryState, 10, -5);
    lv_obj_set_align(uiStatusBar_IconBatteryState, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(uiStatusBar_IconBatteryState, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(uiStatusBar_IconBatteryState, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    uiStatusBar_LabDate = lv_label_create(ui_StatusBar);
    lv_obj_set_size(uiStatusBar_LabDate, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_pos(uiStatusBar_LabDate, -4, -10);
    lv_label_set_text(uiStatusBar_LabDate, "2025/1/22");
    lv_obj_set_style_text_color(uiStatusBar_LabDate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiStatusBar_LabDate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(uiStatusBar_LabDate, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Home 界面 StatusBar 返回按钮（默认隐藏）
    uiStatusBar_BtnBackHome = lv_btn_create(ui_StatusBar);
    // lv_img_set_src(uiStatusBar_BtnBackHome, &back_icon);
    lv_obj_set_size(uiStatusBar_BtnBackHome, 40, 30);
    lv_obj_set_pos(uiStatusBar_BtnBackHome, 0, -10);
    lv_obj_add_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(uiStatusBar_BtnBackHome, ui_event_StatusBar_BtnBackHome, LV_EVENT_CLICKED, NULL);
    // 设置按钮的样式（可选）
    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    lv_style_set_bg_color(&style_btn, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_radius(&style_btn, 0);  // 设置圆角半径
    // lv_style_set_border_width(&style_btn, 2);  // 设置边框宽度
    // lv_style_set_border_color(&style_btn, lv_palette_darken(LV_PALETTE_BLUE, 3));  // 设置边框颜色

    // 将样式应用到按钮
    lv_obj_add_style(uiStatusBar_BtnBackHome, &style_btn, 0);
}

///////////////////// SCREENS ////////////////////
void UI_APP_ID_LAUNCHER_init(void)
{
    uiAppLauncher = lv_obj_create(NULL);
    lv_obj_clear_flag(uiAppLauncher, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_y(uiAppLauncher, 30);
    lv_obj_set_style_bg_color(uiAppLauncher, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiAppLauncher, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(uiAppLauncher, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiStatusBar_init(lv_layer_sys());

    uiAppLauncher_BodyBase = lv_obj_create(uiAppLauncher);
    lv_obj_set_size(uiAppLauncher_BodyBase, SCREEN_WIDTH, 140);
    // lv_obj_set_pos(uiAppLauncher_BodyBase, 0, -10);
    lv_obj_set_align(uiAppLauncher_BodyBase, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(uiAppLauncher_BodyBase, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(uiAppLauncher_BodyBase, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(uiAppLauncher_BodyBase, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiAppLauncher_BodyBase, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiAppLauncher_BodyBase, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiAppLauncher_BodyBase, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiAppLauncher_BodyBase, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(uiAppLauncher_BodyBase, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiAppLauncher_Body = lv_obj_create(uiAppLauncher_BodyBase);
    lv_obj_set_size(uiAppLauncher_Body, SCREEN_WIDTH+100, 140);
    lv_obj_set_align(uiAppLauncher_Body, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(uiAppLauncher_Body, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_scroll_dir(uiAppLauncher_Body, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiAppLauncher_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiAppLauncher_Body, 55, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiAppLauncher_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_timer_date_init();
    m_current_appid = UI_APP_ID_LAUNCHER;
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    UI_APP_ID_LAUNCHER_init();
    lv_disp_load_scr(uiAppLauncher);

    app_ocr_scan_init();
    app_demo_init();
    app_dictionary_init();
    app_audio_player_init();
    app_spelling_init();
    app_setting_init();

    app_sketchpad_init();
}
