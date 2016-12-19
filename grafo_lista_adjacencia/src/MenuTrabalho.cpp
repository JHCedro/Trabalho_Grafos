#include "../include/MenuTrabalho.h"
#include "dirent.h"
#include <iostream>
#include <fstream>

using namespace std;

MenuTrabalho::MenuTrabalho(){
    grafoSelecionado = NULL;
//    opcoesMenu.push_back( make_pair(this->listarGrafos , "Listar Grafos") );

    /// buscando instancias da Arvore de Steiner
    try{ instanciasSteiner = listarArquivos("instanciasTestesSteiner"); }
    catch(int e){
        cout << "Instancias de Steiner nao encontradas!" << endl;   }

    /// buscando instancias de teste do Stenio
    try{ instanciasArcoNaoPonderados = listarArquivos("instancias/arcos_nao_ponderados"); }
    catch(int e){
        cout << "Instancias do teste com arcos nao ponderados nao encontradas!" << endl;    }

    try{ instanciasArcoPonderados = listarArquivos("instancias/arcos_ponderados");  }
    catch(int e){
        cout << "Instancias do teste com arcos ponderados nao encontradas!" << endl;}

    nomeOpcoes = vector<string>({
        " 1 - Exibir opcoes do menu",
        " 2 - Exibir funcoes de Grafo",
        " 3 - Novo grafo",
        " 4 - Novo grafo exemplo",
        " 5 - Listar grafos",
        " 6 - Selecionar grafo",
        " 7 - Mostrar grafo selecionado",
        " 8 - Deletar grafo selecionado",
        " 9 - Listar Instancias de Teste",
        "10 - Carregar Instancia de Teste",
        "11 - Listar Instancias da Arvore de Steiner",
        "12 - Resolver Instancia da Arvore de Steiner",
        " 0 - SAIR"
    });

    nomeFuncoes = vector<string>({
        " 1 - Exibir funcoes",
        " 2 - Imprimir",
        " 3 - Inserir vertice",
        " 4 - Remover vertice",
        " 5 - Inserir arco",
        " 6 - Remover arco",
        " 7 - Obter grau do grafo",
        " 8 - Obter grau de um vertice",
        " 9 - Obter sequencia de grau",
        "10 - Verificar se eh k-regular",
        "11 - Verificar se eh completo",
        "12 - Verificar se dois nos sao adjacentes",
        "13 - Percurso em profundidade",
        "14 - Percurso em largura",
        "15 - Verificar se eh conexo",
        "16 - Verificar se dois vertices estao na mesma componente conexa",
        "17 - Verificar se um vertice eh articulacao",
        "18 - Verificar se um arco eh ponte",
        "19 - Obter vizinhanca de um vertice",
        "20 - Obter fechamento transitivo",
        "21 - Obter ordenacao topologica",
        "22 - Obter caminho minimo entre dois vertices",
        "23 - Algoritmo de Djikstra",
        "24 - Algoritmo de Floyd",
        "25 - Obter subgrafo induzido por conjunto de vertices",
        "26 - Listar componentes conexas",
        "27 - Efetuar produto cartesiano com outro grafo",
        "28 - Algoritmo de Prim",
        "29 - Algoritmo de Kruskal",
        "30 - Verificar se eh k-conexo",
        "31 - Verificar se eh euleriano",
        "32 - Arvore de Steiner",
        " 0 - VOLTAR"
    });

    this->exibirOpcoes();
    this->escolherOpcao();
}

vector<string> MenuTrabalho::listarArquivos(string pasta){
    vector<string> arquivos;
    struct dirent *arquivo;
    DIR *dir = opendir(pasta.c_str());

    for(uint i=0; (arquivo = readdir(dir)); i++){
        if(arquivo->d_name[0] != '.')
            arquivos.push_back(string(arquivo->d_name));
    }

    return arquivos;
}

void MenuTrabalho::exibirOpcoes(){
    cout << "\n-----------------------------------------------------" << endl;
    cout << "Opcoes do menu:" << endl;
    for(string opcao :  nomeOpcoes)
        cout << "\t" << opcao << endl;
    cout << "-----------------------------------------------------" << endl;
}

void MenuTrabalho::escolherOpcao(){
    usint opcao;

    cout << "\n>> opcao menu (int): ";    cin >> opcao;

    while(opcao != 0){
        switch (opcao){
            case  1: this->exibirOpcoes();               break;
            case  2: this->exibirFuncoes();
                    if(grafoSelecionado != NULL){
                        this->escolherFuncao();
                     }                                   break;
            case  3: this->novoGrafo();                  break;
            case  4: this->novoGrafoExemplo();           break;
            case  5: this->listarGrafos();               break;
            case  6: this->selecionarGrafo();            break;
            case  7: this->mostrarSelecionado();         break;
            case  8: this->deletarGrafo();               break;
            case  9: this->listarInstanciasStenio();     break;
            case 10: this->carregarInstanciaStenio();    break;
            case 11: this->listarInstanciasSteiner();    break;
            case 12: this->resolverInstanciaSteiner();   break;

            default: cout << "Opcao invalida!" << endl;  break;
        }
        cout << "\n>> opcao menu (int): ";    cin >> opcao;
    }

    this->sair();
}

