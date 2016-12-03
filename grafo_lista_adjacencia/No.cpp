#include "No.h"
#include "Arco.h"
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

double No::hashing(uint id){
    uint valor = 0;
//    int primos[7] = {251,337,157,193,229,263,127};
//    for(double i = 0; i < id; i+=0.01)
//        valor = valor*primos[valor%7] + id;
    return valor%101;
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

