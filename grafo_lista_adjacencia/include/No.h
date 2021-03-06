#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include "Arco.h"

typedef unsigned int uint;

class Arco;

class No
{
protected:
    uint id;
    uint grau, grauEntrada, grauSaida;
    Arco *it;  ///iterador (it) para lista de arcos
    uint idArvore;///id para auxiliar no algoritmo de Kruskal
    uint nivel; ///(caso grafo seja arvore)
    bool marcado, terminal;///se o no esta marcado ou nao(util na busca em profundidade)
    double peso;
public:
    No(uint id);

    bool ehTerminal(){return terminal;};
    void setTerminal(bool terminal){this->terminal=terminal;};

    uint getIdArvore(){return idArvore;};
    void setIdArvore(unsigned id){this->idArvore=id;};

    uint getNivel(){ return nivel;    };
    void setNivel(uint nivel){    this->nivel = nivel;};

    uint getGrau(){ return grau;    };
    void setGrau(uint grau){    this->grau = grau;};

    uint getGrauEntrada(){ return grauEntrada;    };
    void setGrauEntrada(uint grauEntrada){    this->grauEntrada = grauEntrada;};

    uint getGrauSaida(){ return grauSaida;    };
    void setGrauSaida(uint grauSaida){    this->grauSaida = grauSaida;};

    double getPeso(){   return peso;};
    void setPeso(double peso){  this->peso = peso;};

    uint getID(){   return this->id;    };
    void setID(uint id){  this->id = id;  };

    void atualizaGrau();

    ///funcoes de iteracao na lista de arcos
    virtual void itInicio() = 0;
    virtual Arco* getIt() = 0;
    virtual void itProx() = 0;
    virtual bool itEhFim() = 0;

    virtual Arco* buscaArco(No* noDestino) = 0;
    virtual Arco* buscaArco(uint noDestino) = 0;
    virtual Arco* insereArco(No* noDestino, uint id, double peso) = 0;
    virtual bool removeArco(uint id) = 0;
    virtual bool removeArco(No* noDestino) = 0;

    virtual void removeArcos() = 0;

    void setMarcado(bool marcado){  this->marcado=marcado;  };
    bool getMarcado(){  return this->marcado;   };

    bool ehAdjacente(No *no);
    void imprimirDetelhado(bool direcionado);
    void imprimir(bool direcionado);

    virtual ~No(){};
};

#endif // NO_H_INCLUDED
