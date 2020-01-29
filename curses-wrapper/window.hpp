#pragma once
#include <ncurses.h>

#include <string>

#include "screen.hpp"

namespace curses {
struct window {
    window(int height, int width, int startx, int starty)
    {
        _win = newwin(height, width, startx, starty);
    }

    window() { _win = nullptr; }

    ~window() { delwin(_win); }

    void clear() { wclear(_win); }

    void clear_from_cursor_to_bottom() { wclrtobot(_win); }

    void clear_from_cursor_to_eol() { wclrtoeol(_win); }

    void refresh() { wrefresh(_win); }

    template <class String = std::string>
    void print_at_coords(int y, int x, String&& s)
    {
        std::string str { s };
        mvwprintw(_win, y, x, str.c_str());
    }

    template <class String = std::string>
    void print_at_cursor(String&& s)
    {
        std::string str { s };
        wprintw(_win, str.c_str());
    }

    void print_border
    (chtype left, chtype right, chtype top, chtype bottom, chtype top_left, chtype top_right, chtype bottom_left, chtype bottom_right)
    {
        wborder(_win, left, right, top, bottom, top_left, top_right, bottom_left, bottom_right);
    }

private:
    WINDOW* _win;
};

} // namespace curses
