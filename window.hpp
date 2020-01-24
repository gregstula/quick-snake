#pragma once
#include <ncurses.h>
#include <string>
namespace curses {

struct window {
    window(int height, int width, int startx, int starty)
    {
        _win = newwin(height, width, startx, starty);
    }

    window()
    {
        _win = nullptr;
    }

    ~window()
    {
        delwin(_win);
    }

    void clear_window()
    {
        wclear(this->_win);
    }

    void clear_from_cursor_to_bottom()
    {
        wclrtobot(this->_win);
    }

    void clear_from_cursor_to_eol()
    {
        wclrtoeol(this->_win);
    }

    void refresh_window()
    {
        wrefresh(this->_win);
    }

    template <typename S = std::string>
    void print_at_coords(int y, int x, S&& str)
    {
        mvwprintw(this->_win, y, x, str.c_str());
    }

    template <typename S = std::string>
    void print_at_cursor(S&& str)
    {
        wprintw(this->_win, str.c_str());
    }

private:
    WINDOW* _win;
};

} //namespace curses
