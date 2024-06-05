//
// Created by Alex on 10/05/2024.
//

#ifndef STRATEGY_GAME_IN_ASCII_EXCEPTIONS_H
#define STRATEGY_GAME_IN_ASCII_EXCEPTIONS_H


#include <cstring>

class Exceptions {
private :
    char* LocExc;
    char* MesExc;
public:
    Exceptions(const char *LocExc, const char *MesExc);
    void PrintExc();
    virtual ~Exceptions();
};


#endif //STRATEGY_GAME_IN_ASCII_EXCEPTIONS_H
