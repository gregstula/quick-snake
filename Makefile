CXX=clang++
CXXFLAGS=-Wall -std=c++17
LIBS=-lncurses
GENTOO=-L/usr/lib64 -lncursesw -ltinfow -ldl
SRC=main.cpp snake.cpp game.cpp

all:
	$(CXX) $(CXXFLAGS) $(LIBS) -o qsnake $(SRC)
gcc:
	g++ $(CXXFLAGS) -DMESSAGE='"Compiled with GCC"' $(LIBS) -o qsnake $(SRC)

gentoo:
	g++ $(CXXFLAGS) -DMESSAGE='"Compiled for gentoo"' $(GENTOO) -o qsnake $(SRC)

clean:
	@rm -f snake qsnake
	@rm -f *.o
format:
	clang-format --verbose --sort-includes -i *.cpp *.hpp
