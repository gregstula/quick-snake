#include "snake.h"

// snake_part member function impl
using namespace snake_game;
using namespace std;

//
// snake_part struct
//
snake_part::~snake_part()
{
	delete _next;
}

snake_part* snake_part::grow()
{
	if (_next != nullptr) {
		return _next->grow();
	}
	_next = new snake_part();
	return _next;
}


tuple<int,int,string> snake_part::get_draw_data()
{
	return tuple_cat(coords, make_tuple(_part));
}


//
// snake struct
//
snake::snake() : _head(new snake_part()), _tail(nullptr) {}
snake::~snake()
{
	delete _head;
}


// simply grow from tail pointer if possible
void snake::grow()
{
	if (_tail != nullptr) _tail->grow();
	else _tail = _head->grow();
}

tuple<int,int,string> snake::get_draw_data()
{
	return _head->get_draw_data();
}

