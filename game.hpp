#pragma once

#include <chrono>
#include <fstream>
#include <memory>
#include <thread>
#include <tuple>
#include <utility>
#include "drawable.hpp"
#include "snake.hpp"
#include "window.hpp"

namespace snake_game {

constexpr int GAME_HEIGHT = 40;
constexpr int GAME_WIDTH = 80;

struct game_state {
    int score = 0;
    coords food_position;
    coords snake_position;
    coords snake_direction;
};

using namespace std::chrono_literals;
using std::chrono::nanoseconds;
class game {
    bool is_running = true;

    snake_game::snake snake = snake_game::snake({ 10, 10 }, { 10, 11 });
    snake_game::food food = snake_game::food({ 0, 0 });
    curses::window main_win = curses::window(GAME_HEIGHT, GAME_WIDTH, 10, 10);

    // 1 frame at 60 fps = 16 ms
    nanoseconds game_speed = 16ms;

    game_state current_state;
    game_state previous_state;

    auto process_input(int input) -> int;
    auto update(game_state) -> void;
    void update(nanoseconds delay);
    auto render() -> void;
    auto render_snake() -> void;
    auto render_food() -> void;
    auto process_movement() -> void;
    // counter intuitive method name for writer, but intuitive name for the caller
    auto decrement_game_speed()
    {
        if (game_speed <= 100ms) {
            game_speed += 4ms;
        }
    }
    auto increment_game_speed()
    {
        if (game_speed >= 20ms) {
            game_speed -= 4ms;
        }
    }

public:
    auto end_game() -> void;
    auto game_loop() -> void;
};

} // namespace snake_game
