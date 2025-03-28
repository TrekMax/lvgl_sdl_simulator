/**
 * @file lisaui_app_manager.c
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "../app_common/lisaui_type.h"
#include "../app_common/lisaui_app_common.h"

#include "lisaui_app_manager.h"
#include "lisaui_view_manager.h"

#include <time.h>

#if CONFIG_LISAUI_DBUS_ENABLE
#include "lisaui_dbus.h"
#endif

static const char *TAG = "app_manager";

static struct lisaui_app_manager_t m_app_manager = {
    .dbus = NULL,
    .apps = {NULL},
    .manager_view_stack =
        {
            .capacity = LISAUI_VIEW_MANAGER_MAX_CAPACITY,
            .size = 0,
            .head = NULL,
            .tail = NULL,
        },
    .current_appid = UI_APP_ID_NONE,
    .previous_appid = UI_APP_ID_NONE,
    .registered_count = 0,
    .unhidden_count = 0,
    .lock_app_view = false,
};

static int lisaui_app_check_id(const int app_id)
{
    if (app_id >= LISAUI_APP_MAX) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return LISAUI_ERR_APP_ID_INVALID;
    }
    return LISAUI_ERR_APP_OK;
}

int lisaui_app_manager_get_current_appid(void)
{
    // LISAUI_LOGV(TAG, "current app id: %d", m_app_manager.current_appid);
    return m_app_manager.current_appid;
}

static int lisaui_app_set_current_appid(const int app_id)
{
    if (lisaui_app_check_id(app_id) != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return -1;
    }
    m_app_manager.current_appid = app_id;
    return 0;
}

struct lisaui_app_t **lisaui_app_manager_get_app_lists(void)
{
    return m_app_manager.apps;
}

int lisaui_app_manager_get_registered_count(void)
{
    return m_app_manager.registered_count;
}

int lisaui_app_manager_get_unhidden_count(void)
{
    return m_app_manager.unhidden_count;
}

static int lisaui_app_generate_uuid(struct lisaui_app_t *app)
{
    if (app == NULL) {
        LISAUI_LOGE(TAG, "[ui] app is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    if (m_app_manager.registered_count >= LISAUI_APP_MAX) {
        LISAUI_LOGE(TAG, "[ui] app count is full");
        return LISAUI_ERR_APP_FULL;
    }
    // app->info.uuid = m_app_manager.registered_count;
    while (m_app_manager.apps[app->info.uuid] != NULL) {
        app->info.uuid++;
    }
    return LISAUI_ERR_APP_OK;
}

static int lisaui_app_uuid_find_id(const int uuid, int *app_id)
{
    for (int i = 0; i < UI_APP_ID_MAX; i++) {
        if (m_app_manager.apps[i] != NULL && m_app_manager.apps[i]->info.uuid == uuid) {
            *app_id = m_app_manager.apps[i]->info.id;
            return LISAUI_ERR_APP_OK;
        }
    }
    return LISAUI_ERR_APP_NOT_REGISTERED;
}

static int lisaui_app_id_find_uuid(const int app_id, int *uuid)
{
    if (lisaui_app_check_id(app_id) != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return LISAUI_ERR_APP_ID_INVALID;
    }
    for (int i = 0; i < UI_APP_ID_MAX; i++) {
        if (m_app_manager.apps[i] != NULL && m_app_manager.apps[i]->info.id == app_id) {
            *uuid = m_app_manager.apps[i]->info.uuid;
            return LISAUI_ERR_APP_OK;
        }
    }
    return LISAUI_ERR_APP_NOT_REGISTERED;
}

static lisaui_app_manager_hook_t m_app_register_hook = NULL;
static lisaui_app_manager_hook_t m_app_unregister_hook = NULL;
static lisaui_app_manager_hook_t m_app_enter_hook = NULL;
static lisaui_app_manager_hook_t m_app_exit_hook = NULL;
static lisaui_app_manager_hook_t m_app_close_hook = NULL;

int lisaui_app_register(struct lisaui_app_t *app)
{
    int app_id = app->info.id;
    int ret = LISAUI_ERR_OK;
    if (lisaui_app_check_id(app_id) != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return LISAUI_ERR_APP_ID_INVALID;
    }

    if (lisaui_app_generate_uuid(app) != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "[ui] app generate uuid failed");
        return LISAUI_ERR_APP_UNKNOW_FAILED;
    }
    if (m_app_manager.apps[app->info.uuid] != NULL) {
        LISAUI_LOGD(TAG, "m_app_manager.apps[app->info.uuid:%d]: %p", app->info.uuid,
                    m_app_manager.apps[app->info.uuid]);
        LISAUI_LOGW(TAG, "[ui] app already registered");
        return LISAUI_ERR_APP_ALREADY_REGISTERED;
    }
    m_app_manager.apps[app->info.uuid] = app;
    m_app_manager.registered_count++;

    if (app->icon->icon == NULL) {
        app->hidden_icon = true;
    }

    if (app->hidden_icon == false) {
        m_app_manager.unhidden_count++;
    }

    LISAUI_LOGD(TAG, "app(uuid:%d ID:%d:%s) register successful\r", app->info.uuid, app_id, app->icon->title);

    // #if CONFIG_LISAUI_EXEC_HOOK_ENABLE
    LISAUI_EXEC_HOOK(m_app_register_hook, app, ret);
    if (ret != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "TAG, [ui] app register hook failed");
        return ret;
    }
    // #endif
    return LISAUI_ERR_APP_OK;
}

int lisaui_app_unregister(struct lisaui_app_t *app)
{
    int app_id = app->info.id;
    int ret = LISAUI_ERR_OK;
    if (app_id >= UI_APP_ID_MAX) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return LISAUI_ERR_APP_ID_INVALID;
    }
    if (m_app_manager.apps[app->info.uuid] == NULL) {
        LISAUI_LOGW(TAG, "[ui](%s) app not registered", __FUNCTION__);
        return LISAUI_ERR_APP_NOT_REGISTERED;
    }
    m_app_manager.apps[app->info.uuid] = NULL;
    LISAUI_LOGD(TAG, "m_app_manager.apps[app->info.uuid:%d]: %p", app->info.uuid, m_app_manager.apps[app->info.uuid]);
    m_app_manager.registered_count--;
    if (app->hidden_icon == false) {
        m_app_manager.unhidden_count--;
    }
    LISAUI_LOGD(TAG, "[%d:%s] app(%d:%s) unregister successful\r", __LINE__, __func__, app_id, app->icon->title);
    // #if CONFIG_LISAUI_EXEC_HOOK_ENABLE
    LISAUI_EXEC_HOOK(m_app_unregister_hook, app, ret);
    if (ret != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "TAG, [ui] app unregister hook failed");
        return ret;
    }
    // #endif
    return LISAUI_ERR_APP_OK;
}

lisaui_err_t lisaui_app_enter(const int app_id)
{
    int uuid = -1;
    int ret = lisaui_app_id_find_uuid(app_id, &uuid);
    if (ret != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "app(id:%d) not registered", app_id);
        return LISAUI_ERR_APP_NOT_REGISTERED;
    }
    if (m_app_manager.lock_app_view) {
        LISAUI_LOGW(TAG, "app view is locked");
        return LISAUI_ERR_APP_UNKNOW_FAILED;
    }
    if (lisaui_app_manager_get_current_appid() == app_id) {
        LISAUI_LOGW(TAG, "app already in");
        return LISAUI_ERR_APP_ALREADY_IN;
    }

    struct lisaui_app_t *app = m_app_manager.apps[uuid];
    if (app->get_root_view() == NULL) {
        // LISAUI_LOGW(TAG, "------------>app(%s) root view is NULL", app->icon->title);
        if (app->create(NULL) != LISAUI_ERR_APP_OK) {
            LISAUI_LOGE(TAG, "app(%s) create failed", app->icon->title);
            return LISAUI_ERR_APP_UNKNOW_FAILED;
        }
        LISAUI_LOGI(TAG, "app(%s) create success", app->icon->title);
    }
    if (app->enter == NULL) {
        LISAUI_LOGE(TAG, "TAG, [ui] app enter is NULL");
        return LISAUI_ERR_APP_ENTER_FAILED;
    }
    if (app->enter()) {
        LISAUI_LOGE(TAG, "TAG, [ui] app enter failed");
        return LISAUI_ERR_APP_UNKNOW_FAILED;
    }
#if CONFIG_LISAUI_EXEC_HOOK_ENABLE
    LISAUI_EXEC_HOOK(m_app_enter_hook, app, ret);
    if (ret != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "TAG, [ui] app enter hook failed");
        return ret;
    }
#else
    lisaui_view_page_t *page = (lisaui_view_page_t *)lisaui_malloc(sizeof(lisaui_view_page_t));
    if (page == NULL) {
        LISAUI_LOGE(TAG, "TAG, [ui] malloc failed");
        return LISAUI_ERR_NO_MEMORY;
    }
    memset(page, 0, sizeof(lisaui_view_page_t));
    page->root = (lisaui_view_t *)app->get_root_view();
    page->app_id = app->info.id;
    // LISAUI_LOGI(TAG, "[ui] lv_disp_load_scr page:%p page->root: %p", page, page->root);
    if (page->root == NULL) {
        LISAUI_LOGE(TAG, "TAG, [ui] view page root is NULL");
        return LISAUI_ERR_NO_MEMORY;
    }

    // lisaui_view_manager_print_usage(&m_app_manager.manager_view_stack);
    lisaui_view_manager_push(&m_app_manager.manager_view_stack, page);
    // lisaui_view_manager_print_usage(&m_app_manager.manager_view_stack);
    lv_disp_load_scr(page->root);
    // lisaui_memory_monitor(NULL);
#endif
    m_app_manager.previous_appid = lisaui_app_manager_get_current_appid();
    lisaui_app_set_current_appid(app->info.id);
    LISAUI_LOGI(TAG, "app(%s) enter success", app->icon->title);
    return LISAUI_ERR_APP_OK;
}

lisaui_err_t lisaui_app_exit(const int app_id)
{
    if (lisaui_app_check_id(app_id) != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return LISAUI_ERR_APP_ID_INVALID;
    }
    int uuid = -1;
    int ret = lisaui_app_id_find_uuid(app_id, &uuid);
    if (ret != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "app(id:%d) not registered", app_id);
        return LISAUI_ERR_APP_NOT_REGISTERED;
    }
    if (m_app_manager.lock_app_view) {
        LISAUI_LOGW(TAG, "app view is locked");
        return LISAUI_ERR_APP_UNKNOW_FAILED;
    }
    struct lisaui_app_t *app = m_app_manager.apps[uuid];
    if (app == NULL) {
        LISAUI_LOGE(TAG, "[ui](%s) app(id:%d) not registered", __FUNCTION__, app_id);
        return LISAUI_ERR_APP_NOT_REGISTERED;
    }
    LISAUI_LOGV(TAG, "[ui] exit app: %d, %s", app_id, app->icon->title);
    if (app->exit) {
        if (app->exit()) {
            LISAUI_LOGE(TAG, "[ui] app exit failed");
            return LISAUI_ERR_APP_UNKNOW_FAILED;
        }
    }
#if CONFIG_LISAUI_EXEC_HOOK_ENABLE
    LISAUI_EXEC_HOOK(m_app_exit_hook, app, ret);
    // if (ret != LISAUI_ERR_OK) {
    //     LISAUI_LOGE(TAG, "TAG, [ui] app exit hook failed");
    //     return ret;
    // }
#else
    // lisaui_view_manager_print_usage(&m_app_manager.manager_view_stack);
    lisaui_view_page_t *page = NULL;
    if (lisaui_view_manager_pop(&m_app_manager.manager_view_stack, &page) != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "[ui] view page is NULL");
        return LISAUI_ERR_NO_MEMORY;
    }
    lisaui_free(page);
    page = NULL;
    // lisaui_view_manager_print_usage(&m_app_manager.manager_view_stack);

    if (lisaui_view_manager_get_current(&m_app_manager.manager_view_stack, &page) != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "[ui] view page is NULL");
        return LISAUI_ERR_NO_MEMORY;
    }
    if (page == NULL) {
        LISAUI_LOGE(TAG, "[ui] view page is NULL");
        return LISAUI_ERR_NO_MEMORY;
    }
    // lisaui_app_set_current_appid(page->app_id);
    if (page->root != NULL) {
        lv_disp_load_scr(page->root);
    } else {
        LISAUI_LOGI(TAG, "[ui] view page prev is NULL");
    }
    // LISAUI_LOGI(TAG, "app(%s) exit success", app->icon->title);
    // lisaui_memory_monitor(NULL);
#endif
    lisaui_app_set_current_appid(m_app_manager.previous_appid);
    LISAUI_LOGI(TAG, "app(%s) exit success", app->icon->title);
    return LISAUI_ERR_APP_OK;
}

lisaui_err_t lisaui_app_close(const int app_id)
{
    if (lisaui_app_check_id(app_id) != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return LISAUI_ERR_APP_ID_INVALID;
    }

    int uuid = -1;
    int ret = lisaui_app_id_find_uuid(app_id, &uuid);
    if (ret != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "app(id:%d) not registered", app_id);
        return LISAUI_ERR_APP_NOT_REGISTERED;
    }
    if (m_app_manager.lock_app_view) {
        LISAUI_LOGW(TAG, "app view is locked");
        return LISAUI_ERR_APP_UNKNOW_FAILED;
    }
    struct lisaui_app_t *app = m_app_manager.apps[uuid];
    if (app == NULL) {
        LISAUI_LOGE(TAG, "[ui](%s) app not registered", __FUNCTION__);
        return LISAUI_ERR_APP_NOT_REGISTERED;
    }
    lisaui_app_exit(app_id);
    if (app->destroy) {
        if (app->destroy()) {
            LISAUI_LOGE(TAG, "[ui] app destroy failed");
            return LISAUI_ERR_APP_UNKNOW_FAILED;
        } else {
            LISAUI_LOGV(TAG, "[ui] app destroy success");
        }
    }
#if CONFIG_LISAUI_EXEC_HOOK_ENABLE
    LISAUI_EXEC_HOOK(m_app_close_hook, app, ret);
    if (ret != LISAUI_ERR_OK) {
        LISAUI_LOGE(TAG, "TAG, [ui] app close hook failed");
        return ret;
    }
#endif
    LISAUI_LOGI(TAG, "app(%s) destroy success", app->icon->title);
    // lisaui_memory_monitor(NULL);
    return LISAUI_ERR_APP_OK;
}

lisaui_err_t lisaui_app_manager_enter_view(lisaui_view_page_t *page)
{
    if (page == NULL) {
        LISAUI_LOGE(TAG, "[ui] view page is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    LISAUI_LOGW(TAG, "[%d:%s]--->[TODO] unimplemented", __LINE__, __func__);

    return LISAUI_ERR_OK;
}

#ifdef __APPLE__
    #include <mach-o/getsect.h>
    #include <mach-o/dyld.h> // 包含 _dyld_get_image_header 的头文件
    extern const app_entry_t ___start___DATA_lisaui_apps;
    extern const app_entry_t __stop___DATA_lisaui_apps;
    #define LISAUI_APP_LISTS_START &(___start___DATA_lisaui_apps)
    #define LISAUI_APP_LISTS_END   &(___stop___DATA_lisaui_apps)
#else
    extern const app_entry_t __lisaui_apps_start[];
    extern const app_entry_t __lisaui_apps_end[];
    #define __LISAUI_APP_LISTS_START __lisaui_apps_start
    #define __LISAUI_APP_LISTS_END   __lisaui_apps_end
#endif

lisaui_err_t lisaui_app_manager_init_app(const app_entry_t *app, int app_count)
{
    if (app == NULL) {
        LISAUI_LOGE(TAG, "app is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    for (int i = 0; i < app_count; i++) {
        if (app[i].app_init_func) {
            LISAUI_LOGV(TAG, "Initializing app(%s)", app[i].app_name);
            if (app[i].app_init_func() == LISAUI_ERR_OK) {
                LISAUI_LOGV(TAG, "app(%s) init success", app[i].app_name);
            }
        }
    }
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_manager_init(void)
{
    // LISAUI_LOGD(TAG, "Initializing \r\n\tlisaui_apps[%p:%p - %ld]",
    //         __LISAUI_APP_LISTS_START, __LISAUI_APP_LISTS_END,
    //         (__LISAUI_APP_LISTS_START - __LISAUI_APP_LISTS_END));
    m_app_manager.current_appid = UI_APP_ID_NONE;
    m_app_manager.registered_count = 0;
    m_app_manager.unhidden_count = 0;
    lisaui_app_manager_default_hook_init();
#if CONFIG_LISAUI_DBUS_ENABLE
    if (m_app_manager.dbus == NULL) {
        // LISAUI_LOGW(TAG, "App manager bus already initialized");
        m_app_manager.dbus = lisaui_dbus_create();
        if (!m_app_manager.dbus) {
            LISAUI_LOGE(TAG, "Failed to create event bus");
            return LISAUI_ERR_FAIL;
        }
    }
    LISAUI_LOGI(TAG, "App manager bus created");
#endif
    // view_manager 必须在 app_init 之前初始化
    lisaui_view_manager_init(&m_app_manager.manager_view_stack);

#ifdef __APPLE__
    // 获取当前可执行文件的 Mach-O 头
    // const struct mach_header *header = _dyld_get_image_header(0);
    const struct mach_header_64 *header = (const struct mach_header_64 *)_dyld_get_image_header(0);
    unsigned long size;
    // 获取 __DATA 段的 .lisaui_apps 节的数据
    app_entry_t *apps = (app_entry_t *)getsectiondata(
        header,  // 当前可执行文件的 Mach-O 头
        "__DATA",             // 段名称
        ".lisaui_apps",       // 节名称
        &size                // 输出参数，返回节的大小
    );
    if (apps != NULL) {
        size_t count = size / sizeof(app_entry_t);
        lisaui_app_manager_init_app(apps, count);
    }
#else
    if (__LISAUI_APP_LISTS_START != NULL) {
        size_t count = (__LISAUI_APP_LISTS_END - __LISAUI_APP_LISTS_START);
        lisaui_app_manager_init_app(__LISAUI_APP_LISTS_START, count);
    }
#endif

#if CONFIG_LISAUI_DBUS_ENABLE
    lisaui_dbus_publish(m_app_manager.dbus, LISAUI_DBUS_APP_UPDATE, NULL);
#endif
    return LISAUI_ERR_OK;
}

#if CONFIG_LISAUI_DBUS_ENABLE
lisaui_err_t lisaui_app_manager_get_bus(lisaui_dbus_t **dbus)
{
    if (dbus == NULL) {
        LISAUI_LOGE(TAG, "dbus is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    if (m_app_manager.dbus == NULL) {
        // LISAUI_LOGE(TAG, "App manager bus is NULL(App manager not initialized)");
        // return LISAUI_ERR_FAIL;
        m_app_manager.dbus = lisaui_dbus_create();
        if (!m_app_manager.dbus) {
            LISAUI_LOGE(TAG, "Failed to create event bus");
            return LISAUI_ERR_FAIL;
        }
        LISAUI_LOGI(TAG, "Event bus created");
    }
    *dbus = m_app_manager.dbus;
    return LISAUI_ERR_OK;
}
#endif
lisaui_err_t lisaui_app_manager_show_app_info(struct lisaui_app_t *app)
{
    if (app == NULL) {
        // LISAUI_LOGI(TAG, "app is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    LISAUI_LOGI(TAG, "[%s]: %s", app->info.package_name, app->info.name);
    LISAUI_LOGI(TAG, "\t\tmemory usage: %ld", sizeof(*app));
    LISAUI_LOGI(TAG, "\t\tid:%d, uuid:%d", app->info.id, app->info.uuid);
    if (app->icon == NULL) {
        LISAUI_LOGE(TAG, "icon is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    LISAUI_LOGI(TAG, "\t\ticon %s %dx%d zoom:%d", app->icon->title, app->icon->icon_width, app->icon->icon_height,
                app->icon->zoom);
    LISAUI_LOGI(TAG, "\t\thidden_icon: %d", app->hidden_icon);
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_manager_show_all_app_info(void)
{
    LISAUI_PRINTK("======================================================\r\n");
    LISAUI_LOGI(TAG, "Registered apps: %d", m_app_manager.registered_count);
    for (int i = 0; i < UI_APP_ID_MAX; i++) {
        lisaui_app_manager_show_app_info(m_app_manager.apps[i]);
    }
    LISAUI_PRINTK("======================================================\r\n");
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_manager_get_app_by_id(const int app_id, struct lisaui_app_t **app)
{
    if (lisaui_app_check_id(app_id) != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return LISAUI_ERR_APP_ID_INVALID;
    }
    int uuid = -1;
    int ret = lisaui_app_id_find_uuid(app_id, &uuid);
    if (ret != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "app(id:%d) not registered", app_id);
        return LISAUI_ERR_APP_NOT_REGISTERED;
    }
    *app = m_app_manager.apps[uuid];
    return LISAUI_ERR_APP_OK;
}

lisaui_err_t lisaui_app_manager_get_app_by_uuid(const int uuid, struct lisaui_app_t **app)
{
    if (uuid >= LISAUI_APP_MAX) {
        LISAUI_LOGE(TAG, "[ui] invalid app uuid: %d", uuid);
        return LISAUI_ERR_APP_ID_INVALID;
    }
    *app = m_app_manager.apps[uuid];
    return LISAUI_ERR_APP_OK;
}

struct lisaui_app_t *lisaui_app_manager_get_app(const int app_id)
{
    if (lisaui_app_check_id(app_id) != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "[ui] invalid app id: %d", app_id);
        return NULL;
    }
    int uuid = -1;
    int ret = lisaui_app_id_find_uuid(app_id, &uuid);
    if (ret != LISAUI_ERR_APP_OK) {
        LISAUI_LOGE(TAG, "app(id:%d) not registered", app_id);
        return NULL;
    }
    return m_app_manager.apps[uuid];
}

lisaui_err_t lisaui_app_manager_get_view_stack(lisaui_view_stack_t **view_stask)
{
    *view_stask = &m_app_manager.manager_view_stack;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_lock(void)
{
    m_app_manager.lock_app_view = true;
    return LISAUI_ERR_OK;
}
lisaui_err_t lisaui_app_unlock(void)
{
    m_app_manager.lock_app_view = false;
    return LISAUI_ERR_OK;
}

bool lisaui_app_get_lock_state(void)
{
    return m_app_manager.lock_app_view;
}

/***************************** App manager hook *******************************/
lisaui_err_t LISAUI_DEFINE_WEAK_FUNC lisaui_app_register_lvgl_hook(struct lisaui_app_t *app)
{
    return LISAUI_ERR_OK;
}

