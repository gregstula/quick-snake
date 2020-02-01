# Quick Snake
A fast paced terminal snake-like game written in C++17

![Fast paced to test your skills](https://github.com/gregstula/quick-snake/blob/master/images/qsnake.gif)

# Installing #
This otherwise pure C++ program uses a bit of ncurses for displayig characters. While I was tempted to try using ASCII terminal codes directly for building the TUI, it didn't seem worth the effort so ncurses is required.

I developed the project in Void Linux with clang and tested it on Yakuake and Konsole. For xterm I had to enable unicode support with `XTerm.vt100.locale: true`

On a fresh macOS Catalina I was able to build and test with the default clang you get after being prompted to install developer tools when you type `git` in the default terminal. Otherwise, you can install clang with [homebrew](https://brew.sh/).
While the defautl macOS terminal worked great, iTerm's out of the box configuration had suboptimal line spacing.


Requirments:
  - a UTF-8 Terminal
  - UTF glyph friendly font like Noto Mono or Consolas
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
  - non-UTF terminal or font configurations

## Warning! This game is kind of addicting ##
The fast pace and small initial tail size puts emphasis on control and reaction time. The game quits when you lose, so as to not be a bigger commitment than using `cat`. However, you may find that there is a strong temptation to press Up and Enter in your terminal and try again!

## This is not your typical snake game ##
Other snake games tend to emphasize over tail growth and long play sessions. To be frank, most ncurses snake games out there are pretty boring. BSD Worm, for example, is less of a game and more of novelty. Why are the controls inconsistent? What is the challenge? Slow snake games try to get you to play for a long time but it takes a long time to get to the point where any skill is required.

### Difficulty ###
This game is challenging off the bat. It has one difficulty mode: Hard. If you lose you're back to your shell prompt.

### Vertical movement vs Hortizontal movemnt ###
In every text based sake game I've tried vertical movement is faster than horizontal movement. This is because lines in a terminal are more spaced than columns. This problem is especially difficult because line spacing can be changed in most terminal emulators. I decided to use unicode square characters to make the nature of terminal coordinates explicit and to create a nice according effect. Then, I simply normalized the vertical travel speed so that it was proportiantate to the default terminal line spacing. The result is smooth controls on most terminal emulators.


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
