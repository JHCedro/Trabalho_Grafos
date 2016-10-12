#include "No.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

void No::imprime(){
    cout<<"( "<<"id:"<<this->getID()<<"\tgrau:"<<this->grau<<"\tpeso:"<<this->peso<<" )";
    Aresta *arc = this->getAresta();

    while(arc!=0){
        cout<< " --|A" << arc->getID() << "|--> " << arc->getParaOnde()->getID() << " ";
        arc = arc->getProxAresta();
    }
    cout<<endl;
}

void No::removeArestas(){
    Aresta *aux1, *aux2=this->getAresta();
    while(aux2!=NULL){
        aux1 = aux2;
        aux2 = aux2->getProxAresta();
        delete aux1;
    }
    this->grau = 0;
    this->setAresta(NULL);
}

void No::insereAresta(No* noDestino, unsigned int id){
    Aresta *novaAresta = new Aresta(id);
    novaAresta->setParaOnde(noDestino);
    novaAresta->setProxAresta(this->arco);
    this->setAresta(novaAresta);
}
