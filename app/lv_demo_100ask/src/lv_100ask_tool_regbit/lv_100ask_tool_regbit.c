/**
 ******************************************************************************
 * @file    lv_100ask_tool_regbit.c
 * @author  百问科技
 * @version V1.2
 * @date    2020-12-12
 * @brief   寄存器位查看计算工具
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
#include "lv_100ask_tool_regbit.h"


/**********************
 *  STATIC VARIABLES
 **********************/
static PT_lv_100ask_regbit g_pt_lv_100ask_regbit;  // 数据结构体


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void lv_100ask_tool_regbit_init(void);                             // 界面初始化
static int lv_100ask_tool_regbit_atoi(const char *str);                   // 字符串转换成整型数
static char * lv_100ask_tool_regbit_dec_to_bin(unsigned long dec);        // 十进制转为二进制
static long lv_100ask_tool_regbit_bin_to_dec(const char *pbin);           // 二进制转为十进制
static int lv_100ask_tool_regbit_hex_to_dec(char hexVal[]);               // 十六进制转为十进制
static void lv_100ask_tool_regbit_str_reverse(char str[]);                // 反转字符串
static char * lv_100ask_tool_regbit_get_index_str(int index);             // 获取索引字符串
static void lv_100ask_tool_regbit_update_regbit(bool flag);               // 更新寄存器内容
static void event_handler_ta_cb(lv_event_t * e);                    // 文本框输入触发事件处理函数
static void event_handler_regbit_map(lv_event_t * e);           // 位按键响应事件处理函数，定位到当前选中的位按钮
static void event_handler_kb_cb(lv_event_t * e);                    // 键盘事件处理函数
static void event_handler_back_to_home(lv_event_t * e);     // 返回桌面事件处理函数


/*
 *  函数名：   void lv_100ask_tool_regbit(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用初始化入口
*/
void lv_100ask_tool_regbit(void)
{
    g_pt_lv_100ask_regbit = (T_lv_100ask_regbit *)malloc(sizeof(T_lv_100ask_regbit));   // 申请内存
    lv_snprintf(g_pt_lv_100ask_regbit->regbit_flag, sizeof(g_pt_lv_100ask_regbit->regbit_flag), "00000000000000000000000000000000");

    g_pt_lv_100ask_regbit->bg = lv_obj_create(lv_scr_act());
    lv_obj_set_style_radius(g_pt_lv_100ask_regbit->bg, 0, 0);
    lv_obj_set_style_pad_all(g_pt_lv_100ask_regbit->bg, 0, 0);
    lv_obj_set_size(g_pt_lv_100ask_regbit->bg, LV_HOR_RES, LV_VER_RES);
    //lv_obj_set_y(g_pt_lv_100ask_regbit->bg, 0);

    g_pt_lv_100ask_regbit->kb = NULL;
    lv_100ask_tool_regbit_init();     // 初始化界面

    add_title(g_pt_lv_100ask_regbit->bg, "REGBIT");
    add_back(g_pt_lv_100ask_regbit->bg, event_handler_back_to_home);   // 返回桌面按钮
}


