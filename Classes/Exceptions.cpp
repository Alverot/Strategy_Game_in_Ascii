//
// Created by Alex on 10/05/2024.
//

#include <cstdio>
#include "../HeadersForClasses/Exceptions.h"
#include <cstring>



Exceptions::Exceptions(const char *LocExc, const char *MesExc) {
    this->LocExc = new char[strlen(LocExc)+2];
    strcpy(this->LocExc,LocExc);
    this->MesExc = new char[strlen(MesExc)+2] ;
    strcpy(this->MesExc,MesExc);
}

void Exceptions::PrintExc() {
    printf("\n Exception in { %s } : %s ",LocExc,MesExc);
}

Exceptions::~Exceptions() {
    delete[] LocExc;
    delete[] MesExc;
}
