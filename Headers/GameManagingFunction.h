//
// Created by Alex on 15/04/2024.
//
#include <string>

#ifndef STRATEGY_GAME_IN_ASCII_GAMEMANAGINGFUNCTION_H
#define STRATEGY_GAME_IN_ASCII_GAMEMANAGINGFUNCTION_H

using namespace std;

void testtt();

void Menu();//Menu implementation
std::string info();//displays the rules, commands and more on how to play the game
void NewGame();//starts the sequence fo creating a new game moving the player throw that process
                //and letting him chose the settings of that game.

void LoadGame();//starts the sequence fo creating a Loading a game that was saved

void SaveGame();//saves the game at the Selected saveFile

bool CheckIfFileIsEmpty(const string& save);

void ColorTextBackgroung(const string& mes,int color);

void InitializeGameFromNewGame();

void CovertSelectedFileToData();

void PrintWithColor();

void PrepareInterfaceForGame(int SelectedPlayerNumber);//converts the selected save file in a usable interface for a specific player


#endif //STRATEGY_GAME_IN_ASCII_GAMEMANAGINGFUNCTION_H