void MenuTrabalho::exibirFuncoes(){
    if(grafoSelecionado != NULL){
        ///listar funcoes do grafo
        cout << "\n-----------------------------------------------------" << endl;
        cout << "Funcoes do grafo selecionado:" << endl;
        for(uint i = 0; i < nomeFuncoes.size(); i++){
            /*
            if(i == 30)
                cout << "\n\t (Heuristicas para problema da Arvore de Steiner)" << endl;*/
            cout << "\t" << nomeFuncoes[i] << endl;
        }
        cout << "-----------------------------------------------------" << endl;
    }
    else{
        cout << "Nenhum grafo selecionado!" << endl;
    }
}

void MenuTrabalho::escolherFuncao(){
    usint funcao = 1;
    cout << "\n>> opcao grafo (int): ";     cin >> funcao;
    while(funcao != 0){
        switch (funcao){
            case  1: this->exibirFuncoes();                     break;
            case  2: this->imprimir();                          break;
            case  3: this->inserirVertice();                    break;
            case  4: this->removeVertive();                     break;
            case  5: this->inserirArco();                       break;
            case  6: this->removerArco();                       break;
            case  7: this->grau();                              break;
            case  8: this->grauNo();                            break;
            case  9: this->sequenciaGrau();                     break;
            case 10: this->ehKRegular();                        break;
            case 11: this->ehCompleto();                        break;
            case 12: this->nosSaoAdjacentes();                  break;
            case 13: this->buscaProfundidade();                 break;
            case 14: this->buscaLargura();                      break;
            case 15: this->ehConexo();                          break;
            case 16: this->nosMesmaComponenteConexa();          break;
            case 17: this->noEhArticulacao();                   break;
            case 18: this->arestaEhPonte();                     break;
            case 19: this->vizinhancaNo();                      break;
            case 20: this->fechamentoTransitivo();              break;
            case 21: this->ordenacaoTopologica();               break;
            case 22: this->caminhoMinimo();                     break;
            case 23: this->djikstra();                          break;
            case 24: this->floyd();                             break;
            case 25: this->subGrafoInduzido();                  break;
            case 26: this->componentesConexas();                break;
            case 27: this->produtoCartesiano();                 break;
            case 28: this->prim();                              break;
            case 29: this->kruskal();                           break;
            case 30: this->ehKConexo();                         break;
            case 31: this->ehEuleriano();                       break;

            case 32: this->heuristicaSteiner(grafoSelecionado); break;

            default: cout << "Funcao invalida!" << endl;        break;
        }

        cout << "\n>> opcao grafo (int): ";     cin >> funcao;
    }
}

void MenuTrabalho::novoGrafo(bool exemplo){
    usint opcaoGrafo;
    char opcaoDirecionado;
    bool direcionado;
    string nome;

    cout << "Escolha a estrutura do grafo:" << endl;
    cout << "\t 1 - Lista Encadeada de Ajdacencias" << endl;
    cout << "\t 2 - Tabela Hash de Ajdacencias" << endl;
    cout << ">> estrutura (int): ";
    cin >> opcaoGrafo;

    if(opcaoGrafo != 1 && opcaoGrafo != 2){
        cout << "Opcao invalida!" << endl;
    }else{
        cout << ">> Usar grafo direcionado? (s/n): ";
        cin >> opcaoDirecionado;
        direcionado = opcaoDirecionado == 's';

        Grafo* G = NULL;

        if(exemplo){
            usint opcaoExemplo;
            uint n;
            cout << "Escolha o grafo Exemplo:" << endl;
            cout << "\t 1 - Grafo Completo" << endl;
            cout << "\t 2 - Grafo Circular" << endl;
            cout << "\t 3 - Grafo \"Escada\"" << endl;
            cout << ">> exemplo (int): ";
            cin >> opcaoExemplo;

            cout << ">> numero de vertices (int): ";
            cin >> n;

            switch (opcaoExemplo){
            case 1:
                switch(opcaoGrafo){
                    case 1:   G = GrafoLista::grafoCompleto(n, direcionado);    break;
                    case 2:   G = GrafoHash::grafoCompleto(n, direcionado);     break;
                }   break;
            case 2:
                switch(opcaoGrafo){
                    case 1:   G = GrafoLista::grafoCircular(n, direcionado);    break;
                    case 2:   G = GrafoHash::grafoCircular(n, direcionado);     break;
                }   break;
            case 3:
                switch(opcaoGrafo){
                    case 1:   G = GrafoLista::grafoEscadinha(n, direcionado);    break;
                    case 2:   G = GrafoHash::grafoEscadinha(n, direcionado);     break;
                }   break;

            default:
                cout << "Exemplo invalido!" << endl;
                break;
            }
        }

        cout << ">> Escolha o nome do grafo (sem espacos): ";
        cin >> nome;

        if(!exemplo){
            switch (opcaoGrafo){
                case 1:
                    G = new GrafoLista(direcionado);
                    nome = "[LISTA]_" + nome;
                    break;

                case 2:
                    uint ordem;
                    cout << ">> Escolha a ordem de grandeza do grafo (quantidade de nos esperada - int): ";
                    cin >> ordem;
                    G = new GrafoHash(ordem, direcionado);
                    nome = "[HASH]_" + nome;
                    break;

                default:
                    cout << "Estrutura invalida!" << endl;
            }
        }

        if(G != NULL)
            grafos.push_back( make_pair(G, nome) );
    }
}

