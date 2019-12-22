all:
	clang++ -x c++ -Wall -Werror -lncurses -stdlib=libc++ -std=c++17  main.cpp snake.cpp -o curse
clean:
	rm curse
