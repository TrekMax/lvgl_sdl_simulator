/**
 * @file lisaui_view_manager.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-03
 * 
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 * 
 * SPDX-License-Identifier: Apache-2.0
 */
#include "../app_common/lisaui_app_common.h"
#include "lisaui_view_manager.h"
#include "../app_common/lisaui_type.h"

static const char *TAG = "app_view_manager";

static struct _lisaui_view_stack_t view_stack = {0};

lisaui_err_t lisaui_view_manager_init(void)
{
    view_stack.capacity = LISAUI_VIEW_MANAGER_MAX_CAPACITY;
    view_stack.size = 0;
    // view_stack.pages = NULL;
    view_stack.head = NULL;
    view_stack.tail = NULL;
    // view_stack.current = NULL;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_push(lisaui_view_page_t *page)
{
    if (page == NULL) {
        LISAUI_LOGW(TAG, "Invalid page pointer");
        return LISAUI_ERR_NO_MEMORY;
    }

    if (view_stack.size >= view_stack.capacity) {
        LISAUI_LOGW(TAG, "view stack is full");
        return LISAUI_ERR_NO_MEMORY;
    }
    if (view_stack.size == 0) {
        view_stack.head = page;
        view_stack.tail = page;
    }
    else {
        view_stack.tail->next = page;
        view_stack.tail = page;
    }

    view_stack.tail->next = NULL;
    view_stack.size++;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_pop(lisaui_view_page_t **page)
{
    if (view_stack.size == 0) {
        LISAUI_LOGW(TAG, "view stack is empty");
        return LISAUI_ERR_NO_MEMORY;
    }

    if (view_stack.size == 1) {
        *page = view_stack.head;
        view_stack.head = NULL;
        view_stack.tail = NULL;
    } else {
        *page = view_stack.tail;
        lisaui_view_page_t *p = view_stack.head;
        while (p->next != view_stack.tail) {
            p = p->next;
        }
        view_stack.tail = p;
        view_stack.tail->next = NULL;
    }

    view_stack.size--;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manger_get_current(lisaui_view_page_t **page)
{
    if (view_stack.size == 0) {
        LISAUI_LOGW(TAG, "view stack is empty");
        return LISAUI_ERR_NO_MEMORY;
    }
    *page = view_stack.tail;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manger_print_usage(void)
{
    LISAUI_LOGI(TAG, "view stack usage: %d/%d", view_stack.size, view_stack.capacity);
    LISAUI_LOGI(TAG, "\thead: %p", view_stack.head);
    // LISAUI_LOGI(TAG, "view stack current: %p", view_stack.current);
    void *p = view_stack.head;
    while (p!=NULL) {
        lisaui_view_page_t *page = (lisaui_view_page_t *)p;
        // LISAUI_LOGI(TAG, "\t\tpage: %p, page->prev: %p, page->next: %p", page, page->prev, page->next);
        LISAUI_LOGI(TAG, "\tpage: %p, page->next: %p", page, page->next);
        p = page->next;
    }
    LISAUI_LOGI(TAG, "\ttail: %p", view_stack.tail);
    return LISAUI_ERR_OK;
}