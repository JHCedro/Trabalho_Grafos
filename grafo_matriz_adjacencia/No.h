#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

using namespace std;

class No{
    private:
        unsigned int id, peso;
    public:
        No(unsigned int id, unsigned int peso){
            this->id=id;
            this->peso = peso;
        };

        //void imprime();
        unsigned int getID(){   return this->id;    };
        void setID(unsigned int id){    this->id = id;    };

        unsigned int getPeso(){   return this->peso;    };
        void setPeso(unsigned int peso){    this->peso= peso;    };

        ~No(){};
    protected:
};



#endif // NO_H_INCLUDED
