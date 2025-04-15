/**
 * @file lisaui_dbus.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-03-02
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "lisaui_app_common.h"
#include "lisaui_type.h"
#include "lisaui_dbus.h"
#include <stdlib.h>
#include <string.h>

static const char *TAG = "lisaui_dbus";


lisaui_err_t lisaui_dbus_create(lisaui_dbus_t *bus) {
    if (!bus) return LISAUI_ERR_INVALID_PARAM;
    memset(bus, 0, sizeof(lisaui_dbus_t));
    bus->node = NULL;

#ifdef FREERTOS
    bus->mutex = xSemaphoreCreateMutex();
    if (!bus->mutex) {
        return LISAUI_ERR_FAIL;
    }
#else
    if (pthread_mutex_init(&bus->mutex, NULL) != 0) {
        return LISAUI_ERR_FAIL;
    }
#endif
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_dbus_destroy(lisaui_dbus_t* bus) {
    if (!bus) return LISAUI_ERR_INVALID_PARAM;

    lisaui_dbus_node_t* node = bus->node;
    while (node) {
        lisaui_dbus_node_t* next = node->next;
        lisaui_free(node);
        node = next;
    }

#ifdef FREERTOS
    vSemaphoreDelete(bus->mutex);
#else
    pthread_mutex_destroy(&bus->mutex);
#endif
    lisaui_free(bus);

    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_dbus_subscribe(lisaui_dbus_t* bus, const char* event, lisaui_dbus_handler_t handler) {
    if (!bus || !event || !handler) return false;

    lisaui_dbus_node_t* node = (lisaui_dbus_node_t *)lisaui_malloc(sizeof(lisaui_dbus_node_t));
    if (!node) return LISAUI_ERR_NO_MEMORY;

    node->event = event;
    node->handler = handler;
    node->next = NULL;

#ifdef FREERTOS
    xSemaphoreTake(bus->mutex, portMAX_DELAY);
#else
    pthread_mutex_lock(&bus->mutex);
#endif
    if (bus->node) {
        node->next = bus->node->next;
        bus->node = node;
    } else {
        bus->node = node;
    }

#ifdef FREERTOS
    xSemaphoreGive(bus->mutex);
#else
    pthread_mutex_unlock(&bus->mutex);
#endif

    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_dbus_unsubscribe(lisaui_dbus_t* bus, const char* event, lisaui_dbus_handler_t handler)
{
    if (!bus || !event || !handler) return LISAUI_ERR_INVALID_PARAM;

#ifdef FREERTOS
    xSemaphoreTake(bus->mutex, portMAX_DELAY);
#else
    pthread_mutex_lock(&bus->mutex);
#endif

    lisaui_dbus_node_t* prev = NULL;
    lisaui_dbus_node_t* curr = bus->node;

    while (curr) {
        if (strcmp(curr->event, event) == 0 && curr->handler == handler) {
            if (prev) {
                prev->next = curr->next;
            } else {
                bus->node = curr->next;
            }
            lisaui_free(curr);
#ifdef FREERTOS
            xSemaphoreGive(bus->mutex);
#else
            pthread_mutex_unlock(&bus->mutex);
#endif
            return LISAUI_ERR_OK;
        }
        prev = curr;
        curr = curr->next;
    }

#ifdef FREERTOS
    xSemaphoreGive(bus->mutex);
#else
    pthread_mutex_unlock(&bus->mutex);
#endif

    return LISAUI_ERR_FAIL;
}

lisaui_err_t lisaui_dbus_publish(lisaui_dbus_t* bus, const char* event, void* data) {
    if (!bus || !event) return LISAUI_ERR_INVALID_PARAM;
    LISAUI_LOGD(TAG, "Publishing event: %s", event);
#ifdef FREERTOS
    xSemaphoreTake(bus->mutex, portMAX_DELAY);
#else
    pthread_mutex_lock(&bus->mutex);
#endif

    lisaui_dbus_node_t* node = bus->node;
    while (node) {
        if (strcmp(node->event, event) == 0) {
            LISAUI_LOGI(TAG, "\t\t\tEvent: %s", node->event);
            node->handler(data);
        }
        node = node->next;
    }

#ifdef FREERTOS
    xSemaphoreGive(bus->mutex);
#else
    pthread_mutex_unlock(&bus->mutex);
#endif

    return LISAUI_ERR_OK;
}

#ifdef LISAUI_DBUS_TEST

void test_lisaui_dbus_example1_handler(void* data)
{
    LISAUI_LOGI(TAG, "Event handler called with data: %s", (char*)data);
}

void test_lisaui_dbus_example1(void)
{
    lisaui_dbus_t* bus = (lisaui_dbus_t *)lisaui_malloc(sizeof(lisaui_dbus_t));
    if (!bus) {
        LISAUI_LOGE(TAG, "Failed to allocate memory for event bus");
        return;
    }
    if (lisaui_dbus_create(bus) != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "Failed to create event bus");
        return;
    }

    LISAUI_LOGI(TAG, "Event bus created");
    lisaui_dbus_subscribe(bus, "test_event", test_lisaui_dbus_example1_handler);
    LISAUI_LOGI(TAG, "Event subscribed");
    lisaui_dbus_publish(bus, "test_event", "Hello, World!");
    LISAUI_LOGI(TAG, "Event published");

    lisaui_dbus_destroy(bus);
}
#endif