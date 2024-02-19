/**
 * @file lv_theme_ultra_marine.h
 *
 */

#ifndef LV_THEME_ULTRA_MARINE_H
#define LV_THEME_ULTRA_MARINE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef __ZEPHYR__
    #include <zephyr/kernel.h>
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif
#define LV_USE_THEME_DEFAULT 1

#if LV_USE_THEME_DEFAULT

/*********************
 *      DEFINES
 *********************/
#define THEME_MODE_LIGHT    0
#define THEME_MODE_DARK     1
#define THEME_MODE_BLACK    2

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the theme
 * @param color_primary the primary color of the theme
 * @param color_secondary the secondary color for the theme
 * @param font pointer to a font to use.
 * @return a pointer to reference this theme later
 */
lv_theme_t * lv_theme_ultra_marine_init(lv_disp_t * disp, 
    lv_color_t color_primary, lv_color_t color_secondary, 
    uint32_t theme_mode, const lv_font_t * font);

/**
 * Get default theme
 * @return a pointer to default theme, or NULL if this is not initialized
 */
lv_theme_t * lv_theme_ultra_marine_get(void);

/**
 * Check if default theme is initialized
 * @return true if default theme is initialized, false otherwise
 */
bool lv_theme_ultra_marine_is_inited(void);

/**********************
 *      MACROS
 **********************/

#endif

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_THEME_ULTRA_MARINE_H*/
