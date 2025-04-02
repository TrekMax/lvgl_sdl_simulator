# app/app_dictionary/CMakeLists.txt
set(APP_DICTIONARY_SOURCES
    app_dictionary.c
)

set(APP_UI_RESOURCES
    assets/icons/icon_img_app_fav_png.c
)

add_library(app_dictionary STATIC
    ${APP_DICTIONARY_SOURCES}
    ${APP_UI_RESOURCES}
)

target_include_directories(app_dictionary PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${LISAUI_BASE_DIR}/
    ${LISAUI_BASE_DIR}/app_common
    ${LISAUI_BASE_DIR}/utils
    ${LISAUI_BASE_DIR}/..
)

target_link_libraries(app_dictionary PRIVATE 
    lvgl
    utils
    app_common
    )