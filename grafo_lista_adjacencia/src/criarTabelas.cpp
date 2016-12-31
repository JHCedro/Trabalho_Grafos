#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <dirent.h>
#include <stdio.h>

using namespace std;

vector<string> listarArquivosPasta(string nome){
    string pasta = nome;
    struct dirent *arquivo;
    DIR *dir = opendir(pasta.c_str());
    vector<string> arquivos;

    for(int i=0; arquivo = readdir(dir); i++){
        if(i>1)
            arquivos.push_back((string)arquivo->d_name);
    }
    return arquivos;
}

/** Cria e inicializa tabelas para analise de desempenho das heuristicas gulosas para Arvore de Steiner */
int main(){
    cout << "Inicializando tabelas:" << endl;
    string pasta = "Desempenho/Heuristicas/";
    string heuristicas[4] = { "Guloso", "Randomizado", "Adaptado", "Reativo" };
    vector<string> instancias = listarArquivosPasta("instanciasTestesSteiner");
    string arquivo;
    ofstream tabela;

    for (int p=1; p <= 6; p++){
        for (string instancia : instancias){
            arquivo = pasta + instancia + ".csv";
            cout << '\t' << arquivo << endl;
            tabela.open(arquivo.c_str());
            tabela << instancia << endl;
            tabela << "Semente;Guloso;;;Randomizado;;;Adaptado;;;Reativo" << endl;
            tabela << ";";
            for (int i=0; i < 4; i++)
                tabela << "Solucao;Tempo(s);Clocks;";
            tabela << endl;
            tabela.close();
        }
    }

    return 0;
}
