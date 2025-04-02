cmake_minimum_required(VERSION 3.20)

set(APP_SOURCES
    lisaui_app_common.c
    lisaui_asset_manager.c
)

set(APP_UI_RESOURCES
    # assets/icons/icon_img_app_common_png.c
    assets/fonts/lv_font_chinese_18_old.c
)

add_library(app_common STATIC
    ${APP_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_common PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)