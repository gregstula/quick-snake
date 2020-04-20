cmake_minimum_required(VERSION 3.5)
project(quick-snake LANGUAGES CXX)

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CURSES_NEED_NCURSES, TRUE)
set(CURSES_NEED_WIDE, TRUE)


include(FindPkgConfig)
pkg_check_modules(NCURSESW REQUIRED "ncursesw")
# Some distrib require linking with tinfo
pkg_check_modules(TINFOW QUIET "tinfow")

add_executable(qsnake
    main.cpp
    game.hpp
    game.cpp
    snake.hpp
    snake.cpp
    screen.hpp
    window.hpp
)

target_link_libraries(qsnake ${NCURSESW_LIBRARIES} ${TINFOW_LIBRARIES})

