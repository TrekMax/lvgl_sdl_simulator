add_library(utils STATIC
    img_utils.c
    lv_img_utils.c
)

target_include_directories(utils PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${LISAUI_BASE_DIR}/
    ${LISAUI_BASE_DIR}/app_common
    ${LISAUI_BASE_DIR}/utils
    ${LISAUI_BASE_DIR}/..
)

target_link_libraries(utils PRIVATE 
    lvgl
    )