void MenuTrabalho::novoGrafoExemplo(){
    this->novoGrafo(true);
}

void MenuTrabalho::listarGrafos(){
    cout << "Lista de Grafos: " << endl;
    uint i = 1;
    for(auto p : grafos)
        cout << "\t" << i++ << " - " << p.second << endl;
}

void MenuTrabalho::selecionarGrafo(){
    usint i;
    cout << ">> Selecionar grafo (int): ";
    cin >> i;

    if(i > 0 && i <= grafos.size()){
        posGrafoSelecionado = i - (usint) 1;
        grafoSelecionado = grafos[posGrafoSelecionado].first;
        nomeGrafoSelecionado = grafos[posGrafoSelecionado].second;
        cout << "Grafo (" << nomeGrafoSelecionado << ") selecionado." << endl;
    }
    else
        cout << "Opcao invalida!" << endl;
}

void MenuTrabalho::mostrarSelecionado(){
    if(grafoSelecionado != NULL)
        cout << "Grafo selecionado: " << nomeGrafoSelecionado << endl;
    else
        cout << "Nenhum grafo selecionado!" << endl;
}

void MenuTrabalho::deletarGrafo(){
    if(grafoSelecionado != NULL){
        cout << "Deletando grafo " << nomeGrafoSelecionado << endl;
        delete grafoSelecionado;
        grafos.erase( grafos.begin() + posGrafoSelecionado );
        grafoSelecionado = NULL;
    }
    else
        cout << "Nenhum grafo selecionado!" << endl;
}

void MenuTrabalho::listarInstanciasSteiner(){
    usint i = 1;
    cout << "Instancias da Arvore de Steiner:" << endl;
    for(string instancia : instanciasSteiner)
        cout << "\t" << i++ << " - " << instancia << endl;
}

void MenuTrabalho::listarInstanciasStenio(){
    usint i = 1;
    cout << "\n Instancias sem arcos ponderados:" << endl;
    for(string instancia : instanciasArcoNaoPonderados)
        cout << "\t" << i++ << " - " << instancia << endl;

    i = 1;
    cout << "\n Instancias com arcos ponderados:" << endl;
    for(string instancia : instanciasArcoPonderados)
        cout << "\t" << i++ << " - " << instancia << endl;
}

void MenuTrabalho::resolverInstanciaSteiner(){
    /// escolher uma instancia para carregar em um grafo
    usint opcaoInstancia;
    cout << ">> Carregar instancia da Arvore de Steiner (int): ";
    cin >> opcaoInstancia;

    if(opcaoInstancia > 0 && opcaoInstancia <= instanciasSteiner.size()){
        Grafo *G;
        usint opcaoGrafo;
        string nomeInstancia = instanciasSteiner[opcaoInstancia - 1];
        cout << "Carregar instancia " << nomeInstancia << endl;

        cout << "Escolha a estrutura do grafo:" << endl;
        cout << "\t 1 - Lista Encadeada de Ajdacencias" << endl;
        cout << "\t 2 - Tabela Hash de Ajdacencias" << endl;
        cout << ">> estrutura (int): ";
        cin >> opcaoGrafo;

        if(opcaoGrafo == 1 || opcaoGrafo == 2){
            string nomeArq = "instanciasTestesSteiner/" + nomeInstancia;
            uint* infoTerminais = this->carregarInstanciaSteiner(nomeArq, G, opcaoGrafo != 1);
            this->heuristicaSteiner(G, infoTerminais);
        }else{
            cout << "Opcao invalida!" << endl;
        }
    }else{
        cout << "Opcao invalida!" << endl;
    }
}

