/**
 * @file app_voice.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_voice.h"
#include "../common/lisaui_app_common.h"
#include "../assets/assets_res.h"

static const char *TAG = "app_voice";
static lv_obj_t *g_app_voice = NULL;

/**
 * Print the memory usage periodically
 * @param param
 */
static void memory_monitor(lv_task_t *param)
{
    (void)param; /*Unused*/

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    // printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n", (int)mon.total_size - mon.free_size,
    // mon.used_pct,
    //        mon.frag_pct, (int)mon.free_biggest_size);
    printf("------------Memory usage------------\n");
    printf("\tTotal size              : %0.3lfKB(%d Byte)\n", mon.total_size / 1024.0, mon.total_size);
    printf("\tFree count              : %d\n", mon.free_cnt);
    printf("\tFree size               : %d\n", mon.free_size);
    printf("\tFree biggest size       : %d\n", mon.free_biggest_size);
    printf("\tUsed count              : %d\n", mon.used_cnt);
    printf("\tMax used                : %0.3lfKB(%d Byte)\n", mon.max_used / 1024.0, mon.max_used);
    printf("\tUsed percentage         : %d\n", mon.used_pct);
    printf("\tFragmentation percentage: %d\n", mon.frag_pct);
    printf("\n");

    lisaui_view_manger_print_usage();
}

extern lisaui_err_t lisaui_taskbar_set_battery_charging(int percent);

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED) {
        LISAUI_LOGI(TAG, "Clicked");
        memory_monitor(NULL);
        lisaui_taskbar_set_battery_charging(true);
    } else if (event == LV_EVENT_VALUE_CHANGED) {
        LISAUI_LOGI(TAG, "Open App ocr");
        // lisaui_taskbar_set_battery_charging(false);
        lisaui_app_enter(UI_APP_ID_OCR);
    }
}

void lv_ex_btn_2_test(void *parent)
{
    lv_obj_t *label;

    lv_obj_t *btn1 = lv_btn_create(parent, NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, -160, 0);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button");

    lv_obj_t *btn2 = lv_btn_create(parent, NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 160, 0);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Open App ocr");
}

lisaui_err_t app_voice_create(void *parent)
{
    if (g_app_voice != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_voice = lv_obj_create(parent, parent);
    _lisaui_set_style_container(g_app_voice, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    lv_obj_t *label = lv_label_create(g_app_voice, NULL);
    lv_label_set_text(label, "Hello demo!");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_ex_btn_2_test(g_app_voice);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_voice_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_voice_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_voice_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_voice_get_page(void)
{
    return g_app_voice;
}

static struct app_icon_t app_icon_res = {
    .title = "语音",
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = (const uint8_t *)&ui_img_icon_voice_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_voice = {
    .create = app_voice_create,
    .destroy = app_voice_destroy,
    .enter = app_voice_enter,
    .exit = app_voice_exit,

    .get_root_view = app_voice_get_page,
    .info =
        {
            .name = "Voice",
            .package_name = "com.listenai.lisaui.voice",
            .id = UI_APP_ID_VOICE,
        },
    .icon = &app_icon_res,
};

lisaui_err_t app_voice_init(void)
{
    lisaui_app_register(&app_voice);
    return LISAUI_ERR_OK;
}

REGISTER_LISAUI_APP(voice, &app_voice, app_voice_init);
