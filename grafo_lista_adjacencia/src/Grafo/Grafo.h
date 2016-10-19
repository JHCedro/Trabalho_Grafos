#ifndef DIGRAFO_H_INCLUDED
#define DIGRAFO_H_INCLUDED
#include "No.h"
#include "Arco.h"
#include <iostream>

class Grafo
{
private:
    No *listaNos;
    unsigned int grau;///maior grau de vértice do grafo
    unsigned int numeroNos;///n
    unsigned int numeroArcos;///m
    bool flagDir;///flag indicando se o grafo é direcionado ou não
    bool auxMesmaComponenteConexa(No *i1, No *i2);
public:
    Grafo();
    No* getListaNos(){  return this->listaNos;  };
    unsigned int getGrau(){     return grau;    };
    unsigned int getNumeroNos(){    return numeroNos;   };
    unsigned int getNumeroArcos(){    return numeroArcos;   };
    bool getFlagDir(){  return flagDir; };
    void setFlagDir(bool flag){ flagDir=flag;   };

    void leDataArquivo(char nome[]);

    No* buscaNo(unsigned int id);
    No* insereNo(unsigned int id);
    void removeNo(unsigned int id);

    void imprime();

    void atualizaGrau();
    void desmarcaNos();
    void leArquivo(char nome[]);

    void insereArco(No* noOrigem, No* noDestino, unsigned int id, bool atualizarGrau);
    void insereArco(unsigned int idOrigem, unsigned int idDestino, unsigned int id);

    void removeArco(unsigned int idOrigem, unsigned int idDestino);
    void removeArco(No* noOrigem, No* noDestino, bool atualizarGrau);
    void removeArcos(No *no, bool atualizarGrau);
    void removeArcosLigadasAoNo(No *no, bool atualizarGrau);


    bool ehGrafoCompleto();
    bool ehGrafoKReguar(unsigned int k);
    bool mesmaComponenteConexa(unsigned int id1, unsigned int id2);
    bool mesmaComponenteConexa(No *i1, No *i2);

    Grafo *subGrafoInduzido(unsigned int E[], unsigned int tam);

    unsigned int* sequenciaGrau();

    bool saoAdjacentes(unsigned int id1, unsigned int id2);
    bool saoAdjacentes(No *no1, No *no2);

    bool ehNoArticulacao(unsigned int id);
    bool ehNoArticulacao(No* no);
    int auxEhNoArticulacao(No* no);

    ~Grafo();
};

#endif // DIGRAFO_H_INCLUDED
