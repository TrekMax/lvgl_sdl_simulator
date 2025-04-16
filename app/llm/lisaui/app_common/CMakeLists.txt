cmake_minimum_required(VERSION 3.20)

set(APP_FRAMEWORK_SOURCES
    lisaui_app_manager.c
    lisaui_view_manager.c
)

if(CONFIG_LISAUI_DBUS_ENABLE)
    list(APPEND APP_FRAMEWORK_SOURCES
        lisaui_dbus.c
    )
endif()

set(APP_SOURCES
    lisaui_app_common.c
    lisaui_asset_manager.c
)

add_library(app_common STATIC
    ${APP_SOURCES}
    ${APP_FRAMEWORK_SOURCES}
)

target_include_directories(app_common PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

target_link_libraries(app_common PRIVATE
    lvgl
    utils
    app_widget
    )