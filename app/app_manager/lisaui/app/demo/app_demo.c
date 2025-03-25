/**
 * @file app_demo.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-01-22
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "app_demo.h"
#include "../../app_common/lisaui_app_common.h"
#include "../assets/assets_res.h"
#include "../app_common.h"

static const char *TAG = "app_demo";
static lv_obj_t *g_app_demo = NULL;

void lv_ex_btn_1_test(void *parent);

// 声明[模板]应用需要实现的接口
LISAUI_DECLARE_APP_FUNC(demo, create, destroy, enter, exit, get_page);
// 定义[模板]应用
LISAUI_DEFINE_APP(demo, UI_APP_ID_DEMO, "测试", "Demo", &ui_img_icon_practice_png, {});

// App 模板宏原型在 common/lisaui_app_manager.h 中定义
// 定义[Demo]应用功能实现, 用于创建、销毁、进入、退出、获取页面
lisaui_err_t LISAUI_DEFINE_APP_FUNC(demo, create, void *parent, {
    if (g_app_demo != NULL) {
        return LISAUI_ERR_OK;
    }
    g_app_demo = lv_obj_create(parent);
    _lisaui_set_style_container(g_app_demo, lv_color_hex(0x000000), 255, lv_color_hex(0x000000), 0, 0);

    LISAUI_LOGI(TAG, "[%d:%s] create\n", __LINE__, __func__);
    return LISAUI_ERR_OK;
});

lisaui_err_t LISAUI_DEFINE_APP_FUNC(demo, destroy, void, { return LISAUI_ERR_OK; });
lisaui_err_t LISAUI_DEFINE_APP_FUNC(demo, enter, void, { return LISAUI_ERR_OK; });
lisaui_err_t LISAUI_DEFINE_APP_FUNC(demo, exit, void, { return LISAUI_ERR_OK; });
void *LISAUI_DEFINE_APP_FUNC(demo, get_page, void, { return g_app_demo; });
