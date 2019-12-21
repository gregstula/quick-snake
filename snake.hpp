#include <string>

struct snake {
	void grow() {
		_snake.append("@");
	}

	std::string get_snake() {
		return _snake;
	}
private:
	std::string _snake = "@";
};
