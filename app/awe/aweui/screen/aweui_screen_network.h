/*
 * Copyright (c) 2023, LISTENAI
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif
#include "ui.h"
/**
 * @brief Create a network page
 * 
 * @param parent 
 * @return lv_obj_t* 
 */
lv_obj_t *aweui_network_home_create(lv_obj_t *parent);

/**
 * @brief Create a network loading page
 * 
 * @param parent 
 * @return lv_obj_t* 
 */
lv_obj_t *aweui_network_loading_create(lv_obj_t *parent);

/**
 * @brief Create a network scan page
 * 
 * @param parent 
 * @return lv_obj_t* 
 */
lv_obj_t *aweui_screen_network_scan_create(lv_obj_t *parent);
/**
 * @brief Create a network result page
 * 
 * @param parent 
 * @return lv_obj_t* 
 */
lv_obj_t *aweui_network_result_create(lv_obj_t *parent);

/**
 * @brief 设置二维码扫描图像
 * 
 * @param status 
 */
void aweui_set_scan_img(void *data, int width, int height);
#ifdef __cplusplus
}
#endif
