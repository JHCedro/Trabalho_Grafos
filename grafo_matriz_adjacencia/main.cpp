#include <iostream>
#include "DiGrafo.h"

using namespace std;

int main(){
    DiGrafo* G = new DiGrafo();
    for (int i=0; i < 5; i++){
        G->inserirNo(new No(i, 2*i-i+3));
    }
    G->imprimeMatriz();
    return 0;
}
