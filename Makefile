CC = clang++
CFLAGS = -x c++ -Wall -stdlib=libc++ -std=c++17
LIBS= -lncurses -pthreads
INC= -I./curses-wrapper/ -I
LDFLAFS=-use-ld
all:
	$(CC) $(CFLAGS) $(LDFLAFS) $(INC) $(LIBS) -o snake interface_drawable.cpp snake.cpp main.cpp game.cpp
clean:
	@rm -f snake
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp
