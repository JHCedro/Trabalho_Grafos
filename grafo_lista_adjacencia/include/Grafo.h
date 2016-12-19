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
    uint grau;          /// maior grau de vertice do grafo
    uint numeroNos;     /// n
    uint numeroArcos;   /// m
    uint contAux;       /// contador auxiliar
    bool direcionado;       /// flag indicando se o grafo ehdirecionado ou nao
    uint maiorNivel;

    int auxEhNoArticulacao(No* no);
    void auxBuscaProfundidade(No *no, No* noArv, Grafo* Arv);
    vector<vector<No*>> auxRetornarComponentesConexas(No* no,vector<vector<No*>> componentes, int num);
    void atualizaDist(No* u, map<uint, No*> Q, map<uint, double> distancias);
    double mediaPesosArcos;
    bool auxKConexo(uint offset, int k, vector<No*> people, vector<No*> combination);
    bool verificaSeEhConexoSemOsNos(vector<No*> nos);
    vector<Arco*> auxGulosoRandomizadoSteiner(uint ids[], uint tam, double alpha, uint semente);

    ///funcoes de iteracao na lista de nos
public:
    Grafo(bool grafo_direcionado);
    uint getGrau(){     return grau;    };
    uint getNumeroNos(){    return numeroNos;   };
    uint getNumeroArcos(){    return numeroArcos;   };
    bool getdirecionado(){  return direcionado; };
    uint getContAux(){  return contAux; };
    void setContAux(uint i){ contAux=i;   };

    ///funcoes de iteracao na lista de nos
    virtual No* getIt() = 0;
    virtual void pushIt() = 0;
    virtual void popIt() = 0;
    virtual void itInicio() = 0;
    virtual void itProx() = 0;
    virtual bool itEhFim() = 0;

    virtual No* buscaNo(uint id) = 0;
    virtual No* insereNo(uint id) = 0;
    virtual bool removeNo(uint id) = 0;

    virtual void imprimir(bool detalhado = false);

    void atualizaGrau(bool completamente = false);
    void atualizaGrausEntradaSaidaDosNos();
    void desmarcaNos();
    void desmarcaArcos();
    void leArquivo(char nome[]);

    void insereArco(No* noOrigem, No* noDestino, uint id, bool atualizarGrau = true, double peso = 1.0);
    void insereArcoID(uint idOrigem, uint idDestino, uint id, bool atualizarGrau = true, double peso = 1.0);

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

    void percursoProfundidade(No *inicio);
    void percursoIgnorandoArco(No *inicio, Arco *arcoIgnorado);

    Grafo* buscaProfundidade(uint idNo);
    Grafo* buscaProfundidade(No *no);
    Grafo* buscaLargura(uint idNo);
    Grafo* buscaLargura(No *no);

    vector<No*> vizinhancaNo(uint id, bool fechada = false);
    vector<No*> vizinhancaAberta(uint id);
    vector<No*> vizinhancaFechada(uint id);
    bool ehGrafoKRegular();

    Grafo* clone();

    vector<No*> ordenacaoTopologicaDAG();

    int numeroComponentesConexas();
    vector<vector<No*>> retornarComponentesConexas();
    bool ehConexo();
    bool ehKConexo(int k);

    Arco* buscaArco(uint idOrigem, uint idDestino);
    Arco* buscaArco(No* noOrigem, No* noDestino);
    Arco* buscaArco(uint id);

    Dijkstra* algoritmoDijkstra(No* origem, bool imprimeSolucao = false);
    Dijkstra* algoritmoDijkstra(uint origem, bool imprimeSolucao = false);
    double menorCaminhoDijkstra(uint origem, uint destino);
    double menorCaminhoDijkstra(No* origem, No* destino);

    double** algoritmoFloyd();
    double menorCaminhoFloyd(uint idOrigem, uint idDestino);
    double consultaMenorCaminhoEntreDoisNos(uint i, uint j);

    vector<Arco*> algoritmoPrim();

    /**
    Retorna o subgrafo (ou floresta de subgrafos se o grafo nao e nao-conexo)
    contendo as arestas de peso minimo que ligam todos os nos do grafo
    que formam a arvore/floresta
    */
    vector<Arco*> algoritmoKruskal();

    Grafo* produtoCartesiano(Grafo* B);

    void precursoFechamentoIndireto(No *no, vector<No*> fechamentoDireto, vector<No*> fechamentoIndireto);
    vector<No*> fechamentoTransitivoDireto(uint id);
    vector<No*> fechamentoTransitivoIndireto(uint id);

    bool ehGrafoConexo();
    bool ehGrafoEuleriano();

    /// Criacoes de grafos mais comuns
    virtual Grafo* novoGrafo(uint ordem, bool direcionado) = 0;

    /// ----------------------------------------------
    /// Algoritmos para problema da Arvore de Steiner
    /// ----------------------------------------------
    double funcaoCriterio(Arco *a);
    void iniciaIdArvore();
    vector<pair<double, Arco*>> arcosAdjacentesDesmarcados(vector<No*> nos);
    vector<pair<double, Arco*>> arcosAdjacentesDesmarcados(No* no);
    static bool comparaCriterioSteiner(pair<double, Arco*> p1, pair<double, Arco*> p2);
    bool nosMesmaComponenteConexa(vector<No*> nos);

    void calculaMediaPesosArcos();
    void definirNivelNos();

    double gulosoSteiner(uint ids[], uint tam, bool imprimeSolucao = false);
    double gulosoRandomizadoSteiner(uint ids[], uint tam, double alpha, int num_iteracoes, bool imprimeSolucao = false);
    double gulosoRandomizadoReativoSteiner(uint ids[], uint tam, bool imprimeSolucao = false);
    double gulosoRandomizadoAdaptadoSteiner(uint ids[], uint tam, bool imprimeSolucao = false);
    vector<Arco*> podarArcosSteiner(vector<Arco*> solucao);
    void zeraGraus();
    void imprimirIdsArvore();
    void imprimirGraus();
    void zeraTerminais();
    uint *leituraIntanciaSteiner(string nome);
    /// ----------------------------------------------

    virtual ~Grafo(){};
};

#endif // DIGRAFO_H_INCLUDED
