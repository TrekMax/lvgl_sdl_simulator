cmake_minimum_required(VERSION 3.20)

set(WIDGET_UI_RESOURCES
    # assets/fonts/lv_font_chinese_18.c
    # assets/fonts/lv_font_notosans_cs_medium_18.c
    base/ls_radio_group.c
)

set(APP_UI_RESOURCES
    assets/fonts/lv_font_chinese_18.c
    assets/fonts/lv_font_notosans_cs_medium_18.c
    assets/fonts/lv_font_notosans_cs_medium_14.c
    assets/fonts/lv_font_rubik_bold_64.c
)

add_library(app_widget STATIC
    ${WIDGET_UI_RESOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_widget PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/base/
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

target_link_libraries(app_widget PRIVATE
    lvgl
    utils
    )
