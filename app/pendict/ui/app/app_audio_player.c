/**
 * @file app_audio_player.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_audio_player.h"
#include "../ui.h"

// Audio Player App
lv_obj_t * uiApp_AudioPlayer;
lv_obj_t * uiApp_AudioPlayer_Body;
lv_obj_t * uiApp_AudioPlayer_BtnStart;
lv_obj_t * uiApp_AudioPlayer_BtnStop;


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
        if (obj == uiApp_AudioPlayer_BtnStart) {
            if (ui_audio_play_action_cb) {
                ui_audio_play_action_cb(UI_AUDIO_PLAY_ACTION_PLAY);
            }
        }
        else if (obj == uiApp_AudioPlayer_BtnStop)
        {
            if (ui_audio_play_action_cb) {
                ui_audio_play_action_cb(UI_AUDIO_PLAY_ACTION_STOP);
            }
        }
    }
}

int app_audio_player_create(lv_obj_t * parent)
{
    uiApp_AudioPlayer = lv_obj_create(NULL);
    lv_obj_clear_flag(uiApp_AudioPlayer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiApp_AudioPlayer, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_AudioPlayer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiApp_AudioPlayer_Body = lv_obj_create(uiApp_AudioPlayer);
    lv_obj_set_size(uiApp_AudioPlayer_Body,  (SCREEN_WIDTH), 140);
    lv_obj_set_pos(uiApp_AudioPlayer_Body, 0,0);
    lv_obj_set_align(uiApp_AudioPlayer_Body, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(uiApp_AudioPlayer_Body, LV_OBJ_FLAG_SCROLL_ONE);     /// Flags
    lv_obj_clear_flag(uiApp_AudioPlayer_Body, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
                      LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_scrollbar_mode(uiApp_AudioPlayer_Body, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(uiApp_AudioPlayer_Body, LV_DIR_HOR);
    lv_obj_set_style_bg_color(uiApp_AudioPlayer_Body, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_AudioPlayer_Body, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(uiApp_AudioPlayer_Body, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    uiApp_AudioPlayer_BtnStart = lv_btn_create(uiApp_AudioPlayer);
    lv_obj_set_size(uiApp_AudioPlayer_BtnStart, (SCREEN_WIDTH>>2)-20, 80);
    lv_obj_set_pos(uiApp_AudioPlayer_BtnStart, -(SCREEN_WIDTH>>3)-10,10);
    lv_obj_set_align(uiApp_AudioPlayer_BtnStart, LV_ALIGN_CENTER);
    lv_obj_add_flag(uiApp_AudioPlayer_BtnStart, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiApp_AudioPlayer_BtnStart, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnLabelAudioPlay = lv_label_create(uiApp_AudioPlayer_BtnStart);
    lv_label_set_text(ui_BtnLabelAudioPlay, "Play");
    lv_obj_set_style_text_font(ui_BtnLabelAudioPlay, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnLabelAudioPlay);

    uiApp_AudioPlayer_BtnStop = lv_btn_create(uiApp_AudioPlayer);
    lv_obj_set_size(uiApp_AudioPlayer_BtnStop, (SCREEN_WIDTH>>2)-20, 80);
    lv_obj_set_pos(uiApp_AudioPlayer_BtnStop, (SCREEN_WIDTH>>3)+10,10);
    lv_obj_set_align(uiApp_AudioPlayer_BtnStop, LV_ALIGN_CENTER);
    lv_obj_add_flag(uiApp_AudioPlayer_BtnStop, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(uiApp_AudioPlayer_BtnStop, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_t * ui_BtnLabelAudioStop = lv_label_create(uiApp_AudioPlayer_BtnStop);
    lv_label_set_text(ui_BtnLabelAudioStop, "Stop");
    lv_obj_set_style_text_font(ui_BtnLabelAudioStop, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(ui_BtnLabelAudioStop);

    lv_obj_add_event_cb(uiApp_AudioPlayer_BtnStart, ui_event_AudioPlayerAction, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(uiApp_AudioPlayer_BtnStop, ui_event_AudioPlayerAction, LV_EVENT_CLICKED, NULL);

    return 0;
}

lv_obj_t * app_audio_player_get_page(void)
{
    return uiApp_AudioPlayer;
}

int app_audio_player_destroy(void)
{
    printk("[%d:%s] destroy\n", __LINE__, __func__);
    return 0;
}

int app_audio_player_enter(void)
{
    printk("[%d:%s] enter\n", __LINE__, __func__);
    return 0;
}

int app_audio_player_exit(void)
{
    printk("[%d:%s] exit\n", __LINE__, __func__);
    return 0;
}

struct app_icon_t icon_audio_player = {
    .name = "播音",
    .icon_width = LV_SIZE_CONTENT,
    .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img__launcher_composition_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_audio_player = {
    .create = app_audio_player_create,
    .destroy = app_audio_player_destroy,
    .enter = app_audio_player_enter,
    .exit = app_audio_player_exit,

    .get_obj_handle = app_audio_player_get_page,
    .app_id = UI_APP_ID_AUDIO_PLAY,
    .icon = &icon_audio_player,
};

int app_audio_player_init(void)
{
    app_audio_player.app_id = UI_APP_ID_AUDIO_PLAY;
    return lisaui_app_register(&app_audio_player);
}
