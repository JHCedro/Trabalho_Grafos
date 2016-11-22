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

GrafoLista::GrafoLista() : Grafo(){
    this->listaNos = NULL;
}

///Função que insere nó no inicio(cabeça) do GrafoLista
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


NoLista *GrafoLista::buscaNo(uint id){
    for(itInicio(); !itEhFim(); itProx()){
        if(this->getIt()->getID() == id)
            return this->getIt();
    }
    return NULL;
}

void GrafoLista::removeNo(uint id){
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
//        cout <<"\nremovendo no com id:" << noRemover->getID()<<endl;
        this->removeArcos(noRemover, false);
        this->removeArcosLigadasAoNo(noRemover, false);
        this->atualizaGrau();
        delete noRemover;
        this->numeroNos--;
    }
}

/** IMPLEMENTAR DESTRUTOR */
GrafoLista::~GrafoLista(){
//    NoLista *no, *noAux;
//    Arco *arco, *arcoAux;
//    ///percorre nos
//    no = this->listaNos;
//    while( this->listaNos!=NULL ){
//        ///percorre arcos do no
//        arco = this->listaNos->getListaArcos();
//        while( arco!=NULL ){
//            arcoAux = arco;
//            arco = arco->getProxArco();
//            this->listaNos->setListaArcos(arco);
//            delete arcoAux;
//        }
//
//        noAux = this->listaNos;
//        this->listaNos = this->listaNos->getProxNo();
//        delete noAux;
//    }
//    this->listaNos=NULL;
}
