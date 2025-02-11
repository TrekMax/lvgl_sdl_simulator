/**
 * @file app_bezier_demo.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-02-14
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_bezier_demo.h"
#include "../ui.h"

#define CHART_POINTS_NUM 256
struct {
    lv_obj_t *anim_obj;
    lv_obj_t *chart;
    lv_chart_series_t *ser1;
    lv_obj_t *p1_slider;
    lv_obj_t *p1_label;
    lv_obj_t *p2_slider;
    lv_obj_t *p2_label;
    lv_obj_t *run_btn;
    uint16_t p1;
    uint16_t p2;
    lv_anim_t a;
} ginfo;

static int32_t anim_path_bezier3_cb(const lv_anim_t *a);
static void refer_chart_cubic_bezier(void);
static void run_btn_event_handler(lv_event_t *e);
static void slider_event_cb(lv_event_t *e);
static void page_obj_init(lv_obj_t *par);
static void anim_x_cb(void *var, int32_t v); /** * create an animation */

static lv_obj_t *uiApp_bezier_Demo = NULL;

int app_bezier_demo_create(lv_obj_t *parent)
{
    static lv_coord_t col_dsc[] = {LV_GRID_FR(1), 400, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {50, 20, 20, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST}; /*Create a container with grid*/

    uiApp_bezier_Demo = lv_obj_create(parent);
    lv_obj_set_style_pad_all(uiApp_bezier_Demo, 2, LV_PART_MAIN);
    lv_obj_set_style_pad_column(uiApp_bezier_Demo, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_row(uiApp_bezier_Demo, 10, LV_PART_MAIN);
    lv_obj_set_grid_dsc_array(uiApp_bezier_Demo, col_dsc, row_dsc);
    lv_obj_set_size(uiApp_bezier_Demo, LV_HOR_RES, LV_VER_RES - 30);
    lv_obj_set_y(uiApp_bezier_Demo, 30);
    lv_obj_center(uiApp_bezier_Demo);
    page_obj_init(uiApp_bezier_Demo);
    lv_anim_init(&ginfo.a);
    lv_anim_set_var(&ginfo.a, ginfo.anim_obj);
    int32_t end = lv_obj_get_style_width(uiApp_bezier_Demo, LV_PART_MAIN) -
                  lv_obj_get_style_width(ginfo.anim_obj, LV_PART_MAIN) - 10;

    // printk("%d,%d,%d,%d\r\n", lv_obj_get_style_width(uiApp_bezier_Demo, LV_PART_MAIN),
    //        lv_obj_get_style_width(ginfo.anim_obj, LV_PART_MAIN), lv_obj_get_style_x(uiApp_bezier_Demo, LV_PART_MAIN),
    //        lv_obj_get_style_x(ginfo.anim_obj, LV_PART_MAIN));

    lv_anim_set_values(&ginfo.a, 5, end);
    lv_anim_set_time(&ginfo.a, 2000);
    lv_anim_set_exec_cb(&ginfo.a, anim_x_cb);
    lv_anim_set_path_cb(&ginfo.a, anim_path_bezier3_cb);
    refer_chart_cubic_bezier();

    return 0;
}

static int32_t anim_path_bezier3_cb(const lv_anim_t *a)
{
    uint32_t t = lv_map(a->act_time, 0, a->time, 0, 1024);
    int32_t step = lv_bezier3(t, 0, ginfo.p1, ginfo.p2, 1024);
    int32_t new_value;
    new_value = step * (a->end_value - a->start_value);
    new_value = new_value >> 10;
    new_value += a->start_value;
    return new_value;
}

static void refer_chart_cubic_bezier(void)
{
    for (uint16_t i = 0; i <= CHART_POINTS_NUM; i++) {
        uint32_t t = i * (1024 / CHART_POINTS_NUM);
        int32_t step = lv_bezier3(t, 0, ginfo.p1, ginfo.p2, 1024);
        lv_chart_set_value_by_id2(ginfo.chart, ginfo.ser1, i, t, step);
        // printk("x:%d, y:%d\t", t, step);
    }
    lv_chart_refresh(ginfo.chart);
}

static void anim_x_cb(void *var, int32_t v)
{
    lv_obj_set_style_translate_x(var, v, LV_PART_MAIN);
}

static void run_btn_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        lv_anim_start(&ginfo.a);
    }
}

