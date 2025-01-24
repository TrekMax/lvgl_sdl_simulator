# SPDX-License-Identifier: Apache-2.0

SET(COMMON_SOURCES
    ui.c
    common/lisaui_app_common.c
    common/lisaui_app_manager.c
    common/lisaui_view_manager.c
    common/lisaui_asset_manager.c
    
    # common/app_taskbar.c
    # common/app_launcher.c
)

if (CONFIG_LISAUI_DBUS_ENABLE)
    list(APPEND COMMON_SOURCES
        common/lisaui_dbus.c
    )
endif()

set(WIDGET_SOURCES
)

set(FONTS_SOURCES
    ./assets/fonts/lv_font_chinese_18.c
    #./assets/fonts/lv_font_chinese_18_old.c
)

set(ASSETS_SOURCES
    assets/icons/icon_img_app_composition_png.c
    assets/icons/icon_img_app_fav_png.c
    assets/icons/icon_img_app_practice_png.c
    assets/icons/icon_img_app_scanner_png.c
    assets/icons/icon_img_app_setting_png.c
    assets/icons/icon_img_app_voice_png.c

    common/assets/taskbar_icon/ui_img__status_battery_1_png.c
    common/assets/taskbar_icon/ui_img__status_battery_2_png.c
    common/assets/taskbar_icon/ui_img__status_battery_3_png.c
    common/assets/taskbar_icon/ui_img__status_battery_4_png.c
    common/assets/taskbar_icon/ui_img__status_battery_5_png.c

    common/assets/taskbar_icon/ui_img__status_charging_1_png.c
    common/assets/taskbar_icon/ui_img__status_charging_2_png.c
    common/assets/taskbar_icon/ui_img__status_charging_3_png.c
    common/assets/taskbar_icon/ui_img__status_charging_4_png.c
    common/assets/taskbar_icon/ui_img__status_charging_5_png.c

    assets/gif/example_gif.c
    )

# FIXME: App 在 launcher 显示的顺序与这里的顺序有关(ld链接顺序)
set(APP_SOURCES
    app/app_ocr.c
    app/dictionary/app_dictionary.c
    app/app_demo.c
    app/app_audio_player.c
    app/app_voice.c
    app/app_setting.c
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
    ${CMAKE_CURRENT_BINARY_DIR}/common
    # ${CMAKE_CURRENT_BINARY_DIR}/fonts
    # ${CMAKE_CURRENT_BINARY_DIR}/widgets
    # ${CMAKE_CURRENT_BINARY_DIR}/widgets/ext_lib

    # ${CMAKE_CURRENT_BINARY_DIR}/app
    # ${CMAKE_CURRENT_BINARY_DIR}/app/dictionary
    # ${CMAKE_CURRENT_BINARY_DIR}/utils

    # ${CMAKE_CURRENT_BINARY_DIR}/assets
    # ${CMAKE_CURRENT_BINARY_DIR}/assets/gif
    )

add_library(lisaui
    ${COMMON_SOURCES}
    # ${WIDGET_SOURCES}
    # ${ASSETS_SOURCES}
    # ${FONTS_SOURCES}

    # ${APP_SOURCES}
    # ${EXT_LIB_SOURCE}
    # ${UTILS_SOURCES}
)

target_link_libraries(
    lisaui
    PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/lisaui_apps.ld
)
