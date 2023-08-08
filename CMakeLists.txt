cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(GenerateVersionHeader)

project(lvgl_app C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE Debug)

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
)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(components/lvgl)
add_subdirectory(components/lv_drivers)
add_subdirectory(components/utils)
add_subdirectory(app/ui)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} lvgl lv_drivers ui)
