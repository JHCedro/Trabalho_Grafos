#ifndef ARCO_H_INCLUDED
#define ARCO_H_INCLUDED
#include "No.h"

class Arco
{
private:
    char id;
    Arco *proxArco;
    No *paraOnde;
public:
    Arco(char id){this->id=id; proxArco=0; paraOnde=0;};
    char getID(){return this->id;};
    Arco *getProxArco(){return this->proxArco;};
    No *getParaOnde(){return this->paraOnde;};
    void setParaOnde(No *no){this->paraOnde=no;};
    void setProxArco(Arco *arc){this->proxArco=arc;};
    ~Arco(){};
};


#endif // ARCO_H_INCLUDED
