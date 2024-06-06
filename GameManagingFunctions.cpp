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
int CurrentPlayerTurn;
Map CurrentGameMap;
int SelectedTile =0;

//COLORS

const int CyanForConsoleBackground = BACKGROUND_BLUE | BACKGROUND_GREEN;
const int RedForConsoleBackground = BACKGROUND_RED;
const int BlueForConsoleBackground = BACKGROUND_BLUE;
const int GreenForConsoleBackground = BACKGROUND_GREEN;
const int YellowForConsoleBackground = BACKGROUND_RED | BACKGROUND_GREEN;
const int OrangeForConsoleBackground =  BACKGROUND_GREEN | BACKGROUND_INTENSITY;
const int MagentaForConsoleBackground = BACKGROUND_RED | BACKGROUND_BLUE;
const int PinkForConsoleBackground = BACKGROUND_RED | BACKGROUND_INTENSITY;

//FUNCTIONS


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
                        CovertSelectedFileToData();
                        GameLoopAndComands();
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
                        GameLoopAndComands();

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
                     "      LEGENDA : \n"
                     "V - village 10 gold per turn          _ - plain\n"
                     "F - farm generates 10 food            m - hills\n"
                     "L - lumber camp generates 10 wood     Y - forest\n"
                     "M - mine generates 10 stone           ^ - mountain\n\n"
                     "Resources are generate in this way Building level * 10  per turn of the resource produced by that buiding\n\n"
                     "COMANDS:\n"
                     "next jumps to next turn\n"
                     "save saves the game\n"
                     "claim  claims a teritory\n"
                     "build and that V,F,L,M builds the selected building(if you own that teritory and 50 Wood and 50 Stone)\n"
                     "upgrade to a maximum of 10 levels per building(costs 50 Food 25 wood 25 stone)\n"
                     "select lrtd you whrite a number like 109 to select tile situated at line 1 column 9(only works if in parameters)\n"
                     "help prints the info screen\n"
                     "exit closes the program\n"
                     "trade pay 50 gold for 10 food 10 wood 10 stone\n";
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

    //file.open(FileForInterface,ios::out | ios::trunc);
    cout << "Turn : "<<Turn;

    cout<<"           Player "<<SelectedPlayerNumber<<" of "<<NumberOfPlayers;
    cout<<"    \t\t\tFood: "<<player[SelectedPlayerNumber-1]->getFood()<<"  Wood: "<<player[SelectedPlayerNumber-1]->getWood()<<"  Stone: "<<player[SelectedPlayerNumber-1]->getStone()<<"  Gold: "<<player[SelectedPlayerNumber-1]->getGold();
    cout<<endl;
    for(int i = 0; i <100;i++)
        cout<<(char)205;

    for(int i = 0 ; i<10 ; i++)
    {
        //char* buff1 = new char[100];
        char* buff2 = new char[100];

        //sprintf(buff1,"\n");
        cout<<"\n";
        sprintf(buff2,"\n");

        for(int j = 0 ; j<10 ; j++)
        {
            int indexNum = i*100+j;
            int CollPlay = CurrentGameMap[indexNum].getPlayerControl();
            int Terr = CurrentGameMap[indexNum].getTerrainType();
            int Army = CurrentGameMap[indexNum].getArmyNumber();
            int SetType = CurrentGameMap[indexNum].getSettlementType();
            int SetLevel = CurrentGameMap[indexNum].getSettlementLevel();

            switch(CollPlay){
                case 0:
                    break;
                case 1:
                    SetConsoleTextAttribute(console, BlueForConsoleBackground);
                    break;
                case 2:
                    SetConsoleTextAttribute(console, RedForConsoleBackground);
                    break;
                case 3:
                    SetConsoleTextAttribute(console, GreenForConsoleBackground);
                    break;
                case 4:
                    SetConsoleTextAttribute(console, CyanForConsoleBackground);
                    break;
                case 5:
                    SetConsoleTextAttribute(console, OrangeForConsoleBackground);
                    break;
                case 6:
                    SetConsoleTextAttribute(console, PinkForConsoleBackground);
                    break;
                case 7:
                    SetConsoleTextAttribute(console, MagentaForConsoleBackground);
                    break;
                case 8:
                    SetConsoleTextAttribute(console, YellowForConsoleBackground);
                    break;
            }
            switch (Terr)
            {
                case 1:
                    cout<<"_ ";
                    break;
                case 2:
                    cout<<"m ";
                    break;
                case 3:
                    cout<<"Y ";
                    break;
                case 4:
                    cout<<"^ ";
                    break;
            }
            SetConsoleTextAttribute(console, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            if(Army != 0)
                cout<<"# ";
            else
                cout<<"0 ";
            cout<<(char)186;

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
        //file<<buff1;
        cout<<buff2<<i;
        cout<<"\n";
        for(int k = 0; k < 10 ; k++){
            cout<<(char)205<<(char)205<<(char)205<<(char)205<<(char)206;
        }

    }

    //file.close();
}


void CalculateIncome(){
    for(int i = 0 ; i < 10;i++){
        for(int j = 0; j< 10 ; j++){
            int indexNum = i*100+j;
            if(CurrentGameMap[indexNum].getPlayerControl() != 0){
                int buidty =CurrentGameMap[indexNum].getSettlementType();
                int buldlv =CurrentGameMap[indexNum].getSettlementLevel();
                int ply = CurrentGameMap[indexNum].getPlayerControl();
                switch (buidty) {
                    case 1:
                        *player[ply-1]+=(10*buldlv+0.41f);
                        break;
                    case 2:
                        *player[ply-1]+=(10*buldlv+0.11f);
                        break;
                    case 3:
                        *player[ply-1]+=(10*buldlv+0.21f);
                        break;
                    case 4:
                        *player[ply-1]+=(10*buldlv+0.31f);
                        break;

                }

            }
        }
    }
    for(int i = 0 ; i < NumberOfPlayers;i++){
        *player[i]+=(10+0.41f);
    }
}

//all the comands
void GameLoopAndComands(){
    CurrentPlayerTurn = 1;
    while(1){
        system("cls");
        PrepareInterfaceForGame(CurrentPlayerTurn);
        cout<<endl<<"0    1    2    3    4    5    6    7    8    9";
        cout<<endl<<"Curent selected tile : "<< SelectedTile/100<<"-"<<SelectedTile%100;
        cout<<endl<<"Your comand: "<<endl;
        string line;
        getline(std::cin, line);

        if(line == "select"){
            cout<<endl<<"Select tile : ";
            string ind;
            getline(std::cin, ind);
            int buffff = stoi(ind);
            if(buffff >= 0  and buffff <= 909)
            {
                SelectedTile  = buffff;
            }
        }

        if(line == "save")
        {
            SaveGame();
        }
        if(line== "help")
        {
            cout<<info();
            getchar();
        }
        if(line == "exit"){
            break;
        }
        if(line == "claim"){
            int x =SelectedTile/100;
            int y =SelectedTile%100;
            if(player[CurrentPlayerTurn-1]->getGold() >= 100 and CurrentGameMap[SelectedTile].getPlayerControl() == 0 ){
                *player[CurrentPlayerTurn-1]-=(100+0.41f);
                CurrentGameMap[SelectedTile].setPlayerControl(CurrentPlayerTurn);
            }

        }

        if(line == "upgrade"){
            int x =SelectedTile/100;
            int y =SelectedTile%100;
            if(player[CurrentPlayerTurn-1]->getFood() >= 50 and player[CurrentPlayerTurn-1]->getWood() >= 25 and player[CurrentPlayerTurn-1]->getStone() >= 25 and CurrentGameMap[SelectedTile].getSettlementType() != 0 and CurrentGameMap[SelectedTile].getSettlementLevel() <= 10){
                int tmp = CurrentGameMap[SelectedTile].getSettlementLevel();
                CurrentGameMap[SelectedTile].setSettlementLevel(tmp+1);
                *player[CurrentPlayerTurn-1]-=(50+0.11f);
                *player[CurrentPlayerTurn-1]-=(25+0.21f);
                *player[CurrentPlayerTurn-1]-=(25+0.31f);
            }

        }


        if(line == "build"){
            cout<<endl<<"Select building type: ";
            string ind;
            getline(std::cin, ind);
            if(ind == "V" and player[CurrentPlayerTurn-1]->getStone() >= 50 and player[CurrentPlayerTurn-1]->getWood() >= 50 and CurrentGameMap[SelectedTile].getPlayerControl() == CurrentPlayerTurn and CurrentGameMap[SelectedTile].getSettlementType() == 0){
                *player[CurrentPlayerTurn-1]-=(50+0.21f);
                *player[CurrentPlayerTurn-1]-=(50+0.31f);
                CurrentGameMap[SelectedTile].setSettlementLevel(1);
                CurrentGameMap[SelectedTile].setSettlementType(1);
            }
            if(ind == "F" and player[CurrentPlayerTurn-1]->getStone() >= 50 and player[CurrentPlayerTurn-1]->getWood() >= 50 and CurrentGameMap[SelectedTile].getPlayerControl() == CurrentPlayerTurn and CurrentGameMap[SelectedTile].getSettlementType() == 0 and ( CurrentGameMap[SelectedTile].getTerrainType() == 1 or CurrentGameMap[SelectedTile].getTerrainType() == 2) ){
                *player[CurrentPlayerTurn-1]-=(50+0.21f);
                *player[CurrentPlayerTurn-1]-=(50+0.31f);
                CurrentGameMap[SelectedTile].setSettlementLevel(1);
                CurrentGameMap[SelectedTile].setSettlementType(2);
            }
            if(ind == "L" and player[CurrentPlayerTurn-1]->getStone() >= 50 and player[CurrentPlayerTurn-1]->getWood() >= 50 and CurrentGameMap[SelectedTile].getPlayerControl() == CurrentPlayerTurn and CurrentGameMap[SelectedTile].getSettlementType() == 0 and CurrentGameMap[SelectedTile].getTerrainType() == 3){
                *player[CurrentPlayerTurn-1]-=(50+0.21f);
                *player[CurrentPlayerTurn-1]-=(50+0.31f);
                CurrentGameMap[SelectedTile].setSettlementLevel(1);
                CurrentGameMap[SelectedTile].setSettlementType(3);
            }
            if(ind == "M" and player[CurrentPlayerTurn-1]->getStone() >= 50 and player[CurrentPlayerTurn-1]->getWood() >= 50 and CurrentGameMap[SelectedTile].getPlayerControl() == CurrentPlayerTurn and CurrentGameMap[SelectedTile].getSettlementType() == 0 and  CurrentGameMap[SelectedTile].getTerrainType() == 4 ){
                *player[CurrentPlayerTurn-1]-=(50+0.21f);
                *player[CurrentPlayerTurn-1]-=(50+0.31f);
                CurrentGameMap[SelectedTile].setSettlementLevel(1);
                CurrentGameMap[SelectedTile].setSettlementType(4);
            }



        }


        if(line == "trade" and player[CurrentPlayerTurn-1]->getGold() >= 50){

            *player[CurrentPlayerTurn-1]+=(10+0.11f);
            *player[CurrentPlayerTurn-1]+=(10+0.21f);
            *player[CurrentPlayerTurn-1]+=(10+0.31f);
            *player[CurrentPlayerTurn-1]-=(50+0.41f);
        }
        if(line == "next"){
            if(CurrentPlayerTurn < NumberOfPlayers)
                CurrentPlayerTurn++;
            else
            {
                CalculateIncome();
                CurrentPlayerTurn = 1;
                Turn++;
            }
        }

    }
}