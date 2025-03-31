# app/app_template/CMakeLists.txt
set(APP_TEMPLATE_SOURCES
    app_template.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_store_png.c
)

add_library(app_template STATIC
    ${APP_TEMPLATE_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_template PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
    ${CMAKE_CURRENT_SOURCE_DIR}/../../..
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
)

# 如果需要链接其他库，可以在这里添加
# target_link_libraries(app_template PRIVATE ...)