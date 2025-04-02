# app/app_demo/CMakeLists.txt
set(APP_DEMO_SOURCES
    app_demo.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_demo_png.c
)

add_library(app_demo STATIC
    ${APP_DEMO_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${LISAUI_BASE_DIR}/
    ${LISAUI_BASE_DIR}/app_common
    ${LISAUI_BASE_DIR}/..
)

target_link_libraries(app_demo PRIVATE 
    lvgl
    app_common
    )