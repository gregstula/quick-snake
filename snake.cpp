#include "snake.hpp"
#include <iostream>

namespace snake_game {

// simply grow from tail pointer if possible
auto snake::grow(coords direction) -> void
{
    coords new_coords = std::end(snake_body)->position + direction::invert_direction(direction);
    snake_body.emplace_back(new_coords);
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

auto snake::move(coords direction) -> void
{
    // pop the tail, key to snake-like movement
    snake_body.pop_back();
    // get coords for next head
    auto new_coords = next_position(direction);
    // create new head at first position
    snake_body.emplace(std::begin(snake_body), new_coords);
}

// Teleports the head of the snake to a given position without caring about
// cardinal directions
auto snake::teleport(coords next_point) -> void
{
    // similar to move
    snake_body.pop_back();
    // create new head at new position
    snake_body.emplace(std::begin(snake_body), snake_part(next_point));
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

} /* namespace snake_game */
