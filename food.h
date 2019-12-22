#include <string>

struct snake_part {
	std::string get_snake() {
		return food;
	}
private:
	std::string _food = "o";
};
