#pragma once
#include "interface_drawable.hpp"
namespace snake_game {

struct snake_part : interface_drawable {
    snake_part(coords position)
        : interface_drawable(position, "@") {};
};

struct snake {

    snake(coords head, coords tail)
        : snake_body { { head }, { tail } } {};

    auto grow() -> void;
    auto move(coords direction) -> void;
    auto body() -> std::vector<snake_part>&; // accessor interface for snake body

private:
    std::vector<snake_part> snake_body;
};

struct food : interface_drawable {
    food(coords position)
        : interface_drawable(position, "o") {};
};

} // namespace snake_game
