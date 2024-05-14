//
// Created by Alex on 14/05/2024.
//

#ifndef STRATEGY_GAME_IN_ASCII_PLAYER_H
#define STRATEGY_GAME_IN_ASCII_PLAYER_H


enum Color{     //Colors that the player will be able to assign to themselves
    Blue = 1,
    Read = 2,
    Green = 3,
    Cyan = 4,
    Orange = 5,
    Pink = 6,
    Purple = 7,
    Yellow = 8

};

class Player{
protected:
    int Wood;
    int Food;
    int Stone;
    int Gold;
    int PlayerNumber;
    int Color;

};


#endif //STRATEGY_GAME_IN_ASCII_PLAYER_H
