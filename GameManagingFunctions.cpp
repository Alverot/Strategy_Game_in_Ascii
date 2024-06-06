#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include "Headers/GameManagingFunction.h"
#include "HeadersForClasses/Player.h"
#include "HeadersForClasses/Map.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//for changing colors


//SEPARATORS

const char* SecondarySeparator= ",";
const char* MainSeparator= "|";


//CONSTANTS

const string SaveFile1 = "../SaveFiles/Save1.txt";
const string SaveFile2 = "../SaveFiles/Save2.txt";
const string SaveFile3 = "../SaveFiles/Save3.txt";
const string FileForInterface = "../SaveFiles/Interface.txt";


fstream file;
fstream fille;

//VARIABLES

string SelectedSaveFile = SaveFile1;
int NumberOfPlayers = 2;            //default is set to 2
int PlayerControl[10];
int Turn = 1;                       //at the beginning is set to 1
int GamePreparations = 0; // at this moment 2 if all are done


Player *player[8];
Map CurrentGameMap;

//COLORS

const int CyanForConsoleBackground = BACKGROUND_BLUE | BACKGROUND_GREEN;
const int RedForConsoleBackground = BACKGROUND_RED;
const int BlueForConsoleBackground = BACKGROUND_BLUE;
const int GreenForConsoleBackground = BACKGROUND_GREEN;
const int YellowForConsoleBackground = 0x80;
const int OrangeForConsoleBackground = BACKGROUND_RED | 0x80;
const int MagentaForConsoleBackground = BACKGROUND_RED | BACKGROUND_BLUE;
const int PinkForConsoleBackground = FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE;

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
                            InitializeGameFromNewGame();
                        }
                        Map mmap;
                        CurrentGameMap = mmap;
                        SaveGame();
                        PrepareInterfaceForGame(1);
                        getchar();
                        break;
                    }
                    case 2: {
                        bool OKload = true;
                        if(CheckIfFileIsEmpty(SaveFile1) && CheckIfFileIsEmpty(SaveFile2) && CheckIfFileIsEmpty(SaveFile3)){
                            OKload = false;
                        }
                        if(!OKload){
                            ColorTextBackgroung("!!NO SAVE TO LOAD!!",RedForConsoleBackground);
                            getchar();
                        }
                        LoadGame();
                        CovertSelectedFileToData();

                        PrepareInterfaceForGame(1);
                        
                        stringstream buffer;
                        file.open(FileForInterface,ios::in);
                        buffer << file.rdbuf();

                        cout<<endl;
                        cout<< buffer.str();
                        file.close();




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
        file<<Turn<<endl;           //saves the turn number
        file<<NumberOfPlayers<<endl;    //number of players
        for(int i = 0; i<NumberOfPlayers;i++)
            file << player[i]->ConvertPlayerForSave()<<endl;        //the information about the players
        file << CurrentGameMap.ConvertMapForSave();                            //the 10*10 map
    } else {
        cerr << "Error: Could not create or open file for writing." << endl;
    }
    file.close();
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

void InitializeGameFromNewGame(){

    for(int i = 1 ; i <= NumberOfPlayers;i++){
        player[i-1]->setHumanOrAi( PlayerControl[i]);
    }
}


void LoadGame(){
    int ok = 1;
    bool okLoad = false;
    int OptCurent = 1;
    //for getting the savefile
    do{
        system("cls");
        printf("\tNewGame\n");

        printf("Select a save file:");
        if(OptCurent == 1)
        {
            ColorTextBackgroung("\nSavaFile1",CyanForConsoleBackground);
            if(CheckIfFileIsEmpty(SaveFile1))
            {
                cout << " : File is empty!!";
                okLoad = false;
            }
            else
            {
                cout<<" : File is NOT empty";
                okLoad = true;
            }
        }else{
            cout<<"\nSavaFile1";
        }
        if(OptCurent == 2)
        {
            ColorTextBackgroung("\nSavaFile2",CyanForConsoleBackground);
            if(CheckIfFileIsEmpty(SaveFile2))
            {
                cout << " : File is empty!!";
                okLoad = false;
            }
            else
            {
                cout<<" : File is NOT empty";
                okLoad = true;
            }
        }else{
            cout<<"\nSavaFile2";
        }
        if(OptCurent == 3)
        {
            ColorTextBackgroung("\nSavaFile3",CyanForConsoleBackground);
            if(CheckIfFileIsEmpty(SaveFile3))
            {
                cout << " : File is empty!!";
                okLoad = false;
            }
            else
            {
                cout<<" : File is NOT empty";
                okLoad = true;
            }
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
            if(OptCurent == 1 && okLoad)
                SelectedSaveFile = SaveFile1;
            else if(OptCurent == 2 && okLoad){
                SelectedSaveFile = SaveFile2;
            }else if(OptCurent == 3 && okLoad){
                SelectedSaveFile = SaveFile3;
            }
            if(!okLoad)
            {
                ColorTextBackgroung("\nPlease Select a save that is not empty!!!",RedForConsoleBackground);
                ok = 1;
                getchar();
            }
        }
    } while (ok != 0);

}

