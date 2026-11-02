#!/bin/bash
set -e

cmake -B build-lin -S .
cmake --build build-lin
./build-lin/lab1