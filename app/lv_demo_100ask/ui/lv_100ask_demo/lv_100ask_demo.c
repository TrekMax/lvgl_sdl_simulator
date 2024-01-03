/**
 ******************************************************************************
 * @file    lv_100ask_demo.c
 * @author  百问科技
 * @version V1.2
 * @date    2020-12-12
 * @brief   初始化桌面
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
#include "./lv_100ask_demo.h"


/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * bg_top;           // 背景
static lv_obj_t *tabview_desktop;   // 页签
static uint16_t tabview_desktop_id = 1; // 记录页签当前展示的页面


/**********************
 *       EXTERN
 **********************/
extern void lv_100ask_game_2048(void);                  // 2048游戏
extern void lv_100ask_board_about(void);          // 关于我们
extern void lv_100ask_tool_calc(void);            // 计算器
extern void lv_100ask_game_snake(void);           // 贪吃蛇游戏
extern void lv_100ask_tool_clock(void);           // 时钟
extern void lv_100ask_tool_regbit(void);          // 寄存器位查看计算工具
extern void lv_100ask_tool_qrcode(void);          // 创建二维码
//extern void lv_100ask_music_player(void);         // 音乐播放器
extern void lv_100ask_tool_setting(void);         // 系统设置
//extern void lv_100ask_tool_humiture(void);        // 温湿度检测
//extern void lv_100ask_tool_widget_test(void);     // 部件测试
//extern void lv_100ask_tool_file_browser(void);    // 文件浏览器
extern void lv_100ask_boot_animation(uint32_t delay);   // 开机动画


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void event_handler_demo_tabview(lv_event_t * e);

static void event_handler_demo_about(lv_event_t * e);                 // 打开关于我们应用事件处理函数
static void event_handler_demo_game_2048(lv_event_t * e);             // 打开2048游戏应用事件处理函数事件处理函数
static void event_handler_demo_tools_calc(lv_event_t * e);            // 打开计算器应用事件处理函数
static void event_handler_demo_game_snake(lv_event_t * e);                // 打开贪吃蛇游戏应用事件处理函数
static void event_handler_demo_tools_clock(lv_event_t * e);               // 打开时钟应用事件处理函数
static void event_handler_demo_tools_regbit(lv_event_t * e);              // 打开寄存器位查看计算工具应用事件处理函数
static void event_handler_demo_tools_qrcode(lv_event_t * e);              // 打开创建二维码应用事件处理函数
static void event_handler_demo_music_player(lv_event_t * e);            // 打开音乐播放器应用事件处理函数
//static void event_handler_demo_tools_humiture(lv_event_t * e);          // 打开温湿度应用事件处理函数
static void event_handler_demo_tools_settings(lv_event_t * e);            // 打开系统设置应用事件处理函数
//static void event_handler_demo_tools_widget_test(lv_event_t * e);       // 打开ADC、LED、BEEP测试应用事件处理函数
//static void event_handler_demo_tools_file_browser(lv_event_t * e);      // 打开文件浏览器应用事件处理函数


/* 桌标图标声明 */
LV_IMG_DECLARE(img_lv_100ask_icon_2048);        // 00 LV_100ASK_MENU_ITEM_COUNT
LV_IMG_DECLARE(img_lv_100ask_icon_about_us);    // 01
LV_IMG_DECLARE(img_lv_100ask_icon_setting);     // 02
LV_IMG_DECLARE(img_lv_100ask_icon_data);        // 03
//LV_IMG_DECLARE(img_lv_100ask_icon_floder);        // 04
LV_IMG_DECLARE(img_lv_100ask_icon_music);     // 05
LV_IMG_DECLARE(img_lv_100ask_icon_QRcode);      // 06
LV_IMG_DECLARE(img_lv_100ask_icon_snake);       // 07
//LV_IMG_DECLARE(img_lv_100ask_icon_humiture);  // 08
LV_IMG_DECLARE(img_lv_100ask_icon_regbit);      // 09
LV_IMG_DECLARE(img_lv_100ask_icon_calc);        // 10
//LV_IMG_DECLARE(img_lv_100ask_icon_widgets);       // 11

