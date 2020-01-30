CC=clang++
CFLAGS = -x c++ -O2 -std=c++17
LIBS= -lncurses
SRC=main.cpp snake.cpp game.cpp

all:
	$(CC) $(CFLAGS) $(LIBS) -o qsnake $(SRC)
clean:
	@rm -f snake
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp
