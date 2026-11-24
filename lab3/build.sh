#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"

cmake -S "${SCRIPT_DIR}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Release
cmake --build "${BUILD_DIR}" --config Release -j"$(nproc)"
cmake --install "${BUILD_DIR}" --config Release --prefix "${BUILD_DIR}/dist"

if command -v x86_64-w64-mingw32-gcc >/dev/null 2>&1; then
    WIN_BUILD_DIR="${SCRIPT_DIR}/build-win"
    cmake -S "${SCRIPT_DIR}" -B "${WIN_BUILD_DIR}" \
        -DCMAKE_TOOLCHAIN_FILE="${SCRIPT_DIR}/mingw64.cmake" \
        -DCMAKE_BUILD_TYPE=Release
    cmake --build "${WIN_BUILD_DIR}" --config Release -j"$(nproc)"
fi