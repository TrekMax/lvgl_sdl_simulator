# app/app_taskbar/CMakeLists.txt
set(LISAUI_APP_TARGET_NAME app_taskbar)
set(${LISAUI_APP_TARGET_NAME}_SOURCES
    app_taskbar.c
    private_taskbar.c
)

set(${LISAUI_APP_TARGET_NAME}_UI_RESOURCES
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

add_library(${LISAUI_APP_TARGET_NAME} STATIC
    ${${LISAUI_APP_TARGET_NAME}_SOURCES}
    ${${LISAUI_APP_TARGET_NAME}_UI_RESOURCES}
)

target_include_directories(${LISAUI_APP_TARGET_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

if (CONFIG_LISAUI_ENV_ARCS_SDK)
    target_link_libraries(${LISAUI_APP_TARGET_NAME} 
    PRIVATE
        utils
    PUBLIC 
        listenai_interface)
    listenai_link_libraries(${LISAUI_APP_TARGET_NAME})
else()
    target_link_libraries(${LISAUI_APP_TARGET_NAME} 
    PRIVATE
        lvgl
        utils
        app_common
        )
endif()