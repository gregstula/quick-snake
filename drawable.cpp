#include "drawable.hpp"
#include <stdexcept>

namespace snake_game {
// Return data needed for drawing
// Coordinates and ascii representation
auto drawable::get_draw_data() -> draw_data
{
    return { position, sprite };
}

} // namespace snake_game

// Coords operator overloads
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
    return !(lhs == rhs);
}
