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
constexpr int MAP_WIDTH = 79;
constexpr int MAP_HEIGHT = 33;

struct frame_data {
    coords snake_direction = direction::EAST;
};

struct game {
    auto game_loop() -> uint64_t;
    void end_game();
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

    std::string game_mode = {};
    curses::window main_win = curses::window(MAP_HEIGHT + 1, MAP_WIDTH + 1, 1, 1);
    curses::window menu_win = curses::window(5, 80, 1 + MAP_HEIGHT, 1);

    snake_game::snake snake = { { 10, 10 }, { 10, 11 } };

    snake_game::food_part food = { { 0, 0 } };

    void process_input(int input, frame_data& current_frame);
    void update(frame_data& current_frame);

    void save_state(frame_data& current_frame);

    void render();
    void render_menu();

    // for debuging and develop mode
    void decrement_game_speed();
    void increment_game_speed();
};

// misc
auto random_coords() -> coords;

} // namespace snake_game
