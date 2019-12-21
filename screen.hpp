#include <ncurses.h>
#include <unordered_map>

struct Screen {
	Screen() {
		initscr();
		raw();
		noecho();
		keypad(stdscr, TRUE);
		if(has_colors()) {
			start_color();
		}
	}

	~Screen() {
		endwin();
	}

	int get_key() {
		return getch();
	}

	void refresh_screen() {
		refresh();
	}

	bool is_active() {
		return _active;
	}

	void quit() {
		_active = false;
	}

private:
	bool _active = true;
};

