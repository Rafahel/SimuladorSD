//
// Created by Rafahel on 09/04/2017.
//

#include "Processo.h"




void Processo::tornaLider() {
    Processo::lider =  true;
}

int Processo::getId(){
    return id;
}

bool Processo::isLider(){
    return lider;
}

bool Processo::isAtivo() {
    return ativo;
}
