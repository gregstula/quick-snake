#include <utility>
#include <tuple>
#include <memory>

#include "window.h"
#include "snake.h"

namespace snake_game {


struct game {
	game() : window(std::make_unique<curses::window>()) {}

private:
	std::unique_ptr<curses::window> window;
	snake _snake{};
};



} //namespace snake
