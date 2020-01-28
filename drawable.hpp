#pragma once

#include <string>
#include <vector>
#include <utility>

namespace snake_game {

struct coords {
    int y, x;
};

struct draw_data {
    draw_data(coords c, std::string s) : y(c.y), x(c.x), s(s) {};
    int y, x;
    std::string s;
};

struct direction {
    constexpr static coords NORTH = { -1, 0 };
    constexpr static coords SOUTH = { 1, 0 };
    constexpr static coords EAST = { 0, 1 };
    constexpr static coords WEST = { 0, -1 };

    static auto invert_direction(coords dir) -> coords;
};

struct drawable {
    template <class String>
    drawable(coords position, String&& sprite) : _coords(position), _sprite(std::forward<String>(sprite)) {};

    auto get_draw_data() -> draw_data;
    auto get_coords() -> coords;

    coords _coords;
    std::string _sprite;

protected:
    // this is not an abstract base class
    ~drawable() = default;
public:
    // if you define one you define them all
    drawable(const drawable&) = default;
    drawable& operator=(const drawable&) = default;
    drawable(drawable&&) = default;
    drawable& operator=(drawable&&) = default;
};

} // namespace snake_game

// basic coordinate operator overloads
auto add_coords(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords;
auto operator+(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords;
auto operator==(snake_game::coords lhs, snake_game::coords rhs) -> bool;
auto operator!=(snake_game::coords lhs, snake_game::coords rhs) -> bool;
