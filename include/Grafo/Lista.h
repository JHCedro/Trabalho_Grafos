#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <iostream>
#include <stdlib.h>

using namespace std;
typedef unsigned int uint;

template<class T> class Lista{
private:
    Lista *prox;
    T obj;
    /// funcao getID do objeto (T)
//    uint (*getID)(T);
public:
    Lista(T obj);

    T *getProx();
    void setProx(T *proxNo);

    T buscar(uint id);
    Lista<T>* inserir(T obj);
    Lista<T>* remover(uint id);
    Lista<T>* remover(T id);

    ~Lista();
};

/// DEVERIA ESTAR EM "Hashing.cpp":
/// NAO SEI PORQUE NAO FUNCIONA SE ESTIVER LA

template<class T>
Lista<T>::Lista(T obj){
    this->prox = NULL;
    this->it = NULL;
    this->obj = obj;
//    this->getID = DEFAULTgetID;
}

//template<class T>
//uint Lista<T>::DEFAULTgetID(T obj){
//    return obj->getID();
//}

//template<class T>
//void Lista<T>::setGetID(uint (*funcao)(T)){
//    this->getID = funcao;
//}

template<class T>
Lista<T>* Lista<T>::inserir(T obj){
    Lista *novoNo = new Lista(obj);
    novoNo->setProx(this);
    return novoNo;
}

template<class T>
T Lista<T>::buscar(uint id){
    Lista* it = this;
    while(it != NULL && it->getID())
        it = it->getProx();
    return NULL;
}

/**
* Remocao preguicosa!!
*/
template<class T>
Lista<T>* Lista<T>::remover(uint id){
    Lista<T>* listaRemover = this;
    Lista<T>* listaNova = this;
    ///se primeiro arco sera removido
    if(this->getID() == id){
        listaNova = this->getProx();
    }else{
        Lista *anterior= this;
        while(anterior->getProx() != NULL &&
              anterior->getProx()->getNoDestino()->getID() != id)
            anterior = anterior->getProx();

        if(anterior->getProx() != NULL){
            Lista *sucessor = anterior->getProx()->getProx();
            listaRemover = anterior->getProx();
            anterior->setProx(sucessor);
        }
    }
    if(listaRemover != NULL && listaRemover != this)
        delete listaRemover;

}

template<class T>
T Lista<T>::getIt(){
    return tabela[it];
}

template<class T>
void Lista<T>::itInicio(){
    this->it = 0;
    if(tabela[it] == NULO || tabela[it] == RM)
        this->itProx();
}

template<class T>
void Lista<T>::itProx(){
    it++;
    while(it < tam && (tabela[it] == NULO || tabela[it] == RM)){
        it++;
    }
}

template<class T>
bool Lista<T>::itEhFim(){
    return it == tam;
}

template<class T>
void Lista<T>::imprimir(){
    cout << "\n[";
    for (uint i = 0; i < tam; i++){
        if(tabela[i] == NULO)
            cout << "_" << ", ";
        else if(tabela[i] == RM)
            cout << "*" << ", ";
        else
            cout << tabela[i]->getID() << ", ";
    }
    cout << "]" << endl;
}

template<class T>
Lista<T>::~Lista(){
    delete [] tabela;
    delete NULO;
    delete RM;
}

#endif // LISTA_H_INCLUDED
