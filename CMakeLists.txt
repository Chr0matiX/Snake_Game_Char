cmake_minimum_required(VERSION 3.25)
project(Snake_Char)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(Snake_Char main.cpp src/Util.cpp src/Util.h src/snake/Snake.cpp src/snake/Snake.h src/snake/SnakeMap.cpp src/snake/SnakeMap.h src/snake/prop/PropBase.cpp src/snake/prop/PropBase.h src/Game.cpp src/Game.h src/snake/prop/SnakeLongerProp.cpp src/snake/prop/SnakeLongerProp.h)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "-static")