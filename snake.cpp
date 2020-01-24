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

// We will use the tail as the new head
auto snake::move(coords direction) -> void
{
    snake_body.pop_back();
    auto new_coords = snake_body.at(0).get_coords() + direction;
    snake_body.emplace(snake_body.begin(), snake_part { new_coords });
}

auto snake::body() -> std::vector<snake_part>&
{
    return this->snake_body;
}

} //namespace snake_game
