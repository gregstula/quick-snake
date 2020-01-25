#include <iostream>

#include "interface_drawable.hpp"
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
// caller responsible for only passing a value declared in struct inerface_drawable::direction
auto snake::body() -> std::vector<snake_part>&
{
    return this->snake_body;
}

} //namespace snake_game
