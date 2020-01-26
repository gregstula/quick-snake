#include "game.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <thread>

namespace snake_game {
bool last_move_processed = false;
inline auto game::process_input(int input) -> int
{
    if (input == KEY_END)
        end_game();
    switch (input) {
    case KEY_UP:
        if (last_direction != direction::SOUTH) {
            last_direction = direction::NORTH;
        }

    case KEY_DOWN:
        if (last_direction != direction::SOUTH) {
            last_direction = direction::SOUTH;
        }
        break;

    case KEY_RIGHT:
        if (last_direction != direction::WEST) {
            last_direction = direction::EAST;
        }
        break;

    case KEY_LEFT:
        if (last_direction != direction::WEST) {
            last_direction = direction::WEST;
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
void game::update()
{
    process_movement();
}

void game::update(std::chrono::nanoseconds delay)
{
    process_movement();
    std::this_thread::sleep_for(delay);
}

auto game::process_movement() -> void
{
    auto&& next_position = snake.next_position(last_direction);
    if (next_position.y <= 0) {
        // last_direction = direction::invert_direction(last_direction);
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
        // last_direction = direction::invert_direction(last_direction);
        snake.teleport(coords { next_position.y, 0 });
        return;
    }
    snake.move(last_direction);
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
    int last_input=0;
    while (is_running) {
        auto current_time = now();
        // only get one character at a time
        input = getch();
        last_input = process_input(input);
        render();
        auto loop_time = duration_cast<nanoseconds>(current_time - now());
        if (last_direction == direction::NORTH || last_direction == direction::SOUTH) {
            update(duration_cast<nanoseconds>(loop_time + game_speed * 1.75));
        }
        else {
            update(loop_time + game_speed);
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
    s << "last direction: " << last_direction.x << ", " << last_direction.y;
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

} // namespace snake_game
