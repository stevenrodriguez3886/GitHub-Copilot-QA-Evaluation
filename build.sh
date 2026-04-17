#!/bin/bash
# ==========================================================================
# simple build script removes old build directory and compiles the project
# ==========================================================================

rm -rf build
cmake -S . -B build
cmake --build build