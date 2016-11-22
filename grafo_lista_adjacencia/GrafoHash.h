#ifndef DIGrafoHash_H_INCLUDED
#define DIGrafoHash_H_INCLUDED
#include "Grafo.h"
#include "NoHash.h"
#include "Hashing.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
struct Dijkstra;

class GrafoHash : public Grafo
{
private:
    THash<NoHash*> *tabelaNos;
    uint tamTabNos;
    NoHash *it;  ///iterador (it) para lista de nos
public:
    GrafoHash(uint n);

    ///funcoes de iteracao na lista de nos
    void itInicio();
    NoHash* getIt();
    void itProx();
    bool itEhFim();

    NoHash* buscaNo(uint id);
    NoHash* insereNo(uint id);
    void removeNo(uint id);

//    uint fHashNo(uint id, uint tam);
//    uint fReHashNo(uint id, uint tam);
//    uint noGetID(NoHash* no);

    void imprimirTabela();

    ~GrafoHash();
};

#endif // DIGrafoHash_H_INCLUDED
