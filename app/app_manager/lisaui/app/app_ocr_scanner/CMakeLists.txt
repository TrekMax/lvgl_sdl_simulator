# app/app_ocr_scanner/CMakeLists.txt
set(APP_OCR_SCANNER_SOURCES
    app_ocr.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_scanner_png.c
)

add_library(app_ocr_scanner STATIC
    ${APP_OCR_SCANNER_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_ocr_scanner PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${LISAUI_BASE_DIR}/
    ${LISAUI_BASE_DIR}/app_common
    ${LISAUI_BASE_DIR}/..
)
# target_include_directories(app_ocr_scanner PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../app_common
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../..
#     ${CMAKE_CURRENT_SOURCE_DIR}/assets
# )


target_link_libraries(app_ocr_scanner PRIVATE 
    lvgl
    utils
    app_common
    )