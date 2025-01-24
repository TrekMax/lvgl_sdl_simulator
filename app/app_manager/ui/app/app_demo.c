/**
 * @file app_demo.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_demo.h"
#include "../common/lisaui_app_common.h"
#include "../assets/assets_res.h"
#include "app_common.h"

static const char *TAG = "app_demo";
static lv_obj_t *g_app_demo = NULL;

/**
 * Print the memory usage periodically
 * @param param
 */
static void memory_monitor(lv_task_t *param)
{
    (void)param; /*Unused*/

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    // LISAUI_PRINTK("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n", (int)mon.total_size - mon.free_size,
    // mon.used_pct,
    //        mon.frag_pct, (int)mon.free_biggest_size);
    LISAUI_PRINTK("------------Memory usage------------\n");
    LISAUI_PRINTK("\tTotal size              : %0.3lfKB(%d Byte)\n", mon.total_size / 1024.0, mon.total_size);
    LISAUI_PRINTK("\tFree count              : %d\n", mon.free_cnt);
    LISAUI_PRINTK("\tFree size               : %d\n", mon.free_size);
    LISAUI_PRINTK("\tFree biggest size       : %d\n", mon.free_biggest_size);
    LISAUI_PRINTK("\tUsed count              : %d\n", mon.used_cnt);
    LISAUI_PRINTK("\tMax used                : %0.3lfKB(%d Byte)\n", mon.max_used / 1024.0, mon.max_used);
    LISAUI_PRINTK("\tUsed percentage         : %d\n", mon.used_pct);
    LISAUI_PRINTK("\tFragmentation percentage: %d\n", mon.frag_pct);
    LISAUI_PRINTK("\n");

    lisaui_view_manger_print_usage();
}

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED) {
        LISAUI_LOGI(TAG, "Clicked");
        memory_monitor(NULL);
    } else if (event == LV_EVENT_VALUE_CHANGED) {
        LISAUI_LOGI(TAG, "Open App ocr");
        lisaui_app_enter(UI_APP_ID_DICTIONARY);
    }
}

void lv_ex_btn_1_test(void *parent)
{
    lv_obj_t *label;
    lv_obj_t *btn1 = lv_btn_create(parent, NULL);
    lv_obj_set_event_cb(btn1, event_handler);
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, -160, 0);
    _lisaui_lv_obj_set_btn_custom_style(btn1);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button");

    lv_obj_t *btn2 = lv_btn_create(parent, NULL);
    lv_obj_set_event_cb(btn2, event_handler);
    lv_obj_align(btn2, NULL, LV_ALIGN_CENTER, 160, 0);
    lv_btn_set_checkable(btn2, true);
    lv_btn_toggle(btn2);
    lv_btn_set_fit2(btn2, LV_FIT_NONE, LV_FIT_TIGHT);
    _lisaui_lv_obj_set_btn_custom_style(btn2);

    label = lv_label_create(btn2, NULL);
    lv_label_set_text(label, "Open App ocr");
}

/**
 * Create styles from scratch for buttons.
 */
void lv_ex_get_started_2(void *parent)
{
    static lv_style_t style_btn;
    static lv_style_t style_btn_red;

    /*Create a simple button style*/
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, LV_STATE_DEFAULT, 10);
    lv_style_set_bg_opa(&style_btn, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_bg_grad_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_style_set_bg_grad_dir(&style_btn, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);

    /*Swap the colors in pressed state*/
    lv_style_set_bg_color(&style_btn, LV_STATE_PRESSED, LV_COLOR_GRAY);
    lv_style_set_bg_grad_color(&style_btn, LV_STATE_PRESSED, LV_COLOR_SILVER);

    /*Add a border*/
    lv_style_set_border_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_border_opa(&style_btn, LV_STATE_DEFAULT, LV_OPA_70);
    lv_style_set_border_width(&style_btn, LV_STATE_DEFAULT, 2);

    /*Different border color in focused state*/
    lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED, LV_COLOR_BLUE);
    lv_style_set_border_color(&style_btn, LV_STATE_FOCUSED | LV_STATE_PRESSED, LV_COLOR_NAVY);

    /*Set the text style*/
    lv_style_set_text_color(&style_btn, LV_STATE_DEFAULT, LV_COLOR_WHITE);

    /*Make the button smaller when pressed*/
    lv_style_set_transform_height(&style_btn, LV_STATE_PRESSED, -5);
    lv_style_set_transform_width(&style_btn, LV_STATE_PRESSED, -10);
