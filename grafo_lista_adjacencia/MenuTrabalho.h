#ifndef MENUTRABALHO_H
#define MENUTRABALHO_H
//#include "../Auxiliares.h"
#include "GrafoLista.h"
#include "GrafoHash.h"

typedef unsigned short usint;

class MenuTrabalho{
    private:
        vector<pair<Grafo*, string>> grafos;
        Grafo* grafoSelecionado;
        string nomeGrafoSelecionado;
        usint posGrafoSelecionado;
        vector<string> instanciasSteiner;
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
        /** 12 */ void carregarInstanciaSteiner();
        /**  0 */ void sair();

        /** TODO (jhcedro#1#14-12-2016): Listar e impelemtar chamada das funcoes pedidas na descricao do trabalho */
        /// FUNCOES DO GRAFO
        /**  1   void exibirFuncoes(); */
        /**  2 */ void imprimir();
        /**  3 */ void inserirVertice();
        /**  4 */ void removeVertive();
        /**  5 */ void inserirArco();
        /**  6 */ void removerArco();
        /**  7 */ void grau();
        /**  8 */ void grauNo();
        /**  9 */ void ehKRegular();
        /** 10 */ void ehCompleto();
        /** 11 */ void nosSaoAdjacentes();
        /** 12 */ void buscaProfundidade();
        /** 13 */ void buscaLargura();
        /** 14 */ void ehConexo();
        /** 15 */ void nosMesmaComponenteConexa();
        /** 16 */ void noEhArticulacao();
        /** 17 */ void arestaEhPonte();
        /** 18 */ void vizinhancaNo();
        /** 19 */ void fechamentoTransitivo();
        /** 20 */ void ordenacaoTopologica();
        /** 21 */ void caminhoMinimo();
        /** 22 */ void djikstra();
        /** 23 */ void floyd();
        /** 24 */ void subGrafoInduzido();
        /** 25 */ void componentesConexas();
        /** 26 */ void produtoCartesiano();
        /** 27 */ void prim();
        /** 28 */ void kruskal();
        /** 29 */ void ehKConexo();
        /** 30 */ void ehEuleriano();

        /// FUNCOES DA ARVORE DE STEINER
        /** 31 */ void gulosoSteiner();
        /** 32 */ void gulosoRandomizadoSteiner();
        /** 33 */ void gulosoRandomizadoReativoSteiner1();
        /** 34 */ void gulosoRandomizadoReativoSteiner2();


        ~MenuTrabalho();
    protected:

};

#endif // MENUTRABALHO_H
