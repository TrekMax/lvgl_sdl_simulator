# SPDX-License-Identifier: Apache-2.0

set(LISAUI_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "LISAUI_BASE_DIR: ${LISAUI_BASE_DIR}")

SET(APP_COMMON_SOURCES
    ui.c
    app_common/lisaui_app_common.c
    app_common/lisaui_asset_manager.c
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

set(APP_USER_SOURCES
    app/assets/icons/icon_img_app_voice_png.c

    app/lvgl_demo/app_lvgl_demo.c
)

set(EXT_LIB_SOURCE
    widgets/ext_lib/gifdec.c
    widgets/ext_lib/lv_gif.c
    )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/app_common
    ${CMAKE_CURRENT_BINARY_DIR}/app_framework
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    )

add_subdirectory(utils)

add_subdirectory(app/taskbar)
add_subdirectory(app/launcher)
add_subdirectory(app/app_template)
add_subdirectory(app/demo)
add_subdirectory(app/ocr_scanner)
add_subdirectory(app/audio_player)
add_subdirectory(app/dictionary)
add_subdirectory(app/setting)
add_subdirectory(app/thermography)
# add_subdirectory(app/lvgl_demo)

add_library(lisaui
    ${APP_COMMON_SOURCES}
    ${APP_FRAMEWORK_SOURCES}
    ${APP_USER_SOURCES}
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

        utils
        # FIXME: App 在 launcher 显示的顺序与这里的顺序有关(ld 链接顺序)
        app_taskbar
        app_launcher

        app_ocr
        app_template
        app_demo
        app_dictionary
        app_audio_player
        app_setting
        app_thermography
    )
endif()