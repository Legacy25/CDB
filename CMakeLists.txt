cmake_minimum_required(VERSION 3.3)
include_directories(AFTER /usr/local/include)
file(GLOB SRC_FILES src/*.cpp)

add_executable(llvm ${SRC_FILES})