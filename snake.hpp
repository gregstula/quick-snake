#pragma once
#include "interface_drawable.hpp"
namespace snake_game {

struct snake_part : interface_drawable {
    template <class Coords = coords>
    snake_part(Coords&& position) : interface_drawable(std::forward<Coords>(position), "@") {};
};

struct snake {
    snake(coords head, coords tail) : snake_body { { head }, { tail } } {};

    auto grow() -> void;
    auto body() -> std::vector<snake_part>&; // accessor interface for snake body

    template <class Coords> // universal reference
    auto move(Coords&& direction) -> void // rvalue reference
    {
        // pop the tail, key to snake-like movement
        snake_body.pop_back();
        // get coords for next head
        auto new_coords = snake_body.at(0).get_coords() + direction;
        // create new head at first position
        snake_body.emplace(std::begin(snake_body), snake_part { new_coords });
    }

    // calcutates the next position
    template <class Coords> // forwarding reference
    auto next_position(Coords&& direction) -> coords&& // rvalue reference
    {
        // get coords for next head
        auto new_coords = snake_body.at(0).get_coords() + direction;
        return std::move(new_coords);
    }

    // Teleports the head of the snake to a given position without caring about
    // cardinal directions
    template <class Coords> // forwarding reference
    inline auto teleport(Coords&& next_point) -> void
    {
        // similar to move
        snake_body.pop_back();
        // create new head at new position
        snake_body.emplace(std::begin(snake_body), snake_part(next_point));
    }

private:
    std::vector<snake_part> snake_body;
};

struct food : interface_drawable {
    food(coords position) : interface_drawable(position, "o") {};
};

} // namespace snake_game
