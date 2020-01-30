#include "game.hpp"
#include "screen.hpp"
#include "window.hpp"
#include <stdexcept>
int main()
{
    auto screen = curses::screen();
    try {
        auto game = snake_game::game();
        game.debug_mode = true;
        game.game_loop();
        return 0;
    } catch(std::exception& err) {
        {
            curses::refresh_guard<curses::screen> refresh(screen);
            screen.print_at_coords(10,10, err.what());
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return 1;
    }
}
