#!/bin/bash
set -e

cmake -B build-win -S . -DCMAKE_TOOLCHAIN_FILE=toolchain-mingw64.cmake
cmake --build build-win