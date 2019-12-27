#include <tuple>
#include <vector>
#include <utility>
#include <string>

struct snake_part {
	using coords = std::tuple<int,int>;
	using draw_data = std::tuple<int,int,std::string>;

	coords _coords;
	draw_data _draw_data;

	auto get_draw_data() const  -> draw_data;
	auto set_coords(coords c) -> void;
};


struct snake {
	std::vector<snake_part> parts;
};
