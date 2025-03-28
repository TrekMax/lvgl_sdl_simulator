cmake_minimum_required(VERSION 3.20)

set(target_name example)
add_executable(${target_name})


file(GLOB_RECURSE SRC_FILES
    main.c
)

# add_subdirectory(widgets)
add_subdirectory(benchmark)

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

# 设置可执行文件输出目录
set_target_properties(${target_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SDK_PATH}/dist
)
