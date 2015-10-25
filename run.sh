#!/usr/bin/env bash

set -e
touch build/queryexecutor.ll
./build/llvmruntime
#llc-3.5 build/queryexecutor.ll
#gcc build/queryexecutor.s -o build/final
#./build/final