#pragma once
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace snake_game {

struct coords {
    int y, x;
};

struct draw_data {
    draw_data(coords c, std::string s)
        : y(c.y)
        , x(c.x)
        , s(s) {};
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

struct interface_drawable {
    template <class Coords, class String>
    interface_drawable(Coords&& position, String&& sprite)
        : _coords(std::forward<Coords>(position))
        , _sprite(std::forward<String>(sprite)) {};

    auto get_draw_data() -> draw_data;
    auto get_coords() -> coords;
    void set_coords(coords new_coords);

    coords _coords { 0, 0 };
    std::string _sprite = "";
};

} // namespace snake_game

// basic coordinate operator overloads
auto add_coords(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords;
auto operator+(snake_game::coords lhs, snake_game::coords rhs) -> snake_game::coords;
auto operator==(snake_game::coords lhs, snake_game::coords rhs) -> bool;
auto operator!=(snake_game::coords lhs, snake_game::coords rhs) -> bool;
