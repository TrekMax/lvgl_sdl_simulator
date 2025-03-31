# app/app_setting/CMakeLists.txt
set(APP_SETTING_SOURCES
    app_setting.c
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
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

# 如果需要链接其他库，可以在这里添加
target_link_libraries(app_setting PRIVATE 
    lvgl
    )