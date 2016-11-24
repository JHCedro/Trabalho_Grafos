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
    NoLista *proxNo;
public:
    GrafoLista();

    ///funcoes de iteracao na lista de nos
    void itInicio();
    NoLista* getIt();
    void itProx();
    bool itEhFim();

    NoLista* buscaNo(uint id);
    NoLista* insereNo(uint id);
    bool removeNo(uint id);

    GrafoLista* novoGrafo(uint ordem);
    static GrafoLista* grafoCompleto(uint n);
    static GrafoLista* grafoCircular(uint n);
    static GrafoLista* grafoEscadinha(uint n);

    void imprimirTabela();

    ~GrafoLista();
};

#endif // GrafoLista_H_INCLUDED