/*
 *  函数名：   static void lv_100ask_tool_regbit_init(void)
 *  输入参数： 无
 *  返回值：   无
 *  函数作用： 应用界面初始化
*/
static void lv_100ask_tool_regbit_init(void)
{
    lv_obj_t * obj_show_index;      // 位按钮编号
    lv_obj_t * label_index;             // 位状态指示

    lv_coord_t row = LV_100ASK_OBJ_BIT_H + LV_100ASK_OBJ_BIT_SHOW_INDEX_H + (LV_100ASK_OBJ_BIT_SHOW_INDEX_H * 7);   // 行
    int col = 0;   // 列
    for (int i = 0 ; i < LV_100ASK_OBJ_BIT_COUNT; i++)
    {
        if (i == 16)
        {
            row = LV_100ASK_OBJ_BIT_SHOW_INDEX_H * 6;
            col = 0;
        }
        // 位按钮编号
        obj_show_index = lv_obj_create(g_pt_lv_100ask_regbit->bg);                                                                      // 创建obj对象
        lv_obj_remove_style_all(obj_show_index);
        lv_obj_set_size(obj_show_index, LV_100ASK_OBJ_BIT_W, LV_100ASK_OBJ_BIT_SHOW_INDEX_H);                                                   // 设置对象大小(宽度和高度)
        //lv_obj_clear_flag(obj_show_index, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_bg_opa(obj_show_index, LV_OPA_COVER, 0);               // 设置颜色
        lv_obj_set_style_bg_color(obj_show_index, LV_100ASK_OBJ_BIT_SHOW_INDEX_COLOR, 0);               // 设置颜色
        lv_obj_set_style_text_font(obj_show_index, &lv_font_montserrat_10, 0);
        lv_obj_set_style_text_color(obj_show_index, lv_color_hex(0xffffff), 0);                                 // 设置字符
        lv_obj_align(obj_show_index, LV_ALIGN_TOP_RIGHT, -(LV_100ASK_OBJ_BIT_ROW_SPACE*(col++)+3), row);                                // 设置摆放位置

        label_index  = lv_label_create(obj_show_index);     /* 创建标签 */
        lv_label_set_text(label_index, lv_100ask_tool_regbit_get_index_str(i));
        lv_obj_center(label_index);                         /* 当前画布居中 */

        // 位按钮
        g_pt_lv_100ask_regbit->regbit_obj[i] = lv_btn_create(g_pt_lv_100ask_regbit->bg);                                                    // 创建按钮对象
        lv_obj_set_size(g_pt_lv_100ask_regbit->regbit_obj[i], LV_100ASK_OBJ_BIT_W, LV_100ASK_OBJ_BIT_H);                                        // 设置对象大小(宽度和高度)
        //lv_obj_add_flag(g_pt_lv_100ask_regbit->regbit_obj[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_set_style_radius(g_pt_lv_100ask_regbit->regbit_obj[i], 0, 0);                            // 设置圆角
        lv_obj_set_style_bg_color(g_pt_lv_100ask_regbit->regbit_obj[i], LV_100ASK_OBJ_BIT_COLOR, 0);    // 设置颜色
        lv_obj_set_style_text_font(g_pt_lv_100ask_regbit->regbit_obj[i], &lv_font_montserrat_10, 0);    // 设置数值字体格式
        lv_obj_set_style_border_side(g_pt_lv_100ask_regbit->regbit_obj[i], 0, 0);                       // 设置边界宽度
        lv_obj_set_style_text_color(g_pt_lv_100ask_regbit->regbit_obj[i], lv_color_hex(0xffffff), 0);           // 设置字符
        lv_obj_align_to(g_pt_lv_100ask_regbit->regbit_obj[i], obj_show_index, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);                                   // 设置摆放位置
        lv_obj_add_event_cb(g_pt_lv_100ask_regbit->regbit_obj[i], event_handler_regbit_map, LV_EVENT_CLICKED, label_index);                                // 分配点击事件处理函数

        /* 数字 */
        lv_obj_t * label = lv_label_create(g_pt_lv_100ask_regbit->regbit_obj[i]);   /* 创建标签 */
        lv_label_set_text(label, "0");
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);                         /* 当前画布居中 */
    }

    // 二进制
    g_pt_lv_100ask_regbit->ta_bin = lv_textarea_create(g_pt_lv_100ask_regbit->bg);
    lv_textarea_set_accepted_chars(g_pt_lv_100ask_regbit->ta_bin, "01");                                                            // 设置字符列表，文本区域只接受这些字符
    lv_obj_set_width(g_pt_lv_100ask_regbit->ta_bin, LV_HOR_RES - 20);
    lv_obj_set_style_text_font(g_pt_lv_100ask_regbit->ta_bin, &lv_font_montserrat_14, 0);   // 设置数值字体格式
    //lv_obj_set_style_value_str(g_pt_lv_100ask_regbit->ta_bin, "bin", 0);                      // 设置字符
    //lv_obj_set_style_opa(g_pt_lv_100ask_regbit->ta_bin, 0, 0);                        // 设置字符透明度
    lv_obj_set_style_radius(g_pt_lv_100ask_regbit->ta_bin, 0, 0);                           // 设置圆角
    //lv_cont_set_fit2(g_pt_lv_100ask_regbit->ta_bin, LV_FIT_PARENT, LV_FIT_NONE);
    lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_bin, "");
    lv_textarea_set_placeholder_text(g_pt_lv_100ask_regbit->ta_bin, "Binary");
    lv_textarea_set_one_line(g_pt_lv_100ask_regbit->ta_bin, true);
    //lv_obj_set_style_anim_time(g_pt_lv_100ask_regbit->ta_bin, 0, LV_PART_CURSOR | LV_STATE_FOCUSED);
    //lv_obj_add_event_cb(g_pt_lv_100ask_regbit->ta_bin, event_handler_ta_cb, LV_EVENT_ALL, NULL);
    lv_obj_align(g_pt_lv_100ask_regbit->ta_bin, LV_ALIGN_TOP_MID, 0, (LV_100ASK_OBJ_BIT_H + LV_100ASK_OBJ_BIT_SHOW_INDEX_H + (LV_100ASK_OBJ_BIT_SHOW_INDEX_H * 14)));  // 摆放位置

    // 十进制
    g_pt_lv_100ask_regbit->ta_dec = lv_textarea_create(g_pt_lv_100ask_regbit->bg);
    lv_obj_set_width(g_pt_lv_100ask_regbit->ta_dec, LV_HOR_RES - 20);
    lv_textarea_set_accepted_chars(g_pt_lv_100ask_regbit->ta_dec, "0123456789");                                                    // 设置字符列表，文本区域只接受这些字符
    lv_obj_set_style_text_font(g_pt_lv_100ask_regbit->ta_dec, &lv_font_montserrat_14, 0);   // 设置文本字体格式
    //lv_obj_set_style_value_str(g_pt_lv_100ask_regbit->ta_dec, "dec", 0);                      // 设置字符
    //lv_obj_set_style_opa(g_pt_lv_100ask_regbit->ta_dec, 0, 0);                        // 设置字符透明度
    lv_obj_set_style_radius(g_pt_lv_100ask_regbit->ta_dec, 0, 0);                           // 设置圆角
    //lv_cont_set_fit2(g_pt_lv_100ask_regbit->ta_dec, LV_FIT_PARENT, LV_FIT_NONE);
    lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_dec, "");
    lv_textarea_set_placeholder_text(g_pt_lv_100ask_regbit->ta_dec, "Decimal system");
    lv_textarea_set_one_line(g_pt_lv_100ask_regbit->ta_dec, g_pt_lv_100ask_regbit->ta_dec);
    ///lv_textarea_set_cursor_hidden(g_pt_lv_100ask_regbit->ta_dec, true);
    //lv_obj_set_style_anim_time(g_pt_lv_100ask_regbit->ta_dec, 0, LV_PART_CURSOR | LV_STATE_FOCUSED);
    //lv_obj_set_event_cb(g_pt_lv_100ask_regbit->ta_dec, event_handler_ta_cb);
    //lv_obj_add_event_cb(g_pt_lv_100ask_regbit->ta_dec, event_handler_ta_cb, LV_EVENT_ALL, NULL);
    lv_obj_align_to(g_pt_lv_100ask_regbit->ta_dec, g_pt_lv_100ask_regbit->ta_bin, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);  // 摆放位置

    // 十六进制
    g_pt_lv_100ask_regbit->ta_hex = lv_textarea_create(g_pt_lv_100ask_regbit->bg);
    lv_obj_set_width(g_pt_lv_100ask_regbit->ta_hex, LV_HOR_RES - 20);
    lv_textarea_set_accepted_chars(g_pt_lv_100ask_regbit->ta_hex, "0123456789ABCDEFabcdef");                                        // 设置字符列表，文本区域只接受这些字符
    lv_obj_set_style_text_font(g_pt_lv_100ask_regbit->ta_hex, &lv_font_montserrat_14, 0);   // 设置文本字体格式
    //lv_obj_set_style_value_str(g_pt_lv_100ask_regbit->ta_hex, "hex", 0);                      // 设置字符
    //lv_obj_set_style_opa(g_pt_lv_100ask_regbit->ta_hex, 0, 0);                        // 设置字符透明度
    lv_obj_set_style_radius(g_pt_lv_100ask_regbit->ta_hex, 0, 0);                           // 设置圆角
    ///lv_cont_set_fit2(g_pt_lv_100ask_regbit->ta_hex, LV_FIT_PARENT, LV_FIT_NONE);
    lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_hex, "");
    lv_textarea_set_placeholder_text(g_pt_lv_100ask_regbit->ta_hex, "Hexadecimal");
    lv_textarea_set_one_line(g_pt_lv_100ask_regbit->ta_hex, true);
    //lv_textarea_set_cursor_hidden(g_pt_lv_100ask_regbit->ta_hex, true);
    //lv_obj_set_style_anim_time(g_pt_lv_100ask_regbit->ta_hex, 0, LV_PART_CURSOR | LV_STATE_FOCUSED);
    //lv_obj_set_event_cb(g_pt_lv_100ask_regbit->ta_hex, event_handler_ta_cb);
    //lv_obj_add_event_cb(g_pt_lv_100ask_regbit->ta_hex, event_handler_ta_cb, LV_EVENT_ALL, NULL);
    lv_obj_align_to(g_pt_lv_100ask_regbit->ta_hex, g_pt_lv_100ask_regbit->ta_dec, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);  // 摆放位置

