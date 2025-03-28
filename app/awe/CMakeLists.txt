cmake_minimum_required(VERSION 3.20)

set(target_name awe)
add_executable(${target_name})


file(GLOB_RECURSE SRC_FILES
    main.c
)

add_subdirectory(aweui)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/aweui
)

target_sources(${target_name} PRIVATE ${SRC_FILES})
target_link_libraries(
    ${target_name}
    PRIVATE
    ${SDL2_LIBRARIES} 
    -lm 
    -lpthread
    -ldl
    lv_drivers
    aweui
)

# 设置可执行文件输出目录
set_target_properties(${target_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SDK_PATH}/dist
)