/* 桌标图标数组 */
static const lv_img_dsc_t *app_icon[] = \
    { \
      &img_lv_100ask_icon_data,      &img_lv_100ask_icon_music,     &img_lv_100ask_icon_about_us, \
      &img_lv_100ask_icon_2048,      &img_lv_100ask_icon_snake,     &img_lv_100ask_icon_QRcode, \
      &img_lv_100ask_icon_calc,      &img_lv_100ask_icon_regbit,   \
      &img_lv_100ask_icon_setting};


/* 回调函数指针数组*/
static void (*lv_100ask_event_cb[])(lv_event_t * e) = \
    { \
      event_handler_demo_tools_clock,        event_handler_demo_music_player,       event_handler_demo_about, \
      event_handler_demo_game_2048,          event_handler_demo_game_snake,         event_handler_demo_tools_qrcode,\
      event_handler_demo_tools_calc,         event_handler_demo_tools_regbit, \
      event_handler_demo_tools_settings
    };


/* 应用图标名称 */
static const char * app_name[] = \
    { \
      "time",    "music",  "aboutus", \
      "2048",    "snake", "QRcode",\
      "calc",     "regbit", \
      "setting"
    };


/**********************************************************************
 * 函数名称： lv_100ask_demo
 * 功能描述： 桌面初始化入口
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
void lv_100ask_demo(uint32_t delay)
{
    lv_100ask_boot_animation(delay); /* 开机动画 */
#if 1
    lv_100ask_demo_home(delay + LV_100ASK_HOME_OPEN_TIME);    // 初始化主菜单
#endif
}

void ui_init( void )
{
    lv_100ask_demo(1500);
}

/**********************************************************************
 * 函数名称： lv_100ask_demo_home
 * 功能描述： 桌面初始化
 * 输入参数： 动画延时时间
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
void lv_100ask_demo_home(uint32_t delay)
{
#if 0
    /* 桌面背景 */
    LV_IMG_DECLARE(img_lv_100ask_bg);
    bg_top = lv_img_create(lv_scr_act());
    lv_img_set_src(bg_top, &img_lv_100ask_bg);
    lv_obj_align(bg_top, LV_ALIGN_CENTER, 0, 0);
    lv_obj_fade_in(bg_top,0, delay);
