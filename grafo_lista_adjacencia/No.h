#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED


class Arco;

class No
{
private:
    unsigned int id;
    unsigned int grau, grauEntrada, grauSaida;
    No *proxNo;
    Arco *listaNos;
    bool marcado;///se o no esta marcado ou nao(util na busca em profundidade)
    double peso;
public:
    No(unsigned int id);

    unsigned int getGrau(){ return grau;    };
    void setGrau(int grau){    this->grau = grau;};

    unsigned int getGrauEntrada(){ return grauEntrada;    };
    void setGrauEntrada(int grauEntrada){    this->grauEntrada = grauEntrada;};

    unsigned int getGrauSaida(){ return grauSaida;    };
    void setGrauSaida(int grauSaida){    this->grauSaida = grauSaida;};

    double getPeso(){   return peso;};
    void setPeso(double peso){  this->peso = peso;};

    unsigned int getID(){   return this->id;    };
    void setID(double id){  this->id = id;  };

    No *getProxNo(){    return this->proxNo;    };
    void setProxNo(No *proxNo){this->proxNo=proxNo; };

    void setListaArcos(Arco *listaNos){ this->listaNos=listaNos;    };
    Arco *getListaArcos(){  return this->listaNos;    };

    void insereArco(No* noDestino, unsigned int id);

    void removeArcos();

    void setMarcado(bool marcado){  this->marcado=marcado;  };
    bool getMarcado(){  return this->marcado;   };

    bool ehAdjacente(No *no);

    double hashing(unsigned int id);

    void imprime();
    ~No(){};
};


#endif // NO_H_INCLUDED
