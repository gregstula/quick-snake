#include "game.hpp"
#include <stdexcept>

namespace snake_game {
using namespace std::literals::chrono_literals;
using namespace std::chrono;
using namespace std::this_thread;

auto game::game_loop() -> uint64_t
{
    while (is_running) {
        auto frame_start_time = high_resolution_clock::now();
        auto current_frame = frame_data();
        // get input from stdscr
        process_input(getch(), current_frame);
        update(current_frame);
        render();
        // normalize vertical travel speed which is naturally faster due to line to col size ratio
        if (previous_frame.snake_direction == direction::NORTH || current_frame.snake_direction == direction::SOUTH) {
            sleep_for((frame_start_time + frame_speed * 2) - high_resolution_clock::now());
        }
        else {
            sleep_for(frame_start_time + frame_speed - high_resolution_clock::now());
        }
    }

    if (user_lost) {
        {
            curses::refresh_guard<curses::window> auto_refresh(*menu_win);
            std::stringstream ss;
            ss << "YOU LOST! Your Score: " << score;
            menu_win->print_at_coords(2, 2, ss.str());
        }
        sleep_for(900ms);
    }
    return score;
}

inline void game::process_input(int input, frame_data& current_frame)
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
inline void game::update(frame_data& current_frame)
{
    auto&& [curr_y, curr_x] = snake.head();

    // Did we collide with wall?
    if ((curr_y == 0) || (curr_y == Map_Height)) {
        user_lost = true;
        end_game();
        return;
    }
    if ((curr_x == 0) || (curr_x == Map_Width)) {
        user_lost = true;
        end_game();
        return;
    }

    // Will we eat?
    auto next_head = snake.next_position(current_frame.snake_direction);
    if (next_head == food.position) {
        food_eaten = true;
        snake.grow(current_frame.snake_direction);
    }

    // Always grow before move
    snake.move(current_frame.snake_direction);

    //Did we collide with tail?
    bool head = true;
    for (auto&& part : snake.body()) {
        if (head) {
            head = false;
            continue;
        }
        if (part.position == snake.head()) {
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

inline void game::save_state(frame_data& current_frame)
{
    previous_frame = current_frame;
}

// all render logic goes here
void game::render()
{

    render_menu();
    // render snake
    curses::refresh_guard<curses::window> refresh(*main_win);
    for (auto&& part : snake.body()) {
        auto [y, x, str] = get_draw_data(part);
        main_win->print_at_coords(y, x, str);
        // render food
    }
     auto [fy, fx, fstr] = get_draw_data(food);
     main_win->print_at_coords(fy, fx, fstr);
}

void game::render_menu()
{
    curses::refresh_guard<curses::window> refresh(*main_win);
    std::stringstream ss;
    ss << "Score: " << score;
    menu_win->print_at_coords(2, 2, ss.str());
}

inline void game::end_game()
{
    is_running = false;
}

// counter intuitively increment in a decrement function
inline void game::decrement_game_speed()
{
    if (frame_speed <= 100ms) {
        frame_speed += 4ms;
    }
}

inline void game::increment_game_speed()
{
    if (frame_speed >= 20ms) {
        frame_speed -= 4ms;
    }
}

auto game::random_coords() -> coords
{
    thread_local static std::random_device rd;
    thread_local static std::mt19937 rng(rd());

    thread_local static std::uniform_int_distribution<uint> y_distribution(1, Map_Height - 1);
    int y = y_distribution(rng);

    thread_local static std::uniform_int_distribution<uint> x_distribution(1, Map_Width - 1);
    int x = x_distribution(rng);
    return { y, x };
}

} // namespace snake_game
