#include "game.hpp"
#include <stdexcept>

namespace snake_game {
using namespace std::literals::chrono_literals;
using namespace std::chrono;
using namespace std::this_thread;

auto game::game_loop() -> void
{
    while (is_running) {
        auto frame_start_time = high_resolution_clock::now();
        auto current_frame = frame_data();
        // only get one character at a time
        process_input(getch(), current_frame);
        update(current_frame);
        render();
        if (previous_frame.snake_direction == direction::NORTH || current_frame.snake_direction == direction::SOUTH) {
            sleep_for((frame_start_time + frame_speed * 1.75) - high_resolution_clock::now());
        }
        else {
            sleep_for(frame_start_time + frame_speed - high_resolution_clock::now());
        }
    }

    if (user_lost) {
        {
            curses::refresh_guard<curses::window> auto_refresh(menu_win);
            std::stringstream ss;
            ss << "YOU LOST! Your Score: " << score;
            menu_win.print_at_coords(2, 2, ss.str());
        }
        sleep_for(3s);
    }
}

inline auto game::process_input(int input, frame_data& current_frame) -> void
{
    if (input == KEY_END) {
        end_game();
    }

    current_frame.snake_direction = previous_frame.snake_direction;

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
    auto&& [next_y, next_x] = snake.head();

    if ((next_y == 0) || (next_y == MAP_HEIGHT)) {
        user_lost = true;
        end_game();
        return;
    }
    if ((next_x == 0) || (next_x == MAP_WIDTH)) {
        user_lost = true;
        end_game();
        return;
    }

    auto next_head = snake.next_position(current_frame.snake_direction);
    if (next_head == food.position) {
        food_eaten = true;
        snake.grow(current_frame.snake_direction);
    }

    snake.move(current_frame.snake_direction);

    for (auto part = std::begin(snake.body()) + 1; part != std::end(snake.body()); part++) {
        if (part->position == snake.head()) {
            user_lost = true;
            render();
            end_game();
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

inline auto game::process_movement(frame_data& current_frame) -> void
{
}

// all render logic goes here
auto game::render() -> void
{

    render_menu();
    curses::refresh_guard<curses::window> game(main_win);
    // render food
    auto [y, x, str] = get_draw_data(food);
    main_win.print_at_coords(y, x, str);

    // render snake
    for (auto&& part : snake.body()) {
        auto [y, x, str] = get_draw_data(part);
        main_win.print_at_coords(y, x, str);
    }
}

auto game::render_menu() -> void
{
    curses::refresh_guard<curses::window> menu(menu_win);
    std::stringstream ss;
    ss << "Score: " << score;
    menu_win.print_at_coords(2, 2, ss.str());
}

auto game::end_game() -> void
{
    is_running = false;
}

// counter intuitive to increment in a decrement function, but easier for caller
inline auto game::decrement_game_speed() -> void
{
    if (frame_speed <= 100ms) {
        frame_speed += 4ms;
    }
}

inline auto game::increment_game_speed() -> void
{
    if (frame_speed >= 20ms) {
        frame_speed -= 4ms;
    }
}

auto random_coords() -> coords
{
    thread_local static std::random_device rd;
    thread_local static std::mt19937 rng(rd());

    thread_local static std::uniform_int_distribution<uint> y_distribution(1, MAP_HEIGHT - 1);
    int y = y_distribution(rng);

    thread_local static std::uniform_int_distribution<uint> x_distribution(1, MAP_WIDTH - 1);
    int x = x_distribution(rng);
    return { y, x };
}

} // namespace snake_game
