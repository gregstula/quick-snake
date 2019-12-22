#include <string>
#include <ncurses.h>

class Window {
public:
		Window(int height, int width, int startx, int starty) {
		_win = newwin(height, width, startx, starty);
	}

	~Window() {
		delwin(_win);
	}

	void clear_window() {
		wclear(this->_win);
	}

	void clear_from_cursor_to_bottom() {
		wclrtobot(this->_win);
	}

	void clear_from_cursor_to_eol() {
		wclrtoeol(this->_win);
	}

	template <typename S = std::string>
		void print_at_coords(int y, int x, S&& str) {
			mvwprintw(this->_win, y, x, str.c_str());
		}

	template <typename S = std::string>
		void print_at_cursor(S&& str) {
			wprintw(this->_win, str.c_str());
		}


private:
	WINDOW* _win;

// constructors
public:
	Window() = delete;
	Window(const Window& other) {
		this->_win = dupwin(other->_win);
	}

    Window& operator=(const Window& other) {
		this->_win = dupwin(other->_win);
	}

    Window(Window&& other) = default;
    Window& operator=(Window&& other) = default;
};
