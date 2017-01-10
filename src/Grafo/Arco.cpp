#include "Arco.h"

void Arco::imprimirDetelhado(){
    printf("| --[A%2d: peso: %2.1f]--> (%d) ", id, peso, noDestino->getID());
}

void Arco::imprimir(){
    printf("|--[A%2d]--> (%d) ", id, noDestino->getID());
}

/** Retorna o o adjacente de (no) para o arco (this) */
No* Arco::getVizinho(No* no){
    if(no == noOrigem)
        return noDestino;
    else if(no == noDestino)
        return noOrigem;

    return NULL;
}
