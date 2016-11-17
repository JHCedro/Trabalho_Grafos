#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include "Arco.h"
//#include "../Circulo.h"

typedef unsigned int u_int;

class Arco;
class Circulo;

class No
{
private:
    u_int id;
    u_int grau, grauEntrada, grauSaida;
    No *proxNo;
    Arco *listaArcos, *it;  ///iterador (it) para lista de arcos
    u_int idArvore;///id para auxiliar no algoritmo de Kruskal
    u_int nivel; ///(caso Grafo seja arvore)
    bool marcado;///se o no esta marcado ou nao(util na busca em profundidade)
    double peso;
    Circulo* noCG;
public:
    No(u_int id);

    u_int getIdArvore(){return idArvore;};
    void setIdArvore(unsigned id){this->idArvore=id;};

    u_int getNivel(){ return nivel;    };
    void setNivel(int nivel){    this->nivel = nivel;};

    u_int getGrau(){ return grau;    };
    void setGrau(int grau){    this->grau = grau;};

    u_int getGrauEntrada(){ return grauEntrada;    };
    void setGrauEntrada(int grauEntrada){    this->grauEntrada = grauEntrada;};

    u_int getGrauSaida(){ return grauSaida;    };
    void setGrauSaida(int grauSaida){    this->grauSaida = grauSaida;};

    double getPeso(){   return peso;};
    void setPeso(double peso){  this->peso = peso;};

    u_int getID(){   return this->id;    };
    void setID(double id){  this->id = id;  };

    No *getProxNo(){    return this->proxNo;    };
    void setProxNo(No *proxNo){this->proxNo=proxNo; };

    void setListaArcos(Arco *listaArcos){ this->listaArcos=listaArcos;    };
    Arco *getListaArcos(){  return this->listaArcos;    };

    ///funcoes de iteracao na lista de arcos
    void itInicio();
    Arco* getIt();
    void itProx();

    void insereArco(No* noDestino, u_int id);

    void removeArcos();

    void setMarcado(bool marcado){  this->marcado=marcado;  };
    bool getMarcado(){  return this->marcado;   };

    bool ehAdjacente(No *no);

    double hashing(u_int id);

    void setCirculo(Circulo* C){    this->noCG = C;}
    Circulo* getCirculo(){  return this->noCG;     }

    void imprime();
    ~No(){};
};
/*
class NoArv : public No{
private:
    u_int nivel;
public:
    NoArv(u_int id) : No(id){
        this->nivel = -1;
    };

    u_int getNivel(){return nivel;};
    void setNivel(unsigned nivel){this->nivel=nivel;};
    ~NoArv(){};
};
*/

#endif // NO_H_INCLUDED
