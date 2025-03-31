# app/app_thermography/CMakeLists.txt
set(APP_THERMOGRAPHY_SOURCES
    app_thermography.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_thermo_png.c
)

add_library(app_thermography STATIC
    ${APP_THERMOGRAPHY_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_thermography PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

# 如果需要链接其他库，可以在这里添加
target_link_libraries(app_thermography PRIVATE 
    lvgl
    )