void MenuTrabalho::carregarInstanciaStenio(){
    /// escolher uma instancia para carregar em um grafo
    usint tipoInstancia, opcaoInstancia;
    cout << "\t 1 - Instancias sem arcos ponderados" << endl;
    cout << "\t 2 - Instancias com arcos ponderados" << endl;
    cout << ">> tipo de instancia (int): ";     cin >> tipoInstancia;
    if(tipoInstancia == 1 || tipoInstancia == 2){
        string pasta = "instancias/";
        vector<string> instancias;
        if(tipoInstancia == 1){
            pasta += "arcos_nao_ponderados/";
            instancias = instanciasArcoNaoPonderados;
        }else{
            pasta += "arcos_ponderados/";
            instancias = instanciasArcoPonderados;
        }

        cout << ">> carregar instancia de teste (int): ";
        cin >> opcaoInstancia;

        if(opcaoInstancia > 0 && opcaoInstancia <= instancias.size()){
            Grafo *G;
            usint tipoGrafo;
            string nomeInstancia = instancias[opcaoInstancia - 1];

            cout << "Escolha a estrutura do grafo:" << endl;
            cout << "\t 1 - Lista Encadeada de Ajdacencias" << endl;
            cout << "\t 2 - Tabela Hash de Ajdacencias" << endl;
            cout << ">> estrutura (int): ";
            cin >> tipoGrafo;

            if(tipoGrafo == 1 || tipoGrafo == 2){
                string nomeArq = pasta + nomeInstancia;
                /// griar grafo
                G = carregarInstanciaStenio(nomeArq, tipoInstancia == 2, tipoGrafo == 2);
                string prefixo = ((tipoGrafo == 1) ? "[LISTA]_" : "[HASH]_");
                grafos.push_back( make_pair(G, prefixo + nomeInstancia) );
            }else
                cout << "Opcao invalida!" << endl;
        }else
            cout << "Opcao invalida!" << endl;
    }else
        cout << "Opcao invalida!" << endl;
}

void MenuTrabalho::sair(){
    delete this;
}

/// -------------------------------------------------------------------------#
/// -------------          PRINCIPAIS FUNCOES DO GRAFO          -------------#
/// -------------------------------------------------------------------------#

void MenuTrabalho::imprimir(){
    cout << "\n Imprimindo grafo:" << endl;
    char detalhadamente;
    cout << ">> \t Imprimir grafo detalhadamente? (s/n): \t";
    cin >> detalhadamente;

    cout << "Imprimindo " << nomeGrafoSelecionado << endl;
    grafoSelecionado->imprimir(detalhadamente == 's');
}

void MenuTrabalho::inserirVertice(){
    cout << "\n Inserindo vertice:" << endl;
    uint id, peso;
    cout << ">> id do vertice (int): ";     cin >> id;
    cout << ">> peso do vertice (int): ";   cin >> peso;
    grafoSelecionado->insereNo(id);
}

void MenuTrabalho::removeVertive(){
    cout << "\n Removendo vertice:" << endl;
    uint id;
    cout << ">> id do vertice (int): ";     cin >> id;
    grafoSelecionado->removeNo(id);
}

void MenuTrabalho::inserirArco(){
    cout << "\n Inserindo arco:" << endl;
    uint idArco, idOrigem,  idDestino, peso;
    cout << ">> id do vertice origem (int): ";     cin >> idOrigem;
    cout << ">> id do vertice destino (int): ";    cin >> idDestino;
    cout << ">> peso do arco (int): ";          cin >> peso;
    cout << ">> id do arco (int): ";          cin >> idArco;
    grafoSelecionado->insereArcoID(idOrigem, idDestino, idArco, true, peso);
}

void MenuTrabalho::removerArco(){
    cout << "\n Removendo arco:" << endl;
    uint idOrigem, idDestino;
    cout << ">> id do vertice origem (int): ";     cin >> idOrigem;
    cout << ">> id do vertice destino (int): ";    cin >> idDestino;
    grafoSelecionado->removeArco(idOrigem, idDestino);
}

void MenuTrabalho::grau(){
    cout << "\n Grau do grafo: "<< grafoSelecionado->getGrau() << endl;
}

void MenuTrabalho::grauNo(){
    cout << "\n Grau do vertice:" << endl;
    uint id;
    cout << ">> id do vertice (int): ";     cin >> id;
    No* no = grafoSelecionado->buscaNo(id);
    if(no != NULL)
        cout << "Vertice tem grau: " << no->getGrau();
    else
        cout << "Vertice nao encontrado!";
}

void MenuTrabalho::sequenciaGrau(){
    cout << "Sequencia de grau:" << endl;
    uint *sequencia = grafoSelecionado->sequenciaGrau();
    for (int i=0; i < grafoSelecionado->getNumeroNos(); i++){
        cout << "\t" << sequencia[i] << endl;
    }
}


void MenuTrabalho::ehKRegular(){
    cout << "\n Verificar k-regularidade:" << endl;
    uint k;
    cout << ">> k (int): ";     cin >> k;
    printf("Grafo%s eh %d-regular\n", (grafoSelecionado->ehGrafoKRegular(k) ? "" : " nao"), k);
}

void MenuTrabalho::ehCompleto(){
    printf("Grafo%s eh completo\n", (grafoSelecionado->ehGrafoCompleto() ? "" : " nao"));
}

