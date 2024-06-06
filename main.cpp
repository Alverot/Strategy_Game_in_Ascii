#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <filesystem>
#include <string>
#include <stdexcept>

#include "HeadersForClasses/Exceptions.h"
#include "Headers/GameManagingFunction.h"
#include "HeadersForClasses/Tile.h"

#include "HeadersForClasses/Map.h"
#include "HeadersForClasses/Player.h"

using namespace std;

int main() {
    //START
    try {

        Menu();
        cout << "\nEND\n";
        //test exceptions
        /*
        Map adsadada;
        adsadada[909].setTerrainType(5);
        cout<<adsadada[909].getTerrainType();
        getchar();
         */
    }
    catch(const char* mes)
    {
        printf("\nEROR : %s",mes);
    }
    catch(Exceptions ex){
        ex.PrintExc();
        getchar();
    }
     catch (const std::invalid_argument& e) {
         cerr << "Error: Invalid string format for integer conversion." << endl;
         cerr << "Exception details: " << e.what() << endl;
    }
    catch(...){
        printf("\nEeception not defined!");
    }
    getchar();
    return 0;
}
