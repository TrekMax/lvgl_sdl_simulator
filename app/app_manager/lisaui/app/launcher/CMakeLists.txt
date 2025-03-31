# app/app_launcher/CMakeLists.txt
set(APP_SOURCES
    app_launcher.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_launcher_png.c
)

add_library(app_launcher STATIC
    ${APP_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_launcher PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

# 如果需要链接其他库，可以在这里添加
# target_link_libraries(app_launcher PRIVATE ...)