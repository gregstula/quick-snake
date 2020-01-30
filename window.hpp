#pragma once
#include <ncurses.h>

#include <string>

#include "screen.hpp"

namespace curses {
struct window {
    window(int height, int width, int startx, int starty) noexcept
    {
        _win = newwin(height, width, startx, starty);
        curs_set(0);
    }

    window() noexcept { _win = nullptr; }

    ~window() noexcept {
        wclear(_win);
        wrefresh(_win);
        delwin(_win);
    }

    void clear() noexcept { werase(_win); }

    void clear_from_cursor_to_bottom() noexcept { wclrtobot(_win); }

    void clear_from_cursor_to_eol() noexcept { wclrtoeol(_win); }

    void refresh() noexcept { wrefresh(_win); }

    template <class S>
    void print_at_coords(int y, int x, S&& str)
    {
        std::string s { std::forward<S>(str) };
        mvwprintw(_win, y, x, s.c_str());
    }

    template <class S>
    void print_at_cursor(S&& str)
    {
        std::string s { std::forward<S>(str) };
        wprintw(_win, s.c_str());
    }

    void print_border() noexcept
    {
        wborder(_win, '|', '|', '-', '-', '+', '+', '+', '+');
    }

private:
    WINDOW* _win;
};

} // namespace curses