void MenuTrabalho::nosSaoAdjacentes(){
    if(grafoSelecionado->getdirecionado())
        cout << "\t* Verificando adjacendia de grafo direcionado" << endl;

    cout << "\n Verificar vertices adjacentes:" << endl;
    uint id1, id2;

    cout << ">> id do vertice 1 (int): ";     cin >> id1;
    No* no1 = grafoSelecionado->buscaNo(id1);

    if( no1 == NULL )
        cout << "vertice 1 nao encontrado" << endl;
    else{
        cout << ">> id do vertice 2 (int): ";     cin >> id2;
        No* no2 = grafoSelecionado->buscaNo(id2);

        if( no2 == NULL )
            cout << "vertice 2 nao encontrado" << endl;
        else{
            printf("Vertices %d e %d%s sao adjacentes\n", id1, id2, (no1->ehAdjacente(no2) ? "" : " nao"));
        }
    }
}

void MenuTrabalho::buscaProfundidade(){
    cout << "\n Percurso em profundidade:" << endl;

    uint idRaiz;
    cout << ">> id vertice origem (int): "; cin >> idRaiz;
    Grafo *arv = grafoSelecionado->buscaProfundidade(idRaiz);

    string nomeArq = "percurso_profundidade_" + nomeGrafoSelecionado + ".arv";
    this->salvarArvore(arv, nomeArq);

    adcionarGrafo(arv);
}

void MenuTrabalho::buscaLargura(){
    cout << "\n Percurso em largura:" << endl;

    uint idRaiz;
    cout << ">> id vertice origem (int): "; cin >> idRaiz;
    Grafo *arv = grafoSelecionado->buscaLargura(idRaiz);

    string nomeArq = "percurso_largura_" + nomeGrafoSelecionado + ".arv";
    this->salvarArvore(arv, nomeArq);

    adcionarGrafo(arv);
}

void MenuTrabalho::ehConexo(){
    printf("Grafo%s eh conexo\n", (grafoSelecionado->ehConexo() ? "" : " nao"));
}

void MenuTrabalho::nosMesmaComponenteConexa(){
    cout << "\n Verificar vertices na mesma componente conexa:" << endl;
    uint id1, id2;

    cout << ">> id do vertice 1 (int): ";     cin >> id1;
    No* no1 = grafoSelecionado->buscaNo(id1);

    if( no1 == NULL )
        cout << "vertice 1 nao encontrado" << endl;
    else{
        cout << ">> id do vertice 2 (int): ";     cin >> id2;
        No* no2 = grafoSelecionado->buscaNo(id2);

        if( no2 == NULL )
            cout << "vertice 2 nao encontrado" << endl;
        else{
            bool resultado = grafoSelecionado->nosMesmaComponenteConexa( vector<No*>({no1, no2}) );
            printf("Vertices %d e %d%s estao na mesma componente conexa\n", id1, id2, (resultado ? "" : " nao"));
        }
    }
}

void MenuTrabalho::noEhArticulacao(){
    cout << "\n Verificar vertice de articulacao:" << endl;
    uint id;
    cout << ">> id do vertice (int): ";     cin >> id;
    No* no = grafoSelecionado->buscaNo(id);
    if(no != NULL)
        printf("Vertice %d%s eh articulacao\n", id, (grafoSelecionado->ehNoArticulacao(no) ? "" : " nao"));
    else
        cout << "Vertice nao encontrado!";
}

void MenuTrabalho::arestaEhPonte(){
    cout << "\n Verificar arco ponte:" << endl;
    uint id;
    cout << ">> id do arco  (int): ";     cin >> id;
    Arco* arco = grafoSelecionado->buscaArco(id);
    if(arco != NULL)
        printf("Arco %d%s eh ponte\n", id, (grafoSelecionado->ehArcoPonte(arco) ? "" : " nao"));
    else
        cout << "Arco nao encontrado!" << endl;
}

void MenuTrabalho::vizinhancaNo(){
    cout << "\n Obter vizinhanca do vertice:" << endl;
    uint id;
    char fechada;
    cout << ">> id do vertice (int): ";         cin >> id;
    No* no = grafoSelecionado->buscaNo(id);
    if(no != NULL){
        cout << ">> vizinhanca fechada? (s/n): ";   cin >> fechada;
        vector<No*> vizinhanca = grafoSelecionado->vizinhancaNo(id, (fechada == 's'));
        cout << "\tVizinhanca:" << endl;
        for(No* no : vizinhanca)
            cout << "\t\t" << no->getID() << endl;
    }
    else
        cout << "Vertice nao encontrado!";
}

