CXX=clang++
CXXFLAGS=-Wall -std=c++17
LIBS=-lncurses -ltinfo
SRC=main.cpp snake.cpp game.cpp

all:
	$(CXX) $(CXXFLAGS) $(LIBS) -o qsnake $(SRC)
gcc:
	g++ $(CXXFLAGS) -DMESSAGE='"Compiled with GCC"' $(LIBS) -o qsnake $(SRC)

clean:
	@rm -f snake qsnake
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp

