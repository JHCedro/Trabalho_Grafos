#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include "Arco.h"

typedef unsigned int uint;

class Arco;

class No
{
private:
    uint id;
    uint grau, grauEntrada, grauSaida;
    No *proxNo;
    Arco *listaArcos, *it;  ///iterador (it) para lista de arcos
    uint idArvore;///id para auxiliar no algoritmo de Kruskal
    uint nivel; ///(caso grafo seja arvore)
    bool marcado;///se o no esta marcado ou nao(util na busca em profundidade)
    double peso;
public:
    No(uint id);

    uint getIdArvore(){return idArvore;};
    void setIdArvore(unsigned id){this->idArvore=id;};

    uint getNivel(){ return nivel;    };
    void setNivel(int nivel){    this->nivel = nivel;};

    uint getGrau(){ return grau;    };
    void setGrau(int grau){    this->grau = grau;};

    uint getGrauEntrada(){ return grauEntrada;    };
    void setGrauEntrada(int grauEntrada){    this->grauEntrada = grauEntrada;};

    uint getGrauSaida(){ return grauSaida;    };
    void setGrauSaida(int grauSaida){    this->grauSaida = grauSaida;};

    double getPeso(){   return peso;};
    void setPeso(double peso){  this->peso = peso;};

    uint getID(){   return this->id;    };
    void setID(double id){  this->id = id;  };

    No *getProxNo(){    return this->proxNo;    };
    void setProxNo(No *proxNo){this->proxNo=proxNo; };

    void setListaArcos(Arco *listaArcos){ this->listaArcos=listaArcos;    };
    Arco *getListaArcos(){  return this->listaArcos;    };

    ///funcoes de iteracao na lista de arcos
    void itInicio();
    Arco* getIt();
    void itProx();

    void insereArco(No* noDestino, uint id);

    void removeArcos();

    void setMarcado(bool marcado){  this->marcado=marcado;  };
    bool getMarcado(){  return this->marcado;   };

    bool ehAdjacente(No *no);

    double hashing(uint id);

    void imprime();
    ~No(){};
};
/*
class NoArv : public No{
private:
    uint nivel;
public:
    NoArv(uint id) : No(id){
        this->nivel = -1;
    };

    uint getNivel(){return nivel;};
    void setNivel(unsigned nivel){this->nivel=nivel;};
    ~NoArv(){};
};
*/

#endif // NO_H_INCLUDED
