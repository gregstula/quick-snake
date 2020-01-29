#pragma once

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
constexpr int MAP_WIDTH = 80;

constexpr int MAP_HEIGHT = 40;

struct frame_data {
    coords snake_direction = direction::EAST;
};

struct game {
    auto game_loop() -> void;
    auto end_game() -> void;
    bool debug_mode = false;

private:
    bool is_running = true;
    bool food_eaten = true;
    bool user_lost = false;

    // initial placement increases score
    int64_t score = -1;

    // 1 frame at 60 fps = 16 ms
    std::chrono::nanoseconds frame_speed = std::chrono::milliseconds(16);

    frame_data previous_frame = {};

    curses::window main_win = curses::window(MAP_HEIGHT, MAP_WIDTH, 10, 10);
    snake_game::snake snake = { { 10, 10 }, { 10, 11 } };

    snake_game::food_part food = { { 0, 0 } };

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

} // namespace snake_game
