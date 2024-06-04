//
// Created by Alex on 18/04/2024.
//

#ifndef STRATEGY_GAME_IN_ASCII_TILE_H
#define STRATEGY_GAME_IN_ASCII_TILE_H

//all ot the properties for the tile class
//ths objects will be used in the map class that will manage a table of objects

enum Terrain {plain = 1, forest = 2, hills = 3, mountains = 4}; // the terrain types

class Tile {
    protected:

        Terrain TerrainType;
        int PlayerControl;
        int SettlementType;
        int SettlementLevel;
        int TileNumber;       //the number of the tile on the map(for formatting purposes)
        int ArmyNumber;      //all the armies will be stored in an array and it will check the size of the army at that location
        int ArmyOwner;       //the owner of the army(the player that can use it)

    public:

    //Methods

    char* afisTMP();

    char* ConvetrForSave();


    //CONSTRUCTORS
    Tile();
    Tile(int TerrainType,int PlayerControl,int SettlementType,int SettlementLevel,int TileNumber);

    //METHODS

    Tile& operator =(const Tile &til);

    //GETTERS
    Terrain getTerrainType() const;

    int getPlayerControl() const;

    int getSettlementType() const;

    int getSettlementLevel() const;

    int getTileNumber() const;

    int getArmyNumber() const;

    int getArmyOwner() const;

    //SETTERS
    void setTerrainType(int terrainType);

    void setPlayerControl(int playerControl);

    void setSettlementType(int settlementType);

    void setSettlementLevel(int settlementLevel);

    void setTileNumber(int tileNumber);

    void setArmyNumber(int armyNumber);

    void setArmyOwner(int armyOwner);

};


#endif //STRATEGY_GAME_IN_ASCII_TILE_H
