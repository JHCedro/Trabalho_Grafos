#include "../include/No.h"
#include "../include/Arco.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

No::No(uint id){
    this->id = id;
    this->grau = 0;
    this->peso = 0.0;
    this->marcado = false;
    this->nivel = 0;
}

void No::atualizaGrau(){
    this->grau = 0;
    for(itInicio(); !itEhFim(); itProx())
        this->grau++;
}

void No::imprimirDetelhado(bool direcionado){
    printf("( id:%2d, grau:%2d, peso: %2.1f, nivel:%2d ):", id, grau, peso, nivel);

    for(itInicio(); !itEhFim(); itProx()){
        this->getIt()->imprimirDetelhado();
    }

    cout<<endl;
}

void No::imprimir(bool direcionado){
    printf("( id:%2d, grau:%2d ):", id, grau);

    for(itInicio(); !itEhFim(); itProx()){
        this->getIt()->imprimir();
    }

    cout<<endl;
}

bool No::ehAdjacente(No *no){
    ///pesquisa na lista de adjacencia do no
    for(itInicio(); !itEhFim(); itProx()){
        Arco *arco = this->getIt();
        if(no == arco->getNoDestino())
            return true;
    }
    return false;
}

