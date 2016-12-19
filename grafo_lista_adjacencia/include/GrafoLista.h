#ifndef GrafoLista_H_INCLUDED
#define GrafoLista_H_INCLUDED
#include "Grafo.h"
#include "NoLista.h"
#include "Hashing.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
struct Dijkstra;

class GrafoLista : public Grafo
{
private:
    NoLista *listaNos, *it;  ///iterador (it) para lista de nos
    stack<NoLista*> itPilha;
    NoLista *proxNo;

    void pushIt();
    void popIt();
public:
    GrafoLista(bool grafo_direcionado = true);

    ///funcoes de iteracao na lista de nos
    NoLista* getIt();
    void itInicio();
    void itProx();
    bool itEhFim();

    NoLista* buscaNo(uint id);
    NoLista* insereNo(uint id);
    bool removeNo(uint id);

    GrafoLista* novoGrafo(uint ordem, bool grafo_direcionado = true);
    static GrafoLista* grafoCompleto(uint n, bool grafo_direcionado = true);
    static GrafoLista* grafoCircular(uint n, bool grafo_direcionado = true);
    static GrafoLista* grafoEscadinha(uint n, bool grafo_direcionado = true);

    void imprimir(bool detalhado = false);

    ~GrafoLista();
};

#endif // GrafoLista_H_INCLUDED
