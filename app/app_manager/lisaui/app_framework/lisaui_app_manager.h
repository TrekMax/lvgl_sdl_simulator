/**
 * @file lisaui_app_manager.h
 * @author Tianshuang Ke (dske@listenai.com)
 * @brief 应用程序管理器头文件
 * @version 0.1
 * @date 2025-02-24
 *
 * @copyright Copyright (c) 2021 - 2025 shenzhen listenai co., ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef __LISAUI_APP_MANAGER_H__
#define __LISAUI_APP_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "lisaui_dbus.h"
#include "lisaui_view_manager.h"

#ifndef APP_ICON_ZOOM
#define APP_ICON_ZOOM(x) ((uint16_t)((x) * 256))
#endif

struct app_icon_t {
    const char *title;
    lisaui_icon_res_t *icon;
    uint16_t zoom;
    uint16_t icon_width;
    uint16_t icon_height;
};

// typedef enum _lisaui_app_type {
//     LISAUI_APP_TYPE_NORMAL = 0,
//     LISAUI_APP_TYPE_USER,
//     LISAUI_APP_TYPE_SYSTEM, // 系统应用,会自动创建并启用
// } lisaui_app_type_t;

#define LISAUI_APP_TYPE_NORMAL      (0)
#define LISAUI_APP_TYPE_USER        (1)
#define LISAUI_APP_TYPE_SYSTEM      (2)
#define LISAUI_APP_TYPE_LAUNCHER    (3)
struct app_info_t {
    const char *name;
    const char *package_name;
    const int id;
    int uuid;
    const int type;
};

struct lisaui_app_t {
    lisaui_err_t (*create)(void *parent);
    lisaui_err_t (*destroy)(void);
    lisaui_err_t (*enter)(void);
    lisaui_err_t (*exit)(void);

    void *(*get_root_view)(void);

    struct app_info_t info;
    struct app_icon_t *icon;
    uint8_t hidden_icon;
    struct lisaui_app_t *app;
    lisaui_view_stack_t app_view_stack;
};

typedef struct {
    const char *app_name;
    lisaui_err_t (*app_init_func)(void);
} app_entry_t;

#define LISAUI_APP_MAX (30)

struct lisaui_app_manager_t {
    struct lisaui_app_t *apps[LISAUI_APP_MAX];
    lisaui_dbus_t *dbus;
    lisaui_view_stack_t manager_view_stack;
    int current_appid;
    int previous_appid;
    int registered_count;
    int unhidden_count;
    bool lock_app_view;
};

#ifdef __APPLE__
    // macOS 的 Mach-O 格式要求段和节名称
    #define LISAUI_APP_SECTION __attribute__((used, section("__DATA,.lisaui_apps")))
#else
    // Linux 或其他平台的 ELF 格式
    #define LISAUI_APP_SECTION __attribute__((used, section(".lisaui_apps")))
#endif

#define CONFIG_LISAUI_APP_TEMPLATE_MACRO_ENABLE 1
#ifndef CONFIG_LISAUI_APP_DEFAULT_VIEW_DEPTH
#define CONFIG_LISAUI_APP_DEFAULT_VIEW_DEPTH 10
#endif

#if CONFIG_LISAUI_APP_TEMPLATE_MACRO_ENABLE
#define LISAUI_REGISTER_APP(name, p_app, init_func)                                                                    \
    LISAUI_APP_SECTION                                                                                                 \
    const app_entry_t lisaui_app_##name##_entry = {                                                                    \
        .app_name = #name,                                                                                             \
        .app_init_func = init_func,                                                                                    \
    };

#define LISAUI_USE_APP(name)                                                                                           \
    extern const app_entry_t lisaui_app_##name##_entry;                                                                \
    __attribute__((unused)) void *_app_##name = (void *)&lisaui_app_##name##_entry

#define LISAUI_DECLARE_APP_FUNC(name, func_create, func_destroy, func_enter, func_exit, func_get_page)                 \
    lisaui_err_t app_##name##_##func_create(void *parent);                                                             \
    lisaui_err_t app_##name##_##func_destroy(void);                                                                    \
    lisaui_err_t app_##name##_##func_enter(void);                                                                      \
    lisaui_err_t app_##name##_##func_exit(void);                                                                       \
    void *app_##name##_get_page(void);

#define LISAUI_DEFINE_APP_FUNC(name, func, param, entity)                                                              \
    app_##name##_##func(param)                                                                                         \
    {                                                                                                                  \
        entity LISAUI_LOGI(TAG, "[%d:%s] " #func "\n", __LINE__, __func__);                                            \
    }

#define LISAUI_DEFINE_APP(app, app_id, name_cn, name_en, app_icon, init_entity)                                        \
    static struct app_icon_t app_icon_res_##app = {                                                                    \
        .title = name_cn,                                                                                              \
        .icon = app_icon,                                                                                              \
        .zoom = APP_ICON_ZOOM(0),                                                                                      \
    };                                                                                                                 \
    struct lisaui_app_t app_##app = {                                                                                  \
        .create = app_##app##_create,                                                                                  \
        .destroy = app_##app##_destroy,                                                                                \
        .enter = app_##app##_enter,                                                                                    \
        .exit = app_##app##_exit,                                                                                      \
        .get_root_view = app_##app##_get_page,                                                                         \
        .info =                                                                                                        \
            {                                                                                                          \
                .name = name_en,                                                                                       \
                .package_name = "com.listenai.lisaui." #app,                                                           \
                .id = app_id,                                                                                          \
            },                                                                                                         \
        .icon = &app_icon_res_##app,                                                                                   \
        .app_view_stack =                                                                                              \
            {                                                                                                          \
                .capacity = CONFIG_LISAUI_APP_DEFAULT_VIEW_DEPTH,                                                      \
                .size = 0,                                                                                             \
                .head = NULL,                                                                                          \
                .tail = NULL,                                                                                          \
            },                                                                                                         \
    };                                                                                                                 \
    lisaui_err_t app_##app##_init(void)                                                                                \
    {                                                                                                                  \
        lisaui_app_register(&app_##app);                                                                               \
        init_entity;                                                                                                   \
        return LISAUI_ERR_OK;                                                                                          \
    }                                                                                                                  \
    LISAUI_REGISTER_APP(app, &app_##app, app_##app##_init)

#define LISAUI_APP_INIT_CHECK(app_id, obj, err, ret)                                                                   \
    if (obj == NULL) {                                                                                                 \
        struct lisaui_app_t *app = lisaui_app_manager_get_app(app_id);                                                 \
        if (app == NULL) {                                                                                             \
            LISAUI_LOGE(TAG, "[%s] %d not registered", __FUNCTION__, app_id);                                          \
            return err;                                                                                                \
        }                                                                                                              \
        if (lisaui_app_enter(app_id) != LISAUI_ERR_OK) {                                                               \
            LISAUI_LOGE(TAG, "[%s] %s not init", __FUNCTION__, app->info.name);                                        \
            return err;                                                                                                \
        }                                                                                                              \
        obj = app->get_root_view();                                                                                    \
        if (obj == NULL) {                                                                                             \
            return err;                                                                                                \
        }                                                                                                              \
    }

#define LISAUI_APP_ENTITY(app)     app_##app
#define LISAUI_APP_VIEW_STACK(app) (app_##app.app_view_stack)
#endif

#define LISAUI_EXEC_HOOK(hook, app, ret)                                                                               \
    if (hook) {                                                                                                        \
        ret = hook(app);                                                                                               \
    }

#define LISAUI_DEFINE_WEAK_FUNC __attribute__((weak))

/**
 * @brief App manager 相关 hook 函数，用于扩展应用程序管理器功能
 *
 * @note 目前只支持 APP 注册、注销、进入、退出、关闭时的 hook, 且只支持一个 hook
 *
 */
