cmake_minimum_required(VERSION 3.27)
project(Strategy_Game_in_Ascii)

set(CMAKE_CXX_STANDARD 17)

add_executable(Strategy_Game_in_Ascii main.cpp
        GameManagingFunctions.cpp
        Headers/GameManagingFunction.h
        Classes/Tile.cpp
        HeadersForClasses/Tile.h
        Classes/Map.cpp
        HeadersForClasses/Map.h
        Classes/Exceptions.cpp
        HeadersForClasses/Exceptions.h
        Classes/Player.cpp
        HeadersForClasses/Player.h)
