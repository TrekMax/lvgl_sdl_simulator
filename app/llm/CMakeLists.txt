cmake_minimum_required(VERSION 3.20)

set(target_name llm)
add_executable(${target_name})

file(GLOB_RECURSE SRC_FILES
    main.c
    # mouse_cursor_icon.c
)

set(CONFIG_LVGL_ENV_SIMULATOR 1)
add_definitions(-DCONFIG_LVGL_ENV_SIMULATOR=${CONFIG_LVGL_ENV_SIMULATOR})

set(CONFIG_LISAUI_DBUS_ENABLE 0)
add_definitions(-DCONFIG_LISAUI_DBUS_ENABLE=${CONFIG_LISAUI_DBUS_ENABLE})

set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conf/lv_conf.h PARENT_SCOPE)
set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conf/lv_conf.h)
add_definitions(-DLV_CONF_PATH=${LV_CONF_PATH})

target_sources(${target_name} PRIVATE ${SRC_FILES})
target_include_directories(${target_name} PUBLIC
    # ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/conf
)
add_subdirectory(lisaui)

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
    unity
)

# 设置可执行文件输出目录
set_target_properties(${target_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SDK_PATH}/dist
)
