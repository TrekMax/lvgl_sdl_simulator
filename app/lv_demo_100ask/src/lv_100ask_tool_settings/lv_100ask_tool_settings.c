/**
 ******************************************************************************
 * @file    lv_100ask_tool_settings.c
 * @author  百问科技
 * @version V1.2
 * @date    2020-12-12
 * @brief	系统设置
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
#include <stdlib.h>
#include "lv_100ask_tool_settings.h"

#define LV_100ASK_SETTING_SW_BTN_SIZE		 (LV_VER_RES / 3)

static lv_obj_t * bg_setting;		// 背景
static bool g_theme_state = true;	// 主题状态 true：白天 false：夜间模式

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_100ask_tool_setting_init(void);						// 界面初始化
static void event_handler_switch_themes(lv_event_t * e);	// 切换主题事件处理函数
static void event_handler_back_to_home(lv_event_t * e);	// 返回桌面事件处理函数


/*
 *  函数名：   void lv_100ask_tool_setting(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_tool_setting(void)
{
	/* 初始化桌面背景 */
	bg_setting = lv_obj_create(lv_scr_act());
	lv_obj_set_style_radius(bg_setting, 0, 0);
	lv_obj_set_style_pad_all(bg_setting, 0, 0);
	lv_obj_set_size(bg_setting, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_y(bg_setting, 0);

	/* 初始化主界面 */
    lv_100ask_tool_setting_init();

	/* 创建app标题 */
    add_title(bg_setting, "SETTING");

	/* 创建返回桌面按钮 */
	add_back(bg_setting, event_handler_back_to_home);   // 返回桌面按钮
}


/*
 *  函数名：   static void lv_100ask_tool_setting_init(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用界面初始化
*/
static void lv_100ask_tool_setting_init(void)
{
	/* 默认为白天模式 */
	lv_obj_t * btn_switch_themes = lv_obj_create(bg_setting);
	lv_obj_set_style_radius(btn_switch_themes, 360, 0);
	lv_obj_set_size(btn_switch_themes, LV_100ASK_SETTING_SW_BTN_SIZE, LV_100ASK_SETTING_SW_BTN_SIZE);
	lv_obj_set_style_text_font(btn_switch_themes, &lv_font_montserrat_22, 0);
	lv_obj_align(btn_switch_themes, LV_ALIGN_CENTER, 0, 0);
	lv_obj_add_event_cb(btn_switch_themes, event_handler_switch_themes, LV_EVENT_CLICKED, NULL);

	lv_obj_t * label = lv_label_create(btn_switch_themes);
	lv_obj_center(label);

	if (!g_theme_state)
	{
		//lv_obj_set_style_bg_color(btn_switch_themes, lv_color_hex(0x000000), 0);    	// 设置颜色
		///lv_obj_set_style_value_str(btn_switch_themes, LV_SYMBOL_EYE_CLOSE"Dark", 0);
		lv_label_set_text(label, LV_SYMBOL_EYE_CLOSE"Dark");
	}
	else
	{
		//lv_obj_set_style_bg_color(btn_switch_themes, lv_color_hex(0xffffff), 0);    	// 设置颜色
		///lv_obj_set_style_value_str(btn_switch_themes, LV_SYMBOL_EYE_OPEN"Dark", 0);
		lv_label_set_text(label, LV_SYMBOL_EYE_OPEN"Dark");
	}
}



/*
 *  函数名：   static void event_handler_switch_themes(lv_obj_t * obj, lv_event_t event)
 *  输入参数： 触发事件的对象
 *  输入参数： 触发的事件类型
 *  返回值：   无
 *  函数作用： 切换主题
*/
static void event_handler_switch_themes(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
	{
        bool theme_mode = true;
        lv_theme_t * theme = lv_theme_default_get();

        if(theme->flags == 1)   theme_mode = false;
        else                    theme_mode = true;

        lv_theme_t * th = lv_theme_default_init(lv_disp_get_default(),  /*Use the DPI, size, etc from this display*/
                                            lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_CYAN),   /*Primary and secondary palette*/
                                            theme_mode,    /*Light or dark mode*/
                                            &lv_font_montserrat_14);

        lv_disp_set_theme(lv_disp_get_default(), th); /*Assign the theme to the display*/

        g_theme_state = theme_mode;
	}
}


/*
 *  函数名：   static void event_handler_back_to_home(lv_obj_t * obj, lv_event_t event)
 *  输入参数： 触发事件的对象
 *  输入参数： 触发的事件类型
 *  返回值：   无
 *  函数作用： 返回桌面事件处理函数
*/
static void event_handler_back_to_home(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
		/* 清除背景 */
        if (bg_setting != NULL)			lv_obj_del(bg_setting);

		/* 清空屏幕并返回桌面 */
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_demo_home(10);
    }
}
