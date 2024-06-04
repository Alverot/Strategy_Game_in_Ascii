//
// Created by Alex on 18/04/2024.
//

#include "../HeadersForClasses/Tile.h"
#include "../HeadersForClasses/Exceptions.h"
#include <iostream>

using namespace std;

//SEPARATOR IN FILES , for the variables of a tile and | for tiles

//default constructor
Tile::Tile() {
    TerrainType = plain;
    PlayerControl = 0;
    SettlementType = 0;
    SettlementLevel = 0;
    TileNumber = 0;
    ArmyNumber = 0;
    ArmyOwner = 0;
}
//constructor
Tile::Tile(int TerrainType, int PlayerControl, int SettlementType, int SettlementLevel, int TileNumber) {

    if (TerrainType > 4 or TerrainType < 0)
        throw Exceptions("Tile.cpp_CONS","not a value the enum");
    this->TerrainType = (Terrain)TerrainType;
    if (PlayerControl > 8 or PlayerControl < 0)
        throw Exceptions("Tile.cpp_CONS","the player can be only from 0 to 8");
    this->PlayerControl = PlayerControl;

    this->SettlementType = SettlementType;
    this->SettlementLevel = SettlementLevel;

    this->TileNumber = TileNumber;
    ArmyNumber = 0;    // when creating a new map there is no need to be an army spawned so the army will be set with set and get
    ArmyOwner = 0;
}

char* Tile::afisTMP(){
    char* s = new char [50];
    sprintf(s,"%d %d %d %d %d",TileNumber,TerrainType,PlayerControl,SettlementType,SettlementLevel);
    return s;
}

char* Tile::ConvetrForSave() {
    char* s = new char [50];
    sprintf(s,"%d,%d,%d,%d,%d,%d,%d",TileNumber,TerrainType,PlayerControl,SettlementType,SettlementLevel,ArmyNumber,ArmyOwner);
    return s;
}

Tile& Tile::operator =(const Tile &til){
    TerrainType = til.TerrainType;
    SettlementLevel = til.SettlementLevel;
    PlayerControl = til.PlayerControl;
    SettlementType = til.SettlementType;
    TileNumber = til.TileNumber;
    ArmyOwner = til.ArmyOwner;
    ArmyNumber = til.ArmyNumber;
    return *this;
}

//getters implementation

Terrain Tile::getTerrainType() const {
    return TerrainType;
}

int Tile::getPlayerControl() const {
    return PlayerControl;
}

int Tile::getSettlementType() const {
    return SettlementType;
}

int Tile::getSettlementLevel() const {
    return SettlementLevel;
}

int Tile::getTileNumber() const {
    return TileNumber;
}

int Tile::getArmyOwner() const {
    return ArmyOwner;
}

int Tile::getArmyNumber() const {
    return ArmyNumber;
}



//setters implementation
void Tile::setTerrainType(int terrainType) {
    TerrainType = (Terrain)terrainType;
}

void Tile::setPlayerControl(int playerControl) {
    PlayerControl = playerControl;
}

void Tile::setSettlementType(int settlementType) {
    SettlementType = settlementType;
}

void Tile::setSettlementLevel(int settlementLevel) {
    SettlementLevel = settlementLevel;
}

void Tile::setTileNumber(int tileNumber) {
    TileNumber = tileNumber;
}


void Tile::setArmyNumber(int armyNumber) {
    ArmyNumber = armyNumber;
}

void Tile::setArmyOwner(int armyOwner) {
    ArmyOwner = armyOwner;
}
