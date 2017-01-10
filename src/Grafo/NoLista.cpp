#include "NoLista.h"

using namespace std;

NoLista::NoLista(uint id) : No(id){
    this->listaArcos = NULL;
}

void NoLista::removeArcos(){
    Arco *remover;
    this->itInicio();

    while(!itEhFim()){
        remover = getIt();
        itProx();
        delete remover;
	free(remover);
    }
    //delete getIt();
    free(getIt());
    this->grau = 0;
    this->listaArcos = NULL;
}

Arco* NoLista::insereArco(No* noDestino, uint id, double peso){
    Arco *novoArco = new Arco(id);
    novoArco->setNoDestino(noDestino);
    novoArco->setNoOrigem(this);
    novoArco->setPeso(peso);

    novoArco->setProxArco(this->listaArcos);
    this->listaArcos = novoArco;
    this->grau++;

    return novoArco;
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

Arco* NoLista::buscaArco(No* noDestino){
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
        if(arco->getNoDestino()->getID() == noDestino)
            return arco;
    }

    return NULL;
}

bool NoLista::removeArco(uint noDestino){
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
            //delete arcoRemover;
		free(arcoRemover);
            this->grau--;
            return true;
        }
    }
    return false;
}

bool NoLista::removeArco(No* noDestino){
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
            return true;
        }
    }
    return false;
}

NoLista::~NoLista(){
    ///percorre arcos
    this->itInicio();
    while(!itEhFim()){
        itProx();
        delete this->listaArcos;
        this->listaArcos = getIt();
    }
    this->listaArcos=NULL;
}
