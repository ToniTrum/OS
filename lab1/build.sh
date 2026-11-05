#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"

echo "== [1/3] Updating repository =="
git -C "${REPO_DIR}" pull --ff-only

echo "== [2/3] CMake configuration =="
cmake -S "${SCRIPT_DIR}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Release

echo "== [3/3] Project compilation =="
cmake --build "${BUILD_DIR}" --config Release -j"$(nproc)"

echo "== [OK] Build completed successfully! =="
echo "> Executable is located in: ${BUILD_DIR}"