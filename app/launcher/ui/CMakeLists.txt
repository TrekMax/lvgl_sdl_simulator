SET(SOURCES 
    ui.c
    launcher/app_launcher.c
    assets/lv_font_chinese_18.c
    utils/img_utils.c
    )
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/launcher
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    )

add_library(ui ${SOURCES})
