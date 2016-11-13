#ifndef ARCO_H_INCLUDED
#define ARCO_H_INCLUDED
#include "No.h"

class Arco
{
private:
    unsigned int id;
    Arco *proxArco;
    No *noOrigem, *noDestino;
    double peso;
public:
    Arco(unsigned int id){
        this->id=id;
        this->proxArco=0;
        this->noDestino=0;
        this->peso=0;
    };

    double getPeso(){   return peso;    };
    void setPeso(double peso){  this->peso = peso;};

    unsigned int getID(){   return this->id;    };

    Arco *getProxArco(){    return this->proxArco;  };
    void setProxArco(Arco *arc){    this->proxArco=arc; };

    No *getNoDestino(){ return this->noDestino; };
    void setNoDestino(No *no){  this->noDestino=no; };

    No *getNoOrigem(){ return this->noOrigem; };
    void setNoOrigem(No *no){  this->noOrigem=no; };

    ~Arco(){};
};

#endif // ARCO_H_INCLUDED
