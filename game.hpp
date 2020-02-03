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

struct frame_data {
    coords snake_direction = direction::EAST;
};

struct game {
    game(int map_maxy, int map_maxx) {
        Map_Height = map_maxy;
        Map_Width = map_maxx;
        main_win = std::make_unique<curses::window>(Map_Height + 1, Map_Width + 1, 1, 1);
        menu_win = std::make_unique<curses::window>(5, Map_Width + 1, Map_Height + 1, 1);
    }

    auto game_loop() -> uint64_t;
    void end_game();
    bool debug_mode = false;

private:
    bool is_running = true;
    bool food_eaten = true;
    bool user_lost = false;

    // initial placement increases score
    int64_t score = -1;

    // 1 frame at 60 fps = 16.6 ms
    std::chrono::nanoseconds frame_speed{16600000};

    int Map_Height = 0;
    int Map_Width = 0;

    std::unique_ptr<curses::window> main_win = nullptr;
    std::unique_ptr<curses::window> menu_win = nullptr;

    frame_data previous_frame = {};

    std::string game_mode = {};
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

    // misc
    auto random_coords() -> coords;
};

} // namespace snake_game
