#include "No.h"
#include "Arco.h"
#include <iostream>

using namespace std;

No::No(unsigned int id){
    this->id = id;
    this->proxNo = NULL;
    this->listaNos = NULL;
    this->grau = NULL;
    this->peso = NULL;
    this->marcado = false;
}

void No::removeArcos(){
    Arco *aux1, *aux2=this->getListaArcos();
    while(aux2!=NULL){
        aux1 = aux2;
        aux2 = aux2->getProxArco();
        delete aux1;
    }
    this->grau = 0;
    this->setListaArcos(NULL);
}

void No::insereArco(No* noDestino, unsigned int id){
    Arco *novaArco = new Arco(id);
    novaArco->setNoDestino(noDestino);
    novaArco->setProxArco(this->listaNos);
    this->setListaArcos(novaArco);
    this->grau++;
}

void No::imprime(){
    cout<<"( "<<"id:"<<this->getID()<<"\tgrau:"<<this->grau<<"\tpeso:"<<this->peso<<" )";
    Arco *arc = this->getListaArcos();

    while(arc!=0){
        cout<< " --|A" << arc->getID() << "|--> " << arc->getNoDestino()->getID() << " ";
        arc = arc->getProxArco();
    }
    cout<<endl;
}
