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

GrafoHash::GrafoHash(uint ordem) : Grafo(){
    ///criando tabela hash
    tabelaNos = new THash<NoHash*>(ordem, NULL, new NoHash(-1, 0));
    tabelaNos->setFuncaoHash(fHashNo);
    tabelaNos->setFuncaoReHash(fReHashNo);
    tabelaNos->setGetID(noGetID);
    tamTabNos = ordem;
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

GrafoHash* GrafoHash::novoGrafo(uint ordem){
    return new GrafoHash(ordem);
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

GrafoHash* GrafoHash::grafoCompleto(uint n){
    GrafoHash* G = new GrafoHash(n);
    vector<No*> nos;
    for(uint i=0; i < n; i++)
        nos.push_back(G->insereNo(i));

    for (uint i=0; i < n; i++){
        for (uint j=0; j < n; j++){
            if( i != j )
//                G->insereArcoID(i, j, i*n+j, false);
                G->insereArco(nos[i], nos[j], i*n+j, false);
        }
    }
    G->atualizaGrau();
}

GrafoHash* GrafoHash::grafoCircular(uint n){
    GrafoHash* G = new GrafoHash(n);
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
GrafoHash* GrafoHash::grafoEscadinha(uint n){
    GrafoHash* G = new GrafoHash(n);
    vector<No*> nos;
    for(uint i=0; i < n; i++){
        nos.push_back(G->insereNo(i));
        for (uint j=0; j < i; j++)
            G->insereArco(nos.back(), nos[j], i+j, false);
    }
    G->atualizaGrau();
    return G;
}