typedef lisaui_err_t (*lisaui_app_manager_app_hook_t)(struct lisaui_app_t *app);
lisaui_err_t lisaui_app_manager_set_register_app_hook(lisaui_app_manager_app_hook_t hook);
lisaui_err_t lisaui_app_manager_set_unregister_app_hook(lisaui_app_manager_app_hook_t hook);
lisaui_err_t lisaui_app_manager_set_enter_app_hook(lisaui_app_manager_app_hook_t hook);
lisaui_err_t lisaui_app_manager_set_exit_app_hook(lisaui_app_manager_app_hook_t hook);
lisaui_err_t lisaui_app_manager_set_close_app_hook(lisaui_app_manager_app_hook_t hook);
lisaui_err_t lisaui_app_manager_default_hook_init(void);
lisaui_err_t lisaui_app_manager_default_hook_deinit(void);

typedef lisaui_err_t (*lisaui_app_manager_hook_t)(struct lisaui_app_manager_t *app_manager);
lisaui_err_t lisaui_app_manager_set_hook(lisaui_app_manager_hook_t hook);

lisaui_err_t lisaui_app_register(struct lisaui_app_t *app);
lisaui_err_t lisaui_app_unregister(struct lisaui_app_t *app);
lisaui_err_t lisaui_app_enter(const int app_id);
lisaui_err_t lisaui_app_exit(const int app_id);
lisaui_err_t lisaui_app_close(const int app_id);

lisaui_err_t lisaui_app_lock(void);
lisaui_err_t lisaui_app_unlock(void);
bool lisaui_app_get_lock_state(void);

lisaui_err_t lisaui_app_manager_init(void);
lisaui_err_t lisaui_app_manager_get_bus(lisaui_dbus_t **dbus);
lisaui_err_t lisaui_app_manager_get_view_stack(lisaui_view_stack_t **view_stask);

lisaui_err_t lisaui_app_manager_show_app_info(struct lisaui_app_t *app);
lisaui_err_t lisaui_app_manager_show_all_app_info(void);
lisaui_err_t lisaui_app_manager_get_app_by_uuid(const int uuid, struct lisaui_app_t **app);
lisaui_err_t lisaui_app_manager_get_app_by_id(const int app_id, struct lisaui_app_t **app);

int lisaui_app_manager_get_registered_count(void);
int lisaui_app_manager_get_unhidden_count(void);
int lisaui_app_manager_get_current_appid(void);

struct lisaui_app_t **lisaui_app_manager_get_app_lists(void);
struct lisaui_app_t *lisaui_app_manager_get_app(const int app_id);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif // __LISAUI_APP_MANAGER_H__