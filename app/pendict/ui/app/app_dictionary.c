/**
 * @file app_dictionary.c
 * @author TrekMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_dictionary.h"

#include "incbin.h"

#include "../ui.h"
#include "../utils/lv_img_utils.h"

static lv_obj_t * uiApp_Dictionary;

void app_dictionary_create(lv_obj_t * parent)
{
    uiApp_Dictionary = lv_obj_create(NULL);
    lv_obj_clear_flag(uiApp_Dictionary, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(uiApp_Dictionary, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(uiApp_Dictionary, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

lv_obj_t * app_dictionary_get_page(void)
{
    return uiApp_Dictionary;
}