#if 0
    lv_obj_t * label_ta_flag;
    label_ta_flag = lv_label_create(g_pt_lv_100ask_regbit->ta_bin);
    lv_label_set_text(label_ta_flag, "bin");
    lv_obj_add_flag(label_ta_flag, LV_OBJ_FLAG_HIDDEN);

    label_ta_flag = lv_label_create(g_pt_lv_100ask_regbit->ta_dec);
    lv_label_set_text(label_ta_flag, "dec");
    lv_obj_add_flag(label_ta_flag, LV_OBJ_FLAG_HIDDEN);

    label_ta_flag = lv_label_create(g_pt_lv_100ask_regbit->ta_hex);
    lv_label_set_text(label_ta_flag, "hex");
    lv_obj_add_flag(label_ta_flag, LV_OBJ_FLAG_HIDDEN);
#endif
    lv_obj_refr_pos(g_pt_lv_100ask_regbit->ta_bin);
    lv_obj_refr_pos(g_pt_lv_100ask_regbit->ta_dec);
    lv_obj_refr_pos(g_pt_lv_100ask_regbit->ta_hex);

    lv_obj_t * label_ta_info;
    label_ta_info = lv_label_create(g_pt_lv_100ask_regbit->bg);
    lv_label_set_text(label_ta_info, "Binary");
    lv_obj_align_to(label_ta_info, g_pt_lv_100ask_regbit->ta_bin, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    label_ta_info = lv_label_create(g_pt_lv_100ask_regbit->bg);
    lv_label_set_text(label_ta_info, "Decimal system");
    lv_obj_align_to(label_ta_info, g_pt_lv_100ask_regbit->ta_dec, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    label_ta_info= lv_label_create(g_pt_lv_100ask_regbit->bg);
    lv_label_set_text(label_ta_info, "Hexadecimal");
    lv_obj_align_to(label_ta_info, g_pt_lv_100ask_regbit->ta_hex, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

}


/*
 *  函数名：   static void event_handler_regbit_map(lv_obj_t * obj, lv_event_t event)
 *  输入参数： 触发事件的对象
 *  输入参数： 触发的事件类型
 *  返回值：   无
 *  函数作用： 位按键响应事件，定位到当前选中的位按钮
*/
static void event_handler_regbit_map(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_t * label_index = lv_event_get_user_data(e);

    if(code == LV_EVENT_CLICKED)
    {
        char * tmp_ch;
        int bit_count = 0;
        lv_obj_t * obj_child = lv_obj_get_child(obj, -1);
        tmp_ch = lv_label_get_text(obj_child);

        bit_count = lv_100ask_tool_regbit_atoi(lv_label_get_text(label_index));
        if (strcmp(tmp_ch, "1") == 0)
        {
            lv_label_set_text(obj_child, "0");
            g_pt_lv_100ask_regbit->regbit_flag[bit_count] = '0';
        }
        else if (strcmp(tmp_ch, "0") == 0)
        {
            lv_label_set_text(obj_child, "1");
            g_pt_lv_100ask_regbit->regbit_flag[bit_count] = '1';
        }
#if 1
        char str_buf[32];
        char regbit_flag_buf[LV_100ASK_OBJ_BIT_COUNT] = "00000000000000000000000000000000";
        strcpy(regbit_flag_buf, g_pt_lv_100ask_regbit->regbit_flag);
        lv_100ask_tool_regbit_str_reverse(regbit_flag_buf);
        lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_bin, regbit_flag_buf);
        const char * str_buffer = lv_textarea_get_text(g_pt_lv_100ask_regbit->ta_bin);          // 获取输入内容
        //printf("str_buffer : %s\n\r", str_buffer);
        lv_snprintf(str_buf, sizeof(str_buf), "%d", lv_100ask_tool_regbit_bin_to_dec(str_buffer));    // 二进制转十进制
        lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_dec, str_buf);
        lv_snprintf(str_buf, sizeof(str_buf),"0x%X", lv_100ask_tool_regbit_bin_to_dec(str_buffer));   // 二进制转十六进制
        lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_hex, str_buf);
#endif // 0
    }
}



