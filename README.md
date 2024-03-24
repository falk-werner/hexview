[![Build](https://github.com/falk-werner/hexview/actions/workflows/build.yml/badge.svg)](https://github.com/falk-werner/hexview/actions/workflows/build.yml)

# hexview

A simple hex viewer based on [ncurses](https://invisible-island.net/ncurses/) and [mmap](https://man7.org/linux/man-pages/man2/mmap.2.html).

## Commands

| Key       | Descriptions |
| --------- | ------------ |
| Esc, 'q'  | Terminate the program |
| up, 'w'   | Move cursor one line up |
| down, 's' | Move cursor one line down |
| PageUp    | Move cursor an entire page up |
| PageDown  | Move cursor an entire page down |
| '/'       | Enter value to search for |
| 'n'       | Jump to next match |
| 'N'       | Jump to previous match |
| 'g'       | Enter offset to jump to |
| 'G'       | Jump to end of file |

## Limitations

Search matches are limited to 1.000 matches per implementations.

## Build and Run

```bash
cmake -B build
cmake --build build
sudo cmake --install build
```

## References

- [ncurses](https://invisible-island.net/ncurses/)
- [mmap](https://man7.org/linux/man-pages/man2/mmap.2.html)
