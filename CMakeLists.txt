# Copyright (c) 2024 Falk Werner
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22)
project(hexview)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

add_executable(hexview
    src/memmapped_file.cpp
    src/viewer.cpp
    src/main.cpp
)
target_include_directories(hexview PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(hexview PRIVATE ${CURSES_LIBRARY})

install(TARGETS hexview)
