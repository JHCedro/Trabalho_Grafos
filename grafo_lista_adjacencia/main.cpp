#include <iostream>
#include "Grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>


using namespace std;

bool buscaVetor(unsigned int j, unsigned int aux[], unsigned int tam){
    cout<<"busca:"<<j<<endl;
    for(unsigned int y=0; y<tam; y++){
        if(aux[y]==j)
            return true;
    }
    return false;
}

void geraArquivoDeEntrada(unsigned int tam){
    cout<<"GERACAO DE ARQUIVO DE ENTRADA"<<endl;
    unsigned int i,j,porcento=0;
    ofstream arq;
    arq.open("data.g");
    arq<<tam<<endl;
    for(unsigned int k=0; k< tam; k++){
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

/** retorna grafo escadinha com n vertices */
Grafo* grafoEscadinha(unsigned int n){
    Grafo* G= new Grafo();
    vector<No*> nos;
    for(unsigned int i=0; i < n; i++){
        nos.push_back(G->insereNo(i));
        for (unsigned int j=0; j < i; j++)
            G->insereArco(nos.back(), nos[j], i+j, false);
    }
    G->atualizaGrau();
    return G;
}

Grafo* criarGrafoEscadinha(){
    unsigned int n_nos;
    cout << "numero de nos(gerar em escadinha de forma cadaga):" << endl;
    cin >> n_nos;
    Grafo *G = grafoEscadinha(n_nos);
    G->imprime();

    return G;
}

Grafo* grafoCompleto(unsigned int n){
    Grafo* G= new Grafo();
    vector<No*> nos;
    for(unsigned int i=0; i < n; i++)
        nos.push_back(G->insereNo(i));

    for (unsigned int i=0; i < n; i++){
        for (unsigned int j=0; j < n; j++){
            if( i != j )
                G->insereArco(nos[i], nos[j], i*n+j, false);
        }
    }
    G->atualizaGrau();
    return G;
}

Grafo* criarGrafoCompleto(){
    unsigned int n_nos;
    cout << "numero de nos(gerar grafo completo):" << endl;
    cin >> n_nos;
    Grafo *G = grafoCompleto(n_nos);
    G->imprime();

    return G;
}

/** testes sucessivos de remove Arco e no em grafo escadinha */
void testeGeral(){
    unsigned int i, j;
    Grafo *di= criarGrafoEscadinha();

    while(true){
        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->removeArco(i,j);
        di->imprime();

        cout<<"remover no: ";   cin >> i;
        di->removeNo(i);
        system("pause");
    }
}

/** testar a inserção de 100.000 nos e Arcos */
void testarGrandeInsersao(){
    unsigned int tam = 100000;
    cout<<"numero de nos e Arcos:"<<endl;
    //    cin>>tam;
    geraArquivoDeEntrada(tam);
    Grafo *di= new Grafo();
    char nome[]={"data.g"};
    di->leArquivo(nome);
    delete di;
}

void testarGrafoCompleto(){
    unsigned int i, j;
    Grafo *di= criarGrafoCompleto();

    while(true){
        cout<<" o grafo " << (di->ehGrafoCompleto() ? "eh " : "nao eh ") << "completo"<<endl;
        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->imprime();
        di->removeArco(i,j);
    }
}

void testarGrafoInduzido(){
    unsigned int i, j;
    Grafo *induzido, *di= criarGrafoEscadinha();

    unsigned int v[3]={1,2,3};

    while(true){
        induzido = di->subGrafoInduzido(v, 3);
        cout<<" grafo induzido:"<<endl;
        induzido->imprime();

        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->removeArco(i,j);
        di->imprime();

        system("pause");
    }
}

void testarSequenciaNos(){
    Grafo *di= criarGrafoEscadinha();

    cout << "Sequencia de nos:\n\t";
    unsigned int* seq = di->sequenciaGrau();
    for (unsigned int i=0; i < di->getNumeroNos(); i++){
        cout << seq[i] << ", ";
    }
    delete di;
}

/** nao faco ideia do que isso ta fazendo */
void testarInstanciasStenio(){
    ///teste de leitura de instancias do stenio
    Grafo *di=new Grafo();
    char nome[50];
    for(int i=1;i<=16;i++){
        if(i<=8)sprintf(nome, "instancias/grafo_1000_%d.txt", i);
        else sprintf(nome, "instancias/grafo_10000_%d.txt", i%9+1);
        di->leArquivo(nome);
        cout<<" arquivo:"<<nome<<" lido com sucesso!"<<endl;
        cout<<" o grafo e completo?"  << di->ehGrafoCompleto()<<"   (0= nao completo, 1=completo)"<<endl;
        system("pause");
//        cin>>i;
//        cout<<"O no:"<<i<<" tem grau:"<<di->buscaNo(i)->getGrau()<<endl;
//        system("pause");
//        for(int i=1;i<=10000;i++)
//            di->removeNoPorID(i);
//        system("pause");
    }
}

int main(){
    ///testar na mao
//    testarGrandeInsersao();
//    testarGrafoCompleto();
//    testarGrafoInduzido();
    testarSequenciaNos();

//    testarInstanciasStenio();
    return 0;
}
