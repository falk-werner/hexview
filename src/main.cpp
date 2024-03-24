// Copyright (c) 2024 Falk Werner
// SPDX-License-Identifier: MIT

#include "memmapped_file.hpp"
#include "viewer.hpp"

#include <ncurses.h>

#include <iostream>


using hexview::memmapped_file;
using hexview::viewer;

int main(int argc, char* argv[])
{
    if ((argc != 2) || (std::string("--help") == argv[1]) || (std::string("-h") == argv[1])) {
        std::cout << R"(hexview, (c) 2024 Falk Werner
shows the contents of a file in a hexview

Usage:
    hexview <filename>

Arguments:
    filename - file to show
)";
        return 0;
    }

    try {
        memmapped_file f(argv[1]);
        WINDOW * win = initscr();

        viewer v(win, f.str());

        while (v.service());

        endwin();
        return 0;
    }
    catch (...) {
        std::cerr << "error: failed to open file" << std::endl;
    }
    return 1;
}