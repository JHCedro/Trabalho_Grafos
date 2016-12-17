#include "../include/MenuTrabalho.h"
#include "dirent.h"
#include <iostream>
#include <fstream>

using namespace std;

/** TODO (jhcedro#1#14-12-2016): Todas as chamadas de funcoes sao empilhadas na memoria */

MenuTrabalho::MenuTrabalho(){
    grafoSelecionado = NULL;
//    opcoesMenu.push_back( make_pair(this->listarGrafos , "Listar Grafos") );
    try{
        string pasta = "instanciasTestesSteiner";
        struct dirent *arquivo;
        DIR *dir = opendir(pasta.c_str());

        for(uint i=0; (arquivo = readdir(dir)); i++){
            if(arquivo->d_name[0] != '.')
                instanciasSteiner.push_back((string)arquivo->d_name);
        }
    }catch(int e){
        cout << "Instancias de Steiner nao encontradas!" << endl;
    }

    /** TODO (jhcedro#1#14-12-2016): Listar tambem instacias do Stenio */

    nomeOpcoes = vector<string>({
        " 1 - Exibir opcoes do menu",
        " 2 - Exibir funcoes de Grafo",
        " 3 - Novo grafo",
        " 4 - Novo grafo exemplo",
        " 5 - Listar grafos",
        " 6 - Selecionar grafo",
        " 7 - Mostrar grafo selecionado",
        " 8 - Deletar grafo selecionado",
        " 9 - Listar Instancias da Arvore de Steiner",
        "10 - Listar Instancias de Teste",
        "11 - Carregar Instancias de Teste",
        "12 - Carregar Instancias dA Arvore de Steiner",
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
        " 9 - Verificar se eh k-regular",
        "10 - Verificar se eh completo",
        "11 - Verificar se dois nos sao adjacentes",
        "12 - Percurso em profundidade",
        "13 - Percurso em largura",
        "14 - Verificar se eh conexo",
        "15 - Verificar se dois vertices estao na mesma componente conexa",
        "16 - Verificar se um vertice eh articulacao",
        "17 - Verificar se um arco eh ponte",
        "18 - Obter vizinhanca de um vertice",
        "19 - Obter fechamento transitivo",
        "20 - Obter ordenacao topologica",
        "21 - Obter caminho minimo entre dois vertices",
        "22 - Algoritmo de Djikstra",
        "23 - Algoritmo de Floyd",
        "24 - Obter subgrafo induzido por conjunto de vertices",
        "25 - Listar componentes conexas",
        "26 - Efetuar produto cartesiano com outro grafo",
        "27 - Algoritmo de Prim",
        "28 - Algoritmo de Kruskal",
        "29 - Verificar se eh k-conexo",
        "30 - Verificar se eh euleriano",
        "31 - Algoritmo Guloso",
        "32 - Algoritmo Guloso Randomizado",
        "33 - Algoritmo Guloso Randomizado Reativo 1",
        "34 - Algoritmo Guloso Randomizado Reativo 2",
        " 0 - VOLTAR"
    });

    this->exibirOpcoes();
}

void MenuTrabalho::exibirOpcoes(){
    cout << "\n-----------------------------------------------------" << endl;
    cout << "Opcoes do menu:" << endl;
    for(string opcao :  nomeOpcoes)
        cout << "\t" << opcao << endl;
    cout << "-----------------------------------------------------" << endl;

    this->escolherOpcao();
}

void MenuTrabalho::escolherOpcao(){
    usint opcao;

    cout << "\n>> opcao menu (int): ";
    cin >> opcao;

    switch (opcao){
    case  1: this->exibirOpcoes();               break;
    case  2: this->exibirFuncoes();              break;
    case  3: this->novoGrafo();                  break;
    case  4: this->novoGrafoExemplo();           break;
    case  5: this->listarGrafos();               break;
    case  6: this->selecionarGrafo();            break;
    case  7: this->mostrarSelecionado();         break;
    case  8: this->deletarGrafo();               break;
    case  9: this->listarInstanciasSteiner();    break;
    case 10: this->listarInstanciasStenio();     break;
    case 11: this->carregarInstanciaStenio();    break;
    case 12: this->carregarInstanciaSteiner();   break;
    case  0: this->sair();                       break;

    default:
        cout << "Opcao invalida!" << endl;
        break;
    }
}

void MenuTrabalho::exibirFuncoes(){
    if(grafoSelecionado != NULL){
        ///listar funcoes do grafo
        cout << "\n-----------------------------------------------------" << endl;
        cout << "Funcoes do grafo selecionado:" << endl;
        for(uint i = 0; i < nomeFuncoes.size(); i++){
            if(i == 30)
                cout << "\n\t (Heuristicas para problema da Arvore de Steiner)" << endl;
            cout << "\t" << nomeFuncoes[i] << endl;
        }

        cout << "-----------------------------------------------------" << endl;

        this->escolherFuncao();
    }
    else{
        cout << "Nenhum grafo selecionado!" << endl;
        this->escolherOpcao();
    }
}

