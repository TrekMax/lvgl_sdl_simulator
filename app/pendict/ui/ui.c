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


lv_obj_t * ui_ScreenHome;
lv_obj_t * ui_ScreenHome_BodyBase;
lv_obj_t * ui_ScreenHome_Body;

lv_obj_t * ui_AppName;
lv_obj_t *ui_AppIcon;

typedef struct {
    const int id;
    const char *name;
    const lv_img_dsc_t *icon;
    uint16_t zoom;
    lv_obj_t *icon_canvas;
    uint16_t icon_width;
    uint16_t icon_height;
} ui_app_t;

#define APP_ICON_ID_OCR              (1)
#define APP_ICON_ID_AUDIO_PLAYER     (2)
#define APP_ICON_ID_DIALOGUE         (3)
#define APP_ICON_ID_DICTIONARY       (4)
#define APP_ICON_ID_SPELLING         (5)
#define APP_ICON_ID_SETTING          (6)

#define APP_ICON_ZOOM(x)    (x*256)

ui_app_t apps_list[] = {
    {
        .id = APP_ICON_ID_OCR,
        .name = "扫描",
        .icon_width = LV_SIZE_CONTENT,
        .icon_height = LV_SIZE_CONTENT,
        .icon = &ui_img__launcher_scan_png,
        .zoom = APP_ICON_ZOOM(0),
    },
    {
        .id = APP_ICON_ID_AUDIO_PLAYER,
        .name = "播音",
        .icon_width = LV_SIZE_CONTENT,
        .icon_height = LV_SIZE_CONTENT,
        .icon = &ui_img__launcher_composition_png,
        .zoom = APP_ICON_ZOOM(0),
    },
    {
        .id = APP_ICON_ID_DICTIONARY,
        .name = "词典",
        .icon_width = LV_SIZE_CONTENT,
        .icon_height = LV_SIZE_CONTENT,
        .icon = &ui_img__launcher_fav_png,
        .zoom = APP_ICON_ZOOM(0),
    },
    {
        .id = APP_ICON_ID_SPELLING,
        .name = "拼读",
        .icon_width = LV_SIZE_CONTENT,
        .icon_height = LV_SIZE_CONTENT,
        .icon = &ui_img__launcher_practice_png,
        .zoom = APP_ICON_ZOOM(0),
    },
    {
        .id = APP_ICON_ID_SETTING,
        .name = "设置",
        .icon_width = LV_SIZE_CONTENT,
        .icon_height = LV_SIZE_CONTENT,
        .icon = &ui_img__launcher_setting_png,
        .zoom = APP_ICON_ZOOM(0),
    },
};
lv_obj_t * ui_AppIcon_Wsp;
lv_obj_t * ui_AppName_Wsp;

void ui_event_OpenAppAudioPlayer(lv_event_t * e);
void ui_event_OpenAppSetting(lv_event_t * e);
void ui_event_OpenAppWsp(lv_event_t * e);
void ui_Screen_AppWsp_init(void);
void ui_Screen_AppSetting_init(void);
void ui_Screen_AppAudioPlayer_init(void);
void ui_Screen_AppOCR_init(void);

// 状态栏
void ui_event_StatusBar_BtnBackHome(lv_event_t * e);
lv_obj_t * ui_StatusBar;
lv_obj_t * uiStatusBar_BtnBackHome;
lv_obj_t * uiStatusBar_LabDate;
lv_obj_t * uiStatusBar_LabTime;
lv_obj_t * uiStatusBar_IconBatteryState;
lv_obj_t * uiStatusBar_LabBatteryLevel;

// Scan App
lv_obj_t * uiPage_ScanOCR;
lv_obj_t * uiPage_ScanOCR_Body;
lv_obj_t * uiPageScanOCR_TextResult;
lv_obj_t * uiPage_ScanOCR_ImgOCRTips;
lv_obj_t * uiPage_ScanOCR_LabelOCRTips;
lv_obj_t * uiPage_ScanOCR_BtnStart;
lv_obj_t * uiPage_ScanOCR_BtnStop;

// Audio Player App
lv_obj_t * uiPage_AudioPlayer;
lv_obj_t * uiPage_AudioPlayer_Body;
lv_obj_t * uiPage_AudioPlayer_BtnStart;
lv_obj_t * uiPage_AudioPlayer_BtnStop;

