#!/usr/bin/env bash
rm -rf build/*
g++ -g -std=c++11 src/*.cpp -o build/llvmruntime
./build/llvmruntime