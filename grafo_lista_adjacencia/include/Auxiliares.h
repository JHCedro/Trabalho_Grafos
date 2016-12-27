#ifndef AUXILIARES_H_INCLUDED
#define AUXILIARES_H_INCLUDED
#include "GrafoLista.h"
#include "GrafoHash.h"
#include <iostream>
#include "Arco.h"
#include <vector>
#include <algorithm>
#include <time.h>
#include <string>
#include <fstream>
#include <random>
#include <chrono>
#include <stdio.h>
#include <dirent.h>
#define pastaDesempenho "Desempenho/"

using namespace std;
typedef unsigned short int usint;

bool buscaVetor(uint j, uint aux[], uint tam){
    cout<<"busca:"<<j<<endl;
    for(uint y=0; y<tam; y++){
        if(aux[y]==j)
            return true;
    }
    return false;
}

void geraArquivoDeEntrada(uint tam){
    cout<<"GERACAO DE ARQUIVO DE ENTRADA"<<endl;
    uint i,j,porcento=0;
    ofstream arq;
    arq.open("data.g");
    arq<<tam<<endl;
    for(uint k=0; k< tam; k++){
        if( (uint)(100.0 * k/tam) > porcento ){
            porcento = (uint)(100.0 * k/tam);
            cout<<"#";
        }
        i = k + 1;
        j = tam - k;
        arq<< i << " " << j << endl;
    }
    arq.close();
}

/**
* Persiste vetor de tempos em (nomeArq)
*/
void persisteDesempenho(double* tempos, uint n, uint passo, uint amostra, string titulo, string nomeArq){
    cout<<"\nSalvando desempenho"<<endl;
    ofstream arq;
    nomeArq = pastaDesempenho + nomeArq;
    arq.open(nomeArq.c_str());
    arq << titulo << "amostra: " << amostra << endl;
    arq << "n; tempo\n";
    for(uint i=0; i< n; i+=passo){
        arq << i << ";" << tempos[i/passo] << endl;
    }
    arq.close();
}

/**
* Analisa desempenho de funcao(i) para i = 0, passo, 2*passo... i < n
* Retorna vetor de tempos medio para cada (i) obtido da media de (amostras)
*/
double* analiseDesempenho(uint(*funcao)(uint, uint, bool), uint n, uint passo, uint amostra, bool Ghash){
    double *tempos = new double[n/passo];
    uint t;
    for (uint i=0; i<n; i+=passo){
        printf("\nn=%d \tamostra= %d", i, amostra);
        t = funcao(i, amostra, Ghash);

        tempos[i/passo] = (double) t/(CLOCKS_PER_SEC*amostra);
        printf("\tclocks= %d \t tempo= %fs", t, tempos[i/passo]);
    }

    return tempos;
}

/**
* Analisa desempenho e persiste em (nomeArq)
*/
double* analiseDesempenho(uint(*funcao)(uint, uint, bool), uint n, uint passo, uint amostra, bool Ghash, string titulo, string nomeArq){
    cout<< titulo << endl;
    double* tempos = analiseDesempenho(funcao, n, passo, amostra, Ghash);
    persisteDesempenho(tempos, n, passo, amostra, titulo, nomeArq);
    return tempos;
}

/**
* Gera graficos a partir de um (nomeArq) persistido
* Requer Python, matplotlib
*/
void graficoPython(string nomeArq, string versao = "python", string arg_plot=""){
    cout << "\nPlotando grafico (" + nomeArq + ")..." << endl;
    string args = versao + " plotDesempenho.py " + nomeArq + " " + arg_plot;
    system(args.c_str());
}

Grafo* criarGrafoEscadinha(bool GHash = false){
    uint n_nos;
    cout << "numero de nos(gerar em escadinha):" << endl;
    cin >> n_nos;

    Grafo *G;
    if(GHash)   G = GrafoHash::grafoEscadinha(n_nos);
    else        G = GrafoLista::grafoEscadinha(n_nos);

    G->imprimir();

    return G;
}

Grafo* criarGrafoCompleto(bool GHash = false){
    uint n_nos;
    cout << "numero de nos(gerar grafo completo):" << endl;
    cin >> n_nos;

    Grafo *G;
    if(GHash)   G = GrafoHash::grafoCompleto(n_nos);
    else        G = GrafoLista::grafoCompleto(n_nos);

    G->imprimir();

    return G;
}

Grafo* grafoExemplo(bool GHash = false){
    Grafo *di;
    if(GHash)   di = new GrafoHash(10);
    else        di = new GrafoLista();

    for(uint i=1;i<=8;i++)
        di->insereNo(i);

    di->insereArcoID(1,2,1);
    di->insereArcoID(2,1,1);

    di->insereArcoID(1,4,2);
    di->insereArcoID(4,1,2);

    di->insereArcoID(2,4,3);
    di->insereArcoID(4,2,3);

//    di->insereArcoID(2,3,4);
//    di->insereArcoID(3,2,4);
//
//    di->insereArcoID(3,4,5);
//    di->insereArcoID(4,3,5);

    di->insereArcoID(3,5,6);
    di->insereArcoID(5,3,6);

    di->insereArcoID(3,6,7);
    di->insereArcoID(6,3,7);

    di->insereArcoID(5,8,8);
    di->insereArcoID(8,5,8);

    di->insereArcoID(6,7,9);
    di->insereArcoID(7,6,9);

    di->insereArcoID(7,3,10);
    di->insereArcoID(3,7,10);

    di->insereArcoID(6,7,11);
    di->insereArcoID(7,6,11);

    return di;
}

