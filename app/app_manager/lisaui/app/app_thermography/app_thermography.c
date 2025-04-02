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
#include "app_common/lisaui_app_common.h"
#include "assets/assets_res.h"

static const char *TAG = "app_thermography";
static lv_obj_t *g_app_thermography = NULL;

// 声明[模板]应用需要实现的接口
LISAUI_DECLARE_APP_FUNC(thermography, create, destroy, enter, exit, get_page);
// 定义[模板]应用
LISAUI_DEFINE_APP(thermography, UI_APP_ID_THERMOGRAPHY, "热成像", "Thermography", &icon_img_app_thermo_png, {});

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

// Coolwarm 色彩映射表 (RGB565, 256 entries)
const uint16_t coolwarm_rgb565_table[256] = {
    0x001F, 0x003F, 0x005F, 0x007F, 0x009F, 0x00BF, 0x00DF, 0x00FF, // 深蓝 -> 浅蓝
    0x021F, 0x023F, 0x025F, 0x027F, 0x029F, 0x02BF, 0x02DF, 0x02FF, 0x041F, 0x043F, 0x045F, 0x047F,
    0x049F, 0x04BF, 0x04DF, 0x04FF, 0x061F, 0x063F, 0x065F, 0x067F, 0x069F, 0x06BF, 0x06DF, 0x06FF,
    0x081F, 0x083F, 0x085F, 0x087F, 0x089F, 0x08BF, 0x08DF, 0x08FF, 0x0A1F, 0x0A3F, 0x0A5F, 0x0A7F,
    0x0A9F, 0x0ABF, 0x0ADF, 0x0AFF, 0x0C1F, 0x0C3F, 0x0C5F, 0x0C7F, 0x0C9F, 0x0CBF, 0x0CDF, 0x0CFF,
    0x0E1F, 0x0E3F, 0x0E5F, 0x0E7F, 0x0E9F, 0x0EBF, 0x0EDF, 0x0EFF, // 蓝 -> 青白

    0x0FFF, 0x11FF, 0x13FF, 0x15FF, 0x17FF, 0x19FF, 0x1BFF, 0x1DFF, // 青白 -> 白
    0x1FFF, 0x3DFF, 0x5BFF, 0x79FF, 0x97FF, 0xB5FF, 0xD3FF, 0xF1FF, // 白 -> 浅黄
    0xFFDF, 0xFFBF, 0xFF9F, 0xFF7F, 0xFF5F, 0xFF3F, 0xFF1F, 0xFEFF, // 浅黄 -> 橙
    0xFEDF, 0xFEBF, 0xFE9F, 0xFE7F, 0xFE5F, 0xFE3F, 0xFE1F, 0xFCFF, 0xFCDE, 0xFCBE, 0xFC9E, 0xFC7E,
    0xFC5E, 0xFC3E, 0xFC1E, 0xFAFF, 0xFADE, 0xFABE, 0xFA9E, 0xFA7E, 0xFA5E, 0xFA3E, 0xFA1E, 0xF8FF,
    0xF8DE, 0xF8BE, 0xF89E, 0xF87E, 0xF85E, 0xF83E, 0xF81E, 0xF6FF, 0xF6DE, 0xF6BE, 0xF69E, 0xF67E,
    0xF65E, 0xF63E, 0xF61E, 0xF4FF, // 橙 -> 红

    0xF4FE, 0xF4DE, 0xF4BE, 0xF49E, 0xF47E, 0xF45E, 0xF43E, 0xF41E, // 红 -> 深红
    0xF21E, 0xF01E, 0xEE1E, 0xEC1E, 0xEA1E, 0xE81E, 0xE61E, 0xE41E, 0xE21E, 0xE01E, 0xDE1E, 0xDC1E,
    0xDA1E, 0xD81E, 0xD61E, 0xD41E, 0xD21E, 0xD01E, 0xCE1E, 0xCC1E, 0xCA1E, 0xC81E, 0xC61E, 0xC41E,
    0xC21E, 0xC01E, 0xBE1E, 0xBC1E, 0xBA1E, 0xB81E, 0xB61E, 0xB41E, 0xB21E, 0xB01E, 0xAE1E, 0xAC1E,
    0xAA1E, 0xA81E, 0xA61E, 0xA41E, 0xA21E, 0xA01E, 0x9E1E, 0x9C1E, 0x9A1E, 0x981E, 0x961E, 0x941E,
    0x921E, 0x901E, 0x8E1E, 0x8C1E, 0x8A1E, 0x881E, 0x861E, 0x841E, // 深红 -> 暗红
};

