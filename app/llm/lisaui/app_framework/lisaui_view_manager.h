/**
 * @file lisaui_view_manager.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-03-03
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_VIEW_MANAGER_H__
#define __LISAUI_VIEW_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../app_common/lisaui_type.h"
#include "../app_common/lisaui_app_common.h"

#define LISAUI_VIEW_MANAGER_MAX_CAPACITY 20

struct _lisaui_view_page_t {
    int app_id; // 页面栈归属的 app id, 用于在不同 app 之间 view 切换
    int page_id;
    lisaui_view_t *root;

    // 页面栈生命周期
    // lisaui_err_t (*on_create)(void *parent);
    // lisaui_err_t (*on_destroy)(void);
    // lisaui_err_t (*on_enter)(void);
    // lisaui_err_t (*on_exit)(void);
    // lisaui_err_t (*on_pause)(void);
    // lisaui_err_t (*on_resume)(void);

    lisaui_view_page_t *next;
    // lisaui_view_page_t *prev;
};

struct _lisaui_view_stack_t {
    int capacity;
    int size;

    // lisaui_view_page_t *pages;
    // lisaui_view_page_t *current;
    lisaui_view_page_t *head;
    lisaui_view_page_t *tail;
} ;

lisaui_err_t lisaui_view_manager_init(lisaui_view_stack_t *view_stack);
lisaui_err_t lisaui_view_manager_clean(lisaui_view_stack_t *view_stack);
lisaui_err_t lisaui_view_manager_deinit(lisaui_view_stack_t *view_stack);

lisaui_err_t lisaui_view_manager_get_current(lisaui_view_stack_t *view_stack, lisaui_view_page_t **page);
lisaui_err_t lisaui_view_manager_pop(lisaui_view_stack_t *view_stack, lisaui_view_page_t **page);
lisaui_err_t lisaui_view_manager_push(lisaui_view_stack_t *view_stack, lisaui_view_page_t *page);
lisaui_err_t lisaui_view_manager_print_usage(lisaui_view_stack_t *view_stack);
lisaui_err_t lisaui_view_manager_get_depth(lisaui_view_stack_t *view_stack, int *depth);
lisaui_err_t lisaui_view_manager_get_capacity(lisaui_view_stack_t *view_stack, int *capacity);

#ifdef __cplusplus
}
#endif

#endif /* __LISAUI_VIEW_MANAGER_H__ */