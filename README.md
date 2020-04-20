# Quick Snake
A fast paced terminal snake-like game written in C++17

![Fast paced to test your skills](https://github.com/gregstula/quick-snake/blob/master/images/qsnake.gif)

# Installing #
This otherwise pure C++ program uses a bit of ncurses for displayig characters. While I was tempted to try using ASCII terminal codes directly for building the TUI, it didn't seem worth the effort so ncurses is required.

I developed the project in Void Linux with clang and tested it on Yakuake and Konsole. For xterm I had to enable unicode support with `XTerm.vt100.locale: true`

On a fresh macOS Catalina I was able to build and test with the default clang you get after being prompted to install developer tools when you type `git` in the default terminal. Otherwise, you can install clang with [homebrew](https://brew.sh/).
While the defautl macOS terminal worked great


Requirments:
  - a UTF-8 Terminal
  - UTF friendly font like Noto Mono or Consolas
  - ncurses
  - clang or gcc

*Note: Your Clang or GCC version needs to support the -std=c++17 flag*

**Intallation** (clang):

    git clone https://github.com/gregstula/quick-snake.git
    cd quick-snake
    make
    ./qsnake

**Intallation** (gcc):

    git clone https://github.com/gregstula/quick-snake.git
    cd quick-snake
    make gcc
    ./qsnake
    
Note: Gentoo users should have the `unicode` USE flag set globally and use `make gentoo` so that ncursesw properly links on your system.

## Design ##
A long time ago, I played a facebook game called Snake '08. It was a realy fast snake game where high scores were difficult to get and you rarely got to the point where your tail length mattered, and once you did you felt like you had reached the "end game". It was fairly addicting and my go to distraction when I used that site. While I haven't played that game in years I wanted to capture the quick and fun distracition it offered

### Goals ###
- Challenging gameplay
- Emphasize skill over novelty
- Emphasize quick play session
- Minimal
  - can easily exist in your $PATH
  - the game should feel as if `ls` ran a quick snake session
- Self Contained
  - the game only writes to stdout, no files are used or created

### Non-Goals ###
  - Arcade style start menu
  - touching ~/.local or ~/.config for useless writes about a snake game
  - color
  - non-UTF capable terminals

## Warning! This game is kind of addicting ##
The fast pace and small initial tail size puts emphasis on control and reaction time. The game quits when you lose, so as to not be a bigger commitment than using `cat`. However, you may find that there is a strong temptation to press Up and Enter in your terminal and try again!

## This is not a typical snake game ##
Snake games follow a similar pattern but most are slow paced. This game is isnpired by snake but it has it's own rules
and vision. The vertical movements are marked by an accordion effect, a natural consququence of terminal dimensions I
decided to embrase. The food can appear "under the snakes belly" and that's ok. You can only lose by crashing into
yourself and the walls.

### Difficulty ###
This game is challenging off the bat. It has one difficulty mode: Hard. If you lose you're back to your shell prompt.
The standard map is 80x40 but if the game detects your screen is too small it will try to shrink
accordingly.

### Vertical movement vs Hortizontal movemnt ###
In every text based sake game I've tried vertical movement is faster than horizontal movement. This is because lines in a terminal are more spaced than columns. This problem is especially difficult because line spacing can be changed in most terminal emulators. I decided to use unicode square characters to make the nature of terminal coordinates explicit and to create a nice accordion effect. Then, I simply normalized the vertical travel speed so that it was proportiantate to the map dimensions. The result is smooth controls that feel very natural.


# License #


    Copyright (C) 2020  Gregory D. Stula

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
