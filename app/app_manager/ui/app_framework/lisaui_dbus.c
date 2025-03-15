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
#include "lisaui_dbus.h"
#include <stdlib.h>
#include <string.h>

static const char *TAG = "lisaui_dbus";

typedef struct dbus_node_t {
    const char* event;
    dbus_handler_t handler;
    struct dbus_node_t* next;
} dbus_node_t;

struct _lisaui_dbus_t {
    dbus_node_t* handlers;
#ifdef FREERTOS
    SemaphoreHandle_t mutex;
#else
    pthread_mutex_t mutex;
#endif
};

lisaui_dbus_t* lisaui_dbus_create() {
    lisaui_dbus_t* bus = (lisaui_dbus_t*)lisaui_malloc(sizeof(lisaui_dbus_t));
    if (!bus) return NULL;

    bus->handlers = NULL;
#ifdef FREERTOS
    bus->mutex = xSemaphoreCreateMutex();
    if (!bus->mutex) {
        lisaui_free(bus);
        return NULL;
    }
#else
    if (pthread_mutex_init(&bus->mutex, NULL) != 0) {
        lisaui_free(bus);
        return NULL;
    }
#endif
    return bus;
}

void lisaui_dbus_destroy(lisaui_dbus_t* bus) {
    if (!bus) return;

    dbus_node_t* node = bus->handlers;
    while (node) {
        dbus_node_t* next = node->next;
        lisaui_free(node);
        node = next;
    }

#ifdef FREERTOS
    vSemaphoreDelete(bus->mutex);
#else
    pthread_mutex_destroy(&bus->mutex);
#endif
    lisaui_free(bus);
}

bool lisaui_dbus_subscribe(lisaui_dbus_t* bus, const char* event, dbus_handler_t handler) {
    if (!bus || !event || !handler) return false;

    dbus_node_t* node = (dbus_node_t*)lisaui_malloc(sizeof(dbus_node_t));
    if (!node) return false;

    node->event = event;
    node->handler = handler;
    node->next = NULL;

#ifdef FREERTOS
    xSemaphoreTake(bus->mutex, portMAX_DELAY);
#else
    pthread_mutex_lock(&bus->mutex);
#endif

    node->next = bus->handlers;
    bus->handlers = node;

#ifdef FREERTOS
    xSemaphoreGive(bus->mutex);
#else
    pthread_mutex_unlock(&bus->mutex);
#endif

    return true;
}

lisaui_dbus_t lisaui_dbus_unsubscribe(lisaui_dbus_t* bus, const char* event, dbus_handler_t handler) {
    if (!bus || !event || !handler) return false;

#ifdef FREERTOS
    xSemaphoreTake(bus->mutex, portMAX_DELAY);
#else
    pthread_mutex_lock(&bus->mutex);
#endif

    dbus_node_t* prev = NULL;
    dbus_node_t* curr = bus->handlers;

    while (curr) {
        if (strcmp(curr->event, event) == 0 && curr->handler == handler) {
            if (prev) {
                prev->next = curr->next;
            } else {
                bus->handlers = curr->next;
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

void lisaui_dbus_publish(lisaui_dbus_t* bus, const char* event, void* data) {
    if (!bus || !event) return;
    LISAUI_LOGD(TAG, "Publishing event: %s", event);
#ifdef FREERTOS
    xSemaphoreTake(bus->mutex, portMAX_DELAY);
#else
    pthread_mutex_lock(&bus->mutex);
#endif

    dbus_node_t* node = bus->handlers;
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
}

#ifdef LISAUI_DBUS_TEST
void lisaui_dbus_test(void)
{
    lisaui_dbus_t* bus = lisaui_dbus_create();
    if (!bus) {
        perror("Failed to create event bus");
        return;
    }

    LISAUI_LOGI(TAG, "Event bus created");
    lisaui_dbus_subscribe(bus, "test_event", event_handler);
    LISAUI_LOGI(TAG, "Event subscribed");
    lisaui_dbus_publish(bus, "test_event", "Hello, World!");
    LISAUI_LOGI(TAG, "Event published");

    lisaui_dbus_destroy(bus);
}
#endif