#endif

    /* 创建三个页签作为菜单容器 */
    tabview_desktop = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 0);
    //lv_obj_set_style_bg_opa(tabview_desktop, LV_OPA_0, 0);       // 设置背景透明度
    //lv_tabview_set_btns_pos(tabview_desktop, LV_TABVIEW_TAB_POS_NONE);
    lv_obj_add_event_cb(tabview_desktop, event_handler_demo_tabview, LV_EVENT_VALUE_CHANGED, NULL);

    /* 电池*/
    lv_obj_t * label_state = lv_label_create(lv_scr_act());
    //lv_obj_set_style_text_color(label_state, lv_color_hex(0xffffff), 0);          // 设置颜色
    lv_label_set_text(label_state, LV_SYMBOL_BATTERY_FULL);
    lv_obj_refr_size(label_state);
    lv_obj_align(label_state, LV_ALIGN_TOP_RIGHT, -(8), lv_obj_get_height(label_state)/3);
    lv_obj_fade_in(label_state, 0, delay);

    /* 图标 时间 */
    label_state = lv_label_create(lv_scr_act());
    //lv_obj_set_style_text_color(label_state, lv_color_hex(0xffffff), 0);          // 设置颜色
    lv_label_set_text(label_state, "9:41");
    //lv_obj_set_style_text_font(label_state, &lv_font_montserrat_14, 0);   // 设置文字大小
    lv_obj_refr_size(label_state);
    lv_obj_align(label_state, LV_ALIGN_TOP_MID, 0, lv_obj_get_height(label_state)/3);
    lv_obj_fade_in(label_state, 0, delay);

    lv_obj_t *tab1 = lv_tabview_add_tab(tabview_desktop, "left_desktop");  // 0
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview_desktop, "main_desktop");  // 1
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview_desktop, "right_desktop"); // 2
    lv_obj_set_style_anim_time(tabview_desktop, 0, 0);         // 动画时间
    lv_tabview_set_act(tabview_desktop, tabview_desktop_id, LV_ANIM_OFF);
    lv_obj_fade_in(tabview_desktop, 0 , (delay + LV_100ASK_HOME_OPEN_TIME));

    lv_obj_set_style_pad_hor(tab1, 0, 0);
    lv_obj_set_style_pad_hor(tab2, 0, 0);
    lv_obj_set_style_pad_hor(tab3, 0, 0);

   /* 左菜单指示 */
    lv_obj_t * left_round1 = lv_obj_create(tab1);               // 中间
    lv_obj_set_size(left_round1, 8, 8);
    lv_obj_set_style_bg_opa(left_round1, LV_OPA_40, 0);          // 设置背景透明度
    lv_obj_set_style_radius(left_round1, 100, 0);                // 设置圆角
    lv_obj_set_style_bg_color(left_round1, lv_color_hex(0x00ae42), 0);   // 设置颜色
    lv_obj_align(left_round1, LV_ALIGN_BOTTOM_MID, 0, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    lv_obj_t * left_round2 = lv_obj_create(tab1);       // 右边
    lv_obj_set_size(left_round2, 8, 8);
    lv_obj_set_style_bg_opa(left_round2, LV_OPA_40, 0);          // 设置背景透明度
    lv_obj_set_style_radius(left_round2, 100, 0);                // 设置圆角
    lv_obj_set_style_bg_color(left_round2, lv_color_hex(0x00ae42), 0);   // 设置颜色
    lv_obj_align(left_round2, LV_ALIGN_BOTTOM_MID, 20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    lv_obj_t * left_round3 = lv_obj_create(tab1);       // 左边
    lv_obj_set_size(left_round3, 8, 8);
    lv_obj_set_style_bg_opa(left_round3, LV_OPA_80, 0);          // 设置背景透明度
    lv_obj_set_style_radius(left_round3, 100, 0);                // 设置圆角
    lv_obj_set_style_bg_color(left_round3, lv_color_hex(0x00ae42), 0);   // 设置颜色
    lv_obj_align(left_round3, LV_ALIGN_BOTTOM_MID, -20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));


    /* 主菜单指示 */
    lv_obj_t * main_round1 = lv_obj_create(tab2);               // 中间
    lv_obj_set_size(main_round1, 8, 8);
    lv_obj_set_style_bg_opa(main_round1, LV_OPA_80, 0);          // 设置背景透明度
    lv_obj_set_style_radius(main_round1, 100, 0);                // 设置圆角
    lv_obj_set_style_bg_color(main_round1, lv_color_hex(0x00ae42), 0);   // 设置颜色
    lv_obj_align(main_round1, LV_ALIGN_BOTTOM_MID, 0, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));
    lv_obj_fade_in(main_round1, 0 , (delay + LV_100ASK_HOME_OPEN_TIME));

    lv_obj_t * main_round2 = lv_obj_create(tab2);       // 右边
    lv_obj_set_size(main_round2, 8, 8);
    lv_obj_set_style_bg_opa(main_round2, LV_OPA_40, 0);          // 设置背景透明度
    lv_obj_set_style_radius(main_round2, 100, 0);                // 设置圆角
    lv_obj_set_style_bg_color(main_round2, lv_color_hex(0x00ae42), 0);   // 设置颜色
    lv_obj_align(main_round2, LV_ALIGN_BOTTOM_MID, 20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));
    lv_obj_fade_in(main_round2, 0 , (delay + LV_100ASK_HOME_OPEN_TIME));

    lv_obj_t * main_round3 = lv_obj_create(tab2);       // 左边
    lv_obj_set_size(main_round3, 8, 8);
    lv_obj_set_style_bg_opa(main_round3, LV_OPA_40, 0);          // 设置背景透明度
    lv_obj_set_style_radius(main_round3, 100, 0);                // 设置圆角
    lv_obj_set_style_bg_color(main_round3, lv_color_hex(0x00ae42), 0);   // 设置颜色
    lv_obj_align(main_round3, LV_ALIGN_BOTTOM_MID, -20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));
    lv_obj_fade_in(main_round3, 0 , (delay + LV_100ASK_HOME_OPEN_TIME));


    /* 右菜单指示 */
    lv_obj_t * right_round1 = lv_obj_create(tab3);          // 中间
    lv_obj_set_size(right_round1, 8, 8);
    lv_obj_set_style_bg_opa(right_round1, LV_OPA_40, 0);         // 设置背景透明度
    lv_obj_set_style_radius(right_round1, 100, 0);               // 设置圆角
    lv_obj_set_style_bg_color(right_round1, lv_color_hex(0x00ae42), 0);  // 设置颜色
    lv_obj_align(right_round1, LV_ALIGN_BOTTOM_MID, 0, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    lv_obj_t * right_round2 = lv_obj_create(tab3);      // 右边
    lv_obj_set_size(right_round2, 8, 8);
    lv_obj_set_style_bg_opa(right_round2, LV_OPA_80, 0);         // 设置背景透明度
    lv_obj_set_style_radius(right_round2, 100, 0);               // 设置圆角
    lv_obj_set_style_bg_color(right_round2, lv_color_hex(0x00ae42), 0);  // 设置颜色
    lv_obj_align(right_round2, LV_ALIGN_BOTTOM_MID, 20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    lv_obj_t * right_round3 = lv_obj_create(tab3);      // 左边
    lv_obj_set_size(right_round3, 8, 8);
    lv_obj_set_style_bg_opa(right_round3, LV_OPA_40, 0);         // 设置背景透明度
    lv_obj_set_style_radius(right_round3, 100, 0);               // 设置圆角
    lv_obj_set_style_bg_color(right_round3, lv_color_hex(0x00ae42), 0);  // 设置颜色
    lv_obj_align(right_round3, LV_ALIGN_BOTTOM_MID, -20, -(LV_100ASK_BOTTOM_MENU_H + LV_100ASK_TABVIEW_NAVIGATION_SPACE));

    /* 创建主菜单 */
    lv_obj_t * label_app_name;  // app图标下方的文字
    lv_obj_t * obj_menu_item;   // 用于遍历初始化app图标的指针
    uint8_t row_count = 0;      // 行
    uint8_t col_count = 0;      // 列

    // 列
    lv_coord_t col_space = ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (col_count + 1)) + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * col_count));

    // 行
    lv_coord_t row_space = ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (row_count + 1)) + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * row_count) + 10);

    for (int i = 0; i < LV_100ASK_MENU_ITEM_COUNT; i++)
    {
        if ((i >= 0) && (i < 5))        // 主菜单
        {
            obj_menu_item = lv_img_create(tab2);
            label_app_name = lv_label_create(tab2);
        }

        else if ((i >= 5) && (i < 7))   // 主菜单左侧菜单
        {
            obj_menu_item = lv_img_create(tab1);
            label_app_name = lv_label_create(tab1);
        }
        else                            // 主菜单右侧菜单
        {
            obj_menu_item = lv_img_create(tab3);
            label_app_name = lv_label_create(tab3);
        }

        //lv_obj_set_click(obj_menu_item, 1);            // 允许点击
        lv_obj_add_flag(obj_menu_item, LV_OBJ_FLAG_CLICKABLE);
        lv_img_set_src(obj_menu_item, app_icon[i]);    // 使用数组文件
        //lv_obj_set_drag(obj_menu_item, true);        // 启用拖动
        lv_obj_align(obj_menu_item, LV_ALIGN_TOP_LEFT, col_space, row_space);
        lv_obj_fade_in(obj_menu_item, 0 , delay);
        lv_obj_add_event_cb(obj_menu_item, lv_100ask_event_cb[i], LV_EVENT_CLICKED, NULL);    /* 分配事件回调处理函数 */

        /* 创建 app name 标签 */
        lv_obj_set_style_text_font(label_app_name, &lv_font_montserrat_10, 0);      // 设置字号
        lv_label_set_text(label_app_name, app_name[i]);
        lv_obj_align_to(label_app_name, obj_menu_item, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
        lv_obj_fade_in(label_app_name, 0 , delay);


        col_count++;

        if (((i + 1) % 4) == 0)  // 换行，一行最多有4个图标
        {
            col_count = 0;
            row_count++;
            row_space = ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (row_count + 1)) + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * row_count) + 25);
        }
        col_space = ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (col_count + 1)) + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * col_count));
    }

    /* 创建底部导航栏展示区域 */
    lv_obj_t * obj_bottom_menu = lv_obj_create(lv_scr_act());
    lv_obj_clear_flag(obj_bottom_menu, LV_OBJ_FLAG_SCROLLABLE);
    //lv_obj_set_flex_flow(obj_bottom_menu, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(obj_bottom_menu, LV_100ASK_BOTTOM_MENU_W, LV_100ASK_BOTTOM_MENU_H);                                  // 设置大小
    lv_obj_set_style_bg_opa(obj_bottom_menu, LV_OPA_70, 0);                       // 设置背景透明度
    lv_obj_set_style_pad_all(obj_bottom_menu, 0, 0);
    lv_obj_set_style_radius(obj_bottom_menu, 0, 0);                               // 设置圆角
    lv_obj_set_style_bg_color(obj_bottom_menu, LV_100ASK_BOTTOM_MENU_COLOR, 0);   // 设置颜色
    lv_obj_align(obj_bottom_menu, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_fade_in(obj_bottom_menu, 0 , delay);

    /* 创建底部导航栏内的菜单 */
    lv_obj_t * obj_bottom_menu_item;
    for (int i = 0; i < LV_100ASK_BOTTOM_MENU_ITEM_COUNT; i++)
    {
        obj_bottom_menu_item = lv_img_create(obj_bottom_menu);
        //lv_obj_set_click(obj_bottom_menu_item, 1);            // 允许点击
        lv_obj_add_flag(obj_bottom_menu_item, LV_OBJ_FLAG_CLICKABLE);
        lv_img_set_src(obj_bottom_menu_item, app_icon[i]);    // 使用数组文件
        //lv_obj_set_drag(obj_bottom_menu_item, true);        // 启用拖动
        lv_obj_align(obj_bottom_menu_item, LV_ALIGN_LEFT_MID, ((((LV_100ASK_BOTTOM_MENU_W - (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * LV_100ASK_BOTTOM_MENU_ITEM_COUNT)) / 5) * (i + 1))\
                                                                     + (LV_100ASK_BOTTOM_MENU_ITEM_SIZE * i)), 0);
        lv_obj_fade_in(obj_bottom_menu_item, 0 , delay);
        lv_obj_add_event_cb(obj_bottom_menu_item, lv_100ask_event_cb[i], LV_EVENT_ALL, NULL);    /* 分配事件回调处理函数 */
    }
}



