#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Processo.h"
#include <algorithm>
#include <cstdio>

using namespace std;

int random(int min, int max){

    return min + (rand() % (max - min + 1));
}

vector<Processo> anel( vector<Processo> processos){
    int detector = -1;
    int pos = -1;
    /// Randomiza o processo detector
    try {
        while(1){
            bool sair = false;
            detector = random(1, processos.size());
            for (int i = 0; i < processos.size() ; ++i) {
                if(processos.at(i).getId() == detector && processos.at(i).isAtivo()){
                    cout << "ID do processo detector: " << processos.at(i).getId() << endl;
                    pos = i;
                    sair = true;
                    break;
                }
            }
            if(sair)
                break;
        }
    }catch(...){
        cout << "Erro de randomizacao" << endl;
    }
    int i = pos + 1;
    for (i ; i < processos.size(); ++i) {
//        cout << "i = " << i << "    Size: " << processos.size() << endl;
        if(processos.at(i).getId() == processos.at(pos).getId()){
            cout << "Processo: " << processos.at(i).getId() << " Recebendo mensagem: " << processos.at(pos).getId() << endl;
            cout << "Novo processo lider: ID " <<  processos.at(pos).getId() << endl;
            processos.at(pos).tornaLider();
            break;
        }
        if(processos.at(i).getId() != processos.at(pos).getId()){
            cout << "Processo: " << processos.at(i).getId() << " Recebendo mensagem: " << processos.at(pos).getId();
            if(processos.at(i).getId() > processos.at(pos).getId()){
                pos = i;
                cout << " Modificando a mensagem e enviando: " << processos.at(pos).getId() << endl;
            }
            if(processos.at(i).getId() < processos.at(pos).getId()){
                cout << " Repassando a mensagem: " << processos.at(pos).getId() << endl;
            }

        }
        if(i >= processos.size() - 1){
            i = -1;
        }


    }

    return processos;

}

vector<Processo> bulling( vector<Processo> processos){
    int detector = -1;
    int pos = -1;
    /// Randomiza o processo detector
    try {
        while(1){
            bool sair = false;
            detector = random(1, processos.size());
            for (int i = 0; i < processos.size() ; ++i) {
                if(processos.at(i).getId() == detector && processos.at(i).isAtivo()){
                    //cout << "ID do processo detector: " << processos.at(i).getId() << endl;
                    pos = i;
                    sair = true;
                    break;
                }
            }
            if(sair)
                break;
        }
    }catch(...){
        cout << "Erro de randomizacao" << endl;
    }



    /// Detector envia mensagem de eleição para outros processos

    cout << "Processo: " << processos.at(pos).getId() << " detectou a falha e iniciou a eleicao." << endl;
    int inicial = pos;
    bool novoLider;
    int cont = 0;
    int liderPos = -1;
    while(1){
        for (int i = 0; i < processos.size(); ++i) {
            novoLider = true;
            if(processos.at(i).isAtivo()){
                if(processos.at(i).getId() != processos.at(pos).getId()){
                    liderPos = pos;
                    cout << "Processo: " << processos.at(i).getId() << " Recebendo mensagem: " << processos.at(pos).getId() << " Respondendo a mensagem: " << processos.at(i).getId() << endl;
                    if(processos.at(pos).getId() < processos.at(i).getId()){
//                        cout << processos.at(i).getId() << " > " << processos.at(pos).getId() << endl;
                        novoLider = false;
                    }

                }
            }
        }
//        cout << novoLider << endl;
        if(novoLider){
            cout << "Novo lider: " << processos.at(liderPos).getId() << endl;
            processos.at(liderPos).tornaLider();
            break;
        }
        else{
            while(pos < processos.size()){
                if(cont > 0){
                    pos ++;
                    cont++;
                }
                if(cont == 0){
                    if(processos.at(0).getId() == processos.at(pos).getId()){
                        pos += 1;
                    }
                    else
                        pos = 0;
                    cont ++;
                }
                if(pos < processos.size()){
                    if(pos == inicial)
                        continue;
                    else{
                        cout << "Processo: " << processos.at(pos).getId() << " iniciando nova votacao." << endl;
                        break;
                    }

                } else{
                    cout << "Maior que o numero de elementos do vetor" << endl;
                    break;
                }
            }

        }

    }

    return processos;
}



int main() {
    vector<Processo> processos;
    short op;
    srand(time(NULL));
    int total = random(10, 100); // Numero de processos a serem gerados pelo sistema.
    int id;
    // cria prcessos e o primeiro a ser criado é o lider
    for (int i = 0; i < total ; ++i) {
        id = i + 1;
        if(i == 0) {
            Processo processo(id, true);
            processos.push_back(processo);
        } else{
            Processo processo(id, false);
            processos.push_back(processo);
        }
    }

    for (int i = 0; i < processos.size() ; ++i) {
        cout << "ID: " << processos[i].getId() << "    " << "Status de lider: " << processos[i].isLider() << endl;
    }

    cout << endl << "1 - Algoritmo de Bullyng" << endl;
    cout << "2 - Algoritmo em Anel" << endl;
    cin >> op;
    if(op == 1){

        while(1){
            if(processos.size() == 0){
                cout << "Nao ha mais processos rodando. Finalizando o programa." << endl;
                break;
            }
            op = 0;
            cout << "1 - Fazer com que o processo lider falhe" << endl;
            cout << "2 - Sair" << endl;
            cin >> op;
            cout << endl;

            if (op == 1){

                if(processos.size() - 1 == 0){
                    cout << "Nao ha mais processos. " << endl;
                    fflush(stdin);
                    getchar();
                    return 1;
                }

                if(processos.size() - 1 == 1){
                    cout << "Unico processo restante e o ID: " << processos.at(0).getId() << endl;
                    processos.pop_back();
                    continue;
                }

                for (int i = 0; i < processos.size(); ++i) {
                    try {
                        if(processos.at(i).isLider()){
                            cout << "Processo " << processos.at(i).getId() << " Falhou" << endl;
                            processos.erase(processos.begin() + i);

                            break;
                        }
                    }catch(exception exception1){
                        cout << "Erro ao criar falha de lider... " << endl;
                        break;
                    }
                }

                processos = bulling(processos);
            }
            else if(op == 2){
                return 1;
            }

        }

    }
    if(op == 2){

        while(1){
            cout << "1 - Fazer com que o processo lider falhe" << endl;
            cout << "2 - Sair" << endl;
            cin >> op;
            cout << endl;

            if(op == 1){
                if(processos.size() - 1 == 0){
                    cout << "Nao ha mais processos. " << endl;
                    fflush(stdin);
                    getchar();
                    return 2;
                }

                if(processos.size() - 1 == 1){
                    cout << "Unico processo restante e o ID: " << processos.at(0).getId() << endl;
                    processos.pop_back();
                    continue;
                }
                for (int i = 0; i < processos.size(); ++i) {
                    try {
                        if(processos.at(i).isLider()){
                            cout << "Processo " << processos.at(i).getId() << " Falhou" << endl;
                            processos.erase(processos.begin() + i);

                            break;
                        }
                    }catch(exception exception1){
                        cout << "Erro ao criar falha de lider... " << endl;
                        break;
                    }


                }

                processos = anel(processos);

            }
            if(op == 2)
                return 2;
        }

    }

    return 0;
}