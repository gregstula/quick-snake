#include "game.hpp"
#include "screen.hpp"
#include "window.hpp"
#include <stdexcept>

std::tuple<int,int> get_max_y_x() {
    int y,x;
    getmaxyx(stdscr,y,x);
    return {y,x};
}

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

    uint64_t score = 0;
    try {
        auto screen = curses::screen();
        screen.clear();
        auto&& [y,x] = get_max_y_x();
        int dimx = x/3;
        int dimy = y/1.75;
        auto game = snake_game::game(34,80);
        score = game.game_loop();
        screen.refresh();
    }
    catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
        return -1;
    }

    std::cout << "Score: " << score << std::endl;
    return 0;
}