/**********************************************************************
 * 函数名称： lv_100ask_anim_out_all
 * 功能描述： 退场动画
 * 输入参数： 需要退场的对象
 * 输入参数： 动画延时时间
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
void lv_100ask_anim_out_all(lv_obj_t * obj, uint32_t delay)
{
    uint32_t i;
    for(i = 0; i < lv_obj_get_child_cnt(obj); i++) {
      lv_obj_t * child = lv_obj_get_child(obj, i);
      /*Do something with child*/
      if ((child != bg_top) && (child != lv_scr_act())) {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, child);
            lv_anim_set_time(&a, LV_100SK_DEMO_ANIM_TIME);
            lv_anim_set_delay(&a, delay);
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
            if(lv_obj_get_y(child) < 80) {
                lv_anim_set_values(&a, lv_obj_get_y(child),
                        lv_obj_get_y(child) - LV_100SK_DEMO_ANIM_Y);
            } else {
                lv_anim_set_values(&a, lv_obj_get_y(child),
                        lv_obj_get_y(child) + LV_100SK_DEMO_ANIM_Y);

                delay += LV_100SK_DEMO_ANIM_DELAY;
            }
            lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
            lv_anim_start(&a);
        }
    }
}




static void event_handler_demo_tabview(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * tabview = lv_event_get_target(e);

    if(code == LV_EVENT_VALUE_CHANGED)    tabview_desktop_id = lv_tabview_get_tab_act(tabview);     // 记录当前页面位置
}
/**********************************************************************
 * 函数名称： event_handler_demo_about
 * 功能描述： 打开关于应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_about(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_board_about();
    }
}

/**********************************************************************
 * 函数名称： event_handler_demo_music_player
 * 功能描述： 打开音乐播放器应用
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_music_player(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        // lv_100ask_music_player();
        // lv_demo_music();
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_game_2048
 * 功能描述： 打开2048游戏
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_game_2048(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_game_2048();
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_regbit
 * 功能描述： 打开寄存器位查看计算工具
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_tools_regbit(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_tool_regbit();
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_qrcode
 * 功能描述： 打开二维码创建工具
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_tools_qrcode(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_tool_qrcode();
    }
}

/**********************************************************************
 * 函数名称： event_handler_demo_tools_calc
 * 功能描述： 打开计算器
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_tools_calc(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_tool_calc();
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_snake
 * 功能描述： 打开贪吃蛇游戏
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_game_snake(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_game_snake();
    }
}


/**********************************************************************
 * 函数名称： event_handler_demo_tools_clock
 * 功能描述： 打开时钟
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_tools_clock(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_tool_clock();
    }
}



/**********************************************************************
 * 函数名称： event_handler_demo_tools_settings
 * 功能描述： 打开系统设置
 * 输入参数： 触发事件的对象(图标)
 * 输入参数： 事件触发的事件类型
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
static void event_handler_demo_tools_settings(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED)
    {
        lv_obj_del(tabview_desktop);
        lv_100ask_anim_out_all(lv_scr_act(), 0);
        lv_100ask_tool_setting();
    }
}


/**********************************************************************
 * 函数名称： add_title
 * 功能描述： 给指定对象添加标题
 * 输入参数： 需要添加标题的对象
 * 输入参数： 标题内容
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
lv_obj_t * add_title(lv_obj_t * obj, const char * txt)
{
    // 添加标题
    lv_obj_t * title = lv_label_create(obj);
    //lv_obj_set_style_text_color(title, lv_color_hex(0x000000), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_32, 0);
    lv_label_set_text(title, txt);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, LV_100SK_DEMO_TITLE_PAD);
    return title;
}


/**********************************************************************
 * 函数名称： add_back
 * 功能描述： 添加返回按钮
 * 输入参数： 需要添加返回按钮的对象
 * 输入参数： 需要分配的按钮事件处理函数，NULL为不需要事件处理函数
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期              版本号      修改人         修改内容
 * ---------------------------------------------------------------------
 * 2020/11/11        V1.0     YobeZhou    创建
 ***********************************************************************/
