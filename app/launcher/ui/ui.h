/**
 * @file ui.h
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-18
 * 
 * @copyright Copyright (c) 2021 - 2023 shenzhen tisilicon co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __UI_H__
#define __UI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"



void ui_init(void);

void ui_screens_launcher_init(void);


#ifdef __cplusplus
}
#endif

#endif /* __UI_H__ */