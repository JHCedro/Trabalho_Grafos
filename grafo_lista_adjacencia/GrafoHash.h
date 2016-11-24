#ifndef GrafoHash_H_INCLUDED
#define GrafoHash_H_INCLUDED
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
    uint ordem;
    float ajusteTam = 1.4;  /// ajuste para o tamanho da tabela
    NoHash *it;  ///iterador (it) para lista de nos
public:
    GrafoHash(uint ordem);

    ///funcoes de iteracao na lista de nos
    void itInicio();
    NoHash* getIt();
    void itProx();
    bool itEhFim();

    NoHash* buscaNo(uint id);
    NoHash* insereNo(uint id);
    bool removeNo(uint id);

    GrafoHash* novoGrafo(uint ordem);
    static GrafoHash* grafoCompleto(uint n);
    static GrafoHash* grafoCircular(uint n);
    static GrafoHash* grafoEscadinha(uint n);

//    uint fHashNo(uint id, uint tam);
//    uint fReHashNo(uint id, uint tam);
//    uint noGetID(NoHash* no);

    void imprimirTabela();

    ~GrafoHash();
};

#endif // DIGrafoHash_H_INCLUDED