void add_back(lv_obj_t * obj, lv_event_cb_t event_cb)
{
    //返回按钮
    lv_obj_t * btn = lv_obj_create(obj);                                                            // 创建obj对象
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);    // 启用点击
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);

    //lv_obj_set_style_bg_opa(btn, LV_OPA_0, 0);                    // 设置色彩透明度
    lv_obj_set_style_border_opa(btn, LV_OPA_0, 0);                  // 边框透明度
    //lv_obj_set_style_text_color(btn, lv_color_hex(0x008000), 0);      // 设置数值颜色(默认状态)
    lv_obj_set_style_text_color(btn, lv_color_hex(0x808080), LV_STATE_PRESSED);         // 设置数值颜色(按下状态)
    lv_obj_set_style_text_font(btn, &lv_font_montserrat_22, 0); // 设置数值字体(默认状态)
    lv_obj_set_size(btn, LV_100SK_DEMO_BACK_W, LV_100SK_DEMO_BACK_H);               // 设置对象大小(宽、高)
    lv_obj_set_pos(btn, LV_100SK_DEMO_BACK_PAD, LV_100SK_DEMO_BACK_PAD);            // 设置对象位置(x、y)
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t *btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, LV_SYMBOL_LEFT);
    lv_obj_center(btn_label);                                                               // 分配回调处理函数
}

