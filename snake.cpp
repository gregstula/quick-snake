#include "snake.h"
#include "interface_drawable.h"

#include <iostream>
// drawable member function impl
using namespace snake_game;
using namespace std;

// simply grow from tail pointer if possible
void snake::grow()
{
	coords new_coords = snake_body.back().get_coords();
	new_coords = new_coords + coords{.y = 0, .x = 1};
	snake_body.emplace_back(snake_part{new_coords});
}

// We will use the tail as the new head
void snake::move(coords direction) {
	snake_body.pop_back();
	auto new_coords = snake_body.at(0).get_coords() + direction;
	snake_body.emplace(snake_body.begin(), snake_part{new_coords});
}


