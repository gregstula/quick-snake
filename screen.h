#include <ncurses.h>
#include <string>

namespace curses {

	class screen {
	public:
		screen() {
			initscr();
			raw();
			noecho();
			keypad(stdscr, TRUE);
			if(has_colors()) {
				start_color();
			}
		}

		~screen() {
			endwin();
		}

		int get_key() {
			return getch();
		}

		template <typename S = std::string>
		void print_at_coords(int y, int x, S&& str) {
			mvprintw(y, x, str.c_str());
		}

		template <typename S = std::string>
		void print_at_cursor(S&& str) {
			printw(str.c_str());
		}

		void clear_screen() {
			clear();
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
	//	int _screen_height = 24;
	//	int _screen_width = 80;
		bool _active = true;
	};

} // namespace curses
