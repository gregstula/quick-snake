#include "game.hpp"
#include "screen.hpp"
#include "window.hpp"
int main()
{
    auto screen = curses::screen();
    auto game = snake_game::game();
    game.debug_mode = true;
    game.game_loop();
    return 0;
}
