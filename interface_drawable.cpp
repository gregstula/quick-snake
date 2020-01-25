#include "interface_drawable.hpp"
namespace snake_game {

// Return data needed for drawing
// Coordinates and ascii representation
auto interface_drawable::get_draw_data() -> draw_data
{
    return { _coords, _sprite };
}

auto interface_drawable::get_coords() -> coords
{
    return _coords;
}

// private setter for coordinates, mainly used for turning tail into head
auto interface_drawable::set_coords(coords new_coords) -> void
{
    _coords = new_coords;
}

auto direction::invert_direction(coords dir) -> coords
{
    if (dir == NORTH) {
        return SOUTH;
    }
    if (dir == SOUTH) {
        return NORTH;
    }
    if (dir == WEST) {
        return EAST;
    }
    if (dir == EAST) {
        return WEST;
    }
    throw std::invalid_argument("coordinates not defined in interface_drawable cannot be inverted");
}

}; /* namespace snake_game */

using snake_game::coords;
auto add_coords(coords lhs, coords rhs) -> coords
{
    auto [lhs_y, lhs_x] = lhs;
    auto [rhs_y, rhs_x] = rhs;
    return { .y = lhs_y + rhs_y, .x = lhs_x + rhs_x };
}

auto operator+(coords lhs, coords rhs) -> coords
{
    return add_coords(lhs, rhs);
}

auto operator==(coords lhs, coords rhs) -> bool
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

auto operator!=(coords lhs, coords rhs) -> bool
{
    return (lhs.x != rhs.x || lhs.y != rhs.y);
}
