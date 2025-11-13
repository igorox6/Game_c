cmake_minimum_required(VERSION 4.0)
project(game_1 C)

set(CMAKE_C_STANDARD 11)


add_executable(game_1 main.c
        probabilities.c
        probabilities.h
        gamepad.c
        gamepad.h
)
