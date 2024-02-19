/**
 * @file lv_img_utils.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-23
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LV_IMG_UTILS_H__
#define __LV_IMG_UTILS_H__

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#include "img_utils.h"

int lv_img_png_src_init(lv_img_dsc_t *dsc, const void *data, uint32_t size);

#endif // __LV_IMG_UTILS_H__