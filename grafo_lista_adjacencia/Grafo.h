#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include "Arco.h"
#include "Dijkstra.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
typedef unsigned int uint;
//struct Dijkstra;

class Grafo
{
protected:
    No *it;  /// iterador (it) para lista de nos
    uint grau;          /// maior grau de vértice do grafo
    uint numeroNos;     /// n
    uint numeroArcos;   /// m
    uint contAux;       /// contador auxiliar
    bool flagDir;       /// flag indicando se o grafo é direcionado ou não
    int auxEhNoArticulacao(No* no);
    void auxBuscaProfundidade(No *no, No* noArv, Grafo* Arv);
//    void incrementaContador(No* n);
    void atualizaDist(No* u, map<uint, No*> Q, map<uint, double> distancias);
public:
    Grafo();
    uint getGrau(){     return grau;    };
    uint getNumeroNos(){    return numeroNos;   };
    uint getNumeroArcos(){    return numeroArcos;   };
    bool getFlagDir(){  return flagDir; };
    void setFlagDir(bool flag){ flagDir=flag;   };
    uint getContAux(){  return contAux; };
    void setContAux(uint i){ contAux=i;   };

    ///funcoes de iteracao na lista de nos
    virtual void itInicio() = 0;
    virtual No* getIt() = 0;
    virtual void itProx() = 0;
    virtual bool itEhFim() = 0;

//    void leDataArquivo(char nome[]);

    virtual No* buscaNo(uint id) = 0;
    virtual No* insereNo(uint id) = 0;
    virtual bool removeNo(uint id) = 0;

    void imprimir();

    void atualizaGrau();
    void atualizaGrausEntradaSaidaDosNos();
    void desmarcaNos();
    void leArquivo(char nome[]);

    void insereArco(No* noOrigem, No* noDestino, uint id, bool atualizarGrau = true);
    void insereArcoID(uint idOrigem, uint idDestino, uint id, bool atualizarGrau = true);

    bool removeArco(uint idOrigem, uint idDestino);
    bool removeArco(No* noOrigem, No* noDestino, bool atualizarGrau = true);
    void removeArcos(No *no, bool atualizarGrau);
    void removeArcosLigadasAoNo(No *no, bool atualizarGrau);

    bool ehGrafoCompleto();
    bool ehGrafoKRegular(uint k);
    bool mesmaComponenteFortementeConexa(uint id1, uint id2);
    bool mesmaComponenteFortementeConexa(No *i1, No *i2);

    Grafo *subGrafoInduzido(uint E[], uint tam);

    uint* sequenciaGrau();

    bool saoAdjacentes(uint id1, uint id2);
    bool saoAdjacentes(No *no1, No *no2);

    uint numeroNosComponenteFortementeConexa(No *no);
    bool ehNoArticulacao(uint id);
    bool ehNoArticulacao(No* no);

    bool ehArcoPonte(uint id);
    bool ehArcoPonte(Arco* arco);

    bool ehFortementeConexo();
    uint rubustezVertice(uint *ids);
    uint rubustezAresta();

//    void percursoProfundidade(No *inicio, void(Grafo::*funcao)(No*) = NULL);
    void percursoProfundidade(No *inicio);
    void percursoIgnorandoArco(No *inicio, Arco *arcoIgnorado);

    Grafo* buscaProfundidade(No *no);
    Grafo* BuscaEmLargura(No *no);

    vector<No*> vizinhancaAberta(uint id, bool fechada = false);
    vector<No*> vizinhancaFechada(uint id, bool fechada = true);
    bool ehGrafoKRegular();

    Grafo* clone();

    vector<No*> ordenacaoTopologicaDAG();

    int numeroComponentesConexas();

    Arco* buscaArco(uint idOrigem, uint idDestino);
    Arco* buscaArco(No* noOrigem, No* noDestino);
    Arco* buscaArco(uint id);

    Dijkstra* dijkstra(No* origem);
    Dijkstra* dijkstra(uint origem);
    double dijkstra(uint origem, uint destino);
    double dijkstra(No* origem, No* destino);

    double** algoritmoFloyd();
    double consultaMenorCaminhoEntreDoisNos(uint i, uint j);

    vector<Arco*> algorimoPrim();

    /**
    Retorna o subgrafo (ou floresta de subgrafos se o grafo nao e não-conexo)
    contendo as arestas de peso minimo que ligam todos os nos do grafo
    que formam a arvore/floresta
    */
    vector<Arco*> Kruskal();

    Grafo* produtoCartesiano(Grafo* B);

    vector<No*> fechamentoTransitivoDireto(uint id);
    void precursoFechamentoIndireto(No *no, vector<No*> fechamentoDireto, vector<No*> fechamentoIndireto);
    vector<No*> fechamentoTransitivoIndireto(uint id);

    bool ehGrafoConexo();
    bool ehGrafoEuleriano();

    /// Criacoes de grafos mais comuns
    virtual Grafo* novoGrafo(uint ordem) = 0;
//    virtual Grafo* grafoCompleto(uint n);
//    virtual Grafo* grafoCircular(uint n);
//    virtual Grafo* grafoEscadinha(uint n);

    virtual ~Grafo(){};
};

#endif // DIGRAFO_H_INCLUDED