void MenuTrabalho::fechamentoTransitivo(){
    cout << "\n Obter fechamento transitivo de um vertice:" << endl;
    uint id, fechamento;
    cout << "\t 1 - fechamento transitivo direto"   << endl;
    cout << "\t 2 - fechamento transitivo indireto" << endl;
    cout << ">> fechamento (int): ";         cin >> fechamento;
    cout << ">> id do vertice (int): ";      cin >> id;
    No* no = grafoSelecionado->buscaNo(id);
    if(no != NULL){
        vector<No*> nosFechamento;
        switch(fechamento){
        case 1 :
            nosFechamento = grafoSelecionado->fechamentoTransitivoDireto(id);
            cout << "\tFechamento transitivo direto:" << endl;
            break;
        case 2 :
            nosFechamento = grafoSelecionado->fechamentoTransitivoIndireto(id);
            cout << "\tFechamento transitivo indireto:" << endl;
            break;
        }
        for(No* no : nosFechamento)
            cout << "\t\t" << no->getID() << endl;
    }
    else
        cout << "Vertice nao encontrado!";
}

void MenuTrabalho::ordenacaoTopologica(){
    cout << "\n Obter ordenacao topologica de DAG:" << endl;
    vector<No*> ordTopologica = grafoSelecionado->ordenacaoTopologicaDAG();
    for(No* no : ordTopologica)
        cout << "\t\t" << no->getID() << endl;
}

void MenuTrabalho::caminhoMinimo(){
    cout << "\n Caminho minimo entre dois vertices:" << endl;
    uint id1, id2;
    usint algoritmo;
    cout << ">> id do vertice origem  (int): ";     cin >> id1;
    No* no1 = grafoSelecionado->buscaNo(id1);
    if( no1 == NULL )
        cout << "vertice origem nao encontrado" << endl;
    else{
        cout << ">> id do vertice destino (int): ";     cin >> id2;
        No* no2 = grafoSelecionado->buscaNo(id2);

        if( no2 == NULL )
            cout << "vertice destino nao encontrado" << endl;
        else{
            cout << "\t 1 - Usar algoritmo de Djikstra" << endl;
            cout << "\t 2 - Usar algoritmo de Floyd"    << endl;
            cout << ">> algoritmo (int): ";             cin >> algoritmo;
            double resultado = -1;
            if(algoritmo == 1){
                resultado = grafoSelecionado->menorCaminhoDijkstra(no1, no2);
                printf("\t Menor camminho entre (%d) e (%d) tem custo %f.\n", id1, id2, resultado);
            }else if(algoritmo == 2){
                resultado = grafoSelecionado->menorCaminhoFloyd(id1, id2);
                printf("\t Menor camminho entre (%d) e (%d) tem custo %f.\n", id1, id2, resultado);
            }else
                cout << "Opcao invalida!" << endl;
        }
    }
}

void MenuTrabalho::djikstra(){
    cout << "Algoritimo de Djikstra:" << endl;
    uint idOrigem;
    cout << ">> id do vertice origem  (int): ";     cin >> idOrigem;
    No* noOrigem = grafoSelecionado->buscaNo(idOrigem);
    if( noOrigem == NULL )
        cout << "vertice origem nao encontrado" << endl;
    else{
        Dijkstra *d = grafoSelecionado->algoritmoDijkstra(idOrigem, true);
        d->imprimirPercurso();
        cout << endl;
        delete d;
    }
}

void MenuTrabalho::floyd(){
    cout << "Algoritimo de Floyd:" << endl;
    double** distancias = grafoSelecionado->algoritmoFloyd();
    cout << "Distancias entre vertices:" << endl;
    uint n = grafoSelecionado->getNumeroNos();
    for (uint i = 0; i < n; i++){
        for (uint j = i+1; j < n; j--)
            printf("\t [%2d, %2d]: %f\n", i, j, distancias[i][j]);
    }
}

void MenuTrabalho::subGrafoInduzido(){
    cout << "Subgrafo induzido por conjunto de vertices:" << endl;
    uint nNos, *idNos;
    cout << ">> numero de vertices (int): ";    cin >> nNos;
    idNos = new uint[nNos];
    cout << ">> vertices (" << nNos << " x int): ";
    for (uint i = 0; i < nNos; i++){
        cin >> idNos[i];
    }
    Grafo *subGrafo = grafoSelecionado->subGrafoInduzido(idNos, nNos);

    string nomeArq = "subgrafo_induzido_" + nomeGrafoSelecionado + ".grafo";
    this->salvarGrafo(subGrafo, nomeArq);

    adcionarGrafo(subGrafo);

    delete [] idNos;
}

void MenuTrabalho::componentesConexas(){
    cout << "Obter componentes conexas:" << endl;
    vector<vector<No*>> componentes = grafoSelecionado->retornarComponentesConexas();
    uint i = 1;
    for(vector<No*> componente : componentes){
        cout << "Componente conexa " << i++ << ":" << endl;
        for(No* no : componente){
            cout << "\t" << no->getID() << endl;
        }
    }
}

