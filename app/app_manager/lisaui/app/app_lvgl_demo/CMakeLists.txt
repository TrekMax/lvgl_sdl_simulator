cmake_minimum_required(VERSION 3.20)


# add_subdirectory(benchmark)
# add_subdirectory(keypad_encoder)
# add_subdirectory(music)
# add_subdirectory(stress)
# add_subdirectory(widgets)
set(APP_SOURCES
    app_lvgl_demo.c
)

set(APP_UI_RESOURCES
    # assets/icons/icon_img_app_lvgl_demo_png.c
)

add_library(app_lvgl_demo STATIC
    ${APP_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_lvgl_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

target_link_libraries(app_lvgl_demo PRIVATE 
    lvgl
    utils
    app_common
    )