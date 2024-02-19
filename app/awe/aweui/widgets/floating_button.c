/**
 * @file floating_button.c
 * @author TsMax (QinYUN575@Foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-02-21
 * 
 * @copyright Copyright (c) 2021 - 2024 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "floating_button.h"

#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif
static uint32_t btn_cnt = 1;
static void float_btn_event_cb(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e); // 得到事件code
    lv_obj_t* float_btn = lv_event_get_target(e); //得到事件产生的对象
    if (code == LV_EVENT_CLICKED) {  //点击clicked事件
        lv_obj_t* list = lv_event_get_user_data(e); //得到事件用户数据
        char buf[32];
        lv_snprintf(buf, sizeof(buf), "Track %d", btn_cnt); //格式化字串
        lv_obj_t* list_btn = lv_list_add_btn(list, LV_SYMBOL_AUDIO, buf); //增加列表项
        btn_cnt++; 
        lv_obj_move_foreground(float_btn); // float button移到前台
        lv_obj_scroll_to_view(list_btn, LV_ANIM_ON); //滚动列表显示
    }
}

/**
* Create a list a with a floating button
*/
void lv_example_scroll_3(void)
{
    lv_obj_t* list = lv_list_create(lv_scr_act()); //创建当前界面列表对象
    lv_obj_set_size(list, 280, 220);  // 设置大小
    lv_obj_center(list);     // 居中显示
    for (btn_cnt = 1; btn_cnt <= 2; btn_cnt++) {
        char buf[32];
        lv_snprintf(buf, sizeof(buf), "Track %d", btn_cnt); // 格式化字串
        lv_list_add_btn(list, LV_SYMBOL_AUDIO, buf); // 添加子项到列表控件
    }
    lv_obj_t* float_btn = lv_btn_create(list); // 创建按键对象
    lv_obj_set_size(float_btn, 50, 50); // 设置大小
    lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING); // 设置floating特性
    lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, 0, -lv_obj_get_style_pad_right(list, LV_PART_MAIN)); // 设置对齐
    lv_obj_add_event_cb(float_btn, float_btn_event_cb, LV_EVENT_ALL, list);//添加响应事件
    lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);// 设置圆形风格
    lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_PLUS, 0); //背影图片为内部图片LV_SYMBOL_PLUS
    lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0); //设置字体
}
