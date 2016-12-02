#ifndef ARCO_H_INCLUDED
#define ARCO_H_INCLUDED
#include <stdio.h>
#include <iostream>
#include "No.h"

class No;
typedef unsigned int uint;

class Arco{
private:
    uint id;
    Arco *proxArco;
    No *noOrigem, *noDestino;
    double peso;
    bool marcado;
public:
    Arco(uint id){
        this->id=id;
        this->proxArco=0;
        this->noDestino=0;
        this->peso=0;
    };

    bool getMarcado(){  return marcado; };
    void setMarcado(bool marcado){  this->marcado=marcado;  };

    double getPeso(){   return peso;    };
    void setPeso(double peso){  this->peso = peso;};

    uint getID(){   return this->id;    };

    Arco *getProxArco(){    return this->proxArco;  };
    void setProxArco(Arco *arc){    this->proxArco=arc; };

    No *getNoDestino(){ return this->noDestino; };
    void setNoDestino(No *no){  this->noDestino=no; };

    No *getNoOrigem(){ return this->noOrigem; };
    void setNoOrigem(No *no){  this->noOrigem=no; };

    void imprimir();

    ~Arco(){};
};

#endif // ARCO_H_INCLUDED
