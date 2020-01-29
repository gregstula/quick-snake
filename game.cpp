#include "game.hpp"
#include <stdexcept>

namespace snake_game {
inline auto game::process_input(int input, frame_data& current_frame) -> void
{
    if (input == KEY_END) {
        end_game();
    }
    switch (input) {
    case KEY_UP:
        if (previous_frame.snake_direction != direction::SOUTH) {
            current_frame.snake_direction = direction::NORTH;
        }
        break;
    case KEY_DOWN:
        if (previous_frame.snake_direction != direction::NORTH) {
            current_frame.snake_direction = direction::SOUTH;
        }
        break;

    case KEY_RIGHT:
        if (previous_frame.snake_direction != direction::WEST) {
            current_frame.snake_direction = direction::EAST;
        }
        break;

    case KEY_LEFT:
        if (previous_frame.snake_direction != direction::EAST) {
            current_frame.snake_direction = direction::WEST;
        }
        break;
    default:
        current_frame.snake_direction = previous_frame.snake_direction;
        break;
    }

    if (debug_mode) {
        switch (input) {
        case 43: // plus sign
            increment_game_speed();
            break;
        case 45: // minus sign
            decrement_game_speed();
            break;
        case 32: // space bar
            snake.grow(current_frame.snake_direction);
            break;
        default:
            break;
        }
    }
}

// All gamestate update logic goes here
auto game::update(frame_data& current_frame) -> void
{
    process_movement(current_frame);

    if (snake.head() == food.position) {
        food_eaten = true;
        snake.grow(current_frame.snake_direction);
    }

    for (auto part = std::begin(snake.body()) + 1; part != std::end(snake.body()); part++) {
        if (part->position == snake.head()) {
            throw std::runtime_error("YOU LOSE");
        }
    }

    if (food_eaten) {
        food = { random_coords() };
        food_eaten = false;
        score++;
    }
    save_state(current_frame);
}

inline auto game::save_state(frame_data& current_frame) -> void
{
    previous_frame = current_frame;
}

auto game::process_movement(frame_data& current_frame) -> void
{
    auto&& [next_y, next_x] = snake.next_position(current_frame.snake_direction);

    if (next_y <= 0) {
        // current_frame.snake_direction = direction::invert_direction(previous_frame.snake_direction);
        snake.teleport({ GAME_HEIGHT, next_x });
        return;
    }
    else if (next_y >= GAME_HEIGHT) {
        snake.teleport({ 0, next_x });
        return;
    }
    else if (next_x <= 0) {
        snake.teleport({ next_y, GAME_WIDTH });
        return;
    }
    else if (next_x >= GAME_WIDTH - 0) {
        // current_frame.snake_direction = direction::invert_direction(previous_frame.snake_direction);
        snake.teleport({ next_y, 0 });
        return;
    }
    snake.move(current_frame.snake_direction);
}

// all render logic goes here
auto game::render() -> void
{
    curses::refresh_guard<curses::window> auto_refresh(main_win);
    render_snake();
    render_food();
}

// Get's the current time
auto now() -> std::chrono::time_point<std::chrono::high_resolution_clock>
{
    return std::chrono::high_resolution_clock::now();
}

auto game::game_loop() -> void
{
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;

    while (is_running) {
        auto current_time = now();
        auto current_frame = frame_data();
        // only get one character at a time
        process_input(getch(), current_frame);
        update(current_frame);
        render();
        auto loop_time = duration_cast<nanoseconds>(current_time - now());
        if (previous_frame.snake_direction == direction::NORTH || current_frame.snake_direction == direction::SOUTH) {
            std::this_thread::sleep_for(loop_time + game_speed * 1.73);
        }
        else {
            std::this_thread::sleep_for(loop_time + game_speed);
        }
    }
}

inline auto game::render_snake() -> void
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

inline auto game::decrement_game_speed() -> void
{
    if (game_speed <= 100ms) {
        game_speed += 4ms;
    }
}

inline auto game::increment_game_speed() -> void
{
    if (game_speed >= 20ms) {
        game_speed -= 4ms;
    }
}

std::random_device rd;
std::mt19937 rng(rd());

auto random_coords() -> coords
{
    std::uniform_int_distribution<uint> y_distribution(1, snake_game::GAME_HEIGHT);
    int y = y_distribution(rng);

    std::uniform_int_distribution<uint> x_distribution(1, snake_game::GAME_WIDTH);
    int x = x_distribution(rng);
    return { y, x };
}

} // namespace snake_game
