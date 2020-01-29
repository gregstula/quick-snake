#pragma once
#include <string>
#include <tuple>
#include <vector>

namespace snake_game {

//ncurses uses y, x
struct coords {
    int y, x;
};

namespace direction {
    constexpr coords NORTH = { -1, 0 };
    constexpr coords SOUTH = { 1, 0 };
    constexpr coords EAST = { 0, 1 };
    constexpr coords WEST = { 0, -1 };

    auto invert_direction(coords dir) -> coords;
}

template <class Drawable>
auto get_draw_data(Drawable d) -> std::tuple<int, int, std::string>
{
    return { d.position.y, d.position.x, d.sprite };
}

struct snake_part {
    snake_part(coords c) : position(c) {};
    coords position;
    std::string sprite = "■";
};

struct food_part {
    food_part(coords c) : position(c) {};
    coords position;
    std::string sprite = "♥";
};

struct snake {
    snake(coords head, coords tail) : snake_body { { head }, { tail } } {};

    auto body() -> std::vector<snake_part>; // accessor interface for snake body
    auto head() -> coords;

    // increases snake body by one part
    // growth is opposite of current direction
    auto grow(coords direction) -> void;

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
}

// basic coordinate operator overloads
auto add_coords(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords;
auto operator+(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords;
auto operator==(snake_game::coords lhs, snake_game::coords rhs) -> bool;
auto operator!=(snake_game::coords lhs, snake_game::coords rhs) -> bool; // namespace snake_game
