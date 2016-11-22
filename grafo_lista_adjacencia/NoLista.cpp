#include "NoLista.h"
#include "Arco.h"
#include <stdio.h>
#include <iostream>

using namespace std;

NoLista::NoLista(uint id) : No(id){
    this->listaArcos = NULL;
}

void NoLista::removeArcos(){
    Arco *aux1, *aux2 = this->listaArcos;
    while(aux2!=NULL){
        aux1 = aux2;
        aux2 = aux2->getProxArco();
        delete aux1;
    }
    this->grau = 0;
    this->listaArcos = NULL;
}

Arco* NoLista::insereArco(No* noDestino, uint id){
    Arco *novoArco = new Arco(id);
    novoArco->setNoDestino(noDestino);
    novoArco->setNoOrigem(this);
    novoArco->setProxArco(this->listaArcos);
    novoArco->setPeso(hashing(id));
    this->listaArcos = novoArco;
    this->grau++;
}

NoLista* NoLista::getProxNo(){
    return this->proxNo;
}

void NoLista::setProxNo(NoLista *proxNo){
    this->proxNo = proxNo;
}

void NoLista::itInicio(){
    it = this->listaArcos;
}

Arco* NoLista::getIt(){
    return this->it;
}

void NoLista::itProx(){
    it = it->getProxArco();
}

bool NoLista::itEhFim(){
    return it == NULL;
}

Arco* NoLista::buscaArco(NoLista* noDestino){
    for(itInicio(); !itEhFim(); itProx()){
        Arco *arco = this->getIt();
        if(arco->getNoDestino() == noDestino)
            return arco;
	}
	return NULL;
}

Arco* NoLista::buscaArco(uint noDestino){
    for(itInicio(); !itEhFim(); itProx()){
        Arco *arco = this->getIt();
        if(arco->getNoDestino()->getID() == id)
            return arco;
    }

    return NULL;
}

void NoLista::removeArco(uint noDestino){
    if(this->listaArcos != NULL){
        Arco* arcoRemover = NULL;
        ///se primeiro arco sera removido
        if(this->listaArcos->getNoDestino()->getID() == noDestino){
            arcoRemover = this->listaArcos;
            this->listaArcos = arcoRemover->getProxArco();
        }else{
            Arco *anterior= this->listaArcos;
            while(anterior->getProxArco() != NULL &&
                  anterior->getProxArco()->getNoDestino()->getID() != noDestino)
                anterior=anterior->getProxArco();

            /// arco existe no no
            if(anterior->getProxArco() != NULL){
                Arco *sucessor = anterior->getProxArco()->getProxArco();
                arcoRemover = anterior->getProxArco();
                anterior->setProxArco(sucessor);
            }
        }
        if(arcoRemover != NULL){
            delete arcoRemover;
            this->grau--;
        }
    }
}

void NoLista::removeArco(NoLista* noDestino){
    if(this->listaArcos != NULL){
        Arco* arcoRemover = NULL;
        ///se primeiro arco sera removido
        if(this->listaArcos->getNoDestino() == noDestino){
            arcoRemover = this->listaArcos;
            this->listaArcos = arcoRemover->getProxArco();
        }else{
            Arco *anterior= this->listaArcos;
            while(anterior->getProxArco() != NULL &&
                  anterior->getProxArco()->getNoDestino() != noDestino)
                anterior=anterior->getProxArco();

            /// arco existe no no
            if(anterior->getProxArco() != NULL){
                Arco *sucessor = anterior->getProxArco()->getProxArco();
                arcoRemover = anterior->getProxArco();
                anterior->setProxArco(sucessor);
            }
        }
        if(arcoRemover != NULL){
            delete arcoRemover;
            this->grau--;
        }
    }
}
