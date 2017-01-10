#include "Auxiliares.h"
#include "GrafoHash.h"
#include "GrafoLista.h"
#include "MenuTrabalho.h"
#include "Testes.h"
//#define TESTE

using namespace std;

int main(int args, char **argv){
    #ifndef TESTE
    if(args > 1)
        /// se existem argumentos para testar desempenho das heuristicas
        desempenhoHeuristicas(args, argv);
    else
        /// exibir o menu do trabalho
        new MenuTrabalho();
    #else
    testesAvulsos();
    #endif // TESTE

    return 0;
}
