// Copyright (c) 2024 Falk Werner
// SPDX-License-Identifier: MIT

#ifndef HEXVIEW_MEMMAPPED_FILE_HPP
#define HEXVIEW_MEMMAPPED_FILE_HPP

#include <string>
#include <string_view>

namespace hexview
{

class memmapped_file
{
    memmapped_file(const memmapped_file&) = delete;
    memmapped_file& operator=(const memmapped_file&) = delete;
    memmapped_file(memmapped_file &&) = delete;
    memmapped_file& operator=(memmapped_file&&) = delete;
public:
    memmapped_file(std::string const & filename);
    ~memmapped_file();
    std::string_view str() const;

private:
    int fd;
    std::size_t length;
    char * address;
};

}

#endif
