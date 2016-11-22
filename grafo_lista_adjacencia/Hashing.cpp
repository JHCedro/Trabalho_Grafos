#include "Hashing.h"
#include <iostream>

using namespace std;
//template class THash<int>;

//template<class T>
//uint THash<T>::funcao1(T obj){
//    return (obj)%tam;
//}
//
//template<class T>
//THash<T>::THash(uint tam, T NULO){
//    this->NULO = NULO;
//    this->tam = tam;
//    tabela = new T[tam];
//    for (uint i = 0; i < tam; i++)
//        tabela[i] = NULO;
//    n = 0;
//}
//
//template<class T>
//void THash<T>::inserir(T obj){
//    tabela[funcao1(obj)] = obj;
//}
//
//template<class T>
//void THash<T>::remover(T obj){
//    tabela[funcao1(obj)] = NULO;
//}
//
//template<class T>
//void THash<T>::imprimir(){
//    cout << "\n[";
//    for (uint i = 0; i < tam; i++)
//        cout << tabela[i] << ", ";
//    cout << "]" << endl;
//}
//
//template<class T>
//THash<T>::~THash(){
//    delete [] tabela;
//}