lisaui_err_t LISAUI_DEFINE_WEAK_FUNC lisaui_app_unregister_lvgl_hook(struct lisaui_app_t *app)
{
    return LISAUI_ERR_OK;
}

lisaui_err_t LISAUI_DEFINE_WEAK_FUNC lisaui_app_enter_lvgl_hook(struct lisaui_app_t *app)
{
    return LISAUI_ERR_OK;
}

lisaui_err_t LISAUI_DEFINE_WEAK_FUNC lisaui_app_exit_lvgl_hook(struct lisaui_app_t *app)
{
    return LISAUI_ERR_OK;
}

lisaui_err_t LISAUI_DEFINE_WEAK_FUNC lisaui_app_close_lvgl_hook(struct lisaui_app_t *app)
{
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_manager_set_register_app_hook(lisaui_app_manager_hook_t hook)
{
    if (hook == NULL) {
        LISAUI_LOGW(TAG, "[ui] hook is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    m_app_register_hook = hook;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_manager_set_unregister_app_hook(lisaui_app_manager_hook_t hook)
{
    if (hook == NULL) {
        LISAUI_LOGW(TAG, "[ui] hook is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    m_app_unregister_hook = hook;
    return LISAUI_ERR_OK;
}
lisaui_err_t lisaui_app_manager_set_enter_app_hook(lisaui_app_manager_hook_t hook)
{
    if (hook == NULL) {
        LISAUI_LOGW(TAG, "[ui] hook is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    m_app_enter_hook = hook;
    return LISAUI_ERR_OK;
}
lisaui_err_t lisaui_app_manager_set_exit_app_hook(lisaui_app_manager_hook_t hook)
{
    if (hook == NULL) {
        LISAUI_LOGW(TAG, "[ui] hook is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    m_app_exit_hook = hook;
    return LISAUI_ERR_OK;
}
lisaui_err_t lisaui_app_manager_set_close_app_hook(lisaui_app_manager_hook_t hook)
{
    if (hook == NULL) {
        LISAUI_LOGW(TAG, "[ui] hook is NULL");
        return LISAUI_ERR_INVALID_PARAM;
    }
    m_app_close_hook = hook;
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_manager_default_hook_init(void)
{
    lisaui_app_manager_set_register_app_hook(lisaui_app_register_lvgl_hook);
    lisaui_app_manager_set_unregister_app_hook(lisaui_app_unregister_lvgl_hook);
    lisaui_app_manager_set_enter_app_hook(lisaui_app_enter_lvgl_hook);
    lisaui_app_manager_set_exit_app_hook(lisaui_app_exit_lvgl_hook);
    lisaui_app_manager_set_close_app_hook(lisaui_app_close_lvgl_hook);
    return LISAUI_ERR_OK;
}

lisaui_err_t lisaui_app_manager_default_hook_deinit(void)
{
    lisaui_app_manager_set_register_app_hook(NULL);
    lisaui_app_manager_set_unregister_app_hook(NULL);
    lisaui_app_manager_set_enter_app_hook(NULL);
    lisaui_app_manager_set_exit_app_hook(NULL);
    lisaui_app_manager_set_close_app_hook(NULL);
    return LISAUI_ERR_OK;
}