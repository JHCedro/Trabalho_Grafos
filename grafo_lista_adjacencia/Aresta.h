#ifndef ARCO_H_INCLUDED
#define ARCO_H_INCLUDED
#include "No.h"

class Aresta
{
private:
    unsigned int id;
    Aresta *proxAresta;
    No *paraOnde;
    double peso;
public:
    Aresta(unsigned int id){this->id=id; proxAresta=0; paraOnde=0; peso=0;};
    double getPeso(){return peso;};
    unsigned int getID(){return this->id;};
    Aresta *getProxAresta(){return this->proxAresta;};
    No *getParaOnde(){return this->paraOnde;};
    void setParaOnde(No *no){this->paraOnde=no;};
    void setProxAresta(Aresta *arc){this->proxAresta=arc;};
    ~Aresta(){};
};


#endif // ARCO_H_INCLUDED