vector<string> listarInstanciasSteiner(){
    string pasta = "instanciasTestesSteiner";
    struct dirent *arquivo;
    DIR *dir = opendir(pasta.c_str());
    vector<string> arquivos;

    for(uint i=0; arquivo = readdir(dir); i++){
        if(arquivo->d_name[0] != '.')
            arquivos.push_back(pasta + "/" + (string)arquivo->d_name);
    }

    return arquivos;
}

/**
RETORNA UM VETOR DE INTEIROS EM QUE A PRIMEIRA POSICAO Eh O NUMERO DE NOS TERMINAIS
AS DEMAIS POSICOES SAO OS IDS DOS TERMINAIS
Aloca o Grafo *G passado por referencia
*/
uint* leituraIntanciaSteiner(string nomeArq, Grafo *&G, bool GHash = false){
    ifstream entrada;
    entrada.open(nomeArq, ios::in);

    uint n_nos, n_arcos;

    string aux;
    entrada>>aux;
    while(((string)aux) != "SECTION"){
        entrada >> aux;
    }
    entrada >> aux;

    entrada>>aux>>n_nos;
    entrada>>aux>>n_arcos;
    ///insere todos os nos

    if(GHash) G = new GrafoHash(n_nos*1.5, false);
    else      G = new GrafoLista(false);

    for(uint i=1; i<=n_nos; i++)
        G->insereNo(i);

    ///indices de origem e destino dos arcos
    uint i, j;
    double peso;

    ///PERCORRER TODOS OS ARCOS DA ENTRADA
    for(int linha=0; linha<n_arcos; linha++){
        entrada >> aux >> i >> j >> peso;
        G->insereArcoID(i, j, 1, false, peso);
    }
    G->atualizaGrau();

    entrada>>aux>>aux>>aux>>aux;

    uint n_terminais, *infoTerminais;
    entrada>>n_terminais;

    infoTerminais = new uint[n_terminais + 1];
    infoTerminais[0] = n_terminais;

    ///leitura de terminais
    for(int linha=0; linha<n_terminais; linha++){
        entrada >> aux >>i;
        ///insere ids sempre uma posicao a frente pos na posicao 0 temos o numero de terminais
        infoTerminais[linha + 1] = i;
    }
    return infoTerminais;
}

///---------------------------------------------TESTES EMAIL DO STENIO------------------------------------------
/** argv = {instancia, heuristica, semente} */
int desempenhoHeuristicas(int args, char **argv){
//    for (int i=0; i < args; i++){
//        cout << i << " - " << argv[i] << endl;
//    }

    string arquivo = string(argv[1]);
    usint heuristica = atoi(argv[2]);    int semente = atoi(argv[3]);
    uint nTSementes = atoi(argv[4]);

    string heuristicas[3] = { "Guloso", "Randomizado", "Reativo" };
    ofstream tabela;

    /// Executar heuristicas
    cout << "arquivo: " << arquivo << endl;
    cout << "heuristica: " << heuristicas[heuristica-1] << endl;
    cout << "semente: " << semente << endl;

    Grafo* g = new GrafoLista(false);
    double solucao = INFINITY;
    uint * infoTerminais = leituraIntanciaSteiner(arquivo, g, false);

    unsigned long long tempo;
    tempo = clock();
    if(heuristica==1)
        solucao = g->gulosoSteiner(infoTerminais + 1, infoTerminais[0]);
    if(heuristica==2)
        solucao = g->gulosoRandomizadoSteiner(infoTerminais + 1, infoTerminais[0], 0.25, 30, semente);
    if(heuristica==3)
        solucao = g->gulosoRandomizadoReativoSteiner(infoTerminais + 1, infoTerminais[0], semente);    tempo = clock() - tempo;

    cout << "\n\t solucao: " << solucao << endl;

    /// Persistir resultados
    arquivo.erase(0, arquivo.find_last_of('\\')+1);


    char gambiarraParalela[10];
//    usint aux = semente%6;  cout << "aux: " << aux << endl;
//    if(aux == 0)  aux = 6;  cout << "aux: " << aux << endl;
    sprintf(gambiarraParalela, "%d/", (semente%6 == 0 ? 6 : semente%6));
    arquivo = "Desempenho/Heuristicas/" + (string)gambiarraParalela + arquivo + ".csv";
    cout << "salvando no arquivo: " << arquivo << endl << endl;

    tabela.open(arquivo, ofstream::out | ofstream::app);

    if(heuristica == 1)        tabela << semente << ";";
    tabela << solucao << ";" << (double) tempo / CLOCKS_PER_SEC << ";" << tempo << ";";
    if(heuristica == 3)        tabela << endl;

    tabela.close();
}
///---------------------------------------------TESTES EMAIL DO STENIO------------------------------------------


#endif // AUXILIARES_H_INCLUDED
