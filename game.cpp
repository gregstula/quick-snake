#include "game.hpp"
#include <chrono>
#include <thread>

namespace snake_game {

auto game::game_loop() -> void
{
	while (is_running) {
		int input = getch();
		if (input == KEY_END) end_game();
		switch(input) {
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
			main_win.clear_window();
			render_snake();
			main_win.refresh_window();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

auto game::render_snake() -> void
{
 	for (auto&& snake_part : snake.body()) {
 		auto[y,x,str] = snake_part.get_draw_data();
 		main_win.print_at_coords(y,x,str);
 	}
}


auto game::end_game() -> void
{
    is_running = false;
}

} // namespace snake_game
