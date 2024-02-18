/**
 * @file ui.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-18
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen tisilicon co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ui.h"
#include "resource/resource_pool.h"
#include "page/status_bar/status_bar.h"
#include "ui_page_manager.h"
#include "controller/dialplate_controller.h"

void ui_init( void )
{
    lv_obj_t* scr = lv_scr_act();
    lv_obj_remove_style_all(scr);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

    // 初始化页面栈
    ui_page_manager_init();
    // 初始化码表盘页面控制器
    dialplate_controller_init();
    // 初始化资源池
    resource_pool_init();

    status_bar_init(lv_layer_top());

    pm_install("start_up",    "page/start_up");
    pm_install("dialplate",    "page/dialplate");

    pm_set_global_load_anim_type(LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_out);

    pm_push("page/start_up", NULL);
}