void MenuTrabalho::produtoCartesiano(){
    cout << "Produto cartesiano:" << endl;
    usint grafoB;
    this->listarGrafos();

    cout << ">> efetuar produto cartesiano com (int): ";   cin >> grafoB;
    Grafo *B = grafos[ grafoB-1 ].first;
    string nomeGrafoB = grafos[ grafoB-1 ].second;

    cout << "efetuando produto cartesiano entre (" << nomeGrafoSelecionado << ") e (" << nomeGrafoB << ") " << endl;
    Grafo *C = grafoSelecionado->produtoCartesiano(B);

    string nomeArq = "produto_cartesiano_(" + nomeGrafoSelecionado + ")_x_(" + nomeGrafoB + ").grafo";
    salvarGrafo(C, nomeArq);
    adcionarGrafo(C);
}

void MenuTrabalho::prim(){
    cout << "Arvore geradora minima utilizando algoritmo de Prim:" << endl;
    vector<Arco*> AGM = grafoSelecionado->algoritmoPrim();

    string nomeArq = "AMG_Prim_" + nomeGrafoSelecionado + ".grafo";
    salvarGrafo(AGM, nomeArq);
}

void MenuTrabalho::kruskal(){
    cout << "Floresta geradora minima utilizando algoritmo de Kruskal:" << endl;
    vector<Arco*> AGM = grafoSelecionado->algoritmoKruskal();

    string nomeArq = "FMG_Kruskal_" + nomeGrafoSelecionado + ".grafo";
    salvarGrafo(AGM, nomeArq);
}

void MenuTrabalho::ehKConexo(){
    cout << "\n Verificar k-conexidade:" << endl;
    uint k;
    cout << ">> k (int): ";     cin >> k;
    printf("Grafo%s eh %d-conexo\n", (grafoSelecionado->ehKConexo(k) ? "" : " nao"), k);
}

void MenuTrabalho::ehEuleriano(){
    printf("Grafo%s eh euleriano\n", (grafoSelecionado->ehGrafoEuleriano() ? "" : " nao"));
}

///----------      FUNCOES DA ARVORE DE STEINER       ----------#

void  MenuTrabalho::heuristicaSteiner(Grafo *G, uint* infoTerminais){
    cout << "Problema da Arvore de Steiner: " << endl;
    usint heuristica;
    cout << "Selecione a heuristica a ser utilizada:" << endl;
    cout << "\t 1 - Algoritmo Guloso" << endl;
    cout << "\t 2 - Algoritmo Guloso Randomizado" << endl;
    cout << "\t 3 - Algoritmo Guloso Randomizado Reativo" << endl;
    cout << "\t 4 - Algoritmo Guloso Randomizado Adaptado" << endl;
    cout << ">> heuristica (int): ";    cin >> heuristica;

    if(heuristica < 1 || heuristica > 4){
        cout << "Opcao invalida!" << endl;
    }else{
        uint nTerminais, *idTerminais;
        double alpha;

        if(infoTerminais == NULL){
            /// caso  metodo nao tenha sido chamado por resolverInstanciaSteiner
            cout << ">> numero de vertices terminais (int): ";    cin >> nTerminais;
            idTerminais = new uint[nTerminais];

            cout << ">> vertices terminais (" << nTerminais << " x int): ";
            for (uint i = 0; i < nTerminais; i++)
                cin >> idTerminais[i];
        }else{
            nTerminais = infoTerminais[0];
            idTerminais = infoTerminais + 1;
        }

        if(heuristica == 2){
            cout << ">> alpha para randomizacao (double, [0 ... 1]): ";
            cin >> alpha;
        }

        char opImprimir;
        cout << ">> imprimir solucao? (s/n): ";    cin >> opImprimir;

        double resultado;
        switch(heuristica){
        case 1: resultado = G->gulosoSteiner(idTerminais, nTerminais, (opImprimir == 's'));                          break;
        case 2: resultado = G->gulosoRandomizadoSteiner(idTerminais, nTerminais, alpha, 30, (opImprimir == 's'));    break;
        case 3: resultado = G->gulosoRandomizadoReativoSteiner(idTerminais, nTerminais, (opImprimir == 's'));        break;
        case 4: resultado = G->gulosoRandomizadoAdaptadoSteiner(idTerminais, nTerminais, (opImprimir == 's'));       break;
        }
    }
}

///-----------------      AUXILIARES       -----------------#
Grafo* MenuTrabalho::carregarInstanciaStenio(string nomeArq, bool arcoPonderado, bool GHash){
    /** instancias de grafo direcionado, podendo ser ponderado ou nao*/
    ifstream entrada;
    entrada.open(nomeArq, ios::in);

    uint n_nos, i, j;
    uint idArco = 1;

    entrada >> n_nos;

    Grafo *G;
    if(GHash) G = new GrafoHash(n_nos*1.2, false);
    else      G = new GrafoLista(false);

    ///insere todos os nos
    No* nos[n_nos];
    for(i = 1; i <= n_nos; i++)
        nos[i] = G->insereNo(i);

    double pesoArco;
    while(entrada.good()){
        entrada >> i >> j;
        if(arcoPonderado)   entrada >> pesoArco;
        else                pesoArco = 1.0;
        G->insereArco(nos[i], nos[j], idArco++, false, pesoArco);
    }

    G->atualizaGrau();

    entrada.close();

    return G;
}

