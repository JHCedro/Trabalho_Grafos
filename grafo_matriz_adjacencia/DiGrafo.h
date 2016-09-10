#ifndef DIGRAFO_H_INCLUDED
#define DIGRAFO_H_INCLUDED
#include "string"
#include "No.h"

using namespace std;

class DiGrafo{
    private:
        unsigned int **M;   ///matriz de adjacencias
        unsigned int num_nos, num_arestas;
        No** nos; ///vetor de ponteiros para nos
    public:
        DiGrafo();
        DiGrafo(string arq_entrada);

        /***funcao tem que ser revista
            sobre construtor do no, id, do no ou no no grafo... essas coisas*/
        void inserirNo(No* novo_no);
        void removerNo(No* no);
        void removerNo(unsigned int id);

        void setArco(unsigned int a, unsigned int b, unsigned int peso);
        void removeArco(unsigned int a, unsigned int b);

        No* buscarNo(unsigned int id);

        void imprimeMatriz();

        ~DiGrafo();
    protected:
};

/**Aloca dinamicamente uma matriz M(n x n)
*  e retorna M
*/
/*unsigned int** novaMatriz(unsigned int n){
    unsigned int **M = new unsigned int *[n];
    for (int i=0; i < n; i++){
        M[i] = new unsigned int [n];
        for (int j=0; j < n; j++){
            M[i][j] = 0;
        }
    }
    return M;
}*/

#endif // DIGRAFO_H_INCLUDED
