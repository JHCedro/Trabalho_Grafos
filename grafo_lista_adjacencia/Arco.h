#ifndef ARCO_H_INCLUDED
#define ARCO_H_INCLUDED
#include <stdio.h>
#include <iostream>
#include "No.h"

class No;
typedef unsigned int u_int;

class Arco{
private:
    u_int id;
    Arco *proxArco;
    No *noOrigem, *noDestino;
    double peso;
public:
    Arco(u_int id){
        this->id=id;
        this->proxArco=0;
        this->noDestino=0;
        this->peso=0;
    };

    double getPeso(){   return peso;    };
    void setPeso(double peso){  this->peso = peso;};

    u_int getID(){   return this->id;    };

    Arco *getProxArco(){    return this->proxArco;  };
    void setProxArco(Arco *arc){    this->proxArco=arc; };

    No *getNoDestino(){ return this->noDestino; };
    void setNoDestino(No *no){  this->noDestino=no; };

    No *getNoOrigem(){ return this->noOrigem; };
    void setNoOrigem(No *no){  this->noOrigem=no; };

    void imprime();

    ~Arco(){};
};

#endif // ARCO_H_INCLUDED