void MenuTrabalho::escolherFuncao(){
    usint funcao;
    cout << "\n>> opcao grafo (int): ";     cin >> funcao;

    switch (funcao){
    case  1: this->exibirFuncoes();                     break;
    case  2: this->imprimir();                          break;
    case  3: this->inserirVertice();                    break;
    case  4: this->removeVertive();                     break;
    case  5: this->inserirArco();                       break;
    case  6: this->removerArco();                       break;
    case  7: this->grau();                              break;
    case  8: this->grauNo();                            break;
    case  9: this->ehKRegular();                        break;
    case 10: this->ehCompleto();                        break;
    case 11: this->nosSaoAdjacentes();                  break;
    case 12: this->buscaProfundidade();                 break;
    case 13: this->buscaLargura();                      break;
    case 14: this->ehConexo();                          break;
    case 15: this->nosMesmaComponenteConexa();          break;
    case 16: this->noEhArticulacao();                   break;
    case 17: this->arestaEhPonte();                     break;
    case 18: this->vizinhancaNo();                      break;
    case 19: this->fechamentoTransitivo();              break;
    case 20: this->ordenacaoTopologica();               break;
    case 21: this->caminhoMinimo();                     break;
    case 22: this->djikstra();                          break;
    case 23: this->floyd();                             break;
    case 24: this->subGrafoInduzido();                  break;
    case 25: this->componentesConexas();                break;
    case 26: this->produtoCartesiano();                 break;
    case 27: this->prim();                              break;
    case 28: this->kruskal();                           break;
    case 29: this->ehKConexo();                         break;
    case 30: this->ehEuleriano();                       break;

    case 31: this->gulosoSteiner();                     break;
    case 32: this->gulosoRandomizadoSteiner();          break;
    case 33: this->gulosoRandomizadoReativoSteiner1();  break;
    case 34: this->gulosoRandomizadoReativoSteiner2();  break;
    case  0: this->exibirOpcoes();                      break;

    default:
        cout << "Funcao invalida!" << endl;
        break;
    }
    this->exibirFuncoes();
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
        cout << ">> Usar grado direcionado? (s/n): ";
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

            /// TODO (jhcedro#1#14-12-2016): verificar erro com GrafoHash nao direcionado
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
                    nome = "[LISTA] " + nome;
                    grafos.push_back( make_pair(G, nome) );
                    break;

                case 2:
                    uint ordem;
                    cout << ">> Escolha a ordem de grandeza do grafo (quantidade de nos esperada - int): ";
                    cin >> ordem;
                    G = new GrafoHash(direcionado, ordem);
                    nome = "[HASH] " + nome;
                    break;

                default:
                    cout << "Estrutura invalida!" << endl;
            }
        }

        if(G != NULL)
            grafos.push_back( make_pair(G, nome) );
    }

    this->escolherOpcao();
}

void MenuTrabalho::novoGrafoExemplo(){
    this->novoGrafo(true);
}

void MenuTrabalho::listarGrafos(){
    cout << "Lista de Grafos: " << endl;
    uint i = 1;
    for(auto p : grafos)
        cout << "\t" << i++ << " - " << p.second << endl;

    this->escolherOpcao();
}

void MenuTrabalho::selecionarGrafo(){
    usint i;
    cout << ">> Selecionar grafo (int): ";
    cin >> i;

    if(i > 0 && i <= grafos.size()){
        posGrafoSelecionado = i - 1;
        grafoSelecionado = grafos[posGrafoSelecionado].first;
        nomeGrafoSelecionado = grafos[posGrafoSelecionado].second;
        cout << "Grafo (" << nomeGrafoSelecionado << ") selecionado." << endl;
    }
    else
        cout << "Opcao invalida!" << endl;

    this->escolherOpcao();
}

void MenuTrabalho::mostrarSelecionado(){
    if(grafoSelecionado != NULL)
        cout << "Grafo selecionado: " << nomeGrafoSelecionado << endl;
    else
        cout << "Nenhum grafo selecionado!" << endl;

    this->escolherOpcao();
}

void MenuTrabalho::deletarGrafo(){
    if(grafoSelecionado != NULL){
        cout << "Deletando grafo " << nomeGrafoSelecionado << endl;
        delete grafoSelecionado;
        grafos.erase( grafos.begin() + posGrafoSelecionado);
        grafoSelecionado = NULL;
    }
    else
        cout << "Nenhum grafo selecionado!" << endl;


    this->escolherOpcao();
}

