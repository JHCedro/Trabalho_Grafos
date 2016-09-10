#include "DiGrafo.h"
#include <iostream>

using namespace std;

DiGrafo::DiGrafo(){
    num_nos = 0;
    num_arestas = 0;
    M = NULL;
    nos = NULL;
}

DiGrafo::DiGrafo(string arq_entrada){
    /*
    M = new unsigned int *[n];
    for (int i=0; i < n; i++){
        M[i] = new unsigned int [n];
        for (int j=0; j < n; j++){
            M[i][j] = 0;
        }
    }*/
};


void DiGrafo::inserirNo(No* novo_no){
    /** IF GRAFO ESTIVER VAZIO **/
    if(num_nos == 0){

    }
    No** novo_vetor = new No*[num_nos+1];
    for (int i=0; i < num_nos; i++)
        novo_vetor[i] = nos[i];
    novo_vetor[num_nos] = novo_no;
    delete [] nos;
    nos = novo_vetor;

    unsigned int **nova_matriz = new unsigned int *[num_nos+1];
    for (int i=0; i < num_nos+1; i++){
        nova_matriz[i] = new unsigned int [num_nos+1];
        for (int j=0; j < num_nos+1; j++){
            if( i < num_nos && j < num_nos)
                nova_matriz[i][j] = M[i][j];
            else
                nova_matriz = 0;
        }
    }
    for (int i=0; i < num_nos; i++)
        delete [] M[i];
    delete [] M;
    M = nova_matriz;

    num_nos++;
}

void DiGrafo::removerNo(No* no){

}

void DiGrafo::removerNo(unsigned int id){
    removerNo(buscarNo(id));
}

No* DiGrafo::buscarNo(unsigned int id){
    for (int i=0; i < num_nos; i++){
        if(nos[i]->getID() != id)
            return nos[i];
    }

    return NULL;
}

void DiGrafo::setArco(unsigned int a, unsigned int b, unsigned int peso){
    M[a][b] = peso;
}

void DiGrafo::removeArco(unsigned int a, unsigned int b){
    M[a][b] = 0;
}



void DiGrafo::imprimeMatriz(){
    for (int i=0; i < num_nos; i++){
        cout << "[\t";
        for (int j=0; j < num_nos; j++){
            cout << j << "\t";
        }
        cout << "]\n";
    }
}

DiGrafo::~DiGrafo(){
    for (int i=0; i < num_nos; i++)
        delete [] M[i];
    delete [] M;
}
