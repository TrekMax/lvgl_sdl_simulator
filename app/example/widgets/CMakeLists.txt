SET(SOURCES
    lv_demo_widgets.c

    assets/img_clothes.c
    assets/img_demo_widgets_avatar.c
    assets/img_lvgl_logo.c
    )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    )
add_library(ui ${SOURCES})