// Setting App
lv_obj_t * uiPageSetting;
lv_obj_t * uiPageSetting_LabelBacklight;
lv_obj_t * uiPageSetting_LabelVolume;
lv_obj_t * uiPageSetting_SliderBacklight;
lv_obj_t * uiPageSetting_SliderVolume;

// Wsp App
lv_obj_t * uiPage_Wsp;
lv_obj_t * uiPage_Wsp_Body;
lv_obj_t * uiPage_Wsp_BtnStart;
lv_obj_t * uiPage_Wsp_BtnStop;
lv_obj_t * uiPage_Wsp_Result;

static uint8_t current_screen = UI_PAGE_ID_NONE;

void ui_event_OpenApp(lv_event_t * event)
{
    lv_event_code_t event_code = lv_event_get_code(event);
    lv_obj_t * target = lv_event_get_target(event);
    int app_id = (int)lv_event_get_user_data(event);
    LV_UNUSED(target);
    if(event_code == LV_EVENT_CLICKED) {
        lv_obj_clear_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN); //显示 BackHome 按钮
        lv_obj_add_flag(uiStatusBar_LabDate, LV_OBJ_FLAG_HIDDEN);   // 隐藏日期
        switch (app_id)
        {
        case APP_ICON_ID_OCR:
            current_screen = UI_PAGE_ID_OCR;
            if (uiPage_ScanOCR == NULL) {
                ui_Screen_AppOCR_init();
            }
            lv_obj_set_parent(ui_StatusBar, uiPage_ScanOCR);
            // lv_obj_set_style_text_font(uiPageScanOCR_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
            _ui_screen_change(uiPage_ScanOCR, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
            break;
        case APP_ICON_ID_AUDIO_PLAYER:
            current_screen = UI_PAGE_ID_AUDIO_PLAY;
            if (uiPage_AudioPlayer == NULL) {
                ui_Screen_AppAudioPlayer_init();
            }
            lv_obj_set_parent(ui_StatusBar, uiPage_AudioPlayer);
            _ui_screen_change(uiPage_AudioPlayer, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
            break;
        case APP_ICON_ID_SETTING:
            current_screen = UI_PAGE_ID_SETTING;
            if (uiPageSetting == NULL) {
                ui_Screen_AppSetting_init();
            }
            lv_obj_set_parent(ui_StatusBar, uiPageSetting);
            _ui_screen_change(uiPageSetting, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
            break;
        case APP_ICON_ID_SPELLING:
            current_screen = UI_PAGE_ID_SPELLING;
            if (uiPage_Wsp == NULL) {
                ui_Screen_AppWsp_init();
            }
            lv_obj_set_parent(ui_StatusBar, uiPage_Wsp);
            _ui_screen_change(uiPage_Wsp, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
            break;
        case APP_ICON_ID_DIALOGUE:
            current_screen = UI_PAGE_ID_DIALOGUE;
            if (uiPageSetting == NULL) {
                ui_Screen_AppSetting_init();
            }
            lv_obj_set_parent(ui_StatusBar, uiPageSetting);
            _ui_screen_change(uiPageSetting, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
            break;
        default:
            break;
        }
    }
}

void ui_event_StatusBar_BtnBackHome(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    LV_UNUSED(target);
    if(event_code == LV_EVENT_CLICKED) {
        current_screen = UI_PAGE_ID_HOME;
        lv_obj_set_parent(ui_StatusBar, ui_ScreenHome);
        lv_obj_add_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN); // 隐藏 BackHome 按钮
        lv_obj_clear_flag(uiStatusBar_LabDate, LV_OBJ_FLAG_HIDDEN);   // 显示日期
        _ui_screen_change(ui_ScreenHome, LV_SCR_LOAD_ANIM_FADE_ON, 60, 0);
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
    // lv_img_set_src(uiStatusBar_BtnBackHome, &ui_img__angle_left_double_png);
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
void UI_PAGE_ID_HOME_init(void)
{
    ui_ScreenHome = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ScreenHome, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_y(ui_ScreenHome, 30);
    lv_obj_set_style_bg_color(ui_ScreenHome, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenHome, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_ScreenHome, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiStatusBar_init(lv_layer_sys());

    ui_ScreenHome_BodyBase = lv_obj_create(ui_ScreenHome);
    lv_obj_set_size(ui_ScreenHome_BodyBase, SCREEN_WIDTH, 140);
    // lv_obj_set_pos(ui_ScreenHome_BodyBase, 0, -10);
    lv_obj_set_align(ui_ScreenHome_BodyBase, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_ScreenHome_BodyBase, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(ui_ScreenHome_BodyBase, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(ui_ScreenHome_BodyBase, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_ScreenHome_BodyBase, LV_DIR_HOR);
    lv_obj_set_style_bg_color(ui_ScreenHome_BodyBase, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenHome_BodyBase, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_ScreenHome_BodyBase, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_ScreenHome_BodyBase, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ScreenHome_Body = lv_obj_create(ui_ScreenHome_BodyBase);
    lv_obj_set_size(ui_ScreenHome_Body, SCREEN_WIDTH, 120);
    lv_obj_set_align(ui_ScreenHome_Body, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ScreenHome_Body, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_scroll_dir(ui_ScreenHome_Body, LV_DIR_HOR);
    lv_obj_set_style_bg_color(ui_ScreenHome_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ScreenHome_Body, 55, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_ScreenHome_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    int app_count = sizeof(apps_list)/sizeof(apps_list[0]);
    int app_icon_width = SCREEN_WIDTH/app_count;
    for (int i=0; i<app_count; i++) {
        ui_AppIcon = lv_img_create(ui_ScreenHome_Body);
        lv_img_set_src(ui_AppIcon, apps_list[i].icon);
        if (apps_list[i].zoom) {
            lv_img_set_zoom(ui_AppIcon, apps_list[i].zoom);
        }
        lv_obj_set_x(ui_AppIcon, app_icon_width*i);
        lv_obj_add_flag(ui_AppIcon, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
        lv_obj_clear_flag(ui_AppIcon, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
        lv_obj_add_event_cb(ui_AppIcon, ui_event_OpenApp, LV_EVENT_ALL, (void *)apps_list[i].id);
        lv_obj_set_size(ui_AppIcon, apps_list[i].icon_width, apps_list[i].icon_height);
        lv_obj_set_style_bg_color(ui_AppIcon, lv_color_hex(0xFFFF00), LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_AppName = lv_label_create(ui_ScreenHome_Body);
        lv_obj_set_size(ui_AppName, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_align_to(ui_AppName, ui_AppIcon, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

        lv_label_set_text(ui_AppName, apps_list[i].name);
        lv_obj_set_style_text_color(ui_AppName, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_AppName, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_AppName, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    ui_timer_date_init();
    current_screen = UI_PAGE_ID_HOME;
}

int ui_set_ocr_result_text(const char *result)
{
    if (uiPageScanOCR_TextResult == NULL || uiPage_ScanOCR == NULL)
    {
        return -1;
    }
    if (current_screen == UI_PAGE_ID_NONE) {
        return -1;
    }
    if (current_screen != UI_PAGE_ID_OCR) {
        current_screen = UI_PAGE_ID_OCR;
        lv_obj_set_parent(ui_StatusBar, uiPage_ScanOCR);
        lv_obj_clear_flag(uiStatusBar_BtnBackHome, LV_OBJ_FLAG_HIDDEN); //显示 BackHome 按钮
        lv_obj_add_flag(uiStatusBar_LabDate, LV_OBJ_FLAG_HIDDEN);   // 隐藏日期
        _ui_screen_change(uiPage_ScanOCR, LV_SCR_LOAD_ANIM_OVER_LEFT, 0, 0);
        // lv_obj_set_style_text_font(uiPageScanOCR_TextResult, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    // lv_textarea_set_text(uiPageScanOCR_TextResult, result);
    return 0;
}

int ui_set_wsp_result_text(const char *result)
{
    if (uiPage_Wsp_Result == NULL)
    {
        return -1;
    }
    if (current_screen == UI_PAGE_ID_NONE) {
        return -1;
    }
    lv_textarea_set_text(uiPage_Wsp_Result, result);
    return 0;
}

static ui_translate_action_cb_t ui_translate_action_cb = NULL;
void ui_register_translate_action_cb(ui_translate_action_cb_t update_handler)
{
    ui_translate_action_cb = update_handler;
}

void ui_event_BtnTranslateAction(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    printk("[%d:%s] event: %d\n", __LINE__, __func__, event_code);
    lv_obj_t * obj = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        if (ui_translate_action_cb) {
            ui_translate_action_cb(0);
        }
    }
}

void ui_Screen_AppOCR_init(void)
{
    uiPage_ScanOCR = lv_obj_create(NULL);
    lv_obj_clear_flag(uiPage_ScanOCR, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiPage_ScanOCR, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPage_ScanOCR, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiPage_ScanOCR_Body = lv_obj_create(uiPage_ScanOCR);
    lv_obj_set_size(uiPage_ScanOCR_Body, SCREEN_WIDTH, 140);
    lv_obj_set_pos(uiPage_ScanOCR_Body, 2, 1);
    lv_obj_set_align(uiPage_ScanOCR_Body, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(uiPage_ScanOCR_Body, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(uiPage_ScanOCR_Body, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
                      LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(uiPage_ScanOCR_Body, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiPage_ScanOCR_Body, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiPage_ScanOCR_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPage_ScanOCR_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiPage_ScanOCR_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

#if 1
    uiPageScanOCR_TextResult = lv_textarea_create(uiPage_ScanOCR);
    lv_obj_set_size(uiPageScanOCR_TextResult, SCREEN_WIDTH-140, 120);
    lv_obj_set_pos(uiPageScanOCR_TextResult, 20, 40);
    lv_obj_set_align(uiPageScanOCR_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiPageScanOCR_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_textarea_set_placeholder_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    lv_textarea_set_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    lv_textarea_set_cursor_click_pos(uiPageScanOCR_TextResult, true);
    lv_obj_set_style_text_color(uiPageScanOCR_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiPageScanOCR_TextResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiPageScanOCR_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#else
    uiPageScanOCR_TextResult = lv_label_create(uiPage_ScanOCR);
    lv_obj_set_size(uiPageScanOCR_TextResult, SCREEN_WIDTH-140, 100);
    lv_obj_set_pos(uiPageScanOCR_TextResult, 20, 40);
    lv_obj_set_align(uiPageScanOCR_TextResult, LV_ALIGN_TOP_LEFT);
    lv_obj_set_style_text_font(uiPageScanOCR_TextResult, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_textarea_set_placeholder_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    // lv_textarea_set_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    lv_label_set_text(uiPageScanOCR_TextResult, UI_TEST_STR);
    // lv_textarea_set_cursor_click_pos(uiPageScanOCR_TextResult, true);
    lv_obj_set_style_text_color(uiPageScanOCR_TextResult, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(uiPageScanOCR_TextResult, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(uiPageScanOCR_TextResult, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(uiPageScanOCR_TextResult, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
#endif
    uiPage_ScanOCR_BtnStart = lv_btn_create(uiPage_ScanOCR_Body);
    lv_obj_set_size(uiPage_ScanOCR_BtnStart, 100, SCREEN_WIDTH>320?100:60);
    lv_obj_set_pos(uiPage_ScanOCR_BtnStart, 0, 0);
    lv_obj_set_align(uiPage_ScanOCR_BtnStart, SCREEN_WIDTH>320?LV_ALIGN_RIGHT_MID:LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(uiPage_ScanOCR_BtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiPage_ScanOCR_BtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnTranslate = lv_label_create(uiPage_ScanOCR_BtnStart);
    lv_label_set_text(ui_BtnTranslate, "翻译");
    lv_obj_set_style_text_font(ui_BtnTranslate, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnTranslate);

    lv_obj_add_event_cb(uiPage_ScanOCR_BtnStart, ui_event_BtnTranslateAction, LV_EVENT_CLICKED, NULL);
}

static ui_audio_player_action_cb_t ui_audio_play_action_cb = NULL;
void ui_register_audio_player_action_cb(ui_audio_player_action_cb_t update_handler)
{
    ui_audio_play_action_cb = update_handler;
}

void ui_event_AudioPlayerAction(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    printk("[%d:%s] event: %d\n", __LINE__, __func__, event_code);
    lv_obj_t * obj = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        if (obj == uiPage_AudioPlayer_BtnStart) {
            if (ui_audio_play_action_cb) {
                ui_audio_play_action_cb(UI_AUDIO_PLAY_ACTION_PLAY);
            }
        }
        else if (obj == uiPage_AudioPlayer_BtnStop)
        {
            if (ui_audio_play_action_cb) {
                ui_audio_play_action_cb(UI_AUDIO_PLAY_ACTION_STOP);
            }
        }
    }
}

static ui_wsp_action_cb_t ui_wsp_action_cb = NULL;
void ui_register_wsp_action_cb(ui_wsp_action_cb_t update_handler)
{
    ui_wsp_action_cb = update_handler;
}

void ui_event_WspAction(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    printk("[%d:%s] event: %d\n", __LINE__, __func__, event_code);
    lv_obj_t * obj = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED) {
        if (obj == uiPage_Wsp_BtnStart) {
            printk("[%d:%s] UI_AUDIO_PLAY_ACTION_PLAY\n", __LINE__, __func__);
            if (ui_wsp_action_cb) {
                ui_wsp_action_cb(UI_AUDIO_PLAY_ACTION_PLAY);
            }
        }
        if (obj == uiPage_Wsp_BtnStop) {
            printk("[%d:%s] UI_AUDIO_PLAY_ACTION_STOP\n", __LINE__, __func__);
            if (ui_wsp_action_cb) {
                ui_wsp_action_cb(UI_AUDIO_PLAY_ACTION_STOP);
            }
        }
    }
}

void ui_Screen_AppAudioPlayer_init(void)
{
    uiPage_AudioPlayer = lv_obj_create(NULL);
    lv_obj_clear_flag(uiPage_AudioPlayer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiPage_AudioPlayer, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPage_AudioPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiPage_AudioPlayer_Body = lv_obj_create(uiPage_AudioPlayer);
    lv_obj_set_size(uiPage_AudioPlayer_Body,  (SCREEN_WIDTH), 140);
    lv_obj_set_pos(uiPage_AudioPlayer_Body, 0,0);
    lv_obj_set_align(uiPage_AudioPlayer_Body, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(uiPage_AudioPlayer_Body, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(uiPage_AudioPlayer_Body, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
                      LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(uiPage_AudioPlayer_Body, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiPage_AudioPlayer_Body, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiPage_AudioPlayer_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPage_AudioPlayer_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiPage_AudioPlayer_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiPage_AudioPlayer_BtnStart = lv_btn_create(uiPage_AudioPlayer);
    lv_obj_set_size(uiPage_AudioPlayer_BtnStart, (SCREEN_WIDTH>>2)-20, 80);
    lv_obj_set_pos(uiPage_AudioPlayer_BtnStart, -(SCREEN_WIDTH>>3)-10,10);
    lv_obj_set_align(uiPage_AudioPlayer_BtnStart, LV_ALIGN_CENTER);
    lv_obj_add_flag(uiPage_AudioPlayer_BtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiPage_AudioPlayer_BtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnLabelAudioPlay = lv_label_create(uiPage_AudioPlayer_BtnStart);
    lv_label_set_text(ui_BtnLabelAudioPlay, "Play");
    lv_obj_set_style_text_font(ui_BtnLabelAudioPlay, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnLabelAudioPlay);

    uiPage_AudioPlayer_BtnStop = lv_btn_create(uiPage_AudioPlayer);
    lv_obj_set_size(uiPage_AudioPlayer_BtnStop, (SCREEN_WIDTH>>2)-20, 80);
    lv_obj_set_pos(uiPage_AudioPlayer_BtnStop, (SCREEN_WIDTH>>3)+10,10);
    lv_obj_set_align(uiPage_AudioPlayer_BtnStop, LV_ALIGN_CENTER);
    lv_obj_add_flag(uiPage_AudioPlayer_BtnStop, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiPage_AudioPlayer_BtnStop, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnLabelAudioStop = lv_label_create(uiPage_AudioPlayer_BtnStop);
    lv_label_set_text(ui_BtnLabelAudioStop, "Stop");
    lv_obj_set_style_text_font(ui_BtnLabelAudioStop, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnLabelAudioStop);

    lv_obj_add_event_cb(uiPage_AudioPlayer_BtnStart, ui_event_AudioPlayerAction, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(uiPage_AudioPlayer_BtnStop, ui_event_AudioPlayerAction, LV_EVENT_CLICKED, NULL);
}

void ui_Screen_AppWsp_init(void)
{
    uiPage_Wsp = lv_obj_create(NULL);
    lv_obj_clear_flag(uiPage_Wsp, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiPage_Wsp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPage_Wsp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // uiPage_Wsp_Body = lv_obj_create(uiPage_Wsp);
    // lv_obj_set_size(uiPage_Wsp_Body, 454, 140);
    // lv_obj_set_pos(uiPage_Wsp_Body, 4, 4);
    // lv_obj_set_align(uiPage_Wsp_Body, LV_ALIGN_BOTTOM_LEFT);
    // lv_obj_add_flag(uiPage_Wsp_Body, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    // lv_obj_clear_flag(uiPage_Wsp_Body, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
    //                   LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    // lv_obj_set_scrollbar_mode(uiPage_Wsp_Body, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_set_scroll_dir(uiPage_Wsp_Body, LV_DIR_HOR);
    // lv_obj_set_style_bg_color(uiPage_Wsp_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(uiPage_Wsp_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_side(uiPage_Wsp_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiPage_Wsp_BtnStart = lv_btn_create(uiPage_Wsp);
    lv_obj_set_size(uiPage_Wsp_BtnStart, 120, 50);
    lv_obj_set_pos(uiPage_Wsp_BtnStart, -20, -10);
    lv_obj_set_align(uiPage_Wsp_BtnStart, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(uiPage_Wsp_BtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiPage_Wsp_BtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnLaelWspStart = lv_label_create(uiPage_Wsp_BtnStart);
    lv_label_set_text(ui_BtnLaelWspStart, "WSP Play");
    lv_obj_set_style_text_font(ui_BtnLaelWspStart, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnLaelWspStart);

    uiPage_Wsp_BtnStop = lv_btn_create(uiPage_Wsp);
    lv_obj_set_size(uiPage_Wsp_BtnStop, 120, 50);
    lv_obj_set_pos(uiPage_Wsp_BtnStop, -20, 50);
    lv_obj_set_align(uiPage_Wsp_BtnStop, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(uiPage_Wsp_BtnStop, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiPage_Wsp_BtnStop, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnLabelWspStop = lv_label_create(uiPage_Wsp_BtnStop);
    lv_label_set_text(ui_BtnLabelWspStop, "WSP Stop");
    lv_obj_set_style_text_font(ui_BtnLabelWspStop, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnLabelWspStop);

    // uiPage_Wsp_Result = lv_textarea_create(uiPage_Wsp);
    // lv_obj_set_size(uiPage_Wsp_Result, 280, 120);
    // lv_obj_set_pos(uiPage_Wsp_Result, 20, 20);
    // lv_obj_set_align(uiPage_Wsp_Result, LV_ALIGN_LEFT_MID);
    // lv_textarea_set_placeholder_text(uiPage_Wsp_Result, "...");
    // lv_obj_set_style_text_color(uiPage_Wsp_Result, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_opa(uiPage_Wsp_Result, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(uiPage_Wsp_Result, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(uiPage_Wsp_Result, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(uiPage_Wsp_Result, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_color(uiPage_Wsp_Result, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_opa(uiPage_Wsp_Result, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_add_event_cb(uiPage_Wsp_BtnStart, ui_event_WspAction, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(uiPage_Wsp_BtnStop, ui_event_WspAction, LV_EVENT_CLICKED, NULL);

    arcs_demo_create(uiPage_Wsp);
}

static const lv_font_t * font_normal;
static ui_set_backlight_cb_t backlight_update_cb = NULL;
static ui_set_volume_cb_t volume_update_cb = NULL;

void ui_register_set_backlight_cb(ui_set_backlight_cb_t update_handler)
{
    backlight_update_cb = update_handler;
}
void ui_register_set_volume_cb(ui_set_volume_cb_t update_handler)
{
    volume_update_cb = update_handler;
}

static void ui_event_SliderHandler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);

    if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_coord_t *s = lv_event_get_param(e);
        *s = LV_MAX(*s, 60);
    } else if(code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
        if(dsc->part == LV_PART_KNOB && lv_obj_has_state(obj, LV_STATE_PRESSED)) {
            char buf[8];
            lv_snprintf(buf, sizeof(buf), "%"LV_PRId32, lv_slider_get_value(obj));

            lv_point_t text_size;
            lv_txt_get_size(&text_size, buf, font_normal, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

            lv_area_t txt_area;
            txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - text_size.x / 2;
            txt_area.x2 = txt_area.x1 + text_size.x;
            txt_area.y2 = dsc->draw_area->y1 - 10;
            txt_area.y1 = txt_area.y2 - text_size.y;

            lv_area_t bg_area;
            bg_area.x1 = txt_area.x1 - LV_DPX(8);
            bg_area.x2 = txt_area.x2 + LV_DPX(8);
            bg_area.y1 = txt_area.y1 - LV_DPX(8);
            bg_area.y2 = txt_area.y2 + LV_DPX(8);

            lv_draw_rect_dsc_t rect_dsc;
            lv_draw_rect_dsc_init(&rect_dsc);
            rect_dsc.bg_color = lv_palette_darken(LV_PALETTE_GREY, 3);
            rect_dsc.radius = LV_DPX(5);
            lv_draw_rect(dsc->draw_ctx, &rect_dsc, &bg_area);

            lv_draw_label_dsc_t label_dsc;
            lv_draw_label_dsc_init(&label_dsc);
            label_dsc.color = lv_color_white();
            label_dsc.font = font_normal;
            lv_draw_label(dsc->draw_ctx, &label_dsc, &txt_area, buf, NULL);
        }
    } else if(code == LV_EVENT_VALUE_CHANGED) {
        if (obj == uiPageSetting_SliderBacklight) {
            if (backlight_update_cb) {
                backlight_update_cb(lv_slider_get_value(obj));
            }
        } else if (obj == uiPageSetting_SliderVolume) {
            if (volume_update_cb) {
                volume_update_cb(lv_slider_get_value(obj));
            }
        }
    }
}


void ui_Screen_AppSetting_init(void)
{
    uiPageSetting = lv_obj_create(NULL);
    lv_obj_clear_flag(uiPageSetting, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiPageSetting, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPageSetting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(uiPageSetting, SCREEN_WIDTH, 180);

    uiPageSetting_LabelBacklight = lv_label_create(uiPageSetting);
    lv_obj_set_size(uiPageSetting_LabelBacklight, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_align(uiPageSetting_LabelBacklight, LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(uiPageSetting_LabelBacklight, 30, 0);
    lv_label_set_text(uiPageSetting_LabelBacklight, "亮度");
    lv_obj_set_style_text_color(uiPageSetting_LabelBacklight, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiPageSetting_LabelBacklight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(uiPageSetting_LabelBacklight, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiPageSetting_SliderBacklight = lv_slider_create(uiPageSetting);
    lv_obj_set_size(uiPageSetting_SliderBacklight, SCREEN_WIDTH*0.7, 16);
    lv_obj_set_pos(uiPageSetting_SliderBacklight, 22, 0);
    lv_obj_set_align(uiPageSetting_SliderBacklight, LV_ALIGN_CENTER);
    lv_slider_set_value(uiPageSetting_SliderBacklight, 100, LV_ANIM_OFF);
    lv_slider_set_range(uiPageSetting_SliderBacklight, UI_SILDER_BACKLIGHT_BRIGHTNESS_MIN_VALUE, UI_SILDER_BACKLIGHT_BRIGHTNESS_MAX_VALUE);
    lv_obj_set_style_bg_color(uiPageSetting_SliderBacklight, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPageSetting_SliderBacklight, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    uiPageSetting_LabelVolume = lv_label_create(uiPageSetting);
    lv_obj_set_size(uiPageSetting_LabelVolume, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_align(uiPageSetting_LabelVolume, LV_ALIGN_LEFT_MID);
    lv_obj_set_pos(uiPageSetting_LabelVolume, 30, 40);
    lv_label_set_text(uiPageSetting_LabelVolume, "音量");
    lv_obj_set_style_text_color(uiPageSetting_LabelVolume, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(uiPageSetting_LabelVolume, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(uiPageSetting_LabelVolume, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiPageSetting_SliderVolume = lv_slider_create(uiPageSetting);
    lv_obj_set_size(uiPageSetting_SliderVolume,  SCREEN_WIDTH*0.7, 16);
    lv_obj_set_pos(uiPageSetting_SliderVolume, 22, 40);
    lv_obj_set_align(uiPageSetting_SliderVolume, LV_ALIGN_CENTER);
    lv_slider_set_value(uiPageSetting_SliderVolume, 8, LV_ANIM_OFF);
    lv_slider_set_range(uiPageSetting_SliderVolume, UI_SILDER_VOLUME_MIN_VALUE, UI_SILDER_VOLUME_MAX_VALUE);
    lv_obj_set_style_bg_color(uiPageSetting_SliderVolume, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiPageSetting_SliderVolume, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    font_normal = LV_FONT_DEFAULT;
    lv_obj_add_event_cb(uiPageSetting_SliderBacklight, ui_event_SliderHandler, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(uiPageSetting_SliderVolume, ui_event_SliderHandler, LV_EVENT_ALL, NULL);
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    UI_PAGE_ID_HOME_init();
    lv_disp_load_scr(ui_ScreenHome);
}
