#include <ncurses.h>

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

#include "game.hpp"
#include "interface_drawable.hpp"
#include "screen.hpp"
#include "snake.hpp"
#include "window.hpp"

struct game_state {
    int score = 0;
};

int main()
{
    auto screen = curses::screen();
    auto game = snake_game::game();
    game.game_loop();
    return 0;
}

;