// 查表法 (LUT) 实现 coolwarm -> RGB565
uint16_t coolwarm_rgb565_lut(uint8_t value)
{
    // 预计算 256 种颜色（8位输入）

    return coolwarm_rgb565_table[value];
}

#define RGB565_TO_BRG565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))
#define HEX_RGB565_TO_BRG565(hex)                                                                                      \
    (((((hex) >> 16) & 0xF8) << 8) | (((((hex) >> 8) & 0xFC) << 3)) | (((hex) & 0xF8) >> 3))

// 使用 LUT 的版本（输入 value 需是 0~255 的整数）
uint16_t coolwarm_rgb565_fast(float value)
{
    if (value <= 0.0f) {
        return 0x001F; // 最小值 = 深蓝
    }
    if (value >= 1.0f) {
        return 0xF800; // 最大值 = 深红
    }
    uint8_t index = (uint8_t)(value * 255);
    return coolwarm_rgb565_lut(index);
    // return HEX_RGB565_TO_BRG565(coolwarm_rgb565_table[index]);
}

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
/**
 * @brief 将归一化温度值 (0.0~1.0) 映射到 coolwarm 色系 (RGB565)
 * @param value 归一化的温度值 (0.0~1.0)
 * @return RGB565 格式的颜色值
 */
uint16_t coolwarm_rgb565(float value)
{
    uint8_t r, g, b;

    // 确保 value 在 [0.0, 1.0] 范围内
    if (value < 0.0f) {
        value = 0.0f;
    }
    if (value > 1.0f) {
        value = 1.0f;
    }

    // coolwarm 渐变：蓝 -> 白 -> 红
    if (value < 0.5f) {
        // 冷色到中性 (蓝 -> 白)
        float t = value * 2.0f; // 映射到 [0, 1]
        r = (uint8_t)(t * 255);
        g = (uint8_t)(t * 255);
        b = 255;
    } else {
        // 中性到暖色 (白 -> 红)
        float t = (value - 0.5f) * 2.0f; // 映射到 [0, 1]
        r = 255;
        g = (uint8_t)((1.0f - t) * 255);
        b = (uint8_t)((1.0f - t) * 255);
    }

    // 转换为 RGB565（R:5位, G:6位, B:5位）
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
    // return ((b >> 3) << 11) | ((g >> 2) << 5) | (r >> 3);
}

#define LISAUI_RGB565(r, g, b) (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3))
// 将温度值转换为 RGB565 格式

#define THERMAL_COL 32
#define THERMAL_ROW 24

int R_colour = 0;
int G_colour = 0;
int B_colour = 0;

void getColour(int j)
{
    if (j >= 0 && j < 30) {
        R_colour = 0;
        G_colour = 0;
        B_colour = 20 + 4 * j;
    }

    if (j >= 30 && j < 60) {
        R_colour = 4 * (j - 30);
        G_colour = 0;
        B_colour = 140 - 2 * (j - 30);
    }

    if (j >= 60 && j < 90) {
        R_colour = 120 + 4 * (j - 60);
        G_colour = 0;
        B_colour = 80 - 2 * (j - 60);
    }

    if (j >= 90 && j < 120) {
        R_colour = 255;
        G_colour = 0 + 2 * (j - 90);
        B_colour = 10 - (j - 90) / 3;
    }

    if (j >= 120 && j < 150) {
        R_colour = 255;
        G_colour = 60 + 175 * (j - 120) / 30;
        B_colour = 0;
    }

    if (j >= 150 && j <= 180) {
        R_colour = 255;
        G_colour = 235 + (j - 150) * 20 / 30;
        B_colour = 0 + 85 * (j - 150) / 10;
    }
}

