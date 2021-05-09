cmake_minimum_required(VERSION 3.6)
project(tetris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

enable_testing()
find_package(GTest REQUIRED)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_library(tetromino tetromino.cpp board.cpp rotate.cpp)
add_library(ncurses_setup ncurses_setup.cpp)
target_link_libraries(ncurses_setup ${CURSES_LIBRARIES})

add_executable(tetris main.cpp)
target_link_libraries(tetris tetromino ncurses_setup)

add_executable(test_main tetromino_test.cpp board_test.cpp)
target_link_libraries(test_main GTest::Main tetromino)
add_test(test_main test_main)