#if 1 // LV_USE_ANIMATION
    /*Add a transition to the size change*/
    // static lv_anim_path_t path;
    // lv_anim_path_init(&path);
    // lv_anim_path_set_cb(&path, lv_anim_path_overshoot);

    // lv_style_set_transition_prop_1(&style_btn, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
    // lv_style_set_transition_prop_2(&style_btn, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    // lv_style_set_transition_time(&style_btn, LV_STATE_DEFAULT, 300);
    // lv_style_set_transition_path(&style_btn, LV_STATE_DEFAULT, &path);

    /*Create buttons and use the new styles*/
    lv_obj_t *btn = lv_btn_create(parent, NULL); /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                 /*Set its position*/
    lv_obj_set_size(btn, 120, 50);               /*Set its size*/
    // lv_obj_reset_style_list(btn, LV_BTN_PART_MAIN); /*Remove the styles coming from the theme*/
    lv_obj_add_style(btn, LV_BTN_PART_MAIN, &style_btn);

    lv_obj_t *label = lv_label_create(btn, NULL); /*Add a label to the button*/
    lv_label_set_text(label, "Button");           /*Set the labels text*/
#endif

    /*Create a red style. Change only some colors.*/
    lv_style_init(&style_btn_red);
    lv_style_set_bg_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_bg_grad_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_MAROON);
    lv_style_set_bg_color(&style_btn_red, LV_STATE_PRESSED, LV_COLOR_MAROON);
    lv_style_set_bg_grad_color(&style_btn_red, LV_STATE_PRESSED, LV_COLOR_RED);
    lv_style_set_text_color(&style_btn_red, LV_STATE_DEFAULT, LV_COLOR_WHITE);
#if 1 // LV_USE_BTN
    /*Create a new button*/
    lv_obj_t *btn2 = lv_btn_create(parent, btn);
    lv_obj_set_pos(btn2, 10, 80);
    lv_obj_set_size(btn2, 120, 50);                  /*Set its size*/
    lv_obj_reset_style_list(btn2, LV_BTN_PART_MAIN); /*Remove the styles coming from the theme*/
    lv_obj_add_style(btn2, LV_BTN_PART_MAIN, &style_btn);
    lv_obj_add_style(btn2, LV_BTN_PART_MAIN, &style_btn_red); /*Add the red style on top of the current */
    lv_obj_set_style_local_radius(btn2, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE); /*Add a local style*/

    label = lv_label_create(btn2, NULL);  /*Add a label to the button*/
    lv_label_set_text(label, "Button 2"); /*Set the labels text*/
#endif
}

lisaui_err_t app_demo_create(void *parent)
{
    if (g_app_demo != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_demo = lv_obj_create(parent, parent);
    _lisaui_set_style_container(g_app_demo, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    lv_obj_t *label = lv_label_create(g_app_demo, NULL);
    lv_label_set_text(label, "Hello demo!");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_ex_btn_1_test(g_app_demo);

    // extern const uint8_t example_gif_map[]; /*Use the example gif*/
    // lv_obj_t *img = lv_gif_create_from_data(g_app_demo, example_gif_map);
    // lv_obj_align(img, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_demo_destroy(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_demo_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_demo_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_demo_get_page(void)
{
    return g_app_demo;
}

static struct app_icon_t app_icon_res = {
    .title = "测试",
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = (const uint8_t *)&ui_img_icon_practice_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_demo = {
    .create = app_demo_create,
    .destroy = app_demo_destroy,
    .enter = app_demo_enter,
    .exit = app_demo_exit,

    .get_root_view = app_demo_get_page,
    .info =
        {
            .name = "Demo",
            .package_name = "com.listenai.lisaui.demo",
            .id = UI_APP_ID_DEMO,
        },
    .icon = &app_icon_res,
    // .hidden_icon = true,
};

lisaui_err_t app_demo_init(void)
{
    lisaui_app_register(&app_demo);
    return LISAUI_ERR_OK;
}

REGISTER_LISAUI_APP(demo, &app_demo, app_demo_init);