/*
 *  函数名：   static long lv_100ask_tool_regbit_bin_to_dec(const char *pbin)
 *  输入参数： 待转换的二进制字符串
 *  返回值：   二进制字符串转换为十进制整数的结果。
 *  函数作用： 把二进制字符串转换为十进制
*/
static long lv_100ask_tool_regbit_bin_to_dec(const char *pbin)
{
  int ii=0;
  long result=0;

  while (pbin[ii] != 0)
  {
    result = result * 2 + (pbin[ii] - '0');
    ii++;
  }

  return result;
}



/*
 *  函数名：   static char * lv_100ask_tool_regbit_dec_to_bin(unsigned long dec)
 *  输入参数： 待转换的十进制数值
 *  返回值：   十进制整数转换为二进制字符串的结果
 *  函数作用： 十进制转二进制
*/
static char * lv_100ask_tool_regbit_dec_to_bin(unsigned long dec)
{
    int bit_count = 0;
    int bit_state;
    while(dec > 0)
    {
        bit_state = (dec % 2);
        if (bit_state == 1)
            g_pt_lv_100ask_regbit->regbit_flag[bit_count] = '1';
        else
            g_pt_lv_100ask_regbit->regbit_flag[bit_count] = '0';
        dec = dec / 2;
        bit_count++;
    }
    return g_pt_lv_100ask_regbit->regbit_flag;
}



