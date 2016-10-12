#include <iostream>
#include "Grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <limits.h>
//#include "Aresta.h"


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

int main(){
    ///descomenta pra testar a inserção de 100.000 nos e arestas
//    unsigned int tam=100000;
//    cout<<"numero de nos e arestas:"<<endl;
////    cin>>tam;
//    geraArquivoDeEntrada(tam);
//    Grafo *di= new Grafo();
//    char nome[]={"data.g"};
//    di->leArquivo(nome);
//

    ///testar na mao
    unsigned int n_nos;
    cout<<"numero de nos(gerar em escadinha de forma cadaga):"<<endl;
    cin>>n_nos;
    Grafo *di= new Grafo();
    for(unsigned int i=0;i<n_nos;i++)
        di->insereNo(i);
    for(unsigned int i=0;i<n_nos;i++){
        for(unsigned int j=n_nos-1;j>0;j--){
            if(i!=j)di->insereArestaPorID(i+j+1,i,j);
        }
    }
    di->imprime();
    int i,j;
    Grafo *induzido;
    unsigned int v[3]={1,2,3};
    while(true){
//        cout<<"remover aresta de:";
//        cin>>i;
//        cout<<"para:";
//        cin>>j;
//        di->imprime();
//        cout<<" o grafo e completo?"  <<di->verificarSeGrafoECompleto()<<"   (0= nao completo, 1=completo)"<<endl;
//        cout<<"os nos:"<<i <<" e "<< j <<" estao na mesma componente fortemente conexa?"<<di->verificarSeDoisNosPorIDEstaoNaMesmaComponenteConexa(i,j)<<endl;
//        di->removeArestaPorID(i,j);
//        di->imprime();
        induzido=di->retornaSubGrafoInduzido(v, 3);
        cout<<" grafo induzido:"<<endl;
        induzido->imprime();
        system("pause");
    }



    ///teste de leitura de instancias do stenio
//    Grafo *di=new Grafo();
//    char nome[50];
//    for(int i=1;i<=16;i++){
//        if(i<=8)sprintf(nome, "instancias/grafo_1000_%d.txt", i);
//        else sprintf(nome, "instancias/grafo_10000_%d.txt", i%9+1);
//        di->leArquivo(nome);
//        cout<<" arquivo:"<<nome<<" lido com sucesso!"<<endl;
//        cout<<" o grafo e completo?"  <<di->verificarSeGrafoECompleto()<<"   (0= nao completo, 1=completo)"<<endl;
//        system("pause");
////        cin>>i;
////        cout<<"O no:"<<i<<" tem grau:"<<di->buscaNoPorID(i)->getGrau()<<endl;
////        system("pause");
////        for(int i=1;i<=10000;i++)
////            di->removeNoPorID(i);
////        system("pause");
//    }
    return 0;
}
