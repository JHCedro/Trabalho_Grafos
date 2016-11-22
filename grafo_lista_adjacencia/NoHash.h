#ifndef NOHASH_H_INCLUDED
#define NOHASH_H_INCLUDED
#include "No.h"
#include "Hashing.h"
#include "Arco.h"

class Arco;

class NoHash : public No
{
private:
    THash<Arco*> *tabelaArcos;
    uint tamTabArcos;
public:
    NoHash(uint id, uint n);

    ///funcoes de iteracao na lista de arcos
    void itInicio();
    Arco* getIt();
    void itProx();
    bool itEhFim();

    Arco* buscaArco(NoHash* noDestino);
    Arco* buscaArco(uint id);
    Arco* insereArco(No* noDestino, uint id);
    void removeArco(uint id);
    void removeArco(NoHash* noDestino);
    void removeArcos();

    ~NoHash(){};
};

#endif // NOHASH_H_INCLUDED
