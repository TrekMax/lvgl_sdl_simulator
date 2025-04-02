# SPDX-License-Identifier: Apache-2.0

# 设置基础目录
get_filename_component(LISAUI_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
message(STATUS "LISAUI_BASE_DIR: ${LISAUI_BASE_DIR}")

# 定义源文件分组
set(APP_COMMON_SOURCES
    ui.c
)

set(APP_FRAMEWORK_SOURCES
    app_framework/lisaui_app_manager.c
    app_framework/lisaui_view_manager.c
)

# 条件编译选项
if(CONFIG_LISAUI_DBUS_ENABLE)
    list(APPEND APP_FRAMEWORK_SOURCES
        app_framework/lisaui_dbus.c
    )
endif()

set(APP_USER_SOURCES
    # 预留用户源文件
)

set(EXT_LIB_SOURCE
    widgets/ext_lib/gifdec.c
    widgets/ext_lib/lv_gif.c
)

# 首先创建主库
add_library(lisaui STATIC
    ${APP_COMMON_SOURCES}
    ${APP_FRAMEWORK_SOURCES}
    ${APP_USER_SOURCES}
)

# 然后设置包含目录
target_include_directories(lisaui PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/app_framework
    ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# 添加固定子目录
add_subdirectory(utils)
add_subdirectory(app_common)

# 添加应用子目录 - 只显示app/后面的部分
file(GLOB APP_DIRS "app/*")
foreach(APP_DIR ${APP_DIRS})
    # 提取app/后面的目录名
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/app/" "" REL_APP_DIR ${APP_DIR})
    if(IS_DIRECTORY ${APP_DIR} AND EXISTS "${APP_DIR}/CMakeLists.txt")
        message(STATUS "Adding application directory: app/${REL_APP_DIR}")
        add_subdirectory(${APP_DIR})
    else()
        message(STATUS "Skipping directory (no CMakeLists.txt): app/${REL_APP_DIR}")
    endif()
endforeach()

# 链接器脚本设置
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/lisaui_apps.ld)

if(APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-map,${LINKER_SCRIPT}")
else()
    # 链接依赖库
    # target_link_options(lisaui PRIVATE -T ${LINKER_SCRIPT})

    # 自动收集已添加的应用库
    get_property(ADDED_SUBDIRS DIRECTORY PROPERTY SUBDIRECTORIES)
    set(APP_LIBRARIES
        app_common
        utils
    )

    # 添加所有以"app_"开头且已添加的库
    foreach(SUBDIR ${ADDED_SUBDIRS})
        get_filename_component(SUBDIR_NAME ${SUBDIR} NAME)
        if(SUBDIR_NAME MATCHES "^app_")
            list(APPEND APP_LIBRARIES ${SUBDIR_NAME})
        endif()
    endforeach()

    message(STATUS "APP_LIBRARIES: ${APP_LIBRARIES}")

    target_link_libraries(lisaui PRIVATE
    -T ${LINKER_SCRIPT}
    ${APP_LIBRARIES})
endif()

# 添加编译特性支持
target_compile_features(lisaui PRIVATE c_std_11)

# 设置输出目录
set_target_properties(lisaui PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)