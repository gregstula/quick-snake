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

using namespace std::chrono_literals;
using std::chrono::nanoseconds;

constexpr int GAME_HEIGHT = 40;
constexpr int GAME_WIDTH = 80;

struct frame_data {
    int score = 0;
    coords food_position = { 0, 0 };
    coords snake_position = { 10, 10 };
    coords snake_direction = direction::EAST;
};

struct game {
    auto game_loop() -> void;
    auto end_game() -> void;
    bool debug_mode = false;

private:
    bool is_running = true;
    bool food_eaten = true;
    int64_t score = 0;

    // 1 frame at 60 fps = 16 ms
    nanoseconds game_speed = 16ms;
    // refer to previouslt processed frame
    frame_data previous_frame = {};

    curses::window main_win = curses::window(GAME_HEIGHT, GAME_WIDTH, 10, 10);
    snake_game::snake snake = { { 10, 10 }, { 10, 11 } };
    snake_game::food food = { { 0, 0 } };

    auto process_input(int input, frame_data& current_frame) -> void;
    auto update(frame_data& current_frame) -> void;

    auto process_movement(frame_data& current_frame) -> void;
    auto save_state(frame_data& current_frame) -> void;

    auto render() -> void;
    auto render_snake() -> void;
    auto render_food() -> void;

    // for debuging and develop mode
    auto decrement_game_speed() -> void;
    auto increment_game_speed() -> void;
};

// misc
auto random_coords() -> coords;
auto now() -> std::chrono::time_point<std::chrono::high_resolution_clock>;

} // namespace snake_game
