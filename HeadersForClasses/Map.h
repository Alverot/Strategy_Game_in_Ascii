//
// Created by Alex on 20/04/2024.
//

#ifndef STRATEGY_GAME_IN_ASCII_MAP_H
#define STRATEGY_GAME_IN_ASCII_MAP_H

#include <string>
#include "Tile.h"

using namespace std;

class Map: public Tile
        {
        protected:
            Tile *Mapp[10][10];
        public:

            Map();//note to me make another Map constructor that takes in the map number of players and position them
            void PrintMap();
            string ConvertForSave();


};


#endif //STRATEGY_GAME_IN_ASCII_MAP_H
