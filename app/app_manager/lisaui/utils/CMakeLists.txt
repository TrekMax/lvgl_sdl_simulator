add_library(utils STATIC
    img_utils.c
    lv_img_utils.c
)

target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(utils PRIVATE
    lvgl
    )