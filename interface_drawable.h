#pragma once
#include <string>
#include <memory>
#include <utility>
#include <tuple>
#include <vector>

namespace snake_game {
using std::string;
using std::vector;


struct coords {
	int y,x;
};

struct draw_data {
	draw_data(coords c, string s) : y(c.y), x(c.x), s(s) {};
	int y,x;
	string s;
};

namespace direction {
	constexpr auto north() -> coords { return {-1,0}; };
	constexpr auto south() -> coords { return {1,0}; };
	constexpr auto east() -> coords { return {0,1}; };
	constexpr auto west() -> coords { return {0,-1}; };
};

struct interface_drawable {
	interface_drawable(coords position, string sprite)  : _coords(position), _sprite(sprite) {};

	auto get_draw_data() -> draw_data;
	auto get_coords() -> coords;
	void set_coords(coords new_coords);

	coords _coords{0,0};
	string _sprite = "";
};

} // namespace snake_game

auto add_coords(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords;
auto operator +(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords;


