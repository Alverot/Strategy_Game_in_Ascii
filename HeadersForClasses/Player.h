//
// Created by Alex on 14/05/2024.
//

#ifndef STRATEGY_GAME_IN_ASCII_PLAYER_H
#define STRATEGY_GAME_IN_ASCII_PLAYER_H

#include <string>

using namespace std;

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
    static int NRCollor;
    int Food;
    int Stone;
    int Gold;
    int Wood;
    int HumanOrAi; //false is Ai true is Human controlled
    Color PlayerColor;    //if color is not specified then the program will distribute them in oder

public:

    Player();
    Player(int food,int stone,int gold,int wood,int val = 0);
    string ConvertPlayerForSave();
    int getFood() const;
    void setFood(int food);
    int getStone() const;
    void setStone(int stone);
    int getGold() const;
    void setGold(int gold);
    int getWood() const;
    void setWood(int wood);

};



#endif //STRATEGY_GAME_IN_ASCII_PLAYER_H
