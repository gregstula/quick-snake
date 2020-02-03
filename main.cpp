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
        curses::refresh_guard<curses::screen> refresh(screen);
        auto&& [y,x] = get_max_y_x();

        // standard game is 80x40 but we will still
        // try to get ok dimensions on smaller screens with small fonts etc
        int dimx = 80;
        if (x <= 80) {
            dimx = x - (80 - x);
            if (dimx % 2 != 0) dimx--;
        }

        int dimy = dimx/2;
        while (dimy > y - 6) { // account for score menu size
            dimx -= 2;
            dimy = dimx/2;
        }

        auto game = snake_game::game(dimy,dimx);
        score = game.game_loop();
    }
    catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
        return -1;
    }

    std::cout << "Score: " << score << std::endl;
    return 0;
}
