/**
 * @file app_weather.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_weather.h"
#include "app_common/lisaui_app_common.h"
#include "lv_img_utils.h"

static const char *TAG = "app_weather";
static lv_obj_t *g_app_weather = NULL;
static lv_obj_t *g_app_panel = NULL;

#if CONFIG_LVGL_ENV_SIMULATOR
    #define APP_WEATHER_UI_RES_PERFIX_PATH(path) "app/llm/lisaui/app/app_weather/" path
#else
    #define APP_WEATHER_UI_RES_PERFIX_PATH(path) "src/ui/lisaui/app/app_weather/" path
#endif

UI_RES_IMG_NAME(weather_undefined, APP_WEATHER_UI_RES_PERFIX_PATH("assets/png/weather_undefined.png"));

lv_obj_t *app_weather_create_weather_view(lv_obj_t *parent, metadata_weather_t *weather)
{
    lv_obj_t *weather_view = lv_obj_create(parent);
    _lisaui_set_style_container(weather_view, lv_color_hex(0x000000), 0, lv_color_hex(0x000000), 0, 0);
    lv_obj_set_size(weather_view, LV_PCT(100), LV_PCT(100));

    lv_obj_t *city_label = lv_label_create(weather_view);
    lv_label_set_text(city_label, weather->city);
    lv_obj_align(city_label, LV_ALIGN_TOP_LEFT, LV_DPX(20), LV_DPX(4));
    lv_obj_set_style_text_color(city_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(city_label, &lv_font_chinese_18, LV_PART_MAIN);

    lv_obj_t *date_label = lv_label_create(weather_view);
    lv_label_set_text(date_label, weather->date);
    // lv_obj_align(city_label, LV_ALIGN_TOP_MID, -LV_DPX(100), 0);
    lv_obj_align_to(date_label, city_label, LV_ALIGN_OUT_RIGHT_MID, LV_DPX(10), 0);
    lv_obj_set_style_text_color(date_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(date_label, &lv_font_chinese_18, LV_PART_MAIN);
    // lv_obj_align(date_label, city_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    // lv_obj_t *weather_icon = lv_img_create(weather_view);
    // lv_img_set_src(weather_icon, &icon_img_weather_sunny_png);
    LV_OBJ_ICON(weather_undefined) = lv_img_create(weather_view);
    lv_img_png_src_init(UI_RES_IMG_PNG(weather_undefined));
    lv_img_set_src(LV_OBJ_ICON(weather_undefined), &LV_IMG_DSC(weather_undefined));

    lv_obj_align(LV_OBJ_ICON(weather_undefined), LV_ALIGN_CENTER, -LV_DPX(60), 0);
    // lv_obj_set_size(LV_OBJ_ICON(weather_undefined), LV_DPX(60), LV_DPX(60));
    // lv_obj_set_style_img_recolor(LV_OBJ_ICON(weather_icon), lv_color_hex(0xFFFFFF), LV_PART_MAIN);

    lv_obj_t *temp_label = lv_label_create(weather_view);
    lv_label_set_text(temp_label, weather->temperature);
    // lv_obj_align(temp_label, LV_ALIGN_TOP_RIGHT, -LV_DPX(40), LV_DPX(40));
    lv_obj_align(city_label, LV_ALIGN_TOP_LEFT, LV_DPX(20), LV_DPX(4));
    // lv_obj_align_to(temp_label, date_label, LV_ALIGN_OUT_RIGHT_MID, LV_DPX(10), 0);
    lv_obj_set_style_text_color(temp_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(temp_label, &lv_font_rubik_bold_64, LV_PART_MAIN);
    // lv_obj_align(temp_label, date_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    lv_obj_t *temp_range_label = lv_label_create(weather_view);
    lv_label_set_text(temp_range_label, weather->temperature_range);
    lv_obj_align(city_label, LV_ALIGN_BOTTOM_RIGHT, 0, -LV_DPX(40));
    lv_obj_set_style_text_color(temp_range_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_text_font(temp_range_label, &lv_font_chinese_18, LV_PART_MAIN);
    // lv_obj_align(temp_range_label, temp_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

    // lv_obj_t *description_label = lv_label_create(weather_view);
    // lv_label_set_text(description_label, weather->description);
    // lv_obj_align(city_label, LV_ALIGN_BOTTOM_RIGHT, 0, -LV_DPX(100));
    // lv_obj_set_style_text_color(description_label, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    // lv_obj_set_style_text_font(description_label, &lv_font_chinese_18, LV_PART_MAIN);

    return weather_view;
}

static lv_obj_t *temp_weather_view = NULL;
lisaui_err_t lisaui_app_weather_set_weather_view(metadata_weather_t *weather)
{
    // if (g_app_weather == NULL) {
    //     return LISAUI_ERR_FAIL;
    // }
    // if (g_app_panel == NULL) {
    //     return LISAUI_ERR_FAIL;
    // }
    // lv_obj_clean(g_app_panel);
    LVGL_UI_LOCK();

    LVGL_OBJ_SAFE_DEL(temp_weather_view);
    temp_weather_view = app_weather_create_weather_view(g_app_panel, weather);

    LVGL_UI_UNLOCK();
    return LISAUI_ERR_OK;
}

lisaui_err_t app_weather_create(void *parent)
{
    if (g_app_weather != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_weather = lv_obj_create(parent);
    _lisaui_set_style_container(g_app_weather, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    g_app_panel = lv_obj_create(g_app_weather);
    _lisaui_set_style_container(g_app_panel, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);
    lv_obj_set_size(g_app_panel, LV_PCT(100), LV_PCT(80));
    lv_obj_set_y(g_app_panel, LV_DPX(LISAUI_STATUS_BAR_HEIGHT));
    // // 创建渐变描述符
    // lv_grad_dsc_t grad;
    // grad.dir = LV_GRAD_DIR_VER;  // 垂直方向
    // grad.stops_count = 2;        // 2个颜色停止点
    // grad.stops[0].color = lv_color_hex(0x0000ff);
    // // grad.stops[0].opa = LV_OPA_COVER;
    // grad.stops[0].frac = 0;      // 开始位置(0%)
    // grad.stops[1].color = lv_color_hex(0xff0000);
    // // grad.stops[1].opa = LV_OPA_COVER;
    // grad.stops[1].frac = 255;    // 结束位置(100%)

    // // 创建样式并应用渐变
    // static lv_style_t style;
    // lv_style_init(&style);
    // // lv_style_set_bg_grad(&style, &g_app_panel);
    // // 设置线性渐变
    // // lv_style_set_bg_opa(&style, LV_OPA_COVER);
    // // lv_style_set_bg_grad(&style, LV_GRAD_DIR_VER);  // 垂直方向渐变
    // lv_style_set_bg_color(&style, lv_color_hex(0x0000ff));  // 起始颜色
    // lv_style_set_bg_grad_color(&style, lv_color_hex(0xff0000));  // 结束颜色
    // lv_obj_add_style(g_app_panel, &style, 0);
    // metadata_weather_t weather = {
    //     .type = 0,
    //     .city = "深圳",
    //     // .location = "深圳",
    //     // .time = "2025-01-22 12:00",
    //     // .week = "星期二",
    //     .date = "04/18",
    //     // .title = "天气",
    //     .temperature = "25°C",
    //     .temperature_range = "20°C - 30°C",
    //     .description = "晴天",
    // };
    // lisaui_app_weather_set_weather_view(&weather);
    // lv_obj_t *weather_view = app_weather_create_weather_view(g_app_panel, &weather);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_weather_destroy(void)
{
    LVGL_OBJ_SAFE_DEL(g_app_weather);

    LISAUI_LOGI(TAG, "[%d:%s] destroy\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_weather_enter(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] enter\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

lisaui_err_t app_weather_exit(void)
{
    LISAUI_LOGI(TAG, "[%d:%s] exit\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
}

void *app_weather_get_page(void)
{
    return g_app_weather;
}

static struct app_icon_t app_icon_res_weather = {
    .title = "天气",
    // .icon_width = LV_SIZE_CONTENT,
    // .icon_height = LV_SIZE_CONTENT,
    .icon = NULL, //&icon_img_app_store_png,
    .zoom = APP_ICON_ZOOM(0),
};

struct lisaui_app_t app_weather = {
    .create = app_weather_create,
    .destroy = app_weather_destroy,
    .enter = app_weather_enter,
    .exit = app_weather_exit,

    .get_root_view = app_weather_get_page,
    .info =
        {
            .name = "Weather",
            .package_name = "com.listenai.lisaui.weather",
            .id = UI_APP_ID_WEATHER,
        },
    .icon = &app_icon_res_weather,
};

lisaui_err_t app_weather_init(void)
{
    lisaui_app_register(&app_weather);
    return LISAUI_ERR_OK;
}

LISAUI_REGISTER_APP(weather, &app_weather, app_weather_init);
