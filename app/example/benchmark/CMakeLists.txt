SET(SOURCES
    ./lv_demo_benchmark.c
    ./assets/img_benchmark_cogwheel_alpha16.c
    ./assets/img_benchmark_cogwheel_indexed16.c
    ./assets/lv_font_bechmark_montserrat_12_compr_az.c.c
    ./assets/img_benchmark_cogwheel_argb.c
    ./assets/img_benchmark_cogwheel_rgb565a8.c
    ./assets/lv_font_bechmark_montserrat_16_compr_az.c.c
    ./assets/img_benchmark_cogwheel_chroma_keyed.c
    ./assets/img_benchmark_cogwheel_rgb.c
    ./assets/lv_font_bechmark_montserrat_28_compr_az.c.c
    )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    )
add_library(ui ${SOURCES})