void MenuTrabalho::listarInstanciasSteiner(){
    usint i = 1;
    for(string instancia : instanciasSteiner)
        cout << i++ << " - " << instancia << endl;

    this->escolherOpcao();
}

void MenuTrabalho::listarInstanciasStenio(){
    cout << "Funcionalidade nao ainda implementada!" << endl;
    this->escolherOpcao();
}

/*
uint* leituraIntanciasSteiner(string nomeArq, Grafo* &G, bool GHash = false){
    ifstream entrada;
    entrada.open(nomeArq, ios::in);

    uint n_nos, n_arcos;

    char aux[100];
    entrada >> aux;
    while(((string)aux) != "SECTION Graph"){
        entrada.getline(aux, 100);
    }
    entrada >> aux >> n_nos;
    entrada >> aux >> n_arcos;

    if(GHash) G = new GrafoHash(n_nos, false);
    else      G = new GrafoLista(false);

    ///insere todos os nos
    for(uint i=1; i<=n_nos; i++)
        G->insereNo(i);

    ///indices de origem e destino dos arcos
    uint i, j;
    double peso;

    ///PERCORRER TODOS OS ARCOS DA ENTRADA
    for(int linha=0; linha<n_arcos; linha++){
        entrada >> aux >> i >> j >> peso;
        G->insereArcoID(i, j, 1, false, peso);
    }

    entrada>>aux>>aux>>aux>>aux;

    uint n_terminais, *infoTerminais, idx=0;
    entrada>>n_infoTerminais;

    infoTerminais = new uint[n_terminais + 1];
    infoTerminais[0] = n_terminais;

    ///leitura de terminais
    for(int linha=0; linha<n_terminais; linha++){
        entrada >> aux >>i;
        ///insere ids sempre uma posicao a frente pos na posicao 0 temos o numero de terminais
        infoTerminais[linha + 1] = i;
    }

    return terminais;
}
    */

void MenuTrabalho::carregarInstanciaSteiner(){
    cout << "Funcionalidade nao ainda implementada!" << endl;
    /** DECIDIR SE CARREGA INSTÂNCIA OU RESOLVE DIRETO
    /// escolher uma instancia para carregar em um grafo
    usint opcaoInstancia;
    cout << ">> Carregar instancia da Arvore de Steiner (int): ";
    cin >> opcaoInstancia;

    if(opcaoInstancia > 0 && opcaoInstancia <= instanciasSteiner.size()){
        Grafo *G;
        usint opcaoGrafo;
        string nomeInstancia = instanciasSteiner[opcaoInstancia - 1];

        cout << "Escolha a estrutura do grafo:" << endl;
        cout << "\t 1 - Lista Encadeada de Ajdacencias" << endl;
        cout << "\t 2 - Tabela Hash de Ajdacencias" << endl;
        cout << ">> estrutura (int): ";
        cin >> opcaoGrafo;

        if(opcaoGrafo == 1 || opcaoGrafo == 2){
            string nomeArq = "instanciasTestesSteiner/" + nomeInstancia;
            leituraIntanciasSteiner(nomeArq, G, (opcaoGrafo == 1 ? false : true));
            grafos.push_back( make_pair(G, nomeInstancia) );
        }else{
            cout << "Opcao invalida!" << endl;
        }
    }else{
        cout << "Opcao invalida!" << endl;
    }
    */
    this->exibirOpcoes();
}

void MenuTrabalho::carregarInstanciaStenio(){
    cout << "Funcionalidade nao ainda implementada!" << endl;
    /// escolher uma instancia para carregar em um grafo
    this->exibirOpcoes();
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

    this->escolherFuncao();
}

void MenuTrabalho::inserirVertice(){
    cout << "\n Inserindo vertice:" << endl;
    uint id, peso;
    cout << ">> id do vertice (int): ";     cin >> id;
    cout << ">> peso do vertice (int): ";   cin >> peso;
    grafoSelecionado->insereNo(id);

    this->escolherFuncao();
}

void MenuTrabalho::removeVertive(){
    cout << "\n Removendo vertice:" << endl;
    uint id;
    cout << ">> id do vertice (int): ";     cin >> id;
    grafoSelecionado->removeNo(id);

    this->escolherFuncao();
}

void MenuTrabalho::inserirArco(){
    cout << "\n Inserindo arco:" << endl;
    uint idArco, idOrigem,  idDestino, peso;
    cout << ">> id do vertice origem (int): ";     cin >> idOrigem;
    cout << ">> id do vertice destino (int): ";    cin >> idDestino;
    cout << ">> peso do arco (int): ";          cin >> peso;
    cout << ">> id do arco (int): ";          cin >> idArco;
    grafoSelecionado->insereArcoID(idOrigem, idDestino, idArco, true, peso);

    this->escolherFuncao();
}

