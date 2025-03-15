
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/sdl/sdl.h"

#include "lisaui/ui.h"

#include "version.h"
#include "config.h"
#include "utils_log.h"
#include <stdio.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int tick_thread(void *data);

static const char *TAG = "LVGL";

int show_info()
{
    printf("Hello LVGL!\n");
    LOGI(TAG, "===============================");
    LOGI(TAG, "Author: %s", COMMIT_AUTHOR);
    LOGI(TAG, "Email: %s", AUTHOR_EMAIL);
    LOGI(TAG, "Commit version: %s", COMMIT_COUNT);
    LOGI(TAG, "Commit hash: %s", COMMIT_HASH);
    LOGI(TAG, "Compile Time: %s %s", __TIME__, __DATE__);
    LOGI(TAG, "===============================");

    return 0;
}

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

int main(int argc, char **argv)
{
    (void)argc; /*Unused*/
    (void)argv; /*Unused*/

    show_info();

    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    hal_init();

    lisaui_ui_init();
    // lv_demo_physics();

    while (1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_timer_handler();
        usleep(5 * 1000);
    }

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for LVGL
 */
static void hal_init(void)
{
    /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    sdl_init();
    SDL_CreateThread(tick_thread, "tick", NULL);

    /*Create a display buffer*/
    static lv_color_t buf[SDL_HOR_RES * SDL_VER_RES];
    static lv_disp_draw_buf_t disp_draw_buf;
    lv_disp_draw_buf_init(&disp_draw_buf, buf, NULL, SDL_HOR_RES * SDL_VER_RES);

    /*Create a display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.draw_buf = &disp_draw_buf;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_drv_register(&disp_drv);

    /* Add a mouse as input device */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);

    LOGI(TAG, "SDL_HOR_RES: %d, SDL_VER_RES: %d", SDL_HOR_RES, SDL_VER_RES);
}

/**
 * A task to measure the elapsed time for LVGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void *data)
{
    (void)data;

    while (1) {
        SDL_Delay(5);
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}
#if 0
/**
 * Print the memory usage periodically
 * @param param
 */
static void memory_monitor(lv_task_t *param)
{
    (void)param; /*Unused*/

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    // printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n", (int)mon.total_size - mon.free_size,
    // mon.used_pct,
    //        mon.frag_pct, (int)mon.free_biggest_size);
    printf("------------Memory usage------------\n");
    printf("\tTotal size              : %0.3lfKB(%d Byte)\n", mon.total_size / 1024.0, mon.total_size);
    printf("\tFree count              : %d\n", mon.free_cnt);
    printf("\tFree size               : %d\n", mon.free_size);
    printf("\tFree biggest size       : %d\n", mon.free_biggest_size);
    printf("\tUsed count              : %d\n", mon.used_cnt);
    printf("\tMax used                : %0.3lfKB(%d Byte)\n", mon.max_used / 1024.0, mon.max_used);
    printf("\tUsed percentage         : %d\n", mon.used_pct);
    printf("\tFragmentation percentage: %d\n", mon.frag_pct);
    printf("\n");

    lisaui_view_manger_print_usage();
}
#endif