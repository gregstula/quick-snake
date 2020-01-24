#include <string>
#include <utility>
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

#include "screen.hpp"
#include "window.hpp"
#include "snake.hpp"
#include "interface_drawable.hpp"
#include "game.hpp"

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
