cmake_minimum_required(VERSION 3.20)

set(target_name app_manager)
add_executable(${target_name})


file(GLOB_RECURSE SRC_FILES
    main.c
    # mouse_cursor_icon.c
)


set(CONFIG_LVGL_ENV_SIMULATOR 1)
add_definitions(-DCONFIG_LVGL_ENV_SIMULATOR=${CONFIG_LVGL_ENV_SIMULATOR})

target_sources(${target_name} PRIVATE ${SRC_FILES})

add_subdirectory(lisaui)

target_link_libraries(
    ${target_name}
    PRIVATE
    ${SDL2_LIBRARIES}
    -lm 
    -lpthread
    -ldl
    # lv_examples
    lv_drivers
    lisaui
)

# 设置可执行文件输出目录
set_target_properties(${target_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SDK_PATH}/dist
)
