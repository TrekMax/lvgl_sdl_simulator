/**
 * @file app_thermography.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_thermography.h"
#include "../../app_common/lisaui_app_common.h"
#include "../assets/assets_res.h"

static const char *TAG = "app_thermography";
static lv_obj_t *g_app_thermography = NULL;

// 声明[模板]应用需要实现的接口
LISAUI_DECLARE_APP_FUNC(thermography, create, destroy, enter, exit, get_page);
// 定义[模板]应用
LISAUI_DEFINE_APP(thermography, UI_APP_ID_THERMOGRAPHY, "热成像", "Thermography", &icon_img_app_thermo_png, {});

#include "test_data.h"
void show_thermal_map(lv_obj_t *parent);

// App 模板宏原型在 common/lisaui_app_manager.h 中定义
// 定义[模板]应用功能实现, 用于创建、销毁、进入、退出、获取页面
lisaui_err_t LISAUI_DEFINE_APP_FUNC(thermography, create, void *parent, {
    if (g_app_thermography != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_thermography = lv_obj_create(parent);
    _lisaui_set_style_container(g_app_thermography, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    // lv_obj_t *label = lv_label_create(g_app_thermography);
    // lv_label_set_text(label, "Hello LisaUI!");
    // lv_obj_set_style_text_font(label, &lv_font_chinese_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    show_thermal_map(g_app_thermography);
    return LISAUI_ERR_OK;
});
lisaui_err_t LISAUI_DEFINE_APP_FUNC(thermography, destroy, void, { return LISAUI_ERR_OK; });
lisaui_err_t LISAUI_DEFINE_APP_FUNC(thermography, enter, void, { return LISAUI_ERR_OK; });
lisaui_err_t LISAUI_DEFINE_APP_FUNC(thermography, exit, void, { return LISAUI_ERR_OK; });
void *LISAUI_DEFINE_APP_FUNC(thermography, get_page, void, { return g_app_thermography; });

// 将归一化值 (0.0~1.0) 映射到 coolwarm 色系 (RGB565)
uint16_t coolwarm_colormap(float value)
{
    uint8_t r, g, b;

    // coolwarm 渐变：蓝 -> 白 -> 红
    if (value < 0.5f) {
        r = (uint8_t)(value * 2 * 255); // 冷色到中性
        g = (uint8_t)(value * 2 * 255);
        b = 255;
    } else {
        r = 255; // 中性到暖色
        g = (uint8_t)((1.0f - value) * 2 * 255);
        b = (uint8_t)((1.0f - value) * 2 * 255);
    }

    // 转换为 RGB565
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

// 将温度数组转换为 RGB565 图像缓冲区
void temp_to_rgb565(float temp_array[24][32], uint16_t *rgb_buffer, float min_temp, float max_temp)
{
    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 32; x++) {
            // 归一化温度值
            float normalized = (temp_array[x][y] - min_temp) / (max_temp - min_temp);
            normalized = normalized < 0.0f ? 0.0f : (normalized > 1.0f ? 1.0f : normalized);

            // 写入 RGB565 缓冲区
            rgb_buffer[y * 32 + x] = coolwarm_colormap(normalized);
        }
    }
}

// 定义图像描述符（指向 RGB565 缓冲区的引用）
static lv_img_dsc_t thermal_img_dsc = {
    .header.always_zero = 0,
    .header.w = 32,                    // 图像宽度
    .header.h = 24,                    // 图像高度
    .header.cf = LV_IMG_CF_TRUE_COLOR, // RGB565 格式
    .data_size = 32 * 24 * 2,          // 缓冲区大小（字节）
    .data = NULL                       // 稍后绑定缓冲区
};

#include "temperature_data.h"

// 更新图像数据并显示
void update_thermal_image(lv_obj_t *img, float temp_array[23][32], float min_temp, float max_temp)
{
    // 静态缓冲区（避免频繁动态分配）
    // uint16_t rgb_buffer[24 * 32] = {0};

    // 温度数据转 RGB565
    // temp_to_rgb565(temp_array, rgb_buffer, min_temp, max_temp);

    // 绑定缓冲区到图像描述符
    // thermal_img_dsc.data = (const uint8_t *)rgb_buffer;
    thermal_img_dsc.data = (const uint8_t *)temperature_data;

    // 更新 LVGL 图像控件
    lv_img_set_src(img, &thermal_img_dsc);
    lv_img_set_zoom(img, 256*6);
}

void show_thermal_map(lv_obj_t *parent)
{
    // 创建图像控件
    lv_obj_t *img = lv_img_create(parent);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    // 示例温度数据（需替换为实际 MLX90640 数据）
    // float temp_array[32][24] = { /* ... */ };
    float min_temp = 20.0f, max_temp = 40.0f;

    // 更新图像
    update_thermal_image(img, test_data, min_temp, max_temp);
}
