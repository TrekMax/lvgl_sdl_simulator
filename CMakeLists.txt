cmake_minimum_required(VERSION 3.20)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(GenerateVersionHeader)

project(demo C)
add_compile_options(-g)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_EXPORT_COMPILECOMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# 使用-ffile-prefix-map来减少调试信息中的路径长度，从而固定 ROM 占用
get_filename_component(ROOT_PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR}/ ABSOLUTE)
add_compile_options("-ffile-prefix-map=${ROOT_PROJECT_DIR}=.")

# 移除符号表中的build目录前缀
get_filename_component(BUILD_DIR ${CMAKE_BINARY_DIR} ABSOLUTE)
add_compile_options("-ffile-prefix-map=${BUILD_DIR}=")

# 同时也处理工具链目录的路径
if(DEFINED ENV{NUCLEI_TOOLCHAIN_PATH})
    add_compile_options("-ffile-prefix-map=$ENV{NUCLEI_TOOLCHAIN_PATH}=/toolchain")
endif()

find_package(SDL2 REQUIRED SDL2)
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}/../
)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/components
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/components/utils/include/
    /usr/include/freetype2
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# 添加公共组件
add_subdirectory(components/lvgl)
add_subdirectory(components/lv_drivers)
add_subdirectory(components/utils)
add_subdirectory(components/unity)

# 可选地添加app子目录
if(NOT DEFINED BUILD_APP)
    # 默认构建所有app
    file(GLOB app_dirs LIST_DIRECTORIES true "app/*")
    foreach(app_dir ${app_dirs})
        if(IS_DIRECTORY ${app_dir} AND EXISTS ${app_dir}/CMakeLists.txt)
            add_subdirectory(${app_dir})
        endif()
    endforeach()
else()
    # 构建指定的app
    message(STATUS "Building app: ${BUILD_APP}")
    if(EXISTS "app/${BUILD_APP}/CMakeLists.txt")
        add_subdirectory(app/${BUILD_APP})
    else()
        message(FATAL_ERROR "App [${BUILD_APP}] not found or doesn't have CMakeLists.txt")
    endif()
endif()