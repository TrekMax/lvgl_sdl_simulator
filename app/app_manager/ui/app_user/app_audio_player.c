/**
 * @file app_audio_player.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-03-03
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_audio_player.h"
#include "../app_common/lisaui_app_common.h"
#include "../assets/assets_res.h"
#include "app_common.h"

static const char *TAG = "app_audio_player";
lv_obj_t *g_audio_player = NULL;
lisaui_err_t app_audio_player_create(void *parent)
{
    if (g_audio_player != NULL) {
        return LISAUI_ERR_OK;
    }
    g_audio_player = lv_obj_create(parent, parent);
    _lisaui_set_style_container(g_audio_player, lv_color_hex(0x404040), 255, lv_color_hex(0x000000), 0, 0);

    lv_obj_t *label = lv_label_create(g_audio_player, NULL);
    lv_label_set_text(label, "Hello audio_player!");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_audio_player_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_audio_player_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_audio_player_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_audio_player_get_page(void)
{
    return g_audio_player;
}

static struct app_icon_t app_icon_res = {
    .title = "播放器",
    // .title = "Audio Player",
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = (const uint8_t *)&ui_img_icon_composition_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_audio_player = {
    .create = app_audio_player_create,
    .destroy = app_audio_player_destroy,
    .enter = app_audio_player_enter,
    .exit = app_audio_player_exit,

    .get_root_view = app_audio_player_get_page,
    .info =
        {
            .name = "Audio Player",
            .package_name = "com.listenai.lisaui.audio_player",
            .id = UI_APP_ID_AUDIO_PLAYER,
        },
    .icon = &app_icon_res,
};

lisaui_err_t app_audio_player_init(void)
{
    lisaui_app_register(&app_audio_player);
    return LISAUI_ERR_OK;
}

REGISTER_LISAUI_APP(audio_player, &app_audio_player, app_audio_player_init);
