#include <string>
#include <ncurses.h>

#include "screen.hpp"

constexpr int SCREEN_WIDTH = 80;
constexpr int SCREEN_HEIGHT = 24;

int main() {
	Screen screen = Screen();

	int x = SCREEN_WIDTH/2;
	int y = SCREEN_HEIGHT/2;

	std::string character = {'@'};

	while(screen.is_active()) {
		int input = screen.get_key();

		if (input == KEY_END) screen.quit();

		switch (input) {
			case KEY_LEFT:
				x--;
				break;
			case KEY_RIGHT:
				x++;
				break;
			case KEY_UP:
				y--;
				break;
			case KEY_DOWN:
				y++;
				break;
		}

		mvprintw(y, x, character.c_str());
	}
}
