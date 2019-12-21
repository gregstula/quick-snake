#include <ncurses.h>

struct Screen {
	Screen() {
		initscr();
		raw();
		noecho();
		keypad(stdscr, TRUE);
		_active = true;
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
	bool _active;

public:

};
