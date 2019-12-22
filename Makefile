all:
	clang++ -x c++ -Wall -Werror -lncurses main.cpp -o curse
clean:
	rm curse
