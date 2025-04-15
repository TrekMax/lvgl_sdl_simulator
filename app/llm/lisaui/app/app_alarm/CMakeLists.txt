# app/app_alarm/CMakeLists.txt
set(APP_ALARM_SOURCES
    app_alarm.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_store_png.c
)

add_library(app_alarm STATIC
    ${APP_ALARM_SOURCES}
    # ${APP_UI_RESOURCES}
)

target_include_directories(app_alarm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

target_link_libraries(app_alarm PRIVATE 
    lvgl
    app_common
    )
