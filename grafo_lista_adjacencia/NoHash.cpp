#include "NoHash.h"
#include <stdio.h>
#include <iostream>

using namespace std;

uint fHashArco(uint id, uint tam){
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = (id >> 16) ^ id;

    return (id)%tam;
}

uint fReHashArco(uint id, uint tam){
    return id*2654435761 % 2^32 + 1;
}

//uint fHashArco(uint id, uint tam){
//    return (id)%tam;
//}
//
//uint fReHashArco(uint id, uint tam){
//    return (id)%(tam/3)+1;
//}

uint arcoGetID(Arco* arco){
    return arco->getID();
}

NoHash::NoHash(uint id, uint n) : No(id){
    ///criando tabela hash
    tabelaArcos = new THash<Arco*>(n, NULL, new Arco(-1));
    tabelaArcos->setFuncaoHash(fHashArco);
    tabelaArcos->setFuncaoReHash(fReHashArco);
    tabelaArcos->setGetID(arcoGetID);
    tamTabArcos = n;
}

void NoHash::removeArcos(){
    for(itInicio(); !itEhFim(); itProx()){
        delete getIt();
    }
    delete tabelaArcos;
    tabelaArcos = new THash<Arco*>(tamTabArcos, NULL, new Arco(-1));
    tabelaArcos->setFuncaoHash(fHashArco);
    tabelaArcos->setFuncaoReHash(fReHashArco);
    tabelaArcos->setGetID(arcoGetID);

    this->grau = 0;
}

Arco* NoHash::insereArco(No* noDestino, uint id){
    Arco *novoArco = new Arco(id);
    novoArco->setNoDestino(noDestino);
    novoArco->setNoOrigem(this);
    tabelaArcos->inserir(novoArco);
    this->grau++;

    return novoArco;
}

void NoHash::itInicio(){
    tabelaArcos->itInicio();
}

Arco* NoHash::getIt(){
    return tabelaArcos->getIt();
}

void NoHash::itProx(){
    tabelaArcos->itProx();
}

bool NoHash::itEhFim(){
    return tabelaArcos->itEhFim();
}

Arco* NoHash::buscaArco(No* noDestino){
    for(itInicio(); !itEhFim(); itProx()){
        Arco *arco = this->getIt();
        if(arco->getNoDestino() == noDestino)
            return arco;
	}
	return NULL;
}

Arco* NoHash::buscaArco(uint noDestino){
    for(itInicio(); !itEhFim(); itProx()){
        Arco *arco = this->getIt();
        if(arco->getNoDestino()->getID() == noDestino)
            return arco;
	}
	return NULL;
}

bool NoHash::removeArco(uint id){
    return tabelaArcos->remover(id);
}

bool NoHash::removeArco(No* noDestino){
    for(itInicio(); !itEhFim(); itProx()){
        Arco *arco = this->getIt();
        if(arco->getNoDestino() == noDestino){
//            cout << "Remover arco: " << arco->getID();
            return tabelaArcos->remover(arco->getID());
        }
	}
}

NoHash::~NoHash(){
    for(itInicio(); !itEhFim(); itProx()){
        Arco *arco = getIt();
        delete arco;
	}
	delete tabelaArcos;
}
