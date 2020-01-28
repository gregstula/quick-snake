CC = clang++
CFLAGS = -x c++ -Wall -stdlib=libc++ -std=c++17
LIBS= -lncurses -pthreads
INC= -I./curses-wrapper/
LDFLAFS=-use-ld=/usr/bin/lld
SRC=drawable.cpp snake.cpp main.cpp game.cpp

all:
	$(CC) $(CFLAGS) $(LDFLAFS) $(INC) $(LIBS) -o snake $(SRC)
clean:
	@rm -f snake
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp
