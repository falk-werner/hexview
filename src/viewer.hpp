// Copyright (c) 2024 Falk Werner
// SPDX-License-Identifier: MIT

#ifndef HEXVIEW_VIEWER_HPP
#define HEXVIEW_VIEWER_HPP

#include <ncurses.h>

#include <string_view>
#include <vector>

namespace hexview
{

class viewer
{
public:
    viewer(WINDOW * win_, std::string_view data_);
    ~viewer() = default;

    bool service();

private:
    void update_view();
    void up();
    void down();
    void page_up();
    void page_down();
    void jump_to_offset();
    void jump_to_end();
    void find();
    void find_next();
    void find_prev();

    WINDOW * win;
    std::string_view data;
    size_t page_offset;
    int y;
    size_t page_size;
    size_t current_search_result;
    std::vector<size_t> search_results;
};

}

#endif