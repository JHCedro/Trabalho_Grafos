#ifndef MENUTRABALHO_H
#define MENUTRABALHO_H
//#include "../Auxiliares.h"
#include "GrafoLista.h"
#include "GrafoHash.h"
#define pastaSaidas "Saidas/"

typedef unsigned short usint;

class MenuTrabalho{
    private:
        vector<pair<Grafo*, string>> grafos;
        Grafo* grafoSelecionado;
        string nomeGrafoSelecionado;
        usint posGrafoSelecionado;
        vector<string> instanciasSteiner;
        vector<string> instanciasArcoPonderados;
        vector<string> instanciasArcoNaoPonderados;

        vector<string> nomeOpcoes, nomeFuncoes;
//        vector<pair<void(MenuTrabalho::*)(void), string>> opcoesMenu;
    public:
        MenuTrabalho();
        /**  1 */ void exibirOpcoes();
                  void escolherOpcao();
        /**  2 */ void exibirFuncoes();
                  void escolherFuncao();
        /**  3 */ void novoGrafo(bool exemplo = false);
        /**  4 */ void novoGrafoExemplo();
        /**  5 */ void listarGrafos();
        /**  6 */ void selecionarGrafo();
        /**  7 */ void mostrarSelecionado();
        /**  8 */ void deletarGrafo();
        /**  9 */ void listarInstanciasSteiner();
        /** 10 */ void listarInstanciasStenio();
        /** 11 */ void carregarInstanciaStenio();
        /** 12 */ void resolverInstanciaSteiner();
        /**  0 */ void sair();

        /// FUNCOES DO GRAFO
        /**  1   void exibirFuncoes(); */
        /**  2 */ void imprimir();
        /**  3 */ void inserirVertice();
        /**  4 */ void removeVertive();
        /**  5 */ void inserirArco();
        /**  6 */ void removerArco();
        /**  7 */ void grau();
        /**  8 */ void grauNo();
        /**  9 */ void sequenciaGrau();
        /** 10 */ void ehKRegular();
        /** 11 */ void ehCompleto();
        /** 12 */ void nosSaoAdjacentes();
        /** 13 */ void buscaProfundidade();
        /** 14 */ void buscaLargura();
        /** 15 */ void ehConexo();
        /** 16 */ void nosMesmaComponenteConexa();
        /** 17 */ void noEhArticulacao();
        /** 18 */ void arestaEhPonte();
        /** 19 */ void vizinhancaNo();
        /** 20 */ void fechamentoTransitivo();
        /** 21 */ void ordenacaoTopologica();
        /** 22 */ void caminhoMinimo();
        /** 23 */ void djikstra();
        /** 24 */ void floyd();
        /** 25 */ void subGrafoInduzido();
        /** 26 */ void componentesConexas();
        /** 27 */ void produtoCartesiano();
        /** 28 */ void prim();
        /** 29 */ void kruskal();
        /** 30 */ void ehKConexo();
        /** 31 */ void ehEuleriano();

        /// FUNCOES DA ARVORE DE STEINER
        /** 32 */ void heuristicaSteiner(Grafo *G, uint *infoTerminais = NULL);

        /// Auxiliares
        vector<string> listarArquivos(string pasta);
        Grafo* carregarInstanciaStenio(string nomeArq, bool arcoPonderado, bool GHash);
        uint* carregarInstanciaSteiner(string nomeArq, Grafo* &G, bool GHash);
        void salvarArvore(Grafo *G, string nome);
        void salvarGrafo(vector<Arco*> arcos, string nome);
        void salvarGrafo(Grafo *G, string nome);
        void adcionarGrafo(Grafo *G);

        ~MenuTrabalho();
    protected:

};

#endif // MENUTRABALHO_H
