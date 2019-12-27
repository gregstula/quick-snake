#pragma once
#include <utility>
#include <tuple>
#include <memory>

#include "window.h"
#include "snake.h"

namespace snake_game {

using window = curses::window;
struct game {
	game(snake& s, window w) : snk(s), win(w) {};

	snake snk;
	window win{80,24,0,0};

	void render_snake() {
		for(auto& snake_part : snk.snake_body) {
			auto[y,x,str] = snake_part.get_draw_data();
			win.print_at_coords(y,x,str);
		}
	}
};

} //namespace snake
