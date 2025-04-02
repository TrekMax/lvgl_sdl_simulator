# app/app_voice/CMakeLists.txt
set(APP_VOICE_SOURCES
    app_voice.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_voice_png.c
)

add_library(app_voice STATIC
    ${APP_VOICE_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_voice PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)


target_link_libraries(app_voice PRIVATE 
    lvgl
    utils
    app_common
    )