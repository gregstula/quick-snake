#include <ncurses.h>

struct Window {
		Window(int height, int width, int startx, int starty) {
		_win = newwin(height, width, startx, starty);
	}

	~Window() {
		delwin(_win);
	}
private:
	WINDOW* _win;

public:
	Window() = delete;
	Window(const Window& other) = default;
    Window& operator=(const Window& other) = default;
    Window(Window&& other) = default;
    Window& operator=(Window&& other) = default;
};
