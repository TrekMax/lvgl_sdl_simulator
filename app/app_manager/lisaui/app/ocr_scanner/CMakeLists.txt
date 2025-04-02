# app/app_ocr/CMakeLists.txt

message(STATUS "---> LISAUI_BASE_DIR: ${LISAUI_BASE_DIR}")
set(APP_OCR_SOURCES
    app_ocr.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_scanner_png.c
)

add_library(app_ocr STATIC
    ${APP_OCR_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_ocr PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${LISAUI_BASE_DIR}/
    ${LISAUI_BASE_DIR}/app_common
    ${LISAUI_BASE_DIR}/..
)
# target_include_directories(app_ocr PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../..
#     ${CMAKE_CURRENT_SOURCE_DIR}/assets
# )


target_link_libraries(app_ocr PRIVATE 
    lvgl
    utils
    app_common
    )