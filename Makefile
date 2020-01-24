all:
	clang++ -x c++ -Wall -Werror -lncurses -stdlib=libc++ -std=c++17 -o curse interface_drawable.cpp snake.cpp main.cpp
clean:
	rm curse *.o
