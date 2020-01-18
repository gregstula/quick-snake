#pragma once
#include <utility>
#include <tuple>
#include <memory>

#include "window.h"
#include "snake.h"

constexpr int Game_Height = 24;
constexpr int Game_Width = 80;
namespace snake_game {
using window = curses::window;
struct game {

	window main_win{Game_Height,Game_Width,0,0};

	snake snk{{Game_Height/2, Game_Width/2}, {Game_Height/2, (Game_Width/2) + 1}};
	food fd{{0,0}};

	void render_snake() {
		for(auto& snake_part : snk.snake_body) {
			auto[y,x,str] = snake_part.get_draw_data();
			main_win.print_at_coords(y,x,str);
		}
	}
};

} //namespace snake
