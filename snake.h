#include <string>
#include <memory>
#include <utility>
#include <tuple>

namespace snake_game {

struct snake_part
{
	~snake_part();

	std::tuple<int, int, std::string> get_draw_data();

	private:
		snake_part* grow();
		std::string _part = "@";
		std::tuple<int,int> coords = std::make_tuple(0,0);
		std::tuple<int,int> last_coords = std::make_tuple(0,0);
		snake_part* _next = nullptr;
		friend struct snake;
};


struct snake {
	snake();
	~snake();
	void grow();

	std::tuple<int, int, std::string> get_draw_data();

	private:
		snake_part* _head;
		snake_part* _tail;
};


} // namespace snake_game
