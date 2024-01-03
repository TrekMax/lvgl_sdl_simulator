/**
 ******************************************************************************
 * @file    lv_100ask_boot_animation.c
 * @author  百问科技
 * @version V1.2
 * @date    2020-12-12
 * @brief	开机动画
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2020-12-12     zhouyuebiao     First version
 * 2021-01-25     zhouyuebiao     V1.2
 * 2023-07-10     zhouyuebiao     V1.3(DShanMCU-RA6M5) LVGL V8
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2008-2021 深圳百问网科技有限公司<https://www.100ask.net/>
 * All rights reserved
 *
 ******************************************************************************
 */


/*********************
 *      INCLUDES
 *********************/
#include "lv_100ask_boot_animation.h"


/**********************************************************************
 * 函数名称： lv_100ask_boot_animation
 * 功能描述： 开机动画
 * 输入参数： 动画持续时间
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人	      修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11	     V1.0	  YobeZhou    创建
 ***********************************************************************/
void lv_100ask_boot_animation(uint32_t delay)
{
    LV_IMG_DECLARE(img_lv_100ask_demo_logo);
    lv_obj_t * logo = lv_img_create(lv_scr_act());
    lv_img_set_src(logo, &img_lv_100ask_demo_logo);
    //lv_img_set_zoom(logo, 512);
    lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);

    /*Animate in the content after the intro time*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_path_cb(&a, lv_anim_path_bounce);
    lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
    lv_anim_set_var(&a, logo);
    lv_anim_set_time(&a, delay);
    lv_anim_set_delay(&a, 0);
    lv_anim_set_values(&a, 1, LV_IMG_ZOOM_NONE);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_img_set_zoom);
	lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
    lv_anim_start(&a);

    /* Create an intro from a label */
    lv_obj_t * title = lv_label_create(lv_scr_act());
    //lv_label_set_text(title, "100ASK LVGL DEMO\nhttps://www.100ask.net\nhttp:/lvgl.100ask.net");
	lv_label_set_text(title, "100ASK LVGL DEMO");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_22, LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(title, 8, LV_STATE_DEFAULT);
    lv_obj_align_to(title, logo, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    lv_obj_fade_out(title, 0, delay);
    lv_obj_fade_out(logo, 0, delay);
}

