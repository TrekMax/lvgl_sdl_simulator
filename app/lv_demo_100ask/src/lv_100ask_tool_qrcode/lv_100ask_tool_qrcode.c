/**
 ******************************************************************************
 * @file    lv_100ask_tool_qrcode.c
 * @author  百问科技
 * @version V1.2
 * @date    2020-12-12
 * @brief   二维码创建工具
 ******************************************************************************
 * Change Logs:
 * Date           Author          Notes
 * 2020-12-12     zhouyuebiao     First version
 * 2021-01-25     zhouyuebiao     V1.2
 * 2023-07-10     zhouyuebiao     V1.3(DShanMCU-RA6M5)
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
#include "lv_100ask_tool_qrcode.h"


static PT_lv_100ask_qrcode g_pt_lv_100ask_qrcode;  // 结构体


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_100ask_tool_qrcode_init(void);                         // 界面初始化
static void event_handler_ta_cb(lv_event_t * e);                // 文本框输入触发事件处理函数
static void event_handler_kb_cb(lv_event_t * e);                // 键盘事件处理函数
static void event_handler_back_to_home(lv_event_t * e); // 返回桌面事件处理函数


/*
 *  函数名：   void lv_100ask_tool_qrcode(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_tool_qrcode(void)
{
    g_pt_lv_100ask_qrcode = (T_lv_100ask_qrcode *)malloc(sizeof(T_lv_100ask_qrcode));   // 申请内存

    g_pt_lv_100ask_qrcode->bg = lv_obj_create(lv_scr_act());
    lv_obj_set_style_radius(g_pt_lv_100ask_qrcode->bg, 0, 0);
    lv_obj_set_style_pad_all(g_pt_lv_100ask_qrcode->bg, 0, 0);
    lv_obj_set_size(g_pt_lv_100ask_qrcode->bg, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_y(g_pt_lv_100ask_qrcode->bg, 0);

    lv_100ask_tool_qrcode_init();

    add_title(g_pt_lv_100ask_qrcode->bg, "QRCODE");
    add_back(g_pt_lv_100ask_qrcode->bg, event_handler_back_to_home);   // 返回桌面按钮
}



/*
 *  函数名：   static void lv_100ask_tool_qrcode_init(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用界面初始化
*/
static void lv_100ask_tool_qrcode_init(void)
{

    /* 创建二维码展示框 */
    const char * qr_website_str = "https://www.100ask.net";
    const char * qr_wechat_str = "http://weixin.qq.com/r/M0hvd2-EwjK9rSsU9x0h";
    const char * qr_100ask_lvgl_str = "http://lvgl.100ask.net";
    /*Create a 100x100 QR code*/
    g_pt_lv_100ask_qrcode->qr_input = lv_qrcode_create(g_pt_lv_100ask_qrcode->bg, LV_100ASK_QRCODE_SIZE, lv_color_hex3(0x33f), lv_color_hex3(0xeef));
    /*Set data*/
    lv_qrcode_update(g_pt_lv_100ask_qrcode->qr_input, qr_website_str, strlen(qr_website_str));
    lv_obj_align(g_pt_lv_100ask_qrcode->qr_input, LV_ALIGN_TOP_MID, 0, LV_100ASK_QRCODE_SIZE - 30);  // 摆放位置


    // 创建文本输入框
    g_pt_lv_100ask_qrcode->ta_content = lv_textarea_create(g_pt_lv_100ask_qrcode->bg);
    lv_obj_set_size(g_pt_lv_100ask_qrcode->ta_content, LV_HOR_RES - 10, 80);
    lv_obj_set_style_text_font(g_pt_lv_100ask_qrcode->ta_content, &lv_font_montserrat_14, 0);  // text font
    //lv_obj_set_style_value_str(g_pt_lv_100ask_qrcode->ta_content, "https://www.100ask.net", 0);    // 设置字符
    //lv_obj_set_style_opa(g_pt_lv_100ask_qrcode->ta_content, 0, 0);       // 设置字符透明度
    lv_obj_set_style_radius(g_pt_lv_100ask_qrcode->ta_content, 0, 0); // 设置圆角
    //lv_cont_set_fit2(g_pt_lv_100ask_qrcode->ta_content, LV_FIT_PARENT, LV_FIT_NONE);
    lv_textarea_set_text(g_pt_lv_100ask_qrcode->ta_content, "");
    lv_textarea_set_placeholder_text(g_pt_lv_100ask_qrcode->ta_content, "https://www.100ask.net");
    //lv_textarea_set_cursor_hidden(g_pt_lv_100ask_qrcode->ta_content, true);
    lv_obj_set_style_anim_time(g_pt_lv_100ask_qrcode->ta_content, 0, LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_align_to(g_pt_lv_100ask_qrcode->ta_content, g_pt_lv_100ask_qrcode->qr_input, LV_ALIGN_OUT_BOTTOM_MID, 0, 15);  // 摆放位置

    /* 下面的仅仅是一些展示信息 */
    /* 展示公司信息 */
    /* LOGO */
    LV_IMG_DECLARE(img_lv_100ask_demo_logo);
    lv_obj_t * logo = lv_img_create(g_pt_lv_100ask_qrcode->bg);
    lv_img_set_src(logo, &img_lv_100ask_demo_logo);
    lv_obj_align_to(logo, g_pt_lv_100ask_qrcode->ta_content,  LV_ALIGN_OUT_BOTTOM_LEFT, 20, 30);  //(lv_obj_get_width(logo)/4)


    /* 公司网站信息 */
    lv_obj_t * label_logo = lv_label_create(g_pt_lv_100ask_qrcode->bg);
    lv_obj_set_style_text_font(label_logo, &lv_font_montserrat_14, 0);             // 设置文字大小                        // 设置色彩透明度
    lv_label_set_text(label_logo,  "https://www.100ask.net\nhttp://lvgl.100ask.net");
    lv_obj_align_to(label_logo, logo, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    /* 公司二维码信息 */
    /* 官网 */
    lv_obj_t * label_info1 = lv_label_create(g_pt_lv_100ask_qrcode->bg);
    lv_obj_set_style_text_font(label_info1, &lv_font_montserrat_10, 0);
    lv_label_set_text(label_info1, "100ASK");
    lv_obj_refr_size(label_info1);

    /*Create a 100x100 QR code*/
    g_pt_lv_100ask_qrcode->qr_official_website = lv_qrcode_create(g_pt_lv_100ask_qrcode->bg, LV_100ASK_QRCODE_AD_SIZE, lv_color_hex3(0x008), lv_color_hex3(0xeef));
    /*Set data*/
    lv_qrcode_update(g_pt_lv_100ask_qrcode->qr_official_website, qr_website_str, strlen(qr_website_str));
    ///lv_obj_align_to(g_pt_lv_100ask_qrcode->qr_official_website, label_logo, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);  // 摆放位置
    lv_obj_align(g_pt_lv_100ask_qrcode->qr_official_website, LV_ALIGN_BOTTOM_LEFT, (LV_100ASK_QRCODE_SPACE + (LV_100ASK_QRCODE_SIZE * 0)), -lv_obj_get_height(label_info1) - 5);  // 摆放位置
    lv_obj_align_to(label_info1, g_pt_lv_100ask_qrcode->qr_official_website, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

     /* 微信公众号 */
    lv_obj_t * label_info2 = lv_label_create(g_pt_lv_100ask_qrcode->bg);
    lv_obj_set_style_text_font(label_info2, &lv_font_montserrat_10, 0);
    lv_label_set_text(label_info2, "WeChat");
    lv_obj_refr_size(label_info2);


    /*Create a 100x100 QR code*/
    g_pt_lv_100ask_qrcode->qr_wechat = lv_qrcode_create(g_pt_lv_100ask_qrcode->bg, LV_100ASK_QRCODE_AD_SIZE, lv_color_hex3(0x008), lv_color_hex3(0xeef));
    /*Set data*/
    lv_qrcode_update(g_pt_lv_100ask_qrcode->qr_wechat, qr_wechat_str, strlen(qr_wechat_str));
    lv_obj_align(g_pt_lv_100ask_qrcode->qr_wechat, LV_ALIGN_BOTTOM_LEFT, (LV_100ASK_QRCODE_SPACE + (LV_100ASK_QRCODE_SIZE * 1)), -lv_obj_get_height(label_info2) - 5);  // 摆放位置
    lv_obj_align_to(label_info2, g_pt_lv_100ask_qrcode->qr_wechat, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

     /* 100ASK LVGL */
    lv_obj_t * label_info3 = lv_label_create(g_pt_lv_100ask_qrcode->bg);
    lv_obj_set_style_text_font(label_info3, &lv_font_montserrat_10, 0);
    lv_label_set_text(label_info3, "100ASK LVGL");
    lv_obj_refr_size(label_info3);


    /*Create a 100x100 QR code*/
    g_pt_lv_100ask_qrcode->qr_100ask_lvgl = lv_qrcode_create(g_pt_lv_100ask_qrcode->bg, LV_100ASK_QRCODE_AD_SIZE, lv_color_hex3(0x008), lv_color_hex3(0xeef));
    /*Set data*/
    lv_qrcode_update(g_pt_lv_100ask_qrcode->qr_100ask_lvgl, qr_100ask_lvgl_str, strlen(qr_100ask_lvgl_str));
    lv_obj_align(g_pt_lv_100ask_qrcode->qr_100ask_lvgl, LV_ALIGN_BOTTOM_LEFT, (LV_100ASK_QRCODE_SPACE + (LV_100ASK_QRCODE_SIZE * 2)), -lv_obj_get_height(label_info3) - 5);  // 摆放位置
    lv_obj_align_to(label_info3, g_pt_lv_100ask_qrcode->qr_100ask_lvgl, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

     //  创建键盘
    g_pt_lv_100ask_qrcode->keyboard = lv_keyboard_create(g_pt_lv_100ask_qrcode->bg);
    lv_keyboard_set_textarea(g_pt_lv_100ask_qrcode->keyboard, g_pt_lv_100ask_qrcode->ta_content);
    lv_obj_add_flag(g_pt_lv_100ask_qrcode->keyboard, LV_OBJ_FLAG_HIDDEN);    // 标志为隐藏对象(使对象隐藏，就像它根本不存在一样)
    lv_obj_add_event_cb(g_pt_lv_100ask_qrcode->ta_content, event_handler_ta_cb, LV_EVENT_ALL, g_pt_lv_100ask_qrcode->keyboard);
}


/*
 *  函数名：   static void event_handler_ta_cb(lv_obj_t * ta, lv_event_t e)
 *  输入参数： 触发事件的文本输入框对象
 *  输入参数： 触发的事件类型
 *  返回值：   无
 *  函数作用： 初始化键盘
*/
static void event_handler_ta_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    lv_obj_t * kb = lv_event_get_user_data(e);

    if(code == LV_EVENT_CLICKED || code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
        //lv_obj_set_y(g_pt_lv_100ask_qrcode->bg, -((lv_obj_get_height(ta)/2)));
        //lv_obj_update_layout(g_pt_lv_100ask_qrcode->bg);
    }
    else if(code == LV_EVENT_VALUE_CHANGED)
    {
        const char * str_buffer = lv_textarea_get_text(ta);  // 获取输入内容
        //printf("str_buffer: %s\n\r", str_buffer);

        /*Set data*/
        lv_qrcode_update(g_pt_lv_100ask_qrcode->qr_input, str_buffer, strlen(str_buffer));
    }
    else if(code == LV_EVENT_DEFOCUSED || code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
    {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        //lv_obj_set_y(g_pt_lv_100ask_qrcode->bg, 0);
        //lv_obj_update_layout(g_pt_lv_100ask_qrcode->bg);
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
        if (g_pt_lv_100ask_qrcode->qr_input != NULL)                lv_qrcode_delete(g_pt_lv_100ask_qrcode->qr_input);              // 删除二维码
        if (g_pt_lv_100ask_qrcode->qr_official_website != NULL)     lv_qrcode_delete(g_pt_lv_100ask_qrcode->qr_official_website);   // 删除二维码
        if (g_pt_lv_100ask_qrcode->qr_wechat != NULL)               lv_qrcode_delete(g_pt_lv_100ask_qrcode->qr_wechat);             // 删除二维码
        if (g_pt_lv_100ask_qrcode->qr_100ask_lvgl != NULL)          lv_qrcode_delete(g_pt_lv_100ask_qrcode->qr_100ask_lvgl);        // 删除二维码
        if (g_pt_lv_100ask_qrcode->ta_content != NULL)              lv_obj_del(g_pt_lv_100ask_qrcode->ta_content);                  // 删除文本输入框
        if (g_pt_lv_100ask_qrcode->bg != NULL)                      lv_obj_del(g_pt_lv_100ask_qrcode->bg);                          // 删除背景

        /* 释放内存 */
        free(g_pt_lv_100ask_qrcode);

        /* 清空屏幕，返回桌面 */
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_demo_home(10);
    }
}
