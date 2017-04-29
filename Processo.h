//
// Created by Rafahel on 09/04/2017.
//

#ifndef SIMULADORSD_PROCESSO_H
#define SIMULADORSD_PROCESSO_H

class Processo{
private:
    int id;
    bool lider;
    int mensagem;
    bool ativo;
public:
    Processo(int id, bool lider) : id(id), lider(lider), ativo(true) {}

    bool isAtivo();

    void tornaLider();

    int getId();

    bool isLider();


};


#endif //SIMULADORSD_PROCESSO_H
