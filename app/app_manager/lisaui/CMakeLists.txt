# SPDX-License-Identifier: Apache-2.0

SET(APP_COMMON_SOURCES
    ui.c
    app_common/lisaui_app_common.c
    app_common/lisaui_asset_manager.c

    # app_common/assets/fonts/lv_font_chinese_18.c
    app_common/assets/fonts/lv_font_chinese_18_old.c
)

SET(APP_FRAMEWORK_SOURCES
    app_framework/lisaui_app_manager.c
    app_framework/lisaui_view_manager.c
)

if (CONFIG_LISAUI_DBUS_ENABLE)
    list(APPEND APP_FRAMEWORK_SOURCES
        app_framework/lisaui_dbus.c
        )
endif()

set(APP_SYSTEM_SOURCES
    app_sys/assets/icons/icon_img_app_launcher_png.c
    app_sys/assets/icons/icon_img_app_taskbar_png.c
    app_sys/assets/taskbar_icon/ui_img__status_battery_1_png.c
    app_sys/assets/taskbar_icon/ui_img__status_battery_2_png.c
    app_sys/assets/taskbar_icon/ui_img__status_battery_3_png.c
    app_sys/assets/taskbar_icon/ui_img__status_battery_4_png.c
    app_sys/assets/taskbar_icon/ui_img__status_battery_5_png.c

    app_sys/assets/taskbar_icon/ui_img__status_charging_1_png.c
    app_sys/assets/taskbar_icon/ui_img__status_charging_2_png.c
    app_sys/assets/taskbar_icon/ui_img__status_charging_3_png.c
    app_sys/assets/taskbar_icon/ui_img__status_charging_4_png.c
    app_sys/assets/taskbar_icon/ui_img__status_charging_5_png.c

    # FIXME: App 在 launcher 显示的顺序与这里的顺序有关(ld 链接顺序)
    app_sys/app_launcher.c
    app_sys/app_taskbar.c
)

set(APP_USER_SOURCES
    app_user/assets/icons/icon_img_app_composition_png.c
    app_user/assets/icons/icon_img_app_fav_png.c
    app_user/assets/icons/icon_img_app_practice_png.c
    app_user/assets/icons/icon_img_app_scanner_png.c
    app_user/assets/icons/icon_img_app_setting_png.c
    app_user/assets/icons/icon_img_app_voice_png.c

    # FIXME: App 在 launcher 显示的顺序与这里的顺序有关(ld 链接顺序)
    app_user/ocr_scanner/app_ocr.c
    app_user/dictionary/app_dictionary.c
    app_user/demo/app_demo.c
    # app_user/app_audio_player.c
    # app_user/app_voice.c
    # app_user/app_setting.c
)

set(EXT_LIB_SOURCE
    widgets/ext_lib/gifdec.c
    widgets/ext_lib/lv_gif.c
    )

set(UTILS_SOURCES
    utils/img_utils.c
    utils/lv_img_utils.c
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/app_common
    ${CMAKE_CURRENT_BINARY_DIR}/app_framework
    ${CMAKE_CURRENT_BINARY_DIR}/app_user

    ${CMAKE_CURRENT_BINARY_DIR}/utils
    ${CMAKE_CURRENT_BINARY_DIR}/assets

    # ${CMAKE_CURRENT_BINARY_DIR}/widgets
    # ${CMAKE_CURRENT_BINARY_DIR}/widgets/ext_lib
    

    # ${CMAKE_CURRENT_BINARY_DIR}/app
    # ${CMAKE_CURRENT_BINARY_DIR}/app/dictionary
    )

add_library(lisaui
    # ${WIDGET_SOURCES}
    # ${ASSETS_SOURCES}
    # ${FONTS_SOURCES}

    ${APP_COMMON_SOURCES}
    ${APP_FRAMEWORK_SOURCES}
    ${APP_SYSTEM_SOURCES}
    ${APP_USER_SOURCES}

    # ${EXT_LIB_SOURCE}
    ${UTILS_SOURCES}
)

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/lisaui_apps.ld)

if (APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-map,${LINKER_SCRIPT}")
else()
    # set(CMAKE_EXE_LINKER_FLAGS "-T ${LINKER_SCRIPT}")
    target_link_libraries(
        lisaui
        PRIVATE
        -T ${LINKER_SCRIPT}
    )
endif()