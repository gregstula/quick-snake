
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <sstream>
#include <thread>
#include "game.hpp"

namespace snake_game {
inline auto game::process_input(int input) -> int
{
    if (input == KEY_END)
        end_game();
    switch (input) {
    case KEY_UP:
        if (previous_state.snake_direction != direction::SOUTH) {
            current_state.snake_direction = direction::NORTH;
        }
        break;
    case KEY_DOWN:
        if (previous_state.snake_direction != direction::NORTH) {
            current_state.snake_direction = direction::SOUTH;
        }
        break;

    case KEY_RIGHT:
        if (previous_state.snake_direction != direction::WEST) {
            current_state.snake_direction = direction::EAST;
        }
        break;

    case KEY_LEFT:
        if (previous_state.snake_direction != direction::EAST) {
            current_state.snake_direction = direction::WEST;
        }
        break;
    case 43: // plus sign
        increment_game_speed();
        break;
    case 45: // minus sign
        decrement_game_speed();
        break;
    case 32: // space bar
        snake.grow();
        break;
    default:
        break;
    };
    return input;
}

// All gamestate update logic goes here
void game::update(game_state)
{
    process_movement();
    previous_state = current_state;
    current_state.snake_position = snake.head();
}

void game::update(std::chrono::nanoseconds delay)
{
    process_movement();
    std::this_thread::sleep_for(delay);
}

auto game::process_movement() -> void
{
    auto&& next_position = snake.next_position(current_state.snake_direction);
    if (next_position.y <= 0) {
        // current_state.snake_direction = direction::invert_direction(previous_state.snake_direction);
        snake.teleport(coords { GAME_HEIGHT, next_position.x });
        return;
    }
    else if (next_position.y >= GAME_HEIGHT) {
        snake.teleport(coords { 0, next_position.x });
        return;
    }
    else if (next_position.x <= 0) {
        snake.teleport(coords { next_position.y, GAME_WIDTH });
        return;
    }
    else if (next_position.x >= GAME_WIDTH - 0) {
        // current_state.snake_direction = direction::invert_direction(previous_state.snake_direction);
        snake.teleport(coords { next_position.y, 0 });
        return;
    }
    snake.move(previous_state.snake_direction);
}

// all render logic goes here
auto game::render() -> void
{
    curses::refresh_guard<curses::window> auto_refresh(main_win);
    render_snake();
}

// Get's the current time
inline auto now() -> std::chrono::time_point<std::chrono::high_resolution_clock>
{
    return std::chrono::high_resolution_clock::now();
}

auto game::game_loop() -> void
{
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;

    int input = 0;
    int last_input = 0;
    while (is_running) {
        auto current_time = now();
        // only get one character at a time
        input = getch();
        last_input = process_input(input);
        update(current_state);
        render();
        auto loop_time = duration_cast<nanoseconds>(current_time - now());
        if (previous_state.snake_direction == direction::NORTH || current_state.snake_direction == direction::SOUTH) {
            std::this_thread::sleep_for(loop_time + game_speed * 1.73);
        }
        else {
            std::this_thread::sleep_for(loop_time + game_speed);
        }
    }
}

auto game::render_snake() -> void
{
    for (auto&& snake_part : snake.body()) {
        auto [y, x, str] = snake_part.get_draw_data();
        main_win.print_at_coords(y, x, str);
    }
    std::stringstream s;
    s << "Current Position: " << current_state.snake_direction.x << ", " << current_state.snake_direction.y;
    main_win.print_at_coords(10, 10, s.str());
}

auto game::render_food() -> void
{
    auto [y, x, str] = food.get_draw_data();
    main_win.print_at_coords(y, x, str);
}

inline auto game::end_game() -> void
{
    is_running = false;
}

auto reandom_coords() -> coords
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> y_distribution(1, GAME_HEIGHT);
    std::uniform_int_distribution<int> x_distribution(1, GAME_HEIGHT);
    return { y_distribution(generator), x_distribution(generator) };
}

} // namespace snake_game
