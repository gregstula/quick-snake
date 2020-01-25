#include "game.hpp"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

namespace snake_game {
// 1 / 60 fps = 16 ms
using namespace std::chrono_literals;
constexpr auto FRAME = 32ms;

inline auto game::process_input(int input) -> void
{
    if (input == KEY_END)
        end_game();

    switch (input) {
    case KEY_UP:
        if (last_direction != direction::SOUTH)
            last_direction = direction::NORTH;
        break;

    case KEY_DOWN:
        if (last_direction != direction::NORTH)
            last_direction = direction::SOUTH;
        break;

    case KEY_RIGHT:
        if (last_direction != direction::WEST)
            last_direction = direction::EAST;
        break;

    case KEY_LEFT:
        if (last_direction != direction::EAST)
            last_direction = direction::WEST;
        break;
    default:
        break;
    }
}

// All gamestate update logic goes here
inline auto game::update() -> void
{
    auto&& next_position = snake.move(last_direction);

    if (next_position.x == 0) {
        snake.teleport(coords { next_position.y, GAME_WIDTH });
    }
    else if (next_position.x == GAME_WIDTH) {
        // last_direction = direction::invert_direction(last_direction);
        snake.teleport(coords { next_position.y, 0 });
    }

    // TODO check literal corner case
    if (next_position.y == 0) {
        // last_direction = direction::invert_direction(last_direction);
        snake.teleport(coords { GAME_HEIGHT, next_position.x });
    }
    else if (next_position.y == GAME_HEIGHT) {
        snake.teleport(coords { 0, next_position.x });
    }
}

// all render logic goes here
inline auto game::render() -> void
{
    render_snake();
}

// Get's the current time
inline auto now() -> game_time
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
        curses::refresh_guard<curses::window> auto_refresh(main_win);
        int input = getch();
        process_input(input);
        update();
        render();
        auto loop_time = duration_cast<nanoseconds>(current_time - now());
        std::this_thread::sleep_for(loop_time + FRAME);
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
