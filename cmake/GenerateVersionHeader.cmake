# 执行 Git 命令获取 commit 版本信息
execute_process(
    COMMAND git rev-list --count HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE COMMIT_COUNT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 执行 Git 命令获取最近一次提交的作者信息
execute_process(
    COMMAND git log -1 --format=%an
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE COMMIT_AUTHOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 执行 Git 命令获取最新提交者的邮箱，并将结果存储到 AUTHOR_EMAIL 变量中
execute_process(
    COMMAND git log -1 --format=%ae
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE AUTHOR_EMAIL
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 打印 AUTHOR_EMAIL 变量的值
message("Author email is: ${AUTHOR_EMAIL}")

# 执行 Git 命令获取最新的 commit id，并将结果存储到 COMMIT_HASH 变量中
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 打印 COMMIT_HASH 变量的值
message("Current commit hash is: ${COMMIT_HASH}")

# 生成 version.h 文件
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

# 将生成的 version.h 文件添加到生成的头文件列表中
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
