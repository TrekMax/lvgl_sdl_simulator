SET(SOURCES 
    ui.c
    
    launcher/app_launcher.c

    assets/ui_img__launcher_scan_png.c
    assets/ui_img__launcher_fav_png.c
    assets/ui_img__launcher_practice_png.c
    assets/lv_font_chinese_18.c
    )
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/screens
    ${CMAKE_CURRENT_SOURCE_DIR}/launcher
    )

add_library(ui ${SOURCES})
