// Copyright (c) 2024 Falk Werner
// SPDX-License-Identifier: MIT

#include "memmapped_file.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <stdexcept>

namespace hexview
{

memmapped_file::memmapped_file(std::string const & filename)
{
    fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) {
        throw std::runtime_error("failed to open file");
    }

    struct stat info;
    if (fstat(fd, &info) == -1) {
        close(fd);
        throw std::runtime_error("failed to get file size");
    }
    length = info.st_size;

    address = reinterpret_cast<char*>(mmap(nullptr, length, PROT_READ, MAP_PRIVATE, fd, 0));
    if (MAP_FAILED == address) {
        close(fd);
        throw std::runtime_error("failed to get file size");
    }
}

memmapped_file::~memmapped_file()
{
    munmap(address, length);
    close(fd);
}

std::string_view memmapped_file::str() const
{
    return std::string_view(address, length);
}

}