/*
 *  函数名：   static int lv_100ask_tool_regbit_hex_to_dec(char hexVal[])
 *  输入参数： 待转换的十六进制字符串
 *  返回值：   十六进制字符串转换为十进制整数的结果。
 *  函数作用： 十六进制字符串转换为十进制整数
*/
static int lv_100ask_tool_regbit_hex_to_dec(char hexVal[])
{
    int len = strlen(hexVal);

    // Initializing base value to 1, i.e 16^0
    int base = 1;

    int dec_val = 0;

    // Extracting characters as digits from last character
    for (int i = len - 1; i >= 0; i--)
    {
        // if character lies in '0'-'9', converting
        // it to integral 0-9 by subtracting 48 from
        // ASCII value.
        if (hexVal[i] >= '0' && hexVal[i] <= '9')
        {
            dec_val += (hexVal[i] - 48)*base;

            // incrementing base by power
            base = base * 16;
        }

        // if character lies in 'A'-'F' , converting
        // it to integral 10 - 15 by subtracting 55
        // from ASCII value
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
        {
            dec_val += (hexVal[i] - 55)*base;

            // incrementing base by power
            base = base * 16;
        }
        // if character lies in 'a'-'f' , converting
        // it to integral 10 - 15 by subtracting 87
        // from ASCII value
        else if (hexVal[i] >= 'a' && hexVal[i] <= 'f')
        {
            dec_val += (hexVal[i] - 87) * base;

            // incrementing base by power
            base = base * 16;
        }
    }
    return dec_val;
}


