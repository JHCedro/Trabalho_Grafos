#include "GrafoLista.h"
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

GrafoLista::GrafoLista(bool direcionado) : Grafo(direcionado){
    this->listaNos = NULL;
}

///Funcao que insere no no inicio(cabeca) do GrafoLista
NoLista *GrafoLista::insereNo(uint id){
    NoLista *no = new NoLista(id);
    no->setProxNo(listaNos);
    this->listaNos=no;
    this->numeroNos++;///atualiza numero de vertices(nos)
    return no;
}

void GrafoLista::itInicio(){
    it = this->listaNos;
}

NoLista* GrafoLista::getIt(){
    return this->it;
}

void GrafoLista::itProx(){
    it = it->getProxNo();
}

bool GrafoLista::itEhFim(){
    return it == NULL;
}

GrafoLista* GrafoLista::novoGrafo(uint ordem, bool direcionado){
    return new GrafoLista(direcionado);
}

NoLista *GrafoLista::buscaNo(uint id){
    for(itInicio(); !itEhFim(); itProx()){
        if(this->getIt()->getID() == id)
            return this->getIt();
    }
    return NULL;
}

bool GrafoLista::removeNo(uint id){
    NoLista *noRemover=NULL;

    ///se a listaNos eh o no a ser removido
    if(listaNos->getID()==id){
        noRemover = listaNos;
        listaNos = listaNos->getProxNo();
    }
    else{
        NoLista *anterior= listaNos;
        while(anterior->getProxNo()!=NULL &&
              anterior->getProxNo()->getID()!=id)
            anterior=anterior->getProxNo();

        /// no existe no GrafoLista
        if(anterior->getProxNo() != NULL){
            NoLista *sucessor = anterior->getProxNo()->getProxNo();
            noRemover = anterior->getProxNo();
            anterior->setProxNo(sucessor);
        }
    }
    if(noRemover!=NULL){
        this->removeArcos(noRemover, false);
        this->removeArcosLigadasAoNo(noRemover, false);
        delete noRemover;
        this->numeroNos--;
        this->atualizaGrau();
        return true;
    }
    return false;
}

void GrafoLista::imprimir(bool detalhado){
    cout << "\n[Grafo LISTA] ";
    Grafo::imprimir(detalhado);
}

/** IMPLEMENTAÇÃO DO DESTRUTOR */
GrafoLista::~GrafoLista(){
    ///percorre nos
    this->itInicio();
    while(!itEhFim()){
        itProx();
        delete listaNos;
        listaNos = getIt();
    }
    listaNos = NULL;
}

GrafoLista* GrafoLista::grafoCompleto(uint n, bool direcionado){
    GrafoLista* G = new GrafoLista(direcionado);
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

GrafoLista* GrafoLista::grafoCircular(uint n, bool direcionado){
    GrafoLista* G = new GrafoLista(direcionado);
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
GrafoLista* GrafoLista::grafoEscadinha(uint n, bool direcionado){
    GrafoLista* G = new GrafoLista(direcionado);
    vector<No*> nos;
    for(uint i=0; i < n; i++){
        nos.push_back(G->insereNo(i));
        for (uint j=0; j < i; j++)
            G->insereArco(nos.back(), nos[j], i+j, false);
    }
    G->atualizaGrau();
    return G;
}