// 将温度数组转换为 RGB565 图像缓冲区
void temp_to_rgb565(float temp_array[THERMAL_ROW][THERMAL_COL], uint16_t *rgb_buffer, float min_temp, float max_temp)
{
    LISAUI_LOGI(TAG, "min_temp: %f, max_temp: %f", min_temp, max_temp);
    for (int y = 0; y < THERMAL_ROW; y++) {
        for (int x = 0; x < THERMAL_COL; x++) {
            int index = y * THERMAL_COL + x;

#if 0
            // 归一化温度值
            float normalized = (temp_array[y][x] - min_temp) / (max_temp - min_temp);
            normalized = normalized < 0.0f ? 0.0f : (normalized > 1.0f ? 1.0f : normalized);
            rgb_buffer[index] = coolwarm_rgb565(normalized);
#endif
#if 1

            // 量程规约温度值[0, 180]
            int normalized = (int)(((temp_array[y][x] - min_temp) * 180) / (max_temp - min_temp));
            getColour(normalized);
            rgb_buffer[index] = LISAUI_RGB565(R_colour, G_colour, B_colour);
#endif
#if 0
            // 采用查表法
            float normalized = (temp_array[y][x] - min_temp) / (max_temp - min_temp);
            normalized = normalized < 0.0f ? 0.0f : (normalized > 1.0f ? 1.0f : normalized);
            // rgb_buffer[y * THERMAL_COL + x] = coolwarm_rgb565_lut((uint8_t)(normalized * 255));
            rgb_buffer[index] = coolwarm_rgb565_fast(normalized);
#endif
            // float normalized = ((temp_array[y][x] - min_temp) *32767) / (max_temp - min_temp);
            // rgb_buffer[index] = coolwarm_colormap(normalized);
            // LISAUI_LOGD(TAG, "temp_array[%2d][%2d]: %0.2lf, normalized: %0.2lf", y, x, temp_array[y][x], normalized);
            // LISAUI_LOGI(TAG, "rgb_buffer[%2d][%2d]: %04X", y, x, rgb_buffer[y * 32 + x]);

            // rgb_buffer[y * 32 + x] = LISAUI_RGB565(0, 0xff, 0);
        }
    }
}

// 定义图像描述符（指向 RGB565 缓冲区的引用）
static lv_img_dsc_t thermal_img_dsc = {
    .header.always_zero = 0,
    .header.w = THERMAL_COL,                    // 图像宽度
    .header.h = THERMAL_ROW,                    // 图像高度
    .header.cf = LV_IMG_CF_TRUE_COLOR,          // RGB565 格式
    .data_size = THERMAL_COL * THERMAL_ROW * 2, // 缓冲区大小（字节）
    .data = NULL                                // 稍后绑定缓冲区
};

uint16_t rgb_buffer[THERMAL_ROW * THERMAL_COL] = {0};
void update_thermal_image(lv_obj_t *img, float temp_array[THERMAL_ROW][THERMAL_COL], float min_temp, float max_temp)
{
    temp_to_rgb565(temp_array, rgb_buffer, min_temp, max_temp);

    thermal_img_dsc.data = (const uint8_t *)rgb_buffer;
    // thermal_img_dsc.data = (const uint8_t *)temperature_data;

    lv_img_set_src(img, &thermal_img_dsc);
    lv_img_set_zoom(img, 256 * 4);
}

// #include "temperature_data.h"
#include "test_data.h"

void show_thermal_map(lv_obj_t *parent)
{
    lv_obj_t *img = lv_img_create(parent);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

    // float min_temp = 20.0f, max_temp = 50.0f;
    float min_temp = test_data[0][0];
    float max_temp = test_data[0][0];

    for (int i = 0; i < THERMAL_ROW; i++) {
        for (int j = 0; j < THERMAL_COL; j++) {
            min_temp = min_temp < test_data[i][j] ? min_temp : test_data[i][j];
            max_temp = max_temp > test_data[i][j] ? max_temp : test_data[i][j];
        }
    }
    LISAUI_LOGI(TAG, "min_temp: %f, max_temp: %f", min_temp, max_temp);

    // 更新图像
    update_thermal_image(img, temperature_data, min_temp, max_temp);
    // update_thermal_image(img, test_data, min_temp, max_temp);
}
