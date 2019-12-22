#include <string>
#include <utility>
#include <ncurses.h>

#include "screen.h"
#include "snake.h"

int main()
{
	curses::screen screen{};
	screen.clear_screen();

	snake_game::snake snake{};
	auto[y,x,str] = snake.get_draw_data();
	screen.print_at_coords(y,x,str);
	getch();
	screen.refresh_screen();
	return 0;
}