/*
 *  函数名：   static void lv_100ask_tool_regbit_str_reverse(char str[])
 *  输入参数： 待反转的字符串
 *  返回值：   二进制字符串转换为十进制整数的结果。
 *  函数作用： 反转字符串
*/
static void lv_100ask_tool_regbit_str_reverse(char str[])
{
    int n=strlen(str);
    int i;
    char temp;
    for(i=0;i<(n/2);i++){
        temp=str[i];
        str[i]=str[n-i-1];
        str[n-i-1]=temp;
    }
}


/*
 *  函数名：   static int lv_100ask_tool_regbit_atoi(const char *str)
 *  输入参数： 待转换为int类型的字符串
 *  返回值：   二进制字符串转换为十进制整数的结果。
 *  函数作用： 字符串转为int数值类型
*/
static int lv_100ask_tool_regbit_atoi(const char *str)
{
    int value = 0;
    int flag = 1;           //判断符号

    while (*str == ' ')     //跳过字符串前面的空格
    {
        str++;
    }

    if (*str == '-')        //第一个字符若是‘-’，说明可能是负数
    {
        flag = 0;
        str++;
    }
    else if (*str == '+')   //第一个字符若是‘+’，说明可能是正数
    {
        flag = 1;
        str++;
    }                       //第一个字符若不是‘+’‘-’也不是数字字符，直接返回0
    else if (*str >= '9' || *str <= '0')
    {
        return 0;
    }

    //当遇到非数字字符或遇到‘/0’时，结束转化
    while (*str != '\0' && *str <= '9' && *str >= '0')
    {
        value = value * 10 + *str - '0'; //将数字字符转为对应的整形数
        str++;
    }

    if (flag == 0) //负数的情况
    {
        value = -value;
    }

    return value;
}



