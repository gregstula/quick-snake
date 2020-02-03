#include "snake.hpp"
#include <iostream>

namespace snake_game {

// simply grow from tail pointer if possible
void snake::grow(coords direction)
{
    // there was a bug where move and grow caused
    // weird 0,0 lose tail for a frame so we pop tail now
    auto new_tail = (std::end(snake_body) - 1)->position + direction;
    snake_body.emplace_back(new_tail);
}

// moves the snake by 1x or 1y depending on direction passed
// caller responsible for only passing a value declared in struct
// inerface_drawable::direction
auto snake::body() -> std::vector<snake_part>
{
    return snake_body;
}

auto snake::head() -> coords
{
    return std::begin(snake_body)->position;
}

// calcutates the next position
auto snake::next_position(coords direction) -> coords
{
    // get coords for next head
    auto new_coords = std::begin(snake_body)->position + direction;
    return new_coords;
}

void snake::move(coords direction)
{
    // pop the tail, key to snake-like movement
    snake_body.pop_back();
    // get coords for next head
    auto new_coords = std::begin(snake_body)->position + direction;
    // create new head at first position
    snake_body.emplace(std::begin(snake_body), new_coords);
}

// Teleports the head of the snake to a given position without caring about
// cardinal directions
void snake::teleport(coords next_point)
{
    // similar to move
    snake_body.pop_back();
    // create new head at new position
    snake_body.emplace(std::begin(snake_body), next_point);
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
    throw std::invalid_argument("coordinates not defined in snake_game::direction cannot be inverted");
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
} /* namespace snake_game */
