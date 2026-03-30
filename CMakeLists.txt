cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(array VERSION 1.0 LANGUAGES C)

include_directories(${CMAKE_SOURCE_DIR}/include)
set(SOURCES 
  src/array.c
)
add_library(array SHARED ${SOURCES})
target_compile_options(array PRIVATE -Wall -g -Wpedantic -Wshadow -Wconversion -Wnull-dereference -Wdouble-promotion -Wextra -O0)
