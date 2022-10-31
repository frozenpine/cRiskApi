#!/bin/bash
set -e

cd `dirname $0`
CURR_DIR=`pwd`

BUILD_DIR="${CURR_DIR}/build"
OUT_DIR="${CURR_DIR}/out"
LIB_DIR="${CURR_DIR}/../libs/rohon"

[[ -d "${BUILD_DIR}" ]] && rm -rf "${BUILD_DIR}"
[[ -d "${OUT_DIR}" ]] && rm -rf "${OUT_DIR}"

mkdir -p "${BUILD_DIR}" && cd "${BUILD_DIR}"

cmake ..

make clean && make
cp "${LIB_DIR}/"lib*.so "${OUT_DIR}/"
