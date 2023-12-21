/**
 ******************************************************************************
 * @file    lv_100ask_board_about.c
 * @author  百问科技
 * @version V1.2
 * @date    2020-12-12
 * @brief   关于
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
#include "lv_100ask_board_about.h"

/**********************
 *  STATIC VARIABLES
 **********************/
static PT_lv_100ask_about g_pt_lv_100ask_about;  // 数据结构体


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_100ask_board_about_init(void);                         // 界面初始化
static void draw_table_part_event_cb(lv_event_t * e);
static void lv_task_100ask_aboutus(lv_timer_t  * task);                         // 获取CPU使用率任务
static void event_handler_back_to_home(lv_event_t * e); // 返回桌面事件处理函数


/*
 *  函数名：   void lv_100ask_board_about(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_board_about(void)
{
    g_pt_lv_100ask_about = (T_lv_100ask_about *)malloc(sizeof(T_lv_100ask_about));   // 申请内存

    g_pt_lv_100ask_about->bg_about = lv_obj_create(lv_scr_act());
    lv_obj_clear_flag(g_pt_lv_100ask_about->bg_about, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(g_pt_lv_100ask_about->bg_about, 0, 0);
    lv_obj_set_style_pad_all(g_pt_lv_100ask_about->bg_about, 0, 0);
    lv_obj_set_size(g_pt_lv_100ask_about->bg_about, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_y(g_pt_lv_100ask_about->bg_about, 0);

    lv_100ask_board_about_init();

    g_pt_lv_100ask_about->task_handle = lv_timer_create(lv_task_100ask_aboutus, 500, NULL);

    add_title(g_pt_lv_100ask_about->bg_about, "ABOUTUS");
    add_back(g_pt_lv_100ask_about->bg_about, event_handler_back_to_home);
}


/*
 *  函数名：   static void lv_100ask_board_about_init(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用界面初始化
*/
static void lv_100ask_board_about_init(void)
{
    g_pt_lv_100ask_about->about_table = lv_table_create(g_pt_lv_100ask_about->bg_about);
    lv_obj_set_style_pad_all(g_pt_lv_100ask_about->about_table, 6, LV_PART_ITEMS);
    lv_obj_set_style_pad_ver(g_pt_lv_100ask_about->about_table, 7, LV_PART_ITEMS);
    lv_table_set_col_cnt(g_pt_lv_100ask_about->about_table, 2);
    lv_table_set_row_cnt(g_pt_lv_100ask_about->about_table, 9);
    lv_table_set_col_width(g_pt_lv_100ask_about->about_table, 0, (LV_100ASK_ABOUT_US_TABLE_SPACE * 2));
    lv_table_set_col_width(g_pt_lv_100ask_about->about_table, 1, (LV_100ASK_ABOUT_US_TABLE_SPACE * 4));
    lv_obj_align(g_pt_lv_100ask_about->about_table, LV_ALIGN_TOP_MID, 0, LV_100ASK_ABOUT_US_TITLE_SPACE);

    /*Make the cells of the first row center aligned */
    ///lv_table_set_cell_align(g_pt_lv_100ask_about->about_table, 0, 0, LV_LABEL_ALIGN_LEFT);
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 0, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);

    /*Align the price values to the right in the 2nd column*/
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 1, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 2, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 3, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 4, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 5, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 6, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 7, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);
    lv_table_add_cell_ctrl(g_pt_lv_100ask_about->about_table, 8, 1, LV_TABLE_CELL_CTRL_MERGE_RIGHT);

    ///lv_table_set_cell_type(g_pt_lv_100ask_about->about_table, 0, 0, 2);
    ///lv_table_set_cell_type(g_pt_lv_100ask_about->about_table, 0, 1, 2);

    /*Fill the first column*/
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 0, 0, "Name");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 1, 0, "Version");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 2, 0, "Board Name");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 3, 0, "Producer");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 4, 0, "Core");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 5, 0, "RAM");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 6, 0, "Flash");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 7, 0, "SD card");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 8, 0, "CPU Usage");

    /*Fill the second column*/
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 0, 1, "100ASK");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 1, 1, "V1.3");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 2, 1, "DShanMCU-RA6M5");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 3, 1, "https://www.100ask.net");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 4, 1, "200MHz Arm® Cortex®-M33");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 5, 1, "512KB");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 6, 1, "1024KB");
    //lv_table_set_cell_value_fmt(g_pt_lv_100ask_about->about_table, 7, 1, "%d MB free total %d MB", 0, 0);
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 7, 1, "No Detect");
    lv_table_set_cell_value(g_pt_lv_100ask_about->about_table, 8, 1, "0%");

    lv_obj_add_event_cb(g_pt_lv_100ask_about->about_table, draw_table_part_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

    /* 下面的仅仅是一些展示信息 */
    /* 展示公司信息 */
    /* LOGO */
    LV_IMG_DECLARE(img_lv_100ask_demo_logo);
    lv_obj_t * logo = lv_img_create(g_pt_lv_100ask_about->bg_about);
    lv_img_set_src(logo, &img_lv_100ask_demo_logo);
    lv_obj_align_to(logo, g_pt_lv_100ask_about->about_table, LV_ALIGN_OUT_BOTTOM_LEFT, 5, 0);  //(lv_obj_get_width(logo)/4)


    /* 公司网站信息 */
    lv_obj_t * label_logo = lv_label_create(g_pt_lv_100ask_about->bg_about);
    lv_obj_set_style_text_font(label_logo, &lv_font_montserrat_14, 0);             // 设置文字大小
    lv_label_set_text(label_logo,  "https://www.100ask.net\nhttp://www.lvgl.100ask.net");
    lv_obj_align_to(label_logo, logo, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    /* 公司二维码信息 */
    /* 官网 */
    lv_obj_t * label_info1 = lv_label_create(g_pt_lv_100ask_about->bg_about);
    lv_obj_set_style_text_font(label_info1, &lv_font_montserrat_10, 0);
    lv_label_set_text(label_info1, "100ASK");
    lv_obj_refr_size(label_info1);

    /*Create a 100x100 QR code*/
    g_pt_lv_100ask_about->qr_official_website = lv_qrcode_create(g_pt_lv_100ask_about->bg_about, LV_100ASK_QRCODE_AD_SIZE, lv_color_hex3(0x008), lv_color_hex3(0xeef));
    /*Set data*/
    lv_qrcode_update(g_pt_lv_100ask_about->qr_official_website, "https://www.100ask.net", strlen("https://www.100ask.net"));
    lv_obj_align(g_pt_lv_100ask_about->qr_official_website, LV_ALIGN_BOTTOM_LEFT, (LV_100ASK_QRCODE_SPACE + (LV_100ASK_QRCODE_SIZE * 0)), -lv_obj_get_height(label_info1));  // 摆放位置
    lv_obj_align_to(label_info1, g_pt_lv_100ask_about->qr_official_website, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

     /* 微信公众号 */
    lv_obj_t * label_info2 = lv_label_create(g_pt_lv_100ask_about->bg_about);
    lv_obj_set_style_text_font(label_info2, &lv_font_montserrat_10, 0);
    lv_label_set_text(label_info2, "WeChat");
    lv_obj_refr_size(label_info2);

    /*Create a 100x100 QR code*/
    g_pt_lv_100ask_about->qr_wechat = lv_qrcode_create(g_pt_lv_100ask_about->bg_about, LV_100ASK_QRCODE_AD_SIZE, lv_color_hex3(0x008), lv_color_hex3(0xeef));
    /*Set data*/
    lv_qrcode_update(g_pt_lv_100ask_about->qr_wechat, "http://weixin.qq.com/r/M0hvd2-EwjK9rSsU9x0h", strlen("http://weixin.qq.com/r/M0hvd2-EwjK9rSsU9x0h"));
    lv_obj_align(g_pt_lv_100ask_about->qr_wechat, LV_ALIGN_BOTTOM_LEFT, (LV_100ASK_QRCODE_SPACE + (LV_100ASK_QRCODE_SIZE * 1)), -lv_obj_get_height(label_info2));  // 摆放位置
    lv_obj_align_to(label_info2, g_pt_lv_100ask_about->qr_wechat, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

     /* 100ASK LVGL */
    lv_obj_t * label_info3 = lv_label_create(g_pt_lv_100ask_about->bg_about);
    lv_obj_set_style_text_font(label_info3, &lv_font_montserrat_10, 0);
    lv_label_set_text(label_info3, "100ASK LVGL");
    lv_obj_refr_size(label_info3);


    /*Create a 100x100 QR code*/
    g_pt_lv_100ask_about->qr_100ask_lvgl = lv_qrcode_create(g_pt_lv_100ask_about->bg_about, LV_100ASK_QRCODE_AD_SIZE, lv_color_hex3(0x008), lv_color_hex3(0xeef));
    /*Set data*/
    lv_qrcode_update(g_pt_lv_100ask_about->qr_100ask_lvgl, "http://lvgl.100ask.net", strlen("http://lvgl.100ask.net"));
    lv_obj_align(g_pt_lv_100ask_about->qr_100ask_lvgl, LV_ALIGN_BOTTOM_LEFT, (LV_100ASK_QRCODE_SPACE + (LV_100ASK_QRCODE_SIZE * 2)), -lv_obj_get_height(label_info3));  // 摆放位置
    lv_obj_align_to(label_info3, g_pt_lv_100ask_about->qr_100ask_lvgl, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

static void draw_table_part_event_cb(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
    /*If the cells are drawn...*/
    if(dsc->part == LV_PART_ITEMS) {
        uint32_t row = dsc->id /  lv_table_get_col_cnt(obj);
        uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);

        /*In the first column align the texts to the right*/
        if(col == 0) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_LEFT;
        }
        else if(col == 1) {
            dsc->label_dsc->align = LV_TEXT_ALIGN_RIGHT;
        }
    }
}

/*
 *  函数名：   static void lv_task_100ask_aboutus(lv_timer_t * task)
 *  输入参数： 任务描述符
 *  返回值：   无
 *  函数作用： 获取CPU使用率
*/
static void lv_task_100ask_aboutus(lv_timer_t * task)
{
    lv_table_set_cell_value_fmt(g_pt_lv_100ask_about->about_table, 8, 1, "%d%%", (100 - lv_timer_get_idle()));
}



/*
 *  函数名：   static void event_handler_back_to_home(lv_timer_t * task)
 *  输入参数： 触发事件的对象
 *  输入参数： 触发的事件类型
 *  返回值：   无
 *  函数作用： 返回桌面事件处理函数
*/
//static void event_handler_back_to_home(lv_obj_t * obj, lv_event_t event)
static void event_handler_back_to_home(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        if (g_pt_lv_100ask_about->task_handle != NULL)          lv_timer_del(g_pt_lv_100ask_about->task_handle);                // 删除任务
        if (g_pt_lv_100ask_about->qr_official_website != NULL)  lv_qrcode_delete(g_pt_lv_100ask_about->qr_official_website);    // 删除二维码
        if (g_pt_lv_100ask_about->qr_wechat != NULL)            lv_qrcode_delete(g_pt_lv_100ask_about->qr_wechat);              // 删除二维码
        if (g_pt_lv_100ask_about->qr_100ask_lvgl != NULL)       lv_qrcode_delete(g_pt_lv_100ask_about->qr_100ask_lvgl);         // 删除二维码
        if (g_pt_lv_100ask_about->about_table != NULL)          lv_obj_del(g_pt_lv_100ask_about->about_table);                  // 删除表格
        if (g_pt_lv_100ask_about->bg_about != NULL)             lv_obj_del(g_pt_lv_100ask_about->bg_about);                     // 删除背景

        /* 释放内存 */
        free(g_pt_lv_100ask_about);

        /* 清空屏幕，返回桌面 */
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_demo_home(100);
    }
}
