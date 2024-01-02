/**
 * @file ui.c
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
#include "ui.h"
#include "app_launcher.h"
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX
#include "incbin.h"

INCBIN(camera_png, "assets/icons/camera.png");
INCBIN(video_png, "assets/icons/video_card.png");
INCBIN(music_png, "assets/icons/music_player.png");
INCBIN(qq_music, "assets/icons/qq_music.png");
INCBIN(video_player, "assets/icons/video_player.png");
INCBIN(music_album, "assets/icons/music_album.png");

void ui_app_run(app_t *app, lv_event_t * e)
{
    printf("app %s\n", app->name);
#if 1
    app_t music_album = {
        .name = "音乐专辑",
        .icon = {
            .type = APP_ICON_TYPE_PNG,
            .data = music_album_data,
            .size = music_album_size,
        },
        .run = ui_app_run,
    };
    ui_app_register(music_album);
#endif
}

void ui_app_manager_init(void)
{
    app_t *app_handle;

    app_t app_music = {
        .name = "音乐播放器",
        .icon = {
            .type = APP_ICON_TYPE_PNG,
            .data = music_png_data,
            .size = music_png_size,
        },
        .run = ui_app_run,
    };

    app_t app_camera = {
        .name = "相机",
        .icon = {
            .type = APP_ICON_TYPE_PNG,
            .data = camera_png_data,
            .size = camera_png_size,
        },
        .run = ui_app_run,
    };

    app_t app_video = {
        .name = "显卡",
        .icon = {
            .type = APP_ICON_TYPE_PNG,
            .data = video_png_data,
            .size = video_png_size,
        },
        .run = ui_app_run,
    };
    ui_app_register(app_camera);
    ui_app_register(app_music);
    ui_app_register(app_video);
    
    app_handle = ui_app_register(app_music);
    // 注销 App 测试
    ui_app_unregister(app_handle);

    app_camera.name = "视频";
    app_camera.icon.data = video_player_data;
    app_camera.icon.size = video_player_size;
    ui_app_register(app_camera);

    app_music.name = "QQ 音乐";
    app_music.icon.data = qq_music_data;
    app_music.icon.size = qq_music_size;
    ui_app_register(app_music);

}

void ui_init( void )
{
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_screens_launcher_init();

    extern lv_obj_t *ui_launcherContainer;
    lv_disp_load_scr( ui_launcherContainer);

    ui_app_manager_init();
}

