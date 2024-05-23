#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <filesystem>

#include "Headers/GameManagingFunction.h"
#include "HeadersForClasses/Tile.h"
#include "HeadersForClasses/Exceptions.h"
#include "HeadersForClasses/Map.h"
#include "HeadersForClasses/Player.h"

using namespace std;

int main() {
    //START

    try {

        Menu();
        cout << "\nEND\n";
        SaveGame();
    }
    catch(const char* mes)
    {
        printf("\nEROR : %s",mes);
    }
    catch(Exceptions exceptions){
        exceptions.PrintExc();
    }
    catch(...){
        printf("\nEeception not defined!");
    }
    getchar();
    return 0;
}
