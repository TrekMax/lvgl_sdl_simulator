# app/app_setting/CMakeLists.txt
set(APP_SETTING_SOURCES
    app_setting.c
    app_setting_view_volume_backlight.c
    app_setting_view_wakeup_config.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_setting_png.c
)

add_library(app_setting STATIC
    ${APP_SETTING_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_setting PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)


target_link_libraries(app_setting PRIVATE 
    lvgl
    utils
    app_common
    )