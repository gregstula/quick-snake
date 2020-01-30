# Quick Snake
A fast paced terminal snake-like game written in C++17

![Fast paced to test your skills](https://github.com/gregstula/quick-snake/blob/master/images/qsnake.gif)


## Design Goals ##
- Challenging
- Emphasize skill over novelty
- Emphasise quick play session
- Minimal
  - can easily exist in your $PATH
  - the game should feel as if `ls` ran a quick snake session
- Self Contained
  - the game only writes to stdout, no files are used or created

A long time ago, I played a facebook game called Snake '08. It was a realy fast snake game where high scores were difficult to get and you rarely got to the point where your tail length matter, and once you did you felt like you had reached the end game portion. It was fairly addicting and my go to distraction when I used that site. While I haven't played that game in years I wanted to capture the quick and fun distracition it offered

## Warning! This game is kind of addicting ##
The fast pace and small initial tail size puts emphasis on control and reaction time. The game quits when you lose, so as to not be a bigger commitment than using `cat` However, you may find that there is a strong temptation to press Up and Enter in your terminal and try again!

## This is not your typical snake game ##
Other snake games tend to emphasize over tail growth and long play sessions. To be frank, most ncurses snake games out there are pretty boring. BSD Worm, for example, is less of a game and more of novelty. Why are the controls inconsistent? What is the challenge? Slow snake games try to get you to play for a long time but it takes a long time to get to the point where any skill is required.

This game is challenging off the bat. It has one difficulty mode: Hard. If you lose you're back to your shell prompt.

# Installing #
This otherwise pure C++ program uses a bit of ncurses for displayig characters. While I was tempted to use ASCII terminal codes directly for extra portability, it didn't seem worth the effort so ncurses is required. 

On macOS I beleive you can install ncurses and llvm(clang) with [homebrew](/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)) on Linux you just need a C++ compiler.

Requirments:
  - a UTF-8 Terminal
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
