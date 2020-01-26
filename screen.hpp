#pragma once

#include <iostream>
#include <ncurses.h>
#include <string>
namespace curses {

// Attatch a window to this class to use
// RAII to refresh an ncurses screen automatically when it falls out of scopt
template <class Screen>
struct refresh_guard {
    typedef Screen screen_type;

    inline explicit refresh_guard(screen_type& s) : screen(s)
    {
        screen.clear();
        screen.print_border();
    }

    inline ~refresh_guard() { screen.refresh(); }
    refresh_guard& operator=(refresh_guard const&) = delete;
    refresh_guard(refresh_guard const&) = delete;

private:
    screen_type& screen;
};

class screen {
public:
    screen()
    {
        setlocale(LC_ALL, "en_US.UTF-8");
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        meta(stdscr, TRUE);
        nodelay(stdscr, TRUE); // let getch pass through
        curs_set(0);
        typeahead(-1); // turn off look ahead optimization
        //        if (has_colors()) {
        //            start_color();
        //        }
    }

    ~screen() { endwin(); }

    int get_key() { return getch(); }

    template <typename S = std::string>
    void print_at_coords(int y, int x, S&& str)
    {
        mvprintw(y, x, str.c_str());
    }

    template <typename S = std::string>
    void print_at_cursor(S&& str)
    {
        printw(str.c_str());
    }

    void clear() { ::clear(); }
    void refresh() { ::refresh(); }

    bool is_active() { return _active; }

    void quit() { _active = false; }
    void print_border() {};

private:
    //	int _screen_height = 24;
    //	int _screen_width = 80;
    bool _active = true;
};

} // namespace curses
