# app/app_taskbar/CMakeLists.txt
set(APP_TASKBAR_SOURCES
    app_taskbar.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_taskbar_png.c

    assets/taskbar_icon/ui_img__status_battery_1_png.c
    assets/taskbar_icon/ui_img__status_battery_2_png.c
    assets/taskbar_icon/ui_img__status_battery_3_png.c
    assets/taskbar_icon/ui_img__status_battery_4_png.c
    assets/taskbar_icon/ui_img__status_battery_5_png.c

    assets/taskbar_icon/ui_img__status_charging_1_png.c
    assets/taskbar_icon/ui_img__status_charging_2_png.c
    assets/taskbar_icon/ui_img__status_charging_3_png.c
    assets/taskbar_icon/ui_img__status_charging_4_png.c
    assets/taskbar_icon/ui_img__status_charging_5_png.c
)

add_library(app_taskbar STATIC
    ${APP_TASKBAR_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_taskbar PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

# 如果需要链接其他库，可以在这里添加
target_link_libraries(app_taskbar PRIVATE 
    lvgl
    )