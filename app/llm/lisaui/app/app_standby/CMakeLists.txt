# app/app_standby/CMakeLists.txt
set(APP_STANDBY_SOURCES
    app_standby.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_store_png.c
)

add_library(app_standby STATIC
    ${APP_STANDBY_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_standby PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

target_link_libraries(app_standby PRIVATE 
    lvgl
    app_common
    )