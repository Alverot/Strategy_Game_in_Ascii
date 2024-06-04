#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "Headers/GameManagingFunction.h"
#include "HeadersForClasses/Player.h"
#include "HeadersForClasses/Map.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//for changing colors

//CONSTANTS

const string SaveFile1 = "../SaveFiles/Save1.txt";
const string SaveFile2 = "../SaveFiles/Save2.txt";
const string SaveFile3 = "../SaveFiles/Save3.txt";
const string FileForInterface = "../SaveFiles/Interface.txt";


fstream file;

//VARIABLES

string SelectedSaveFile = SaveFile1;
int NumberOfPlayers = 2;
int PlayerControl[10];
int Turn = 1;
int GamePreparations = 0; // at this moment 2 if all are done


Player *player[8];
Map map;

//COLORS

const int CyanForConsoleBackground = BACKGROUND_BLUE | BACKGROUND_GREEN;


//FUNCTIONS
void testtt(){
    printf("Merge bine ............cered");
}

void Menu(){
    //TEMP
    for(int i =0 ; i<8; i++)
        player[i] = new Player();
    //TEMP

    int ok =1;
    int optcurenta = 1;

    do {

        system("cls");
        printf("\t\tMENU\n");
        switch (optcurenta)//afisare meniu
        {
            case 1:
            {
                SetConsoleTextAttribute(console, CyanForConsoleBackground);
                printf("\t\tNEW GAME\n");
                SetConsoleTextAttribute(console, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                printf("\t\tLOAD GAME\n");
                printf("\t\tINFO\n");
                printf("\t\tEXIT\n");
                break;
            }
            case 2:
            {
                printf("\t\tNEW GAME\n");
                SetConsoleTextAttribute(console, CyanForConsoleBackground);
                printf("\t\tLOAD GAME\n");
                SetConsoleTextAttribute(console, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                printf("\t\tINFO\n");
                printf("\t\tEXIT\n");
                break;
            }
            case 3:
            {
                printf("\t\tNEW GAME\n");
                printf("\t\tLOAD GAME\n");
                SetConsoleTextAttribute(console, CyanForConsoleBackground);
                printf("\t\tINFO\n");
                SetConsoleTextAttribute(console, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                printf("\t\tEXIT\n");
                break;
            }
            case 4:
            {
                printf("\t\tNEW GAME\n");
                printf("\t\tLOAD GAME\n");
                printf("\t\tINFO\n");
                SetConsoleTextAttribute(console, CyanForConsoleBackground);
                printf("\t\tEXIT\n");
                SetConsoleTextAttribute(console, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
            }
        }
        printf("(move in the menu from arows and select with enter)");

        // citirea sagetilor

        int opt= getch();
        if (opt == 0xE0) {
            opt = getch();

            switch (opt) {
                case 72: {
                    if(optcurenta > 1){
                        optcurenta = optcurenta - 1;
                    }
                    break;
                }
                case 80:{
                    if(optcurenta <4){
                        optcurenta++;
                    }

                    break;
                }
                default: break;
            }
        }else if (opt == 13) {
                switch (optcurenta) {
                    case 1: {
                        NewGame();
                        if(GamePreparations == 2)
                        {
                            InitializeGame();
                        }
                        getchar();
                        break;
                    }
                    case 2: {
                        cout << "\nload game";
                        getchar();
                        break;
                    }
                    case 3: {

                        cout<<info();
                        getchar();
                        break;
                    }
                    case 4: {
                        ok = 0;
                        break;
                    }
                    default: {
                        printf("\nNot an option!!");
                        getchar();
                        break;
                    }

                }

        }


    } while (ok != 0);
}

//info function
//displays the rules, commands and more on how to play the game
string info(){
    system("cls");
    string mesInfo = "Program realizat de Melinte Alexandru \n"
                     "//aici o sa vina instructiunile despre cum se joaca jocul\n"
                     "//+reguli si comenzi";
    return mesInfo;
}


//new game function
//starts the sequence fo creating a new game moving the player throw that process
//and letting him chose the settings of that game.
//Steps on the way :
//1. chose one of the save slots (1,2,3) and warn him if the save slot already has a game saved
//




void NewGame(){
    int ok = 1;
    int OptCurent = 1;
    int cancel = 0; // if the user decides to go back to the menu
    //for getting the savefile
    do{
        system("cls");
        printf("\tNewGame\n");

        printf("Select a save file:");
        if(OptCurent == 1)
        {
            ColorTextBackgroung("\nSavaFile1",CyanForConsoleBackground);
            if(CheckIfFileIsEmpty(SaveFile1))
                cout<<" : File is empty";
            else{cout<<" : File is NOT empty";}
        }else{
            cout<<"\nSavaFile1";
        }
        if(OptCurent == 2)
        {
            ColorTextBackgroung("\nSavaFile2",CyanForConsoleBackground);
            if(CheckIfFileIsEmpty(SaveFile2))
                cout<<" : File is empty";
            else{cout<<" : File is NOT empty";}
        }else{
            cout<<"\nSavaFile2";
        }
        if(OptCurent == 3)
        {
            ColorTextBackgroung("\nSavaFile3",CyanForConsoleBackground);
            if(CheckIfFileIsEmpty(SaveFile3))
                cout<<" : File is empty";
            else{cout<<" : File is NOT empty";}
        }else{
            cout<<"\nSavaFile3";
        }
        int opt= getch();
        if (opt == 0xE0) {
            opt = getch();

            switch (opt) {
                case 72: {
                    if(OptCurent > 1){
                        OptCurent = OptCurent - 1;
                    }
                    break;
                }
                case 80:{
                    if(OptCurent <3){
                        OptCurent++;
                    }

                    break;
                }
                default: break;
            }
        }else if (opt == 13){
            ok = 0;
            GamePreparations++;
            if(OptCurent == 1)
                 SelectedSaveFile = SaveFile1;
            else if(OptCurent == 2){
                SelectedSaveFile = SaveFile2;
            }else if(OptCurent == 3){
                SelectedSaveFile = SaveFile3;
            }
        }
    } while (ok != 0);

    //get the number of players
    ok =1;
    OptCurent = 2;
    do{
        if(cancel == 1)
            break;
        system("cls");
        printf("\tNewGame\n");
        printf("Select the number of players:");
        if(OptCurent == 2)
        {ColorTextBackgroung("\n2",CyanForConsoleBackground);
        }else{cout<<"\n2";}
        if(OptCurent == 3)
        {ColorTextBackgroung("\n3",CyanForConsoleBackground);
        }else{cout<<"\n3";}
        if(OptCurent == 4)
        {ColorTextBackgroung("\n4",CyanForConsoleBackground);
        }else{cout<<"\n4";}
        if(OptCurent == 5)
        {ColorTextBackgroung("\n5",CyanForConsoleBackground);
        }else{cout<<"\n5";}
        if(OptCurent == 6)
        {ColorTextBackgroung("\n6",CyanForConsoleBackground);
        }else{cout<<"\n6";}
        if(OptCurent == 7)
        {ColorTextBackgroung("\n7",CyanForConsoleBackground);
        }else{cout<<"\n7";}
        if(OptCurent == 8)
        {ColorTextBackgroung("\n8",CyanForConsoleBackground);
        }else{cout<<"\n8";}

        int opt= getch();
        if (opt == 0xE0) {
            opt = getch();

            switch (opt) {
                case 72: {
                    if(OptCurent > 2){
                        OptCurent = OptCurent - 1;
                    }
                    break;
                }
                case 80:{
                    if(OptCurent <8){
                        OptCurent++;
                    }

                    break;
                }
                default: break;
            }
        }else if (opt == 13){
            ok = 0;
            GamePreparations++;
            NumberOfPlayers = OptCurent;
        }
    }while(ok != 0);

    OptCurent = 0;
    int CurentPlayer = 1;
    do{
        if(cancel == 1)
            break;
        system("cls");
        printf("\tNewGame\n");
        printf("Select the how will control the player %d:",CurentPlayer);
        if(OptCurent == 0)
        {ColorTextBackgroung("\nAi",CyanForConsoleBackground);
        }else{cout<<"\nAi";}
        if(OptCurent == 1)
        {ColorTextBackgroung("\nHuman",CyanForConsoleBackground);
        }else{cout<<"\nHuman";}
        int opt= getch();
        if (opt == 0xE0) {
            opt = getch();

            switch (opt) {
                case 72: {
                    if(OptCurent > 0){
                        OptCurent = OptCurent - 1;
                    }
                    break;
                }
                case 80:{
                    if(OptCurent <1){
                        OptCurent++;
                    }
                    break;
                }
                default: break;
            }
        }else if (opt == 13){
            PlayerControl[CurentPlayer] = OptCurent;
            CurentPlayer++;
        }
    }while(CurentPlayer <= NumberOfPlayers);
}


void SaveGame(){

    file.open(SelectedSaveFile,ios::out | ios::trunc);//deletes the existing file before writing something new

    if (file.is_open()) {
        file<<Turn<<endl;
        for(int i = 0; i<NumberOfPlayers;i++)
            file << player[i]->ConvertPlayerForSave()<<endl;
        file << map.ConvertMapForSave();
    } else {
        cerr << "Error: Could not create or open file for writing." << endl;
    }
    file.close();
}

void CheckIfFileIsEmpty(){

}

void ColorTextBackgroung(const string& mes,int color)
{
    SetConsoleTextAttribute(console, color);
    cout<<mes;
    SetConsoleTextAttribute(console, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}

//checks if a file is empty by looking at one position ahead and comparing it with eof(end of file)
bool CheckIfFileIsEmpty(const string& save){
    ifstream fil(save);
    return fil.peek() == ifstream::traits_type::eof();

}

void InitializeGame(){

    for(int i = 1 ; i <= NumberOfPlayers;i++){
        player[i-1]->setHumanOrAi( PlayerControl[i]);
    }
}