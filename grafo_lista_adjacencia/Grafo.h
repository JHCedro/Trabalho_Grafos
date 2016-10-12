#ifndef DIGRAFO_H_INCLUDED
#define DIGRAFO_H_INCLUDED
#include "No.h"
#include "Aresta.h"
#include <iostream>

class Grafo
{
private:
    No *cabeca;
    unsigned int numeroNos;///n
    unsigned int numeroArestas;///m
    bool flagDir;///flag indicando se o grafo � direcionado ou n�o
    unsigned int grau;///maior grau de v�rtice do grafo
public:
    Grafo(){cabeca=NULL; grau=0; numeroArestas=0; numeroNos=0; flagDir=true;};
    unsigned int getNumeroNos(){return numeroNos;};
    unsigned int getNumeroArestas(){return numeroArestas;};
    bool getFlagDir(){return flagDir;};
    unsigned int getGrau(){return grau;};
    void setFlagDir(bool flag){flagDir=flag;};
    void atualizaGrau();
    void leDataArquivo(char nome[]);
    No *buscaNoPorPosicao(unsigned int pos);
    No *buscaNoPorID(unsigned int id);
    void removeNoPorID(unsigned int id);
    void removeArestaPorID(unsigned int deOnde, unsigned int paraOnde);
    void insereNo(unsigned int id);
    void insereArestaPorID(unsigned int id, unsigned int deOnde, unsigned int paraOnde);
    void imprime();
    void leArquivo(char nome[]);
    void removeArestasLigadasAoNo(No *no, bool atualizarGrau);
    void removeArestas(No *no, bool atualizarGrau);
    void removeAresta(No* deOnde, No* paraOnde, bool atualizarGrau);
    bool saoAdjacentes(unsigned int id1, unsigned int id2);
    bool saoAdjacentes(No *no1, No *no2);
    ~Grafo(){};
};

#endif // DIGRAFO_H_INCLUDED
