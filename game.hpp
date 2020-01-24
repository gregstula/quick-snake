#pragma once

#include <chrono>
#include <memory>
#include <thread>
#include <tuple>
#include <utility>
#include <fstream>

#include "snake.hpp"
#include "window.hpp"
namespace snake_game {

constexpr int GAME_HEIGHT = 24;
constexpr int GAME_WIDTH = 80;
using game_time = std::chrono::time_point<std::chrono::high_resolution_clock>;

struct game_state {
    int score = 0;
};

class game {
    bool is_running = true;
    coords last_direction = direction::WEST;

    snake_game::snake snake = snake_game::snake({ 10, 10 }, { 10, 11 });
    snake_game::food food = snake_game::food({ 0, 0 });

    game_state current_state;
    game_state previous_state;

    uint_fast64_t frames = 0;

    auto process_input(int input) -> void;
    auto render() -> void;
    auto render_snake() -> void;
    auto render_food() -> void;

public:
    curses::window main_win = curses::window(GAME_HEIGHT, GAME_WIDTH, 10, 10);
    auto end_game() -> void;
    auto game_loop() -> void;

};

} //namespace snake
