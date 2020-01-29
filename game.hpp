#pragma once

#include "drawable.hpp"
#include "snake.hpp"
#include "window.hpp"
#include <chrono>
#include <fstream>
#include <memory>
#include <random>
#include <sstream>
#include <thread>
#include <tuple>
#include <utility>

namespace snake_game {

constexpr int GAME_HEIGHT = 40;
constexpr int GAME_WIDTH = 80;

struct frame_data {
    int score = 0;
    coords food_position;
    coords snake_position;
    coords snake_direction = direction::WEST;
};

using namespace std::chrono_literals;
using std::chrono::nanoseconds;
struct game {
    auto game_loop() -> void;
    bool debug_mode = false;

private:
    bool is_running = true;
    nanoseconds game_speed = 16ms;

    snake_game::snake snake = { { 10, 10 }, { 10, 11 } };
    snake_game::food food = { { 0, 0 } };
    curses::window main_win = curses::window(GAME_HEIGHT, GAME_WIDTH, 10, 10);

    // 1 frame at 60 fps = 16 ms
    frame_data previous_frame;

    auto process_input(int input, frame_data& current_frame) -> void;
    auto process_movement(frame_data& current_frame) -> void;
    auto save_state(frame_data& current_frame) -> void;
    auto update(frame_data& current_frame) -> void;
    auto render() -> void;
    auto render_snake() -> void;
    auto render_food() -> void;
    // counter intuitive method name for writer, but intuitive name for the caller
    auto decrement_game_speed() -> void;
    auto increment_game_speed() -> void;
    auto end_game() -> void;
};

} // namespace snake_game
