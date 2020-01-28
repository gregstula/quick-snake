#pragma once
#include "drawable.hpp"

namespace snake_game {

struct snake_part : drawable {
    snake_part(coords position) : drawable(position, "@") {};
};

struct food : drawable {
    food(coords position) : drawable(position, "o") {};
};

struct snake {
    snake(coords head, coords tail) : snake_body { { head }, { tail } } {};

    auto body() -> std::vector<snake_part>; // accessor interface for snake body
    auto head() -> coords;

    // increases snake body by one part
    auto grow() -> void;

    // moves snake head to current pos + direction
    auto move(coords direction) -> void;

    // calcutates the next position
    auto next_position(coords direction) -> coords;

    // Teleports the head of the snake to a given position without caring about
    // cardinal directions
    auto teleport(coords next_point) -> void;

private:
    std::vector<snake_part> snake_body;
};
} // namespace snake_game


