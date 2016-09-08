#include <iostream>
#include "DiGrafo.h"
//#include "Arco.h"

#define n_nos 7

using namespace std;

int main(){
    DiGrafo *di=new DiGrafo();

    for(int i=1;i<=7;i++)
        di->insereNo(i);

    di->insereArco('a', 1, 2);
    di->insereArco('b', 1, 7);
    di->insereArco('c', 1, 6);
    di->insereArco('d', 7, 6);
    di->insereArco('e', 7, 4);
    di->insereArco('f', 5, 4);
    di->insereArco('g', 3, 5);
    di->insereArco('h', 4, 3);
    di->insereArco('i', 2, 4);
    di->insereArco('j', 2, 3);


    /*
    c = new char[3];  c[0]='A';   c[1]='B';   c[2]='C';
    id_adjacentes = new unsigned int[3];    id_adjacentes[0]=2; id_adjacentes[1]=7; id_adjacentes[2]=6;
    di->insereArco(1, id_adjacentes, c, 3);
    delete c; delete id_adjacentes;

    c = new char[2];  c[0]='J';   c[1]='I';
    id_adjacentes = new unsigned int[2];    id_adjacentes[0]=3; id_adjacentes[1]=4;
    di->insereArco(2, id_adjacentes, c, 2);
    delete c; delete id_adjacentes;

    c = new char[1];  c[0]='G';
    id_adjacentes = new unsigned int[1];    id_adjacentes[0]=5;
    di->insereArco(3, id_adjacentes, c, 1);
    delete c; delete id_adjacentes;

    c = new char[1];  c[0]='H';
    id_adjacentes = new unsigned int[1];    id_adjacentes[0]=3;
    di->insereArco(4, id_adjacentes, c, 1);
    delete c; delete id_adjacentes;

    c = new char[1];  c[0]='F';
    id_adjacentes = new unsigned int[1];    id_adjacentes[0]=4;
    di->insereArco(5, id_adjacentes, c, 1);
    delete c; delete id_adjacentes;


    ///o nó 6 não possui arcos saindo de sí

    c = new char[2];  c[0]='E';   c[1]='D';
    id_adjacentes = new unsigned int[2];    id_adjacentes[0]=4; id_adjacentes[1]=6;
    di->insereArco(7, id_adjacentes, c, 2);
    delete c; delete id_adjacentes;


    */
    di->imprime();
    unsigned int i,j;
    while(true){
        cout<< "no a ser removido:";
        cin>>i;
        di->removeNoPorID(i);
        cout<< "\n\n apos remocao\n" <<endl;
        di->imprime();


        cout<< "no de origem do vertice a ser removido:";
        cin>>i;
        cout<< "no de destino do vertice a ser removido:";
        cin>>j;
        di->removeArco(i, j);
        cout<< "\n\n apos remocao\n" <<endl;
        di->imprime();

    }
    return 0;
}