uint* MenuTrabalho::carregarInstanciaSteiner(string nomeArq, Grafo* &G, bool GHash){
    ifstream entrada;
    entrada.open(nomeArq, ios::in);

    uint n_nos, n_arcos;

    string aux;
    entrada>>aux;
    while(((string)aux) != "SECTION"){
        entrada >> aux;
    }
    entrada >> aux;

    entrada>>aux>>n_nos;
    entrada>>aux>>n_arcos;
    ///insere todos os nos
    if(GHash) G = new GrafoHash(n_nos*1.2, false);
    else      G = new GrafoLista(false);

    for(uint i=1; i<=n_nos; i++) {
        G->insereNo(i);
    }

    ///indices de origem e destino dos arcos
    uint i, j;
    double peso;

    ///PERCORRER TODOS OS ARCOS DA ENTRADA
    for(int linha=0; linha<n_arcos; linha++){
        entrada >> aux >> i >> j >> peso;
        G->insereArcoID(i, j, 1, false, peso);
    }
    G->atualizaGrau(true);

    entrada>>aux>>aux>>aux>>aux;

    uint n_terminais, *infoTerminais;
    entrada>>n_terminais;

    infoTerminais = new uint[n_terminais + 1];
    infoTerminais[0] = n_terminais;

    ///leitura de terminais
    for(int linha=0; linha<n_terminais; linha++){
        entrada >> aux >>i;
        ///insere ids sempre uma posicao a frente pos na posicao 0 temos o numero de terminais
        infoTerminais[linha + 1] = i;
    }
    return infoTerminais;
}

/** Utilizado para salvar arvores geradas por busca em largura e busca em profundidade */
void MenuTrabalho::salvarArvore(Grafo *G, string nomeArq){
    /// mapeamento dos pais de cada no
    map<No*, uint> nosPais;
    for(G->itInicio(); !G->itEhFim(); G->itProx()){
        No* no = G->getIt();
        if(no->getNivel() == 0)
            nosPais[no] = 0;
        for (no->itInicio(); !no->itEhFim(); no->itProx())
            nosPais[ no->getIt()->getNoDestino() ] = no->getID();
    }

    nomeArq = pastaSaidas + nomeArq;
    ofstream arq;
    arq.open(nomeArq.c_str());
    arq << "vertice \t pai \t nivel" << endl;
    for(auto p : nosPais)
        arq << p.first->getID() << "\t" << p.second << "\t" << p.first->getNivel() << endl;

    arq.close();

    cout << "Resultado salvo em \"" << nomeArq << "\"" <<endl;
}

/** Utilizado para salvar AGM */
void MenuTrabalho::salvarGrafo(vector<Arco*> arcos, string nomeArq){
    double peso = 0.0;
    for(Arco* arco : arcos)
        peso += arco->getPeso();

    nomeArq = pastaSaidas + nomeArq;
    ofstream arq;
    arq.open(nomeArq.c_str());
    arq << "Soma dos pesos " << peso << endl;
    arq << "Arcos: \norigem \t destino" << endl;
    for(Arco* arco : arcos)
        arq << arco->getNoOrigem()->getID() << "\t" << arco->getNoDestino()->getID()
            << "\t" << arco->getPeso() << endl;
    arq.close();

    cout << "Resultado salvo em \"" << nomeArq << "\"" <<endl;
}

void MenuTrabalho::salvarGrafo(Grafo *G, string nomeArq){
    nomeArq = pastaSaidas + nomeArq;
    ofstream arq;
    arq.open(nomeArq.c_str());
    arq << "Grau do grafo: " << G->getGrau() << endl;
    arq << "Arcos: \norigem \t destino" << endl;
    for(G->itInicio(); !G->itEhFim(); G->itProx()){
        No *no = G->getIt();
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            arq << no->getID() << "\t" << no->getIt()->getNoDestino()->getID() << endl;;
    }
    arq.close();

    cout << "Resultado salvo em \"" << nomeArq << "\"" <<endl;
}

/** Menu que da a opcao de salvar um grafo */
void MenuTrabalho::adcionarGrafo(Grafo *G){
    char add;
    string nome;
    cout << ">> adcionar grafo a lista (s/n): ";
    cin >> add;

    if(add == 's'){
        cout << ">> Escolha o nome do grafo (sem espacos): ";
        cin >> nome;
        grafos.push_back( make_pair(G, nome) );
    }else{
        delete G;
    }
}

MenuTrabalho::~MenuTrabalho(){
    for (auto p : grafos)
        delete p.first;
}
