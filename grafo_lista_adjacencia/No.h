#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED


class Arco;

class No
{
private:
    unsigned int id;
    No *proxNo;
    Arco *arco;
public:
    No(unsigned int id){this->id=id;proxNo=0;arco=0;};
    void imprime();
    ///gets
    unsigned int getID(){return this->id;};
    No *getProxNo(){return this->proxNo;};
    ///sets
    void setProxNo(No *proxNo){this->proxNo=proxNo;};
    void setArco(Arco *arco){this->arco=arco;};
    Arco *getArco(){return this->arco;};
    ~No(){};
};


#endif // NO_H_INCLUDED
