#include "interface_drawable.h"
namespace snake_game {
// Return data needed for drawing
// Coordinates and ascii representation
auto interface_drawable::get_draw_data() -> draw_data
{
	return {_coords, _sprite};
}

auto interface_drawable::get_coords() -> coords {
	return _coords;
}

// private setter for coordinates, mainly used for turning tail into head
void interface_drawable::set_coords(coords new_coords)
{
	_coords = new_coords;
}

}; // namespace snake_game

auto add_coords(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords {
	auto[lhs_y, lhs_x] = lhs;
	auto[rhs_y, rhs_x] = rhs;
	return {.y = lhs_y + rhs_y, .x = lhs_x + rhs_x};
}

auto operator +(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords {
	return add_coords(lhs, rhs);
}


