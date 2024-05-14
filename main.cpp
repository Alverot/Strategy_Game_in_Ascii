#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <filesystem>

#include "Headers/GameManagingFunction.h"
#include "HeadersForClasses/Tile.h"
#include "HeadersForClasses/Exceptions.h"
#include "HeadersForClasses/Map.h"

using namespace std;

int main() {
    //START

    try {


        Menu();
        cout << "\nEND\n";
        Tile patrat(3, 2, 3, 1, 3);
        patrat.afisTMP();
        Map map;
        //map.PrintMap();
        cout<<map.ConvertForSave();

        cout<<"Gata?";
        getchar();getchar();
        filesystem::path currentPath = filesystem::current_path();
        cout << "Current Working Directory: " << currentPath << endl;
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
