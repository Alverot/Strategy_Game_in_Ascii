//
// Created by Alex on 20/04/2024.
//

#include "../HeadersForClasses/Map.h"
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

