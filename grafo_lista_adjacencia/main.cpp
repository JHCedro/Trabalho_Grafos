#include <iostream>
#include "DiGrafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
//#include "Arco.h"

#define n_nos 7

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
    bool print;
    unsigned int k;
    while(true){
        cout<<"GERAR ARQUIVO DE ENTRADA COM QUANTOS VALORES:"<<endl;
        cin>>k;
        cout<<endl<<endl<<endl;
        geraArquivoDeEntrada(k);

        DiGrafo *di=new DiGrafo();
        char nome[]={"data.g"};
        di->leDataArquivo(nome);
        //di->imprime();
        cout<<endl<<endl<<endl;
        delete di;
        cout<<"DESEJA IMPRIMIR GRAFO?(1 para sim e 0 para nao)"<<endl;
        cin>>print;
        if(print){
            di->imprime();
            system("pause");
            system("cls");
        }
        else
            system("cls");
    }
    return 0;
}
