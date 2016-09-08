#ifndef DIGRAFO_H_INCLUDED
#define DIGRAFO_H_INCLUDED
#include "No.h"
#include "Arco.h"

class DiGrafo
{
private:
    No *cabeca;
public:
    DiGrafo(){cabeca=0;};
    No *buscaNoPorPosicao(unsigned int pos);
    No *buscaNoPorID(unsigned int id);
    void removeNoPorID(unsigned int id);
    void removeArco(unsigned int deOnde, unsigned int paraOnde);
    Arco *auxInsereArco(No *no, Arco *arc, unsigned int i, unsigned int id_no, unsigned int id_adjacentes[], char c[], int n_adjacentes);
    void insereNo(unsigned int id);
    void insereArco(char id, unsigned int deOnde, unsigned int paraOnde);
    void imprime();
    ~DiGrafo(){};
};

#endif // DIGRAFO_H_INCLUDED
