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

lisaui_err_t lisaui_view_manager_init(lisaui_view_stack_t *view_stack)
{
    // view_stack->capacity = LISAUI_VIEW_MANAGER_MAX_CAPACITY;
    view_stack->size = 0;
    // view_stack->pages = NULL;
    view_stack->head = NULL;
    view_stack->tail = NULL;
    // view_stack->current = NULL;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_push(lisaui_view_stack_t *view_stack, lisaui_view_page_t *page)
{
    if (page == NULL) {
        LISAUI_LOGW(TAG, "Invalid page pointer");
        return LISAUI_ERR_NO_MEMORY;
    }

    if (view_stack->size >= view_stack->capacity) {
        LISAUI_LOGW(TAG, "view stack is full");
        return LISAUI_ERR_NO_MEMORY;
    }
    if (view_stack->size == 0) {
        view_stack->head = page;
        view_stack->tail = page;
    }
    else {
        view_stack->tail->next = page;
        view_stack->tail = page;
    }

    view_stack->tail->next = NULL;
    view_stack->size++;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_pop(lisaui_view_stack_t *view_stack, lisaui_view_page_t **page)
{
    if (view_stack->size == 0) {
        LISAUI_LOGW(TAG, "view stack is empty");
        return LISAUI_ERR_NO_MEMORY;
    }

    if (view_stack->size == 1) {
        *page = view_stack->head;
        view_stack->head = NULL;
        view_stack->tail = NULL;
    } else {
        *page = view_stack->tail;
        lisaui_view_page_t *p = view_stack->head;
        while (p->next != view_stack->tail) {
            p = p->next;
        }
        view_stack->tail = p;
        view_stack->tail->next = NULL;
    }

    view_stack->size--;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_get_current(lisaui_view_stack_t *view_stack, lisaui_view_page_t **page)
{
    if (view_stack->size == 0) {
        LISAUI_LOGW(TAG, "view stack is empty");
        return LISAUI_ERR_NO_MEMORY;
    }
    *page = view_stack->tail;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_print_usage(lisaui_view_stack_t *view_stack)
{
    LISAUI_LOGD(TAG, "--------------------------------------------------------");
    LISAUI_LOGD(TAG, "view stack usage: %d/%d", view_stack->size, view_stack->capacity);
    LISAUI_LOGD(TAG, "\thead: %p", view_stack->head);
    // LISAUI_LOGD(TAG, "view stack current: %p", view_stack.current);
    void *p = view_stack->head;
    int depth = 0;
    while (p!=NULL) {
        depth++;
        lisaui_view_page_t *page = (lisaui_view_page_t *)p;
        // LISAUI_LOGD(TAG, "\t\tpage: %p, page->prev: %p, page->next: %p", page, page->prev, page->next);
        LISAUI_LOGD(TAG, "\t[%d]page: %p, page->next: %p", depth, page, page->next);
        p = page->next;
    }
    LISAUI_LOGD(TAG, "\ttail: %p", view_stack->tail);
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_clean(lisaui_view_stack_t *view_stack)
{
    lisaui_view_page_t *page = NULL;
    while (view_stack->size > 0) {
        lisaui_view_manager_pop(view_stack, &page);
        lisaui_free(page);
        page = NULL;
    }
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_deinit(lisaui_view_stack_t *view_stack)
{
    lisaui_view_manager_clean(view_stack);
    view_stack->size = 0;
    view_stack->head = NULL;
    view_stack->tail = NULL;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_get_depth(lisaui_view_stack_t *view_stack, int *depth)
{
    if (depth == NULL) {
        LISAUI_LOGW(TAG, "Invalid depth pointer");
        return LISAUI_ERR_INVALID_PARAM;
    }
    *depth = view_stack->size;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_view_manager_get_capacity(lisaui_view_stack_t *view_stack, int *capacity)
{
    if (capacity == NULL) {
        LISAUI_LOGW(TAG, "Invalid capacity pointer");
        return LISAUI_ERR_INVALID_PARAM;
    }
    *capacity = view_stack->capacity;
    return LISAUI_ERR_OK;
}