/**
 * @file app_ocr.h
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __APP_OCR_H__
#define __APP_OCR_H__

#include "../ui.h"

#ifdef __cplusplus
extern "C" {
#endif

void app_ocr_create(lv_obj_t * parent);
lv_obj_t * app_ocr_get_page(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_OCR_H__ */