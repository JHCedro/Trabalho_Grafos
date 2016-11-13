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

double No::hashing(unsigned int id){
    unsigned int valor = 0;
    int primos[7] = {251,337,157,193,229,263,127};
    for(double i = 0; i < id; i+=0.01)
        valor = valor*primos[valor%7] + id;
    return valor%101;
}

void No::insereArco(No* noDestino, unsigned int id){
    Arco *novaArco = new Arco(id);
    novaArco->setNoDestino(noDestino);
    novaArco->setNoOrigem(this);
    novaArco->setProxArco(this->listaNos);
    novaArco->setPeso(hashing(id));
    this->setListaArcos(novaArco);
    this->grau++;
}

void No::imprime(){
    cout<<"( "<<"id:"<<this->getID()<<"\tgrau:"<<this->grau<<"\tpeso:"<<this->peso<<" )";
    Arco *arc = this->getListaArcos();

    while(arc!=NULL){
        cout<< " --|A" << arc->getID() << "|--> " << arc->getNoDestino()->getID() << " " << "Peso: " << arc->getPeso() << " ";
        arc = arc->getProxArco();
    }
    cout<<endl;
}

bool No::ehAdjacente(No *no){
    ///pesquisa na lista de adjacencia do nó
    Arco *aux=this->listaNos;
    while(aux!=NULL){
        if(no==aux->getNoDestino())
            return true;
        aux=aux->getProxArco();
    }
    return false;
}
