#include <string>
#include <utility>
#include <ncurses.h>

#include "screen.hpp"

int main() {
	Screen screen = Screen();
		screen.clear_screen();

		const std::string test{"Hello World"};
		screen.print_at_coords(80/2, 24/2, test);

		getch();
		screen.refresh_screen();
		return 0;
}