void CovertSelectedFileToData(){
    file.open(SelectedSaveFile,ios::in);// opening the file

    string line;
    getline(file,line);//reading first line(turn number)
    Turn = stoi(line);      //converting to  int

    getline(file,line);//reading Number of players
    NumberOfPlayers = stoi(line);
    for(int i = 0; i<NumberOfPlayers;i++) // reads and updates all the players statistics
    {
        getline(file,line);
        istringstream iss(line);
        string segment;
        int segmentConvToint[10];
        int j = 0;
        while (getline(iss, segment, ','))
        {
            segmentConvToint[j] = stoi(segment);
            j++;
        }
        player[i] = new Player(segmentConvToint[0],segmentConvToint[1],segmentConvToint[2],segmentConvToint[3],segmentConvToint[4],segmentConvToint[5]);
    }

    for(int i = 0; i < 10 ; i++)     //reads and converts all the tiles
    {
        getline(file,line);
        char* lineCH = new char[line.size() + 1];
        strcpy(lineCH, line.c_str());

        int j = 0;
        char* mainContext; //forstrtok_r
        char* StringTile = strtok_r(lineCH, MainSeparator,&mainContext);   //separates in tiles  ex 0,2,0,0,0,0,0|

        while (StringTile != nullptr) {
            char* secondaryContext;
            char* StringTileVariable = strtok_r(StringTile, SecondarySeparator,&secondaryContext);   //separates in tiles  ex 0,2,0,0,0,0,0|
            int tempvect[10] = {0};
            int tempVectIndex = 0;
            while (StringTileVariable != nullptr) {
                tempvect[tempVectIndex] = stoi(StringTileVariable);
                tempVectIndex++;
                StringTileVariable = strtok_r(nullptr,SecondarySeparator,&secondaryContext);
            }
            int indexNum = i*100+j;
            CurrentGameMap[indexNum].setTileNumber(tempvect[0]);
            CurrentGameMap[indexNum].setTerrainType(tempvect[1]);
            CurrentGameMap[indexNum].setPlayerControl(tempvect[2]);
            CurrentGameMap[indexNum].setSettlementType(tempvect[3]);
            CurrentGameMap[indexNum].setSettlementLevel(tempvect[4]);
            CurrentGameMap[indexNum].setArmyNumber(tempvect[5]);
            CurrentGameMap[indexNum].setArmyOwner(tempvect[6]);
            j++;

            StringTile = strtok_r(nullptr,MainSeparator, &mainContext);
        }
        delete[] lineCH;
    }
    file.close();   //colsing the file
}


//ideea Y tree ^ mountain m hills? _ plain?

void PrepareInterfaceForGame(int SelectedPlayerNumber){

    file.open(FileForInterface,ios::out | ios::trunc);
    file << "Turn : "<<Turn;

    file<<"           Player "<<SelectedPlayerNumber<<" of "<<NumberOfPlayers;
    file<<"    \t\t\tFood: "<<player[SelectedPlayerNumber-1]->getFood()<<"  Wood: "<<player[SelectedPlayerNumber-1]->getWood()<<"  Stone: "<<player[SelectedPlayerNumber-1]->getStone()<<"  Gold: "<<player[SelectedPlayerNumber-1]->getGold();
    file<<endl;
    for(int i = 0; i <100;i++)
        file<<(char)205;

    for(int i = 0 ; i<10 ; i++)
    {
        char* buff1 = new char[100];
        char* buff2 = new char[100];

        sprintf(buff1,"\n");
        sprintf(buff2,"\n");

        for(int j = 0 ; j<10 ; j++)
        {
            int indexNum = i*100+j;
            int CollPlay = CurrentGameMap[indexNum].getPlayerControl();
            int Terr = CurrentGameMap[indexNum].getTerrainType();
            int Army = CurrentGameMap[indexNum].getArmyNumber();
            int SetType = CurrentGameMap[indexNum].getSettlementType();
            int SetLevel = CurrentGameMap[indexNum].getSettlementLevel();
            switch (Terr)
            {
                case 1:
                    sprintf(buff1,"%s_ ",buff1);
                    break;
                case 2:
                    sprintf(buff1,"%sm ",buff1);
                    break;
                case 3:
                    sprintf(buff1,"%sY ",buff1);
                    break;
                case 4:
                    sprintf(buff1,"%s^ ",buff1);
                    break;
            }
            if(Army != 0)
                sprintf(buff1,"%s# ",buff1);
            else
                sprintf(buff1,"%s0 ",buff1);
            sprintf(buff1,"%s%c",buff1,186);

            switch (SetType)
            {
                case 0:
                    sprintf(buff2,"%s0 ",buff2);
                    break;
                case 1:
                    sprintf(buff2,"%sV ",buff2);
                    break;
                case 2:
                    sprintf(buff2,"%sF ",buff2);
                    break;
                case 3:
                    sprintf(buff2,"%sL ",buff2);
                    break;
                case 4:
                    sprintf(buff2,"%sM ",buff2);
                    break;
            }
            if(SetLevel < 10)
            {
                sprintf(buff2,"%s%d ",buff2,SetLevel);
            }else if(SetLevel == 10){
                sprintf(buff2,"%s* ",buff2);
            }
            sprintf(buff2,"%s%c",buff2,186);

        }
        file<<buff1;
        file<<buff2;
        file<<"\n";
        for(int k = 0; k < 10 ; k++){
            file<<(char)205<<(char)205<<(char)205<<(char)205<<(char)206;
        }

    }


    file.close();
}

void PrintWithColor(){

    system("cls");
    stringstream buffer;
    file.open(FileForInterface,ios::in);
    buffer << file.rdbuf();

    cout<<endl;
    cout<< buffer.str();
    file.close();

    cout<<endl;
    for(int i = 0 ; i < 10 ;i++){
        for(int j = 0 ; j < 10 ; j++){
            int indexNum = i*100+j;
            int PlayerColl = CurrentGameMap[indexNum].getPlayerControl();
            if(PlayerColl != 0){

            }
        }
    }
}