/*
 *  函数名：   static void lv_100ask_tool_regbit_update_regbit(bool flag)
 *  输入参数： 标志位(true - update ; false - reset)
 *  返回值：   无
 *  函数作用： 更新寄存器内容
*/
static void lv_100ask_tool_regbit_update_regbit(bool flag)
{
    if (flag)
    {
        lv_obj_t * obj_child;
        for (int i = 0 ; i < LV_100ASK_OBJ_BIT_COUNT; i++)
        {
            obj_child = lv_obj_get_child(g_pt_lv_100ask_regbit->regbit_obj[i], -1); // 获取标签句柄
            if (g_pt_lv_100ask_regbit->regbit_flag[i] == '1')
            {
                lv_label_set_text(obj_child, "1"); // 设置标签内容
            }
            else if (g_pt_lv_100ask_regbit->regbit_flag[i] == '0')
            {
                lv_label_set_text(obj_child, "0"); // 设置标签内容
            }
        }
    }
    else
    {
        lv_obj_t * obj_child;
        for (int i = 0 ; i < LV_100ASK_OBJ_BIT_COUNT; i++)
        {
            g_pt_lv_100ask_regbit->regbit_flag[i] = '0';
            obj_child = lv_obj_get_child(g_pt_lv_100ask_regbit->regbit_obj[i], -1); // 获取标签句柄
            lv_label_set_text(obj_child, "0"); // 设置标签内容
        }
    }

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

    if((code == LV_EVENT_CLICKED) && (g_pt_lv_100ask_regbit->kb == NULL))
    {
        lv_obj_set_y(g_pt_lv_100ask_regbit->bg, -80);

        g_pt_lv_100ask_regbit->kb = lv_keyboard_create(lv_scr_act());
        //lv_keyboard_set_cursor_manage(g_pt_lv_100ask_regbit->kb, true);
        lv_obj_add_event_cb(g_pt_lv_100ask_regbit->kb, event_handler_kb_cb, LV_EVENT_ALL, NULL);

        ///lv_textarea_set_cursor_hidden(ta, false);
        lv_keyboard_set_textarea(g_pt_lv_100ask_regbit->kb, ta);

        lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_bin, "");
        lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_dec, "");
        lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_hex, "");
        //lv_textarea_set_placeholder_text(g_pt_lv_100ask_regbit->ta_bin, "");
        //lv_textarea_set_placeholder_text(g_pt_lv_100ask_regbit->ta_dec, "");
        //lv_textarea_set_placeholder_text(g_pt_lv_100ask_regbit->ta_hex, "");
    }
    else if(code == LV_EVENT_VALUE_CHANGED)
    {
        lv_100ask_tool_regbit_update_regbit(false);

        // 根据输入类型转换数据
        char str_tmp[32];
        char * str_type = lv_label_get_text(lv_obj_get_child(ta, -1));  // 获取键盘类型
        const char * str_buffer = lv_textarea_get_text(ta);                         // 获取输入内容
        if (strcmp(str_type, "bin") == 0)
        {
            if (str_buffer != NULL)
            {
                lv_100ask_tool_regbit_dec_to_bin(lv_100ask_tool_regbit_atoi(str_buffer));               // 只是为了更新 g_pt_lv_100ask_regbit->regbit_flag
                lv_snprintf(str_tmp, sizeof(str_tmp),"%d", lv_100ask_tool_regbit_bin_to_dec(str_buffer));     // 二进制转十进制
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_dec, str_tmp);
                lv_snprintf(str_tmp, sizeof(str_tmp), "0x%X", lv_100ask_tool_regbit_bin_to_dec(str_buffer));  // 二进制转十六进制
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_hex, str_tmp);

            }
            else
            {
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_dec, "");
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_hex, "");
            }
        }
        else if (strcmp(str_type, "dec") == 0)
        {
            if (str_buffer != NULL)
            {
                // 十进制转二进制
                char regbit_flag_buf[LV_100ASK_OBJ_BIT_COUNT] = "00000000000000000000000000000000";
                strcpy(regbit_flag_buf, lv_100ask_tool_regbit_dec_to_bin(lv_100ask_tool_regbit_atoi(str_buffer)));
                lv_100ask_tool_regbit_str_reverse(regbit_flag_buf);
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_bin, regbit_flag_buf);
                lv_snprintf(str_tmp, sizeof(str_tmp), "0x%X", lv_100ask_tool_regbit_atoi(str_buffer));         // 十进制转十六进制
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_hex, str_tmp);
            }
            else
            {
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_bin, "");
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_hex, "");
            }

        }
        else if (strcmp(str_type, "hex") == 0)
        {
            if (str_buffer != NULL)
            {
                lv_snprintf(str_tmp, sizeof(str_tmp), "%d", lv_100ask_tool_regbit_hex_to_dec((char *)str_buffer));    // 十六进制转十进制
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_dec, str_tmp);

                // 十进制转二进制
                char regbit_flag_buf[LV_100ASK_OBJ_BIT_COUNT] = "00000000000000000000000000000000";
                strcpy(regbit_flag_buf, lv_100ask_tool_regbit_dec_to_bin(lv_100ask_tool_regbit_atoi(lv_textarea_get_placeholder_text(g_pt_lv_100ask_regbit->ta_dec))));
                lv_100ask_tool_regbit_str_reverse(regbit_flag_buf);   // 反转字符串
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_bin, regbit_flag_buf);
            }
            else
            {
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_dec, "");
                lv_textarea_set_text(g_pt_lv_100ask_regbit->ta_bin, "");
            }
        }
        lv_100ask_tool_regbit_update_regbit(true);
    }
}


/*
 *  函数名：   static void event_handler_kb_cb(lv_obj_t * keyboard, lv_event_t e)
 *  输入参数： 触发事件的对象
 *  输入参数： 触发的事件类型
 *  返回值：   无
 *  函数作用： 退出键盘
*/
static void event_handler_kb_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if((code == LV_EVENT_CANCEL) || (code == LV_EVENT_READY)) {
        if(g_pt_lv_100ask_regbit->kb) {
            lv_keyboard_set_textarea(g_pt_lv_100ask_regbit->kb, NULL);
            lv_obj_del(g_pt_lv_100ask_regbit->kb);
            g_pt_lv_100ask_regbit->kb = NULL;
            lv_obj_set_y(g_pt_lv_100ask_regbit->bg, 0);

        }
    }
}


/*
 *  函数名：   static void lv_100ask_tool_regbit_get_index_str(int index)
 *  输入参数： 位索引
 *  返回值：   对应位索引的字符串
 *  函数作用： 获取位索引的字符串
*/
static char * lv_100ask_tool_regbit_get_index_str(int index)
{
    switch(index){
        case 0:  return "0"; //break;
        case 1:  return "1"; //break;
        case 2:  return "2"; //break;
        case 3:  return "3"; //break;
        case 4:  return "4"; //break;
        case 5:  return "5"; //break;
        case 6:  return "6"; //break;
        case 7:  return "7"; //break;
        case 8:  return "8"; //break;
        case 9:  return "9"; //break;
        case 10: return "10";//break;
        case 11: return "11";//break;
        case 12: return "12";//break;
        case 13: return "13";//break;
        case 14: return "14";//break;
        case 15: return "15";//break;
        case 16: return "16";//break;
        case 17: return "17";//break;
        case 18: return "18";//break;
        case 19: return "19";//break;
        case 20: return "20";//break;
        case 21: return "21";//break;
        case 22: return "22";//break;
        case 23: return "23";//break;
        case 24: return "24";//break;
        case 25: return "25";//break;
        case 26: return "26";//break;
        case 27: return "27";//break;
        case 28: return "28";//break;
        case 29: return "29";//break;
        case 30: return "30";//break;
        case 31: return "31";//break;
        default : return "0";//break;
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
        /* 删除位对象 */
        for (int i = 0; i < LV_100ASK_OBJ_BIT_COUNT; i++)
        {
            if (g_pt_lv_100ask_regbit->regbit_obj[i] != NULL)
                lv_obj_del(g_pt_lv_100ask_regbit->regbit_obj[i]);
        }

        if (g_pt_lv_100ask_regbit->kb != NULL)      lv_obj_del(g_pt_lv_100ask_regbit->kb);      // 删除键盘
        if (g_pt_lv_100ask_regbit->ta_bin != NULL)  lv_obj_del(g_pt_lv_100ask_regbit->ta_bin);  // 删除文本输入框
        if (g_pt_lv_100ask_regbit->ta_dec != NULL)  lv_obj_del(g_pt_lv_100ask_regbit->ta_dec);  // 删除文本输入框
        if (g_pt_lv_100ask_regbit->ta_hex != NULL)  lv_obj_del(g_pt_lv_100ask_regbit->ta_hex);  // 删除文本输入框
        if (g_pt_lv_100ask_regbit->bg != NULL)      lv_obj_del(g_pt_lv_100ask_regbit->bg);      // 删除文背景

        /* 释放内存 */
        free(g_pt_lv_100ask_regbit);

        /* 清空屏幕，返回桌面 */
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_demo_home(0);
    }
}
