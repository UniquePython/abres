cmake_minimum_required(VERSION 3.20)

project(abres C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(abres src/error.c src/result.c)

target_include_directories(abres PUBLIC include/)