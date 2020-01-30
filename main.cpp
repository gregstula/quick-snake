#include "game.hpp"
#include "screen.hpp"
#include "window.hpp"
#include <stdexcept>

int main(int argc, char** argv)
{
    if (argc == 2) {
        auto opt = std::string(argv[1]);
        if (opt == "--version" || opt == "-v") {
            std::cout << "quick snake version 1.0\n";
            std::cout << "https://www.github.com/gregstula/quick-snake" << std::endl;
            return 0;
        }
    }

    try {
        auto screen = curses::screen();
        curses::refresh_guard<curses::screen> refresh(screen);

        auto game = snake_game::game();
        game.debug_mode = true;
        game.game_loop();
        return 0;
    }
    catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
        return -1;
    }
}
