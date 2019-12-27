#pragma once
#include "interface_drawable.h"

namespace snake_game {

struct snake_part : interface_drawable {
	snake_part(coords position) : interface_drawable(position, "@") {};
};

struct snake {
	snake(coords head, coords tail) : snake_body{{head}, {tail}} {};
	vector<snake_part> snake_body;
	void shift_snake();
	void grow();
	void move(coords direction);

};

struct food : interface_drawable {
	food(coords position) : interface_drawable(position, "o") {};
};

} // namespace snake_game
