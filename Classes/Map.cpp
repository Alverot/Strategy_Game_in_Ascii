//
// Created by Alex on 20/04/2024.
//

#include "../HeadersForClasses/Map.h"
#include "../HeadersForClasses/Exceptions.h"
#include <iostream>
#include <string>

using namespace std;

Map::Map() //generate a random map with no imputs
{
    int k = 0;
    for(int i = 0; i <=9 ; i++)
    {
        for(int j = 0; j <= 9; j++)
        {
            int rndNumb = 1 + (rand() % 4);
            Mapp[i][j] = new Tile(rndNumb, 0, 0, 0, k++);
        }
    }
}

void Map::PrintMap()
{
    for(int i = 0; i <=9 ; i++)
    {
        for(int j = 0; j <= 9; j++)
        {
            //cout<<Mapp[i][j]->afisTMP()<<"|";
            printf("%s|",Mapp[i][j]->ConvetrForSave());
        }
        cout<<endl;
    }
}

Map& Map::operator=(const Map& mpp){
    for(int i = 0; i <=9 ; i++)
    {
        for(int j = 0; j <= 9; j++)
        {
            Mapp[i][j]=mpp.Mapp[i][j];
        }
    }
    return *this;
}

string Map::ConvertMapForSave(){
    string s;
    char* tmp = new char [100];
    for(int i = 0; i <=9 ; i++)
    {
        for(int j = 0; j <= 9; j++)
        {
            sprintf(tmp,"%s|",Mapp[i][j]->ConvetrForSave());
            s = s +(string)tmp;
        }
        sprintf(tmp,"\n");
        s = s +(string)tmp;
    }
    return s;
}

//gets a number like 909 that represents Mapp[9][9]
Tile& Map::operator[](int TileNumberSelected){
    if(TileNumberSelected < 0 || TileNumberSelected > 909)
    {
        throw Exceptions("Map.cpp_[]","not a valid value between 0 and 909");
    }
    int x,y;
    y = TileNumberSelected%100;
    x = TileNumberSelected/100;
    return *Mapp[x][y];
}

