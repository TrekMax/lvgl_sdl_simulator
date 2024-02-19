cmake_minimum_required(VERSION 3.20)

set(target_name launcher)
add_executable(${target_name})


file(GLOB_RECURSE SRC_FILES
    main.c
    smart_home/control_ui.c
    smart_home/info_ui.c
    smart_home/music_ui.c
    smart_home/smart_home_ui.c
    home/home_ui.c
    setting/*.c
    lv_port_file.c
    lv_port_indev.c
    ui_btnmatrix.c
    ui_common.c
    intercom_homepage/*.c
    intercom_homepage/video_monitor/*.c
    intercom_homepage/intercom_call/*.c
)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/smart_home
    ${CMAKE_CURRENT_SOURCE_DIR}/home
    ${CMAKE_CURRENT_SOURCE_DIR}/setting
    ${CMAKE_CURRENT_SOURCE_DIR}/intercom_homepage
    ${CMAKE_CURRENT_SOURCE_DIR}/intercom_homepage/video_monitor
    ${CMAKE_CURRENT_SOURCE_DIR}/intercom_homepage/intercom_call
    )
add_subdirectory(ui)

target_sources(${target_name} PRIVATE ${SRC_FILES})
target_link_libraries(
    ${target_name}
    PRIVATE
    ${SDL2_LIBRARIES} 
    -lm 
    -lpthread
    -ldl
    lv_drivers
    ui
)

