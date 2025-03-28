/**
 * @file img_utils.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen tisilicon co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __IMG_UTILS_H__
#define __IMG_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t img_size;
} img_header_t;

uint8_t img_png_get_info(const uint8_t * src, int size, img_header_t * header);


#ifdef __cplusplus
}
#endif

#endif // __IMG_UTILS_H__