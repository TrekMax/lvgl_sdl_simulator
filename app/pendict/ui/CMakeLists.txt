# SPDX-License-Identifier: Apache-2.0

SET(SOURCES
    assets/bitmaps/ui_img__charging_0_png.c
    assets/bitmaps/ui_img__guide_scan_png.c

    assets/bitmaps/ui_img__angle_left_double_png.c
    assets/bitmaps/ui_img__launcher_composition_png.c
    assets/bitmaps/ui_img__launcher_scan_png.c
    assets/bitmaps/ui_img__launcher_setting_png.c
    assets/bitmaps/ui_img__launcher_fav_png.c
    assets/bitmaps/ui_img__launcher_practice_png.c

    assets/bitmaps/ui_img__status_battery_1_png.c
    assets/bitmaps/ui_img__status_battery_2_png.c
    assets/bitmaps/ui_img__status_battery_3_png.c
    assets/bitmaps/ui_img__status_battery_4_png.c
    assets/bitmaps/ui_img__status_battery_5_png.c

    assets/bitmaps/ui_img__status_charging_1_png.c
    assets/bitmaps/ui_img__status_charging_2_png.c
    assets/bitmaps/ui_img__status_charging_3_png.c
    assets/bitmaps/ui_img__status_charging_4_png.c
    assets/bitmaps/ui_img__status_charging_5_png.c

    assets/bitmaps/xiaoling_thinking_s.c
    assets/bitmaps/xiaoling_listening_s.c
    assets/bitmaps/xiaoling_standby_s.c

    ./assets/fonts/lv_font_chinese_18.c

    ui.c
    ui_helpers.c
    
    ./utils/img_utils.c
    ./utils/lv_img_utils.c
    
    ./app/app_ocr.c
    ./app/app_demo.c
    ./app/app_dictionary.c
    ./app/app_audio_player.c
    ./app/app_bezier_demo.c
    ./app/app_spelling.c
    ./app/app_setting.c
    # ./app/sketchpad/app_sketchpad.c
    # ./app/sketchpad/lv_100ask_sketchpad.c

    ./app/widgets/llm_dialog.c
    ./app/widgets/floating_button.c
    )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/fonts
    ${CMAKE_CURRENT_BINARY_DIR}/app
    ${CMAKE_CURRENT_BINARY_DIR}/widgets
    # ${CMAKE_CURRENT_BINARY_DIR}/app/sketchpad/
    )

add_library(ui ${SOURCES})
