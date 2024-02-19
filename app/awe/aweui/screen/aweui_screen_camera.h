/*
 * Copyright (c) 2023, LISTENAI
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __ZEPHYR__
#include <zephyr/kernel.h>
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include "aweui_screen_camera.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a camera page
 * 
 * @param init_pg 
 * @return lv_obj_t* 
 */
lv_obj_t * aweui_camera_create(lv_obj_t *parent);

/**
 * @brief Set the camera status object
 * 
 * @param status 
 */
void set_camera_status(uint8_t status);

/**
 * @brief Set the camre object
 * 
 * @param data 
 * @param width 
 * @param height 
 */
void aweui_set_camera(void *data, int width, int height);

/**
 * @brief Create a photo page
 * 
 * @param parent 
 */
void ui_create_photo(lv_obj_t *parent);
#ifdef __cplusplus
}
#endif
