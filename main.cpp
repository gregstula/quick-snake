#include <string>
#include <utility>
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

#include "screen.h"
#include "window.h"
#include "snake.h"
#include "interface_drawable.h"

using snake_game::snake;


void render_snake(curses::screen& s, snake& snk) {
	for(auto& snake_part : snk.snake_body) {
		auto[y,x,str] = snake_part.get_draw_data();
		s.print_at_coords(y,x,str);
		std::stringstream ss;
		ss << "(" << y << "," << x << x << ")";
		s.print_at_coords(24,80,ss.str());
	}
}

int main()
{
	curses::screen scr{};
	snake s{{10,10}, {10,11}};
	s.grow();
	s.grow();
	s.grow();
	s.grow();
	s.grow();
	s.grow();
	s.grow();
	bool exit_game = false;
	snake_game::coords last_direction = {0,1};
	while (!exit_game) {
		int input = getch();
		if (input == KEY_END) exit_game = true;
		switch(input) {
			case KEY_UP:
				last_direction = snake_game::direction::north();
				s.move(last_direction);
			break;

			case KEY_DOWN:
				last_direction = snake_game::direction::south();
				s.move(last_direction);
			break;

			case KEY_RIGHT:
				last_direction = snake_game::direction::east();
				s.move(last_direction);
			break;

			case KEY_LEFT:
				last_direction = snake_game::direction::west();
				s.move(last_direction);
			break;
			default:
				s.move(last_direction);
			break;
		}
			scr.clear_screen();
			render_snake(scr,s);
			scr.refresh_screen();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 1;
}
