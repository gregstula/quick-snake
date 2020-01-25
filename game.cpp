#include "game.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

namespace snake_game {
bool last_move_processed = false;
inline auto game::process_input() -> void
{
    int input;
    while ((input = getch()) != ERR) {

        if (input == KEY_END)
            end_game();
        switch (input) {
        case KEY_UP:
            if (last_direction != direction::SOUTH)
                last_direction = direction::NORTH;
                last_move_processed = false;
            break;

        case KEY_DOWN:
            if (last_direction != direction::NORTH)
                last_direction = direction::SOUTH;
                last_move_processed = false;
            break;

        case KEY_RIGHT:
            if (last_direction != direction::WEST)
                last_direction = direction::EAST;
                last_move_processed = false;
            break;

        case KEY_LEFT:
            if (last_direction != direction::EAST)
                last_direction = direction::WEST;
                last_move_processed = false;
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
        }
    }
}

// All gamestate update logic goes here
void game::update() {
    process_movement();
}

inline auto game::process_movement() -> void
{
    auto&& next_position = snake.next_position(last_direction);
    if (next_position.y <= 1) {
        // last_direction = direction::invert_direction(last_direction);
        snake.teleport(coords { GAME_HEIGHT - 1, next_position.x });
        return;
    }
    else if (next_position.y >= GAME_HEIGHT - 1) {
        snake.teleport(coords { 1, next_position.x });
        return;
    }
    else if (next_position.x <= 1) {
        snake.teleport(coords { next_position.y, GAME_WIDTH - 1 });
        return;
    }
    else if (next_position.x >= GAME_WIDTH - 1) {
        // last_direction = direction::invert_direction(last_direction);
        snake.teleport(coords { next_position.y, 1 });
        return;
    }
    snake.move(last_direction);
    last_move_processed = true;
}

// all render logic goes here
inline auto game::render() -> void
{
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

    while (is_running) {
        auto current_time = now();
        // auto elapsed_time = current_time - previous_time;
        process_input();
        update();
        auto loop_time = duration_cast<nanoseconds>(current_time - now());
        curses::refresh_guard<curses::window> auto_refresh(main_win);
        render();
        if (last_direction == direction::NORTH || last_direction == direction::SOUTH) {
            std::this_thread::sleep_for(loop_time + game_speed * 1.39);
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
}

inline auto game::render_food() -> void
{
    auto [y, x, str] = food.get_draw_data();
    main_win.print_at_coords(y, x, str);
}

inline auto game::end_game() -> void
{
    is_running = false;
}

} // namespace snake_game
