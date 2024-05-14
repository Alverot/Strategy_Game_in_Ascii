#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Headers/GameManagingFunction.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//for changing colors

//COLORS

const int CyanForConsoleBackground = BACKGROUND_BLUE | BACKGROUND_GREEN;

void testtt(){
    printf("Merge bine ............cered");
}

void Menu(){
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
            if(opt == 13) {
                switch (optcurenta) {
                    case 1: {
                        cout << "\nnew game";
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


}