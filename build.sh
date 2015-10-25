#!/usr/bin/env bash

set -e
rm -rf build/*
clang++-3.5 src/*.cpp -g -O0 \
    `llvm-config-3.5 --cxxflags --ldflags --system-libs --libs core mcjit native bitwriter` \
    -o build/llvmruntime