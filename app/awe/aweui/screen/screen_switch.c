
#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include <zephyr/logging/log.h>
    #include "zephyr/sys/printk.h"
    #include <zephyr/kernel.h>
    #include <zephyr/logging/log.h>
    LOG_MODULE_REGISTER(screen_switch, LOG_LEVEL_INF);

    #include "lvgl.h"
    #include <stdint.h>
#else
    #include "lvgl/lvgl.h"
    #define LOG_ERR LV_LOG_ERROR
    #define LOG_INF LV_LOG_USER
    #define printk LV_LOG_USER
    #define EINVAL 22
#endif

#include "screen_switch.h"
static struct aweui_scr *aweui_screens[AWEUI_SCR_MAX] = {0};

static struct aweui_scr *aweui_scr_find_by_id(uint32_t id)
{
    if (id >= AWEUI_SCR_MAX) {
        return NULL;
    }

    return aweui_screens[id];
}

int aweui_scr_register(uint32_t id, struct aweui_scr *scr)
{
    if (id >= AWEUI_SCR_MAX) {
        LOG_ERR("Couldn't register screen id:%d", id);
        return -EINVAL;
    }

    if (aweui_screens[id] != NULL) {
        LOG_ERR("Couldn't register screen id:%d, screen is not null", id);
        return -EINVAL;
    }

    aweui_screens[id] = scr;

    return 0;
}

static uint32_t curr_src_id = 0;

static uint32_t aweui_curr_scr_id_get()
{
    return curr_src_id;
}

int aweui_scr_switch_to(uint32_t from, uint32_t to)
{
    struct aweui_scr *scr_from;
    struct aweui_scr *scr_to;

    LOG_INF("try to screen switch from %d to %d", from, to);

    if (from == to) {
        return 0;
    }

    scr_from = aweui_scr_find_by_id(from);
    scr_to = aweui_scr_find_by_id(to);

    if (scr_from == NULL || scr_to == NULL) {
        return -EINVAL;
    }

    LOG_INF("screen switch from %d to %d", from, to);

    if (scr_from->exit) {
        LOG_INF("scr %d exit", from);
        scr_from->exit(scr_from, scr_to);
        LOG_INF("scr %d exit done", from);
    }

    if (scr_to->enter) {
        LOG_INF("scr %d enter", to);
        scr_to->enter(scr_from, scr_to);
        LOG_INF("scr %d done", to);
    }

    return 0;
}

int aweui_scr_switch_to_id(uint32_t to)
{
    int err;
    uint32_t from = aweui_curr_scr_id_get();

    err = aweui_scr_switch_to(from, to);
    if (err == 0) {
        curr_src_id = to;
    }

    return err;
}