# app/app_audio_player/CMakeLists.txt
set(APP_AUDIO_PLAYER_SOURCES
    app_audio_player.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_composition_png.c
)

add_library(app_audio_player STATIC
    ${APP_AUDIO_PLAYER_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_audio_player PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

# 如果需要链接其他库，可以在这里添加
# target_link_libraries(app_audio_player PRIVATE ...)