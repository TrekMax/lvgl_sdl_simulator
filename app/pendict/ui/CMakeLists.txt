# SPDX-License-Identifier: Apache-2.0


SET(SOURCES 
        ui.c
        ui_helpers.c
        # ui_font_PocketDictPenRegular.c
        lv_font_chinese_18.c

        assets/ui_img__charging_0_png.c
        assets/ui_img__guide_scan_png.c

        assets/ui_img__angle_left_double_png.c
        assets/ui_img__launcher_composition_png.c
        assets/ui_img__launcher_scan_png.c
        assets/ui_img__launcher_setting_png.c
        assets/ui_img__launcher_fav_png.c
        assets/ui_img__launcher_practice_png.c

        assets/ui_img__status_battery_1_png.c
        assets/ui_img__status_battery_2_png.c
        assets/ui_img__status_battery_3_png.c
        assets/ui_img__status_battery_4_png.c
        assets/ui_img__status_battery_5_png.c

        assets/ui_img__status_charging_1_png.c
        assets/ui_img__status_charging_2_png.c
        assets/ui_img__status_charging_3_png.c
        assets/ui_img__status_charging_4_png.c
        assets/ui_img__status_charging_5_png.c

        # lv_font_chinese_20.c
        # myFont_bin.c
        )
# zephyr_include_directories(./)

# zephyr_library_sources(
        
        # )
        
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library(ui ${SOURCES})