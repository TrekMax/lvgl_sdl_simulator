SET(SOURCES
    ./lv_arcs_demo.c
    ./lv_demo_widgets.c
    ./assets/img_clothes.c
    ./assets/img_demo_widgets_avatar.c
    ./assets/img_lvgl_logo.c
    ./assets/img_bulb_gif.c
    ./utils/img_utils.c
    ./utils/lv_img_utils.c
    ./lv_port_file.c
    ./lv_font_chinese_18.c
    )

add_library(ui ${SOURCES})
