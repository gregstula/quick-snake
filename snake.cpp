#include <iostream>
#include "snake.hpp"

namespace snake_game {

// simply grow from tail pointer if possible
auto snake::grow() -> void
{
    coords new_coords = snake_body.back().get_coords();
    new_coords = new_coords + coords { .y = 0, .x = 1 };
    snake_body.emplace_back(snake_part { new_coords });
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
    return snake_body.at(0).get_coords();
}

// calcutates the next position
auto snake::next_position(coords direction) -> coords
{
    // get coords for next head
    auto new_coords = snake_body.at(0).get_coords() + direction;
    return new_coords;
}

auto snake::move(coords direction) -> void
{
    // pop the tail, key to snake-like movement
    snake_body.pop_back();
    // get coords for next head
    auto new_coords = snake_body.at(0).get_coords() + direction;
    // create new head at first position
    snake_body.emplace(std::begin(snake_body), snake_part(new_coords));
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

} /* namespace snake_game */



