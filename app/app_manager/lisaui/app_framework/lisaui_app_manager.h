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
#include "../app_common/lisaui_type.h"
#include "lisaui_dbus.h"

#ifndef APP_ICON_ZOOM
#define APP_ICON_ZOOM(x) ((uint16_t)((x) * 256))
#endif

struct app_icon_t {
    const char *title;
    const uint8_t *icon;
    uint16_t zoom;
    uint16_t icon_width;
    uint16_t icon_height;
};

// typedef 
// enum _lisaui_app_type {
//     LISAUI_APP_TYPE_NORMAL = 0,
//     LISAUI_APP_TYPE_USER,
//     LISAUI_APP_TYPE_SYSTEM, // 系统应用,会自动创建并启用
// } lisaui_app_type_t;

#define LISAUI_APP_TYPE_NORMAL  (0)
#define LISAUI_APP_TYPE_USER    (1)
#define LISAUI_APP_TYPE_SYSTEM  (2)
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
};

typedef struct {
    const char *app_name;
    lisaui_err_t (*app_init_func)(void);
} app_entry_t;

#define LISAUI_APP_MAX (20)

struct lisaui_app_manager_t {
    struct lisaui_app_t *apps[LISAUI_APP_MAX];
    lisaui_dbus_t *dbus;
    int current_appid;
    int previous_appid;
    int registered_count;
    int unhidden_count;
};

#ifdef __APPLE__
    // macOS 的 Mach-O 格式要求段和节名称
    #define LISAUI_APP_SECTION __attribute__((used, section("__DATA,.lisaui_apps")))
#else
    // Linux 或其他平台的 ELF 格式
    #define LISAUI_APP_SECTION __attribute__((used, section(".lisaui_apps")))
#endif

#define REGISTER_LISAUI_APP(name, p_app, init_func)                             \
    LISAUI_APP_SECTION                                                         \
    const app_entry_t lisaui_app_##name##_entry = {                            \
        .app_name = #name,                                                     \
        .app_init_func = init_func,                                            \
    };

#define LISAUI_USE_APP(name)                                                   \
    extern const app_entry_t lisaui_app_##name##_entry;                        \
    __attribute__((unused)) void *_app_##name = (void *)&lisaui_app_##name##_entry

lisaui_err_t lisaui_app_register(struct lisaui_app_t *app);
lisaui_err_t lisaui_app_unregister(struct lisaui_app_t *app);

typedef lisaui_err_t (*lisaui_app_register_hook_t)(struct lisaui_app_t *app);
lisaui_err_t lisaui_app_set_app_register_hook(lisaui_app_register_hook_t hook);
lisaui_err_t lisaui_app_set_app_unregister_hook(lisaui_app_register_hook_t hook);

lisaui_err_t lisaui_app_enter(const int app_id);
lisaui_err_t lisaui_app_exit(const int app_id);
lisaui_err_t lisaui_app_close(const int app_id);

lisaui_err_t lisaui_app_manager_init(void);
lisaui_err_t lisaui_app_show_info(struct lisaui_app_t *app);
lisaui_err_t lisaui_app_show_all_info(void);

int lisaui_app_get_current_appid(void);
int lisaui_app_get_registered_count(void);
int lisaui_app_get_unhidden_count(void);
struct lisaui_app_t **lisaui_app_get_app_lists(void);

lisaui_err_t lisaui_get_app_manager_bus(lisaui_dbus_t **dbus);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif // __LISAUI_APP_MANAGER_H__