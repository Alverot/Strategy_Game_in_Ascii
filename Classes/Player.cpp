//
// Created by Alex on 14/05/2024.
//

#include "../HeadersForClasses/Player.h"
#include "../HeadersForClasses/Exceptions.h"

int Player::NRCollor = 1;

Player::Player(){
    Food = 200;
    Wood = 200;
    Stone = 200;
    Gold = 200;
    HumanOrAi = false;
    PlayerColor = (Color)NRCollor++;
}

Player::Player(int food,int stone,int gold,int wood,int val){
    Food = food;
    Wood = wood;
    Stone = stone;
    Gold = gold;
    if(val != 1 and val !=0)
    {
        throw Exceptions("Player.cpp_Constructor","not a value for player type");
    }
    HumanOrAi = val;
    if(NRCollor > 8 )
    {
        throw Exceptions("Player.cpp_Constructor","not a value the Color enum");
    }
    PlayerColor = (Color)NRCollor++;
}

Player::Player(int food,int stone,int gold,int wood,int val,int col){
    Food = food;
    Wood = wood;
    Stone = stone;
    Gold = gold;
    if(val != 1 and val !=0)
    {
        throw Exceptions("Player.cpp_Constructor","not a value for player type");
    }
    HumanOrAi = val;
    if(NRCollor > 8 )
    {
        throw Exceptions("Player.cpp_Constructor","not a value the Color enum");
    }
    PlayerColor = (Color)col;
}

string Player::ConvertPlayerForSave(){
    string s;
    char* tmp = new char [200];
    sprintf(tmp,"%d,%d,%d,%d,%d,%d",Food,Wood,Stone,Gold,HumanOrAi,PlayerColor);
    s = s +(string)tmp;
    return s;
}


Player& Player::operator +=(float nr){
    nr= nr+ 0.01f;       //after some tests i noticed that if i have 10.4 i actually have 10.39999 and its messing with may operations
    int resource = (int)((nr -(long)nr)*10);   //takes the last number after . does *10     ex 19.4 => 4

    if(resource <1 or resource > 4)
    {
        throw Exceptions("Player.cpp_+=","not a good value for resources");
    }
    if(resource == 1){
            Food = Food + (int)nr;
    }
    if(resource == 2){
        Wood = Wood + (int)nr;
    }
    if(resource == 3){
        Stone = Stone + (int)nr;
    }
    if(resource == 4){
        Gold = Gold + (int)nr;
    }
    return *this;
}

Player& Player::operator -=(float nr){
    nr= nr+ 0.01f;       //after some tests i noticed that if i have 10.4 i actually have 10.39999 and its messing with may operations
    int resource = (int)((nr -(long)nr)*10);   //takes the last number after . does *10     ex 19.4 => 4

    if(resource <1 && resource > 4)
    {
        throw Exceptions("Player.cpp_+=","not a good value for resources");
    }
    if(resource == 1){
        Food = Food - (int)nr;
    }
    if(resource == 2){
        Wood = Wood - (int)nr;
    }
    if(resource == 3){
        Stone = Stone - (int)nr;
    }
    if(resource == 4){
        Gold = Gold - (int)nr;
    }
    return *this;
}

Player& Player::operator =(const Player &play){
    Food = play.Food;
    Wood = play.Wood;
    Stone = play.Stone;
    Gold = play.Gold;
    HumanOrAi = play.HumanOrAi;
    PlayerColor = play.PlayerColor;
    return *this;
}


int Player::getFood() const {
    return Food;
}

void Player::setFood(int food) {
    Food = food;
}

int Player::getStone() const {
    return Stone;
}

void Player::setStone(int stone) {
    Stone = stone;
}

int Player::getGold() const {
    return Gold;
}

void Player::setGold(int gold) {
    Gold = gold;
}

int Player::getWood() const {
    return Wood;
}

void Player::setWood(int wood) {
    Wood = wood;
}

void Player::setHumanOrAi(int humanOrAi) {
    HumanOrAi = humanOrAi;
}

Player::~Player() {

}
