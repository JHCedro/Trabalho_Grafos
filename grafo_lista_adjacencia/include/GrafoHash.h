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
    float ajusteTam = 1.2;  /// ajuste para o tamanho da tabela

    void pushIt();
    void popIt();
public:
    GrafoHash(uint ordem, bool grafo_direcionado = true);

    ///funcoes de iteracao na lista de nos
    NoHash* getIt();
    void itInicio();
    void itProx();
    bool itEhFim();

    NoHash* buscaNo(uint id);
    NoHash* insereNo(uint id);
    bool removeNo(uint id);

    GrafoHash* novoGrafo(uint ordem, bool grafo_direcionado = true);
    static GrafoHash* grafoCompleto(uint n, bool grafo_direcionado = true);
    static GrafoHash* grafoCircular(uint n, bool grafo_direcionado = true);
    static GrafoHash* grafoEscadinha(uint n, bool grafo_direcionado = true);

    uint getNumColisoes();

    void imprimir(bool detalhado = false);
    void imprimirTabela();

    ~GrafoHash();
};

#endif // DIGrafoHash_H_INCLUDED
