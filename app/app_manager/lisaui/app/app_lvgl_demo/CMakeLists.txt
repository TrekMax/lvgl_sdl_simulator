cmake_minimum_required(VERSION 3.20)


# add_subdirectory(benchmark)
# add_subdirectory(keypad_encoder)
# add_subdirectory(music)
# add_subdirectory(stress)
# add_subdirectory(widgets)
set(APP_SOURCES
    app_lvgl_demo.c

    flex/app_flex_1.c
    flex/app_flex_2.c
    flex/app_flex_3.c
    flex/app_flex_4.c
    flex/app_flex_5.c
    flex/app_flex_6.c
    flex/app_flex.c

    freetype/lv_example_freetype_1.c
)

set(APP_UI_RESOURCES
    # assets/icons/icon_img_app_lvgl_demo_png.c
)

add_library(app_lvgl_demo STATIC
    ${APP_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_lvgl_demo PRIVATE
    ${LISAUI_BASE_DIR}/
    ${LISAUI_BASE_DIR}/app_common
    ${LISAUI_BASE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

target_link_libraries(app_lvgl_demo PRIVATE 
    lvgl
    utils
    app_common
    )