static void slider_event_cb(lv_event_t *e)
{
    char buf[16];
    lv_obj_t *label;
    lv_obj_t *slider = lv_event_get_target(e);
    if (slider == ginfo.p1_slider) {
        label = ginfo.p1_label;
        ginfo.p1 = lv_slider_get_value(slider);
        printk(buf, "p1:%d", ginfo.p1);
    } else {
        label = ginfo.p2_label;
        ginfo.p2 = lv_slider_get_value(slider);
        printk(buf, "p2:%d", ginfo.p2);
    }
    lv_label_set_text(label, buf);
    refer_chart_cubic_bezier();
}

static void page_obj_init(lv_obj_t *par)
{
    ginfo.anim_obj = lv_obj_create(par);
    lv_obj_set_size(ginfo.anim_obj, 50, 50);
    lv_obj_set_align(ginfo.anim_obj, LV_ALIGN_TOP_LEFT);
    lv_obj_clear_flag(ginfo.anim_obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(ginfo.anim_obj, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_set_grid_cell(ginfo.anim_obj, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 0, 1);
    ginfo.p1_label = lv_label_create(par);
    ginfo.p2_label = lv_label_create(par);
    lv_label_set_text(ginfo.p1_label, "p1:0");
    lv_label_set_text(ginfo.p2_label, "p2:0");
    lv_obj_set_grid_cell(ginfo.p1_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_cell(ginfo.p2_label, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_START, 2, 1);
    ginfo.p1_slider = lv_slider_create(par);
    ginfo.p2_slider = lv_slider_create(par);
    lv_slider_set_range(ginfo.p1_slider, 0, 1024);
    lv_slider_set_range(ginfo.p2_slider, 0, 1024);
    lv_obj_set_style_pad_all(ginfo.p1_slider, 2, LV_PART_KNOB);
    lv_obj_set_style_pad_all(ginfo.p2_slider, 2, LV_PART_KNOB);
    lv_obj_add_event_cb(ginfo.p1_slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_add_event_cb(ginfo.p2_slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_set_grid_cell(ginfo.p1_slider, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_START, 1, 1);
    lv_obj_set_grid_cell(ginfo.p2_slider, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_START, 2, 1);
    ginfo.run_btn = lv_btn_create(par);
    lv_obj_add_event_cb(ginfo.run_btn, run_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t *btn_label = lv_label_create(ginfo.run_btn);
    lv_label_set_text(btn_label, LV_SYMBOL_PLAY);
    lv_obj_center(btn_label);
    lv_obj_set_grid_cell(ginfo.run_btn, LV_GRID_ALIGN_STRETCH, 2, 1, LV_GRID_ALIGN_STRETCH, 1, 2);
    // Y方向占两格
    ginfo.chart = lv_chart_create(par);
    lv_obj_set_style_pad_all(ginfo.chart, 0, LV_PART_MAIN);
    lv_obj_set_style_size(ginfo.chart, 0, LV_PART_INDICATOR);
    lv_chart_set_type(ginfo.chart, LV_CHART_TYPE_SCATTER);
    lv_chart_set_point_count(ginfo.chart, CHART_POINTS_NUM);
    ginfo.ser1 = lv_chart_add_series(ginfo.chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_range(ginfo.chart, LV_CHART_AXIS_PRIMARY_Y, 0, 1024);
    lv_chart_set_range(ginfo.chart, LV_CHART_AXIS_PRIMARY_X, 0, 1024);
    lv_obj_set_grid_cell(ginfo.chart, LV_GRID_ALIGN_STRETCH, 0, 3, LV_GRID_ALIGN_STRETCH, 3,
                         1); // x方向占3格
}

lv_obj_t *app_bezier_demo_get_page(void)
{
    return uiApp_bezier_Demo;
}

int app_bezier_demo_destroy(void)
{
    printk("[%d:%s] destroy\n", __LINE__, __func__);
    return 0;
}

int app_bezier_demo_enter(void)
{
    printk("[%d:%s] enter\n", __LINE__, __func__);
    return 0;
}

int app_bezier_demo_exit(void)
{
    printk("[%d:%s] exit\n", __LINE__, __func__);
    return 0;
}

struct app_icon_t icon_demo = {
    .name = "Demo",
    .icon_width = LV_SIZE_CONTENT,
    .icon_height = LV_SIZE_CONTENT,
    .icon = &ui_img__launcher_fav_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_bezier_demo = {
    .create = app_bezier_demo_create,
    .destroy = app_bezier_demo_destroy,
    .enter = app_bezier_demo_enter,
    .exit = app_bezier_demo_exit,

    .get_obj_handle = app_bezier_demo_get_page,
    .app_id = UI_APP_ID_DEMO,
    .icon = &icon_demo,
};

int app_bezier_demo_init(void)
{
    return lisaui_app_register(&app_bezier_demo);
}
