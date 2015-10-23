#!/usr/bin/env bash

set -e
rm -rf build/*
clang++-3.5 src/*.cpp \
    `llvm-config-3.5 --cxxflags --ldflags --system-libs --libs core bitwriter` \
    -o build/llvmruntime