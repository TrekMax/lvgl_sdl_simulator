cmake_minimum_required(VERSION 3.20)

set(target_name watch)
add_executable(${target_name})

file(GLOB_RECURSE SRC_FILES
    main.c
    # mouse_cursor_icon.c
    ./watch/*.c
)
add_definitions(-DCONFIG_LOG_COLORS=1)
add_definitions(-DCONFIG_LOG_ENABLE=4)
set(CONFIG_LVGL_ENV_SIMULATOR 1)
add_definitions(-DCONFIG_LVGL_ENV_SIMULATOR=${CONFIG_LVGL_ENV_SIMULATOR})

set(CONFIG_LISAUI_DBUS_ENABLE 0)
add_definitions(-DCONFIG_LISAUI_DBUS_ENABLE=${CONFIG_LISAUI_DBUS_ENABLE})

set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conf/lv_conf.h PARENT_SCOPE)
set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conf/lv_conf.h)
add_definitions(-DLV_CONF_PATH=${LV_CONF_PATH})

target_sources(${target_name} PRIVATE ${SRC_FILES})
target_include_directories(${target_name} 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/conf
    ${CMAKE_CURRENT_SOURCE_DIR}/watch
    ${CMAKE_CURRENT_SOURCE_DIR}/watch/func/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/watch/app/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/watch/app/screens
    ${CMAKE_CURRENT_SOURCE_DIR}/watch/app/screens/Inc
)

target_link_libraries(
    ${target_name}
    PRIVATE
    ${SDL2_LIBRARIES}
    -lm 
    -lpthread
    -ldl
    lv_drivers
)

# 设置可执行文件输出目录
set_target_properties(${target_name} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SDK_PATH}/dist
)
