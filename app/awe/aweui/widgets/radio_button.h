/**
 * @file radio_button.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __RADIO_BUTTON_H__
#define __RADIO_BUTTON_H__
#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif
void lv_example_checkbox_2(void);

#endif // __RADIO_BUTTON_H__

