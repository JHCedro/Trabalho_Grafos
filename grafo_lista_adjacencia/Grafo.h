#ifndef DIGRAFO_H_INCLUDED
#define DIGRAFO_H_INCLUDED
#include "No.h"
#include "Arco.h"
#include "Dijkstra.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
typedef uint uint;
struct Dijkstra;

class Grafo
{
private:
    No *listaNos, *it;  /// iterador (it) para lista de nos
    uint grau;          /// maior grau de v�rtice do grafo
    uint numeroNos;     /// n
    uint numeroArcos;   /// m
    uint contAux;       /// contador auxiliar
    bool flagDir;       /// flag indicando se o grafo � direcionado ou n�o
    int auxEhNoArticulacao(No* no);
    void auxBuscaProfundidade(No *no, No* noArv, Grafo* Arv);
    vector<vector<No*>> auxRetornarComponentesConexas(No* no,vector<vector<No*>> componentes, int num);
//    void incrementaContador(No* n);
    void atualizaDist(No* u, map<uint, No*> Q, map<uint, double> distancias);
public:
    Grafo();
    No *getListaNos(){return this->listaNos;};
    uint getGrau(){     return grau;    };
    uint getNumeroNos(){    return numeroNos;   };
    uint getNumeroArcos(){    return numeroArcos;   };
    bool getFlagDir(){  return flagDir; };
    void setFlagDir(bool flag){ flagDir=flag;   };
    uint getContAux(){  return contAux; };
    void setContAux(uint i){ contAux=i;   };

    ///funcoes de iteracao na lista de nos
    void itInicio(){ this->it = listaNos;   };
    No* getIt(){   return this->it;         };
    void itProx(){  it = it->getProxNo();   };
    bool itEhFim(){   return (it == NULL);  };

//    void leDataArquivo(char nome[]);

    No* buscaNo(uint id);
    No* insereNo(uint id);
    void removeNo(uint id);

    void imprime();

    void atualizaGrau();
    void atualizaGrausEntradaSaidaDosNos();
    void desmarcaNos();
    void leArquivo(char nome[]);

    void insereArco(No* noOrigem, No* noDestino, uint id, bool atualizarGrau = true);
    void insereArcoID(uint idOrigem, uint idDestino, uint id, bool atualizarGrau = true);

    void removeArco(uint idOrigem, uint idDestino);
    void removeArco(No* noOrigem, No* noDestino, bool atualizarGrau = true);
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
    vector<vector<No*>> retornarComponentesConexas();

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
    Retorna o subgrafo (ou floresta de subgrafos se o grafo nao e n�o-conexo)
    contendo as arestas de peso minimo que ligam todos os nos do grafo
    que formam a arvore/floresta
    */
    vector<Arco*> Kruskal();

    Grafo* produtoCartesiano(Grafo* B);

    vector<No*> fechamentoTransitivoDireto(uint id);
    void precursoFechamentoIndireto(No *no, vector<No*> fechamentoDireto, vector<No*> fechamentoIndireto);
    vector<No*> fechamentoTransitivoIndireto(uint id);

    bool ehGrafoConexo();   /// <------------------------ MELHORAR
    bool ehGrafoEuleriano();

    ~Grafo();
};

/*
class Arvore : public Grafo{
public:
    Arvore() : Grafo(){}
    NoArv* insereNo(NoArv* pai, uint id);
};*/

#endif // DIGRAFO_H_INCLUDED