void MenuTrabalho::removerArco(){
    cout << "\n Removendo arco:" << endl;
    uint idOrigem, idDestino;
    cout << ">> id do vertice origem (int): ";     cin >> idOrigem;
    cout << ">> id do vertice destino (int): ";    cin >> idDestino;
    grafoSelecionado->removeArco(idOrigem, idDestino);

    this->escolherFuncao();
}

void MenuTrabalho::grau(){
    cout << "\n Grau do grafo: "<< grafoSelecionado->getGrau() << endl;

    this->escolherFuncao();
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

    this->escolherFuncao();
}

void MenuTrabalho::ehKRegular(){
    cout << "\n Verificar k-regularidade:" << endl;
    uint k;
    cout << ">> k (int): ";     cin >> k;
    printf("Grafo%s eh %d-regular\n", (grafoSelecionado->ehGrafoKRegular(k) ? "" : " nao"), k);

    this->escolherFuncao();
}

void MenuTrabalho::ehCompleto(){
    printf("Grafo%s eh completo\n", (grafoSelecionado->ehGrafoCompleto() ? "" : " nao"));

    this->escolherFuncao();
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

    this->escolherFuncao();
}

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
}

void MenuTrabalho::buscaProfundidade(){
    cout << "\n Percurso em profundidade:" << endl;

    uint idRaiz;
    cout << ">> id vertice origem (int): "; cin >> idRaiz;
    Grafo *arv = grafoSelecionado->buscaProfundidade(idRaiz);

    string nomeArq = "percurso_profundidade_" + nomeGrafoSelecionado + ".arv";
    this->salvarArvore(arv, nomeArq);

    this->escolherFuncao();
}

void MenuTrabalho::buscaLargura(){
    cout << "\n Percurso em largura:" << endl;

    uint idRaiz;
    cout << ">> id vertice origem (int): "; cin >> idRaiz;
    Grafo *arv = grafoSelecionado->buscaLargura(idRaiz);

    string nomeArq = "percurso_largura_" + nomeGrafoSelecionado + ".arv";
    this->salvarArvore(arv, nomeArq);

    this->escolherFuncao();
}

void MenuTrabalho::ehConexo(){
    printf("Grafo%s eh conexo\n", (grafoSelecionado->ehConexo() ? "" : " nao"));

    this->escolherFuncao();
}

void MenuTrabalho::nosMesmaComponenteConexa(){
/** TODO (jhcedro#1#17-12-2016): Se grafo eh direcionado metodo deve usar componente fortemente conexa */

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

    this->escolherFuncao();
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


    this->escolherFuncao();
}

void MenuTrabalho::arestaEhPonte(){
    cout << "\n Verificar arco ponte:" << endl;
    uint id;
    cout << ">> id do arco  (int): ";     cin >> id;
    Arco* arco = grafoSelecionado->buscaArco(id);
    if(arco != NULL)
        printf("Arco %d%s eh ponte\n", id, (grafoSelecionado->ehArcoPonte(arco) ? "" : " nao"));
    else
        cout << "Arco nao encontrado!";

    this->escolherFuncao();
}

void MenuTrabalho::vizinhancaNo(){
    cout << "\n Obter vizinhanca do no:" << endl;
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

    this->escolherFuncao();
}

void MenuTrabalho::fechamentoTransitivo(){


    this->escolherFuncao();
}

void MenuTrabalho::ordenacaoTopologica(){


    this->escolherFuncao();
}

void MenuTrabalho::caminhoMinimo(){


    this->escolherFuncao();
}

void MenuTrabalho::djikstra(){


    this->escolherFuncao();
}

void MenuTrabalho::floyd(){


    this->escolherFuncao();
}

void MenuTrabalho::subGrafoInduzido(){


    this->escolherFuncao();
}

void MenuTrabalho::componentesConexas(){


    this->escolherFuncao();
}

void MenuTrabalho::produtoCartesiano(){


    this->escolherFuncao();
}

void MenuTrabalho::prim(){


    this->escolherFuncao();
}

void MenuTrabalho::kruskal(){


    this->escolherFuncao();
}

void MenuTrabalho::ehKConexo(){


    this->escolherFuncao();
}

void MenuTrabalho::ehEuleriano(){


    this->escolherFuncao();
}

void MenuTrabalho::gulosoSteiner(){


    this->escolherFuncao();
}

void MenuTrabalho::gulosoRandomizadoSteiner(){


    this->escolherFuncao();
}

void MenuTrabalho::gulosoRandomizadoReativoSteiner1(){


    this->escolherFuncao();
}

void MenuTrabalho::gulosoRandomizadoReativoSteiner2(){


    this->escolherFuncao();
}


MenuTrabalho::~MenuTrabalho(){
    for (auto p : grafos)
        delete p.first;
}
