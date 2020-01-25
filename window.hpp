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

    void clear() { wclear(this->_win); }

    void clear_from_cursor_to_bottom() { wclrtobot(this->_win); }

    void clear_from_cursor_to_eol() { wclrtoeol(this->_win); }

    void refresh() { wrefresh(this->_win); }

    template <class String>
    void print_at_coords(int y, int x, String&& str)
    {
        mvwprintw(this->_win, y, x, str.c_str());
    }

    template <class String>
    void print_at_cursor(String&& str)
    {
        wprintw(this->_win, str.c_str());
    }

    void print_border()
    {
        wborder(_win, '|', '|', '-', '-', '+', '+', '+', '+');
    }

private:
    WINDOW* _win;
};

} // namespace curses
