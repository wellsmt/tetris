cmake_minimum_required(VERSION 3.6)
project(tetris)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()
find_package(GTest REQUIRED)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

add_executable(main_test main_test.cpp)
target_link_libraries(main_test GTest::Main)

add_executable(tetris main.cpp win.h create_box.h create_box.cpp)
target_link_libraries(tetris ${CURSES_LIBRARIES} )

add_test(main_test main_test)

add_executable(ncurses main_ncurses.cpp)
target_link_libraries(ncurses ${CURSES_LIBRARIES})
