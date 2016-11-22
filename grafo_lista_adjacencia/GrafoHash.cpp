#include "GrafoHash.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <map>
#include <set>
#define INFINITO HUGE_VAL

using namespace std;

uint fHashNo(uint id, uint tam){
    return (id)%tam;
}

uint fReHashNo(uint id, uint tam){
    return (id)%(tam/3)+1;
}

uint noGetID(NoHash* no){
    return no->getID();
}

GrafoHash::GrafoHash(uint n) : Grafo(){
    ///criando tabela hash
    tabelaNos = new THash<NoHash*>(n, NULL, new NoHash(-1, 0));
    tabelaNos->setFuncaoHash(fHashNo);
    tabelaNos->setFuncaoReHash(fReHashNo);
    tabelaNos->setGetID(noGetID);
    tamTabNos = n;
}

///Função que insere nó no inicio(cabeça) do GrafoHash
NoHash *GrafoHash::insereNo(uint id){
    NoHash *no = new NoHash(id, tamTabNos);
    tabelaNos->inserir(no);
    this->numeroNos++;///atualiza numero de vertices(nos)
    return no;
}

void GrafoHash::itInicio(){
    this->tabelaNos->itInicio();
}

NoHash* GrafoHash::getIt(){
    this->tabelaNos->getIt();
}

void GrafoHash::itProx(){
    this->tabelaNos->itProx();
}

bool GrafoHash::itEhFim(){
    this->tabelaNos->itEhFim();
}


NoHash *GrafoHash::buscaNo(uint id){
    return tabelaNos->buscar(id);
}

void GrafoHash::removeNo(uint id){
    tabelaNos->remover(id);
    removeArcosLigadasAoNo(buscaNo(id), true);
    this->numeroNos--;
}

void GrafoHash::imprimirTabela(){
    cout<<"Grau do GrafoHash: "<<this->grau<<"\tnumero de nos: "<<this->numeroNos
    <<"\tnumero de arcos: "<<this->numeroArcos<<endl;
    for(tabelaNos->itInicio(); !tabelaNos->itEhFim(); tabelaNos->itProx()){
        tabelaNos->getIt()->imprimir();
    }
}

/** IMPLEMENTAR DESTRUTOR */
GrafoHash::~GrafoHash(){
    for(itInicio(); !itEhFim(); itProx()){
        NoHash *no = getIt();
        delete no;
	}
	delete tabelaNos;
}
