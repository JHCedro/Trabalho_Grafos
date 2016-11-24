#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED
#include <iostream>
#include <stdlib.h>

using namespace std;
typedef unsigned int uint;

template<class T> class THash{
private:
    T *tabela;
    uint insercoes, colisoes;
    uint tam, alocados, removidos;

    ///Iterador da tabela
    uint it;

    ///Elemento nulo e elemento Removido:
    T NULO, RM;
    ///funcoes de hash
    uint (*funcaoHash)(uint, uint);
    uint (*funcaoReHash)(uint, uint);

    /// funcao getID do objeto (T)
    uint (*getID)(T);
public:
    THash(uint tam, T NULO, T RM);

    uint getInsercoes(){    return insercoes;   };
    uint getColisoes(){     return colisoes;    };

    void setFuncaoHash(uint (*funcao)(uint, uint));
    void setFuncaoReHash(uint (*funcao)(uint, uint));
    void setGetID(uint (*funcao)(T));

    T getIt();
    void itInicio();
    void itProx();
    bool itEhFim();

    T buscar(uint id);
    uint buscarPos(uint id);
    bool inserir(T obj);
    bool remover(uint id);
    void imprimir();

    static bool IsPrime(uint number);
    static uint NextPrime(uint a);

    ~THash();
};

/// DEVERIA ESTAR EM "Hashing.cpp":
/// NAO SEI PORQUE NAO FUNCIONA SE ESTIVER LA

template<class T>
THash<T>::THash(uint tam, T NULO, T RM){
    this->NULO = NULO;
    this->RM = RM;
//    this->tam = this->NextPrime(tam);
    this->tam = (tam);
    this->insercoes = 0;
    this->colisoes = 0;
    tabela = new T[tam];
    for (uint i = 0; i < tam; i++)
        tabela[i] = NULO;
    alocados = 0;
    removidos = 0;

    ///FUNCOES DEFAULT ### MUDAR
    this->funcaoHash = NULL;
    this->funcaoReHash = NULL;
    this->getID = NULL;
//    this->iguais = NULL;
}

template<class T>
void THash<T>::setFuncaoHash(uint (*funcao)(uint, uint)){
    this->funcaoHash = funcao;
}

template<class T>
void THash<T>::setFuncaoReHash(uint (*funcao)(uint, uint)){
    this->funcaoReHash = funcao;
}

template<class T>
void THash<T>::setGetID(uint (*funcao)(T)){
//    if(T == NULO)
//        return -1;
//    if(T == RM)
//        return -2;
    this->getID = funcao;
}

template<class T>
bool THash<T>::IsPrime(uint number){
    if (number == 2 || number == 3)
        return true;

    if (number % 2 == 0 || number % 3 == 0)
        return false;

    uint divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number){
        if (number % (divisor - 1) == 0)
            return false;

        if (number % (divisor + 1) == 0)
            return false;

        divisor += 6;
    }

    return true;
}

template<class T>
uint THash<T>::NextPrime(uint a){
    while (!IsPrime(++a)){ }
    return a;

}
//template<class T>
//void THash<T>::iguais(uint (*funcao)(T, T)){
//    this->getID = funcao;
//}

template<class T>
bool THash<T>::inserir(T obj){
    if(alocados+removidos < tam){
        uint cont = 1;
        uint pos = funcaoHash(getID(obj), tam);
//        printf("\npos: %d\t tem %d\n", pos, tabela[pos]);
        while(tabela[pos] != NULO){
            pos = (pos+funcaoReHash(getID(obj), tam))%tam;
//            printf("\npos: %d\t tem %d\n", pos, tabela[pos]);
            cont++;
            if (cont == tam){
                cout << "\nLoop infinito na insercao!\n";
                return false;
            }
        }
        tabela[pos] = obj;
        alocados++;
        insercoes++;
        colisoes += cont - 1;
        return true;
    }
    else{
        cout << "\nTabela cheia!\n";
        return false;
    }
}

template<class T>
uint THash<T>::buscarPos(uint id){
//    cout<< "\nBuscando: " << id << endl;
    uint cont = 1; /// contar posicoes testadas
    uint pos = funcaoHash(id, tam);
//    printf("\npos: %d\t tem %d\n", pos, getID(tabela[pos]));
    while(tabela[pos] != NULO && getID(tabela[pos]) != id){
        pos = (pos+funcaoReHash(id, tam))%tam;
//        printf("\npos: %d\t tem %d\n", pos, getID(tabela[pos]));
        cont++;
        if (cont == tam){
            cout << "\nLoop infinito na busca!\n";
            return -1;
        }
    }
    if (tabela[pos] == NULO){
        cout << "\nObjeto inexixtente";
        return -1;
    }

//    cout << "\nreturn pos"<< pos <<endl;
    return pos;
}

template<class T>
T THash<T>::buscar(uint id){
    uint pos = this->buscarPos(id);
    if(pos != (uint) -1);
        return tabela[pos];
    return NULO;
}

/**
* Remocao preguicosa!!
*/
template<class T>
bool THash<T>::remover(uint id){
    uint pos = buscarPos(id);
    if(pos == (uint) -1)
        return false;
    tabela[pos] = RM;
    alocados--;
    removidos++;

    return true;
//    uint proxPos = (pos+funcaoReHash(obj, tam))%tam;
//    while(tabela[proxPos] != NULO){
//        tabela[pos] = tabela[proxPos];
//        pos = proxPos;
//        proxPos = (proxPos+funcaoReHash(obj, tam))%tam;
////        printf("\npos: %d\t tem %d\n", pos, tabela[pos]);
////        cont++;
////        if (cont == tam){
////            cout << "\nLoop infinito na insercao!\n";
////            return;
////        }
//    }
//    tabela[pos] = NULO;
//    n--;
}

template<class T>
T THash<T>::getIt(){
    return tabela[it];
}

template<class T>
void THash<T>::itInicio(){
    this->it = 0;
    if(tabela[it] == NULO || tabela[it] == RM)
        this->itProx();
}

template<class T>
void THash<T>::itProx(){
    it++;
    while(it < tam && (tabela[it] == NULO || tabela[it] == RM)){
        it++;
    }
}

template<class T>
bool THash<T>::itEhFim(){
    return it == tam;
}

template<class T>
void THash<T>::imprimir(){
    cout << "\n[";
    for (uint i = 0; i < tam; i++){
        if(tabela[i] == NULO)
            cout << "_" << ", ";
        else if(tabela[i] == RM)
            cout << "*" << ", ";
        else
            cout << tabela[i]->getID() << ", ";
    }
    cout << "]" << endl;
}

template<class T>
THash<T>::~THash(){
    delete [] tabela;
    delete NULO;
    delete RM;
}

#endif // HASHING_H_INCLUDED
