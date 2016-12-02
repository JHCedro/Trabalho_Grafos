#ifndef NOLISTA_H_INCLUDED
#define NOLISTA_H_INCLUDED
#include "Hashing.h"
#include "Arco.h"

class Arco;

class NoLista : public No
{
private:
    Arco *listaArcos, *it;
    NoLista *proxNo;
public:
    NoLista(uint n);

    ///funcoes de iteracao na lista de arcos
    void itInicio();
    Arco* getIt();
    void itProx();
    bool itEhFim();

    Arco* buscaArco(No* noDestino);
    Arco* buscaArco(uint noDestino);
    Arco* insereArco(No* noDestino, uint id, double peso = 1.0);
    bool removeArco(uint id);
    bool removeArco(No* noDestino);
    void removeArcos();

    NoLista *getProxNo();
    void setProxNo(NoLista *proxNo);

    void imprimir();

    ~NoLista();
};

#endif // NOHASH_H_INCLUDED
