#include <string>
#include <memory>
#include <utility>

struct  snake_part {
	snake_part(std::string str = {"@"}) :_part(std::move(str)), next(nullptr) {}
	std::string _part;
	snake_part* next;

	~snake_part() {
		snake_part* curr = nullptr;
		while(curr) {

		}
	}
};

class snake {
public:
	snake() : _head(std::make_unique<snake_part>()) {}
	~snake() {}
private:
	std::unique_ptr<snake_part> _head;
};
