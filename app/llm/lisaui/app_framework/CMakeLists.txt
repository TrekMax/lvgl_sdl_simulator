cmake_minimum_required(VERSION 3.20)

set(APP_SOURCES
    lisaui_app_manager.c
    lisaui_view_manager.c
)

if(CONFIG_LISAUI_DBUS_ENABLE)
    list(APPEND APP_SOURCES
        lisaui_dbus.c
    )
endif()

add_library(app_framework STATIC
    ${APP_SOURCES}
)

target_include_directories(app_framework PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../app_common
)

