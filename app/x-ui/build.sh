#!/bin/bash

# 获取脚本所在目录
SCRIPT_DIR=$(cd $(dirname ${BASH_SOURCE[0]}); pwd)
BUILD_DIR=${SCRIPT_DIR}/build

# 创建构建目录
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# 运行CMake
cmake -DBUILD_APP=x-ui ../..
make -j$(nproc)

# 将可执行文件复制到bin目录
mkdir -p ${SCRIPT_DIR}/bin
cp ${BUILD_DIR}/bin/x-ui ${SCRIPT_DIR}/bin/