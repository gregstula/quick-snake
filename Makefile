CC = clang++
CFLAGS = -x c++ -Wall -stdlib=libc++ -std=c++17
LIBS= -lncurses -pthreads
LDFLAFS=-use-ld=/usr/bin/lld
SRC=main.cpp snake.cpp game.cpp

all:
	$(CC) $(CFLAGS) $(LDFLAFS) $(LIBS) -o snake $(SRC)
clean:
	@rm -f snake
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp
