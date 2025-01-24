cmake_minimum_required(VERSION 3.20)

set(target_name app_manager)
add_executable(${target_name})


file(GLOB_RECURSE SRC_FILES
    main.c
    # mouse_cursor_icon.c
)

target_sources(${target_name} PRIVATE ${SRC_FILES})

add_subdirectory(ui)

target_link_libraries(
    ${target_name}
    PRIVATE
    ${SDL2_LIBRARIES}
    -lm 
    -lpthread
    -ldl
    # lvgl
    # lv_examples
    lv_drivers
    lisaui
)
