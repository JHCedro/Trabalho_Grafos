#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED


class Aresta;

class No
{
private:
    unsigned int id;
    No *proxNo;
    Aresta *arco;
    bool marcado;///se o no esta marcado ou nao(util na busca em profundidade)
    unsigned int grau;
    double peso;
public:
    No(unsigned int id){this->id=id; proxNo=0; arco=0; grau=0; peso=0; this->marcado=false;};
    unsigned int getGrau(){return grau;};
    double getPeso(){return peso;};
    void alteraGrau(int i){grau+=i;};///    QUE PORRA E ESSA
    void setGrau(int i){grau=i;};
    void imprime();
    ///gets
    unsigned int getID(){return this->id;};
    No *getProxNo(){return this->proxNo;};
    ///sets
    void setProxNo(No *proxNo){this->proxNo=proxNo;};
    void setAresta(Aresta *arco){this->arco=arco;};
    Aresta *getAresta(){return this->arco;};
    void removeArestas();
    void insereAresta(No* noDestino, unsigned int id);
    void setMarcado(bool marcado){this->marcado=marcado;};
    bool getMarcado(){return this->marcado;};
    ~No(){};
};


#endif // NO_H_INCLUDED
