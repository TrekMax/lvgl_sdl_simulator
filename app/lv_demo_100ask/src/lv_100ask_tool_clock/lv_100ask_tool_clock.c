/**
 ******************************************************************************
 * @file    lv_100ask_tool_clock.c
 * @author  百问科技
 * @version V1.2
 * @date    2020-12-12
 * @brief	计算器应用
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
#include <stdio.h>
#include <stdlib.h>
#include "lv_100ask_tool_clock.h"


/**********************
 *  STATIC VARIABLES
 **********************/
static PT_lv_100ask_clock g_pt_lv_100ask_clock;  // 结构体


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_100ask_tool_clock_init(void);										// 界面初始化
//static void lv_100ask_tool_clock_anim(void * indic, int32_t v);	            // 时钟动画
static void lv_100ask_tool_clock_update_timer(lv_timer_t * timer);
static void event_handler_back_to_home(lv_event_t * e);			                	// 返回桌面事件处理函数


/*
 *  函数名：   void lv_100ask_tool_clock(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_tool_clock(void)
{
	g_pt_lv_100ask_clock = (T_lv_100ask_clock *)malloc(sizeof(T_lv_100ask_clock));   // 申请内存

	g_pt_lv_100ask_clock->bg_tool_clock = lv_obj_create(lv_scr_act());
	lv_obj_set_style_radius(g_pt_lv_100ask_clock->bg_tool_clock, 0, 0);
	lv_obj_set_style_pad_all(g_pt_lv_100ask_clock->bg_tool_clock, 0, 0);
	lv_obj_set_size(g_pt_lv_100ask_clock->bg_tool_clock, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_y(g_pt_lv_100ask_clock->bg_tool_clock, 0);


    lv_100ask_tool_clock_init();

    add_title(g_pt_lv_100ask_clock->bg_tool_clock, "CLOCK");
	add_back(g_pt_lv_100ask_clock->bg_tool_clock, event_handler_back_to_home);   // 返回主菜单
}


/*
 *  函数名：   static void lv_100ask_tool_clock_init(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用界面初始化
*/
static void lv_100ask_tool_clock_init(void)
{
    g_pt_lv_100ask_clock->g_gauge_clock = lv_meter_create(g_pt_lv_100ask_clock->bg_tool_clock);
    lv_obj_set_size(g_pt_lv_100ask_clock->g_gauge_clock, 220, 220);
    lv_obj_center(g_pt_lv_100ask_clock->g_gauge_clock);

    /*Create a scale for the second*/
    /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
    lv_meter_scale_t * scale_sec = lv_meter_add_scale(g_pt_lv_100ask_clock->g_gauge_clock);
    lv_meter_set_scale_ticks(g_pt_lv_100ask_clock->g_gauge_clock, scale_sec, 61, 1, 10, lv_palette_main(LV_PALETTE_YELLOW));
    lv_meter_set_scale_range(g_pt_lv_100ask_clock->g_gauge_clock, scale_sec, 0, 60, 360, 270);

    /*Create a scale for the minutes*/
    /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
    lv_meter_scale_t * scale_min = lv_meter_add_scale(g_pt_lv_100ask_clock->g_gauge_clock);
    lv_meter_set_scale_ticks(g_pt_lv_100ask_clock->g_gauge_clock, scale_min, 61, 1, 10, lv_palette_main(LV_PALETTE_BLUE));
    lv_meter_set_scale_range(g_pt_lv_100ask_clock->g_gauge_clock, scale_min, 0, 60, 360, 270);

    /*Create another scale for the hours. It's only visual and contains only major ticks*/
    lv_meter_scale_t * scale_hour = lv_meter_add_scale(g_pt_lv_100ask_clock->g_gauge_clock);
    lv_meter_set_scale_ticks(g_pt_lv_100ask_clock->g_gauge_clock, scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               /*12 ticks*/
    lv_meter_set_scale_major_ticks(g_pt_lv_100ask_clock->g_gauge_clock, scale_hour, 1, 2, 20, lv_color_black(), 10);    /*Every tick is major*/
    lv_meter_set_scale_range(g_pt_lv_100ask_clock->g_gauge_clock, scale_hour, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/

    LV_IMG_DECLARE(img_hand)

    /*Add a the hands from images*/
    g_pt_lv_100ask_clock->indic_sec = lv_meter_add_needle_img(g_pt_lv_100ask_clock->g_gauge_clock, scale_min, &img_hand, 5, 5);
    g_pt_lv_100ask_clock->indic_min = lv_meter_add_needle_img(g_pt_lv_100ask_clock->g_gauge_clock, scale_min, &img_hand, 5, 5);
    g_pt_lv_100ask_clock->indic_hour = lv_meter_add_needle_img(g_pt_lv_100ask_clock->g_gauge_clock, scale_min, &img_hand, 5, 5);

    lv_meter_set_indicator_end_value(g_pt_lv_100ask_clock->g_gauge_clock, g_pt_lv_100ask_clock->indic_sec, 0);
    lv_meter_set_indicator_end_value(g_pt_lv_100ask_clock->g_gauge_clock, g_pt_lv_100ask_clock->indic_min, 0);
    lv_meter_set_indicator_end_value(g_pt_lv_100ask_clock->g_gauge_clock, g_pt_lv_100ask_clock->indic_hour, 0);


    g_pt_lv_100ask_clock->g_label_clock_time = lv_label_create(g_pt_lv_100ask_clock->bg_tool_clock);
    lv_obj_set_style_text_font(g_pt_lv_100ask_clock->g_label_clock_time, &lv_font_montserrat_32, 0);  	// text font
    lv_label_set_text_fmt(g_pt_lv_100ask_clock->g_label_clock_time, "%s:%s:%s", "09", "00", "00");
    lv_obj_align_to(g_pt_lv_100ask_clock->g_label_clock_time, g_pt_lv_100ask_clock->g_gauge_clock, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    g_pt_lv_100ask_clock->timer_handle = lv_timer_create(lv_100ask_tool_clock_update_timer, 1000,  NULL);

}


/*
 *  函数名：   static void lv_100ask_tool_clock_anim(lv_obj_t * obj, lv_anim_value_t value)
 *  输入参数： 动画对象
 *  输入参数： 传递给动画的数据
 *  返回值：   无
 *  函数作用： 更新时分秒、表盘指针位置
*/
//static void lv_100ask_tool_clock_anim(void * indic, int32_t v)
//{
//    lv_meter_set_indicator_end_value(g_pt_lv_100ask_clock->g_gauge_clock, indic, v);
//}

static void lv_100ask_tool_clock_update_timer(lv_timer_t * timer)
{
    static int32_t sec = 0,hours = 48, minutes = 41; // Hours, minutes, seconds

    sec++;

    if (sec >= 60)
    {
        sec = 0;
        minutes++;

        if ((minutes % 12) == 0)
        {
            hours++;
        }
        if (minutes >= 60)
        {
            minutes = 0;
        }
        if (hours >= 60)
        {
            hours = 0;
            minutes = 0;
        }
    }

    lv_meter_set_indicator_end_value(g_pt_lv_100ask_clock->g_gauge_clock, g_pt_lv_100ask_clock->indic_sec, sec);
    lv_meter_set_indicator_end_value(g_pt_lv_100ask_clock->g_gauge_clock, g_pt_lv_100ask_clock->indic_min, minutes);
    lv_meter_set_indicator_end_value(g_pt_lv_100ask_clock->g_gauge_clock, g_pt_lv_100ask_clock->indic_hour, hours);


    char tmpc[32] = {0};
    strcat(tmpc, (hours / 5) >=10 ? "%d:":"0%d:");
    strcat(tmpc, (minutes)   >=10 ? "%d:":"0%d:");
    strcat(tmpc, (sec)     >=10 ? "%d":"0%d");

    lv_label_set_text_fmt(g_pt_lv_100ask_clock->g_label_clock_time, tmpc, (hours / 5), minutes, sec);
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
        //lv_anim_del_all();
		if (g_pt_lv_100ask_clock->timer_handle != NULL)			lv_timer_del(g_pt_lv_100ask_clock->timer_handle);  				// 删除任务

		/* 删除背景 */
        if (g_pt_lv_100ask_clock->bg_tool_clock != NULL)	lv_obj_del(g_pt_lv_100ask_clock->bg_tool_clock);

		/* 释放内存 */
		free(g_pt_lv_100ask_clock);

		/* 清空屏幕，返回桌面 */
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_demo_home(10);
    }
}
