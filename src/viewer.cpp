// Copyright (c) 2024 Falk Werner
// SPDX-License-Identifier: MIT

#include "viewer.hpp"
#include <string>

#define KEY_ESC 27

namespace hexview
{

viewer::viewer(WINDOW * win_, std::string_view data_)
: win(win_)
, data(data_)
, page_offset(0)
{
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, TRUE);
}

bool viewer::service()
{
    y = getmaxy(win);
    page_size = 16 * (y - 1);

    update_view();

    bool done = false;
    int const c = getch();
    switch (c)
    {
        case KEY_ESC:
            // fall-through
        case 'q':
            done = true;
            break;
        case 'w':
            // fall-through
        case KEY_UP:
            up();
            break;
        case 's':
            // fall-through
        case KEY_DOWN:
            down();
            break;
        case KEY_PPAGE:
            page_up();
            break;
        case KEY_NPAGE:
            page_down();
            break;
        case 'g':
            jump_to_offset();
            break;
        case 'G':
            jump_to_end();
            break;
        case '/':
            find();
            break;
        case 'n':
            find_next();
            break;
        case 'N':
            find_prev();
        default:
            break;
    }

    return !done;
}

void viewer::update_view()
{
    int lines_to_show = y - 1;
    if (!search_results.empty()) {
        lines_to_show--;
    }

    clear();
    mvprintw(0, 0, "hexview    0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f    0123456789abcdef");
    for(int line = 0; line < lines_to_show; line++) {
        size_t offset = page_offset + (16 * line);
        if (offset >= data.size()) {
            break;
        }
        mvprintw(line + 1, 0, "%08lx | ", offset);
        mvprintw(line + 1, 59, "|");

        for(int i = 0; i < 16; i++) {
            if ((offset + i) >= data.size()) {
                continue;
            }

            char const c = data[offset + i];

            mvprintw(line + 1, 11 + (3*i), "%02X", (int) (c & 0xff));
            mvprintw(line + 1, 13 + (3*16) + i, "%c", ((c > 32) && (c <= 127)) ? c : '.');
        }

    }

    if (!search_results.empty()) {
        mvprintw(y-1, 0, "match %zu / %zu", current_search_result + 1, search_results.size());
    }
    refresh();
}

void viewer::up()
{
    if (page_offset >= 16) {
        page_offset -= 16;
    }
}

void viewer::down()
{
    if (page_offset < data.size()) {
        page_offset += 16;
    }
}

void viewer::page_up()
{
    if (page_offset > page_size) {
        page_offset -= page_size;
    }
    else {
        page_offset = 0;
    }
}

void viewer::page_down()
{
    if ((page_offset + page_size) < data.size()) {
        page_offset += page_size;
    }
}

void viewer::jump_to_offset()
{
    move(y-1, 0);
    clrtoeol();
    mvprintw(y-1, 0, "goto offset: ");
    refresh();

    echo();
    curs_set(1);
    char buffer[80];
    mvgetnstr(y-1, 13, buffer, 80);
    noecho();
    curs_set(0);

    try {
        auto pos = std::stoul(buffer, nullptr, 16);
        if (pos < data.size()) {
            page_offset = pos & 0xffffffff0;
        }
        else {
            page_offset = data.size() & 0xfffffff0;
        }
    }
    catch (...) {
        // swallow
    }
}

void viewer::jump_to_end()
{
    page_offset = data.size() & 0xfffffff0;
}

void viewer::find()
{
    move(y-1, 0);
    clrtoeol();
    mvprintw(y-1, 0, "find: ");
    refresh();

    echo();
    curs_set(1);
    char buffer[80];
    mvgetnstr(y-1, 7, buffer, 80);
    noecho();
    curs_set(0);

    std::string const target = buffer;
    search_results.clear();
    auto pos = data.find(target);
    current_search_result = 0;
    while ((pos != std::string::npos) && (search_results.size() < 1000)) {
        search_results.push_back(pos);
        pos = data.find(target, pos + target.size());
    }

    if (!search_results.empty()) {
        page_offset = search_results[0] & 0xffffffff0;
    }
    else {
        mvprintw(y-1, 0, "not found");
    }
}

void viewer::find_next()
{
    if (!search_results.empty()) {
        current_search_result++;
        if (current_search_result >= search_results.size()) {
            current_search_result = 0;
        }

        page_offset = search_results[current_search_result] & 0xffffffff0;
    }
}

void viewer::find_prev()
{
    if (!search_results.empty()) {
        if (current_search_result == 0) {
            current_search_result = search_results.size();
        }
        current_search_result--;
    }

    page_offset = search_results[current_search_result] & 0xffffffff0;
}

}
