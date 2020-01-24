#include <chrono>
#include <thread>
#include <cstdint>
#include <iostream>
#include "game.hpp"

namespace snake_game {
// 1 / 60 fps = 16 ms
constexpr auto NS_PER_FRAME = std::chrono::nanoseconds(std::chrono::milliseconds(16));

inline auto game::process_input(int input) -> void
{
    if (input == KEY_END) end_game();

    switch (input) {
    case KEY_UP:
        if (last_direction != direction::SOUTH) last_direction = direction::NORTH;
        snake.move(last_direction);
        break;

    case KEY_DOWN:
        if (last_direction != direction::NORTH) last_direction = direction::SOUTH;
        snake.move(last_direction);
        break;

    case KEY_RIGHT:
        if (last_direction != direction::WEST) last_direction = direction::EAST;
        snake.move(last_direction);
        break;

    case KEY_LEFT:
        if (last_direction != direction::EAST) last_direction = direction::WEST;
        snake.move(last_direction);
        break;
    default:
        snake.move(last_direction);
        break;
    }
}

inline auto game::render() -> void
{
    render_snake();
}

inline auto now() -> game_time {
    return std::chrono::high_resolution_clock::now();
}

auto game::game_loop() -> void
{
    using std::chrono::nanoseconds;
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;

    while (is_running) {
        auto current_time = now();
        //auto elapsed_time = current_time - previous_time;
        curses::refresh_guard<curses::window> auto_refresh(main_win);
        int input = getch();
        process_input(input);
        render();
        auto frame_time = duration_cast<nanoseconds>(current_time - now());
        std::this_thread::sleep_for( frame_time + NS_PER_FRAME);

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
