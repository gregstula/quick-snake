#pragma once

#include <functional>
#include <iostream>
#include <ncurses.h>
#include <string>
namespace curses {

// Attatch a window to this class to use
// RAII to refresh an ncurses screen automatically when it falls out of scopt
template <class Screen>
struct refresh_guard {
    typedef Screen screen_type;

    inline explicit refresh_guard(screen_type& s) noexcept : screen(s)
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
    screen() noexcept
    {
        setlocale(LC_ALL, "en_US.UTF-8");
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        meta(stdscr, TRUE);
        nodelay(stdscr, TRUE); // let getch pass through
        curs_set(0);
    }

    ~screen() noexcept
    {
        clear();
        endwin();
    }

    auto get_key() -> int { return getch(); }

    template <typename S>
    void print_at_coords(int y, int x, S&& str)
    {
        std::string s { std::forward<S>(str) };
        mvprintw(y, x, s.c_str());
    }

    template <typename S>
    void print_at_cursor(S&& str)
    {
        std::string s { std::forward<S>(str) };
        printw(s.c_str());
    }

    void print_border() noexcept {}
    void clear() noexcept { ::clear(); }
    void refresh() noexcept { ::refresh(); }

private:
};

} // namespace curses
