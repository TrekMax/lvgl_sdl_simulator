cmake_minimum_required(VERSION 3.20)

# 如果作为独立项目构建
if(NOT TARGET lv_drivers)
    # 包含顶层项目设置
    include(../../CMakeLists.txt)
endif()

set(target_name x-ui)
add_executable(${target_name})

file(GLOB_RECURSE SRC_FILES
    main.c
)

# 添加UI子目录
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
    lvgl
)

# 设置可执行文件输出目录
set_target_properties(${target_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SDK_PATH}/dist
)