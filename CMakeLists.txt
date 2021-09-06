cmake_minimum_required(VERSION 3.20)
project(terminal_snake_game C)

set(CMAKE_C_STANDARD 99)

include_directories(
        "./entities/include"
        "./window/include"
        "./memory/include"
        "./tools/include"
)

add_executable(terminal_snake_game main.c entities/snake.c entities/include/snake/snake.h entities/food.c entities/include/food/food.h memory/include/mem.h window/terminal.c window/include/terminal/terminal.h tools/refresh.c tools/include/refresh.h tools/draw_to_screen.c tools/include/draw_to_screen.h window/include/terminal/keystrokes_codes.h tools/equations.c tools/include/equations.h)
