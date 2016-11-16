#ifndef AUXILIARES_H_INCLUDED
#define AUXILIARES_H_INCLUDED
#include "Grafo.h"
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

using namespace std;

bool buscaVetor(u_int j, u_int aux[], u_int tam){
    cout<<"busca:"<<j<<endl;
    for(u_int y=0; y<tam; y++){
        if(aux[y]==j)
            return true;
    }
    return false;
}

void geraArquivoDeEntrada(u_int tam){
    cout<<"GERACAO DE ARQUIVO DE ENTRADA"<<endl;
    u_int i,j,porcento=0;
    ofstream arq;
    arq.open("data.g");
    arq<<tam<<endl;
    for(u_int k=0; k< tam; k++){
        if( (int)(100.0 * k/tam) > porcento ){
            porcento = (int)(100.0 * k/tam);
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
void persisteDesempenho(double* tempos, u_int n, u_int passo, u_int amostra, string titulo, string nomeArq){
    cout<<"\nSalvando desempenho"<<endl;
    ofstream arq;
    arq.open(nomeArq.c_str());
    arq << titulo << "amostra: " << amostra << endl;
    arq << "n; tempo\n";
    for(u_int i=0; i< n; i+=passo){
        arq << i << ";" << tempos[i/passo] << endl;
    }
    arq.close();
}

/**
* Analisa desempenho de funcao(i) para i = 0, passo, 2*passo... i < n
* Retorna vetor de tempos médio para cada (i) obtido da média de (amostras)
*/
double* analiseDesempenho(u_int(*funcao)(u_int), u_int n, u_int passo, u_int amostra){
    cout<<"\nTeste de desempenho" <<endl;
    double *tempos = new double[n/passo];
    u_int t;
    u_int porcento;
    for (u_int i=0; i<n; i+=passo){
        t = 0;
        printf("\nn=%d \tamostras=", i);
        for (u_int j=0; j < amostra; j++){
            cout << j << ' ';
            t += funcao(i);
        }
        tempos[i/passo] = (double) t/(CLOCKS_PER_SEC*amostra);
        printf("\tclocks= %d \t tempo= %fs", t, tempos[i/passo]);
    }

    return tempos;
}

/**
* Analisa desempenho e persiste em (nomeArq)
*/
double* analiseDesempenho(u_int(*funcao)(u_int), u_int n, u_int passo, u_int amostra,  string titulo, string nomeArq){
    double* tempos = analiseDesempenho(funcao, n, passo, amostra);
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


/** retorna grafo escadinha com n vertices */
Grafo* grafoEscadinha(u_int n){
    Grafo* G= new Grafo();
    vector<No*> nos;
    for(u_int i=0; i < n; i++){
        nos.push_back(G->insereNo(i));
        for (u_int j=0; j < i; j++)
            G->insereArco(nos.back(), nos[j], i+j, false);
    }
    G->atualizaGrau();
    return G;
}

Grafo* criarGrafoEscadinha(){
    u_int n_nos;
    cout << "numero de nos(gerar em escadinha de forma cadaga):" << endl;
    cin >> n_nos;
    Grafo *G = grafoEscadinha(n_nos);
    G->imprime();

    return G;
}

Grafo* grafoCompleto(u_int n){
    Grafo* G= new Grafo();
    vector<No*> nos;
    for(u_int i=0; i < n; i++)
        nos.push_back(G->insereNo(i));

    for (u_int i=0; i < n; i++){
        for (u_int j=0; j < n; j++){
            if( i != j )
                G->insereArcoID(i, j, i*n+j, false);
//                G->insereArco(nos[i], nos[j], i*n+j, false);
        }
    }
    G->atualizaGrau();
    return G;
}

Grafo* criarGrafoCompleto(){
    u_int n_nos;
    cout << "numero de nos(gerar grafo completo):" << endl;
    cin >> n_nos;
    Grafo *G = grafoCompleto(n_nos);
    G->imprime();

    return G;
}

Grafo* grafoCircular(u_int n){
    Grafo* G= new Grafo();
    No *aux, *primeiro, *ultimo;
    primeiro = ultimo = G->insereNo(0);
    for(u_int i=1; i < n; i++){
        aux = G->insereNo(i);
        G->insereArco(ultimo, aux, 2*i);
        G->insereArco(aux, ultimo, 2*i+1);
        ultimo = aux;
    }
    if(ultimo != primeiro){
        G->insereArco(ultimo, primeiro, 2*n);
        G->insereArco(primeiro, ultimo, 2*n+1);
    }

    G->atualizaGrau();
    return G;
}

Grafo* grafoDuardo(){
    /// GrafoDuardo.png
    Grafo *di=new Grafo();
    for(int i=1;i<=8;i++)
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


#endif // AUXILIARES_H_INCLUDED
