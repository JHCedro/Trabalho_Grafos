#include "../include/GrafoHash.h"
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
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = ((id >> 16) ^ id) * 0x45d9f3b;
    id = (id >> 16) ^ id;

    return (id)%tam;
}

uint fReHashNo(uint id, uint tam){
    return id*2654435761 % 2^32 + 1;
}

uint noGetID(NoHash* no){
    return no->getID();
}

GrafoHash::GrafoHash(uint ordem, bool direcionado) : Grafo(direcionado){
    ///criando tabela hash
    this->ordem = ordem;
    tabelaNos = new THash<NoHash*>((uint) ordem * ajusteTam, NULL, new NoHash(-1, 1));
    tabelaNos->setFuncaoHash(fHashNo);
    tabelaNos->setFuncaoReHash(fReHashNo);
    tabelaNos->setGetID(noGetID);
}

///Funcao que insere no no inicio(cabeca) do GrafoHash
NoHash *GrafoHash::insereNo(uint id){
    NoHash *no = new NoHash(id, (uint) ordem * ajusteTam);
    tabelaNos->inserir(no);
    this->numeroNos++;///atualiza numero de vertices(nos)
    return no;
}

void GrafoHash::itInicio(){
    this->tabelaNos->itInicio();
}

NoHash* GrafoHash::getIt(){
    return this->tabelaNos->getIt();
}

void GrafoHash::itProx(){
    this->tabelaNos->itProx();
}

bool GrafoHash::itEhFim(){
    return this->tabelaNos->itEhFim();
}

GrafoHash* GrafoHash::novoGrafo(uint ordem, bool direcionado){
    return new GrafoHash(ordem, direcionado);
}

NoHash *GrafoHash::buscaNo(uint id){
    return tabelaNos->buscar(id);
}

bool GrafoHash::removeNo(uint id){
    No* no = buscaNo(id);
    if(no != NULL){
        removeArcosLigadasAoNo(no, true);
        tabelaNos->remover(id);
        this->numeroNos--;
        return true;
    }
    return false;
}

void GrafoHash::imprimir(bool detalhado){
    cout << "\n[Grafo HASH] ";
    Grafo::imprimir(detalhado);
}

void GrafoHash::imprimirTabela(){
    printf("Grau do GrafoHash: %d\t numero de nos: %d\t numero de arcos: %d\t colisoes: %d\n",
           grau, numeroNos, numeroArcos, tabelaNos->getColisoes());
    for(itInicio(); !itEhFim(); itProx()){
        getIt()->imprimir(direcionado);
    }
}

uint GrafoHash::getNumColisoes(){
    return tabelaNos->getColisoes();
}

/** IMPLEMENTA��O DO DESTRUTOR */
GrafoHash::~GrafoHash(){
    for(itInicio(); !itEhFim(); itProx()){
        NoHash *no = getIt();
        delete no;
	}
	delete tabelaNos;
}

GrafoHash* GrafoHash::grafoCompleto(uint n, bool direcionado){
    GrafoHash* G = new GrafoHash(n, direcionado);
    vector<No*> nos;
    for(uint i=0; i < n; i++)
        nos.push_back(G->insereNo(i));

    for (uint i=0; i < n; i++){
        for (uint j=0; j < n; j++){
            if( i != j )
                G->insereArco(nos[i], nos[j], i*n+j, false);
        }
    }
    G->atualizaGrau();

    return G;
}

GrafoHash* GrafoHash::grafoCircular(uint n, bool direcionado){
    GrafoHash* G = new GrafoHash(n, direcionado);
    No *aux, *primeiro, *ultimo;
    primeiro = ultimo = G->insereNo(0);
    for(uint i=1; i < n; i++){
        aux = G->insereNo(i);
        G->insereArco(ultimo, aux, 2*i);
        G->insereArco(aux, ultimo, 2*i+1);
        ultimo = aux;
    }
    if(ultimo != primeiro){
        G->insereArco(ultimo, primeiro, 2*n);
        G->insereArco(primeiro, ultimo, 2*n+1);
    }

    G->atualizaGrau();
    return G;
}

/** retorna grafo escadinha com n vertices */
GrafoHash* GrafoHash::grafoEscadinha(uint n, bool direcionado){
    GrafoHash* G = new GrafoHash(n, direcionado);
    vector<No*> nos;
    for(uint i=0; i < n; i++){
        nos.push_back(G->insereNo(i));
        for (uint j=0; j < i; j++)
            G->insereArco(nos.back(), nos[j], i+j, false);
    }
    G->atualizaGrau();
    return G;
}

