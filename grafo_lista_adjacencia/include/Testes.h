#ifndef TESTES_H_INCLUDED
#define TESTES_H_INCLUDED
#include <ctime>
#include <set>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <set>
#include <string.h>
#include <stdio.h>


void testeFechamentoTransitivoNaMao(bool GHash = false){
    Grafo *di;
    if(GHash)   di = new GrafoHash(10);
    else        di = new GrafoLista();


    for(int i=1;i<=7;i++)
        di->insereNo(i);

    di->insereArcoID(1,2,1);
    di->insereArcoID(1,3,2);
    di->insereArcoID(1,4,3);
    di->insereArcoID(6,2,4);
    di->insereArcoID(6,4,5);
    di->insereArcoID(7,6,6);
    di->insereArcoID(4,7,7);
    di->insereArcoID(5,4,8);
    di->insereArcoID(5,7,9);
    di->insereArcoID(3,5,10);

    vector<No*> direto, indireto;

    di->imprimir();

    cout<<"\n\nDIRETOS(QUAIS NOS EU CHEGO DIRETO, SAO ADJACENTES A MIM):"<<endl;
    for( int j=1;j<=7;j++){
        ///fechamento transitivo direto do no 1
        direto=di->fechamentoTransitivoDireto(j);

        cout<<"\n\n\n fechamento transitivo direto do no "<<j<<endl;
        for(uint i=0; i<direto.size(); i++)
            cout<<"no:"<<direto.at(i)->getID()<<endl;
    }

    cout<<"\n\nINDIRETOS(QUAIS NOS EU CONSIGO CHEGAR INDIRETAMENTE, PASSANDO POR OUTROS NOS):"<<endl;
    for( int j=1;j<=7;j++){
        cout<<"\n\n\n fechamento transitivo indireto do no "<<j<<endl;
        indireto=di->fechamentoTransitivoIndireto(j);
        for(uint i=0; i<indireto.size(); i++)
            cout<<"no:"<<indireto.at(i)->getID()<<endl;
    }
}

/** testes sucessivos de remove Arco e no em grafo escadinha */
void testeGeral(bool GHash = false){
    uint i, j;
    Grafo *di= criarGrafoEscadinha();

    while(true){
        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->removeArco(i,j);
        di->imprimir();

        cout<<"remover no: ";   cin >> i;
        di->removeNo(i);
        system("pause");
    }
}

/** testar a insercao de 100.000 nos e Arcos */
void testarGrandeInsersao(bool GHash = false){
    uint tam = 100000;
    cout<<"numero de nos e Arcos:"<<endl;
    geraArquivoDeEntrada(tam);
    Grafo *di;
    if(GHash)   di = new GrafoHash(tam);
    else        di = new GrafoLista();

    char nome[]={"data.g"};
    di->leArquivo(nome);
    delete di;
}

void testarGrafoCompleto(bool GHash = false){
    uint i, j;
    Grafo *di= criarGrafoCompleto();

    while(true){
        cout<<" o grafo " << (di->ehGrafoCompleto() ? "eh " : "nao eh ") << "completo"<<endl;
        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->imprimir();
        di->removeArco(i,j);
    }
}

void testarGrafoInduzido(bool GHash = false){
    uint i, j;
    Grafo *induzido, *di= criarGrafoCompleto();

    uint v[3]={1,2,3};

    while(true){
        induzido = di->subGrafoInduzido(v, 3);
        cout<<" grafo induzido:"<<endl;
        induzido->imprimir();

        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->removeArco(i,j);
        di->imprimir();

        system("pause");
    }
}

void testarSequenciaNos(bool GHash = false){
    Grafo *di= criarGrafoEscadinha();

    cout << "Sequencia de nos:\n\t";
//    uint* seq = di->sequenciaGrau();
    vector<uint> seq = di->sequenciaGrau();
    for (uint i=0; i < di->getNumeroNos(); i++){
        cout << seq[i] << ", ";
    }
    delete di;
}

void testarNoArticulacao(bool GHash = false){
    Grafo *di= criarGrafoEscadinha();
    di->insereNo(3);
    di->insereNo(4);
    di->insereArcoID(2,3,4);
    di->insereArcoID(3,4,5);
    di->imprimir();
    int id;
    cout<<"Digite o id do no para testar se eh de articulacao:";
    while(true){
        cin>>id;
        cout<<di->ehNoArticulacao(id)<<endl;
        cout<<"Digite o id do no para testar se eh de articulacao:";
    }
}

void testeComponenteConexa(bool GHash = false){
    Grafo *di;
    if(GHash)   di = new GrafoHash(10);
    else        di = new GrafoLista();


    di->imprimir();

    for(int i=1;i<=8;i++){
        for(int j=1;j<=i;j++){
            if(i!=j && di->mesmaComponenteFortementeConexa(i,j))
                cout<<i<<"e "<<j<<" estao na mesma componente fortemente conexa"<<endl;
        }
    }
}

void testePercursoProfundidade(bool GHash = false){
    Grafo *di=grafoExemplo();

    di->imprimir();
    cout<<"busca a partir de 1"<<endl;
    di->percursoProfundidade(di->buscaNo(1));
    di->desmarcaNos();

    cout<<"busca a partir de 3"<<endl;
    cout<<"busca a partir de 3 marcando o 5"<<endl;
    di->buscaNo(5)->setMarcado(true);
    di->percursoProfundidade(di->buscaNo(3));
    di->desmarcaNos();
}

void testeBuscaProdundidadeLargura(bool GHash = false){
    Grafo *di = grafoExemplo();
    di->imprimir();
    cout<<"busca a partir de 1"<<endl;
    Grafo* Arv = di->buscaLargura(di->buscaNo(1));
    Arv->imprimir();
    delete Arv;

    cout<<"busca a partir de 3"<<endl;
    Arv = di->buscaLargura(di->buscaNo(3));
    Arv->imprimir();

    cout<<"busca a partir de 8"<<endl;
    Arv = di->buscaLargura(di->buscaNo(8));
    Arv->imprimir();
}

void testeNoArticulacao(bool GHash = false){
    Grafo *di=grafoExemplo();

    for(int i=1;i<=8;i++)
        cout<<"numero de nos da componente fortemente conexa de "<<i<<":"<<di->numeroNosComponenteFortementeConexa(di->buscaNo(i))<<endl;

    for(int i=1;i<=8;i++)
        cout<<"O no:"<<i<<" e no de articulacao?"<<di->ehNoArticulacao(i)<<endl;
}

void verificaGrafoKRegular(bool GHash = false){
    Grafo *G = criarGrafoEscadinha();
    cout << endl << "Grafo completo? " << G->ehGrafoKRegular() << endl;
}

void verificarGrafoConexo(bool GHash = false){
    Grafo *G = criarGrafoCompleto();
    cout << endl << "Grafo conexo? " << G->ehFortementeConexo() << endl;
}

void imprimirVizinhanca(vector<No*> nos, bool GHash = false){
    for(uint i = 0; i< nos.size(); i++)
        cout << nos[i]->getID() << "\t";
    cout << endl;
}

void vizinhancaAberta(bool GHash = false){
    Grafo *G;
    if(GHash)   G = GrafoHash::grafoEscadinha(10, true);
    else        G = GrafoLista::grafoEscadinha(10, true);
    int id;
    G->imprimir(false);
    cout<<"Digite o id do no para verificar vizinhanca aberta: ";
    cin>>id;
    vector<No*> nos = G->vizinhancaAberta(id);

    imprimirVizinhanca(nos);
}

void vizinhancaFechada(bool GHash = false){
    Grafo* G = criarGrafoCompleto();
    int id;
    cout<<"Digite o id do no para verificar vizinhanca fechada: ";
    cin>>id;
    vector<No*> nos = G->vizinhancaFechada(id);

    imprimirVizinhanca(nos);
}

void testeOrdenacaoTopologicaDAG(bool GHash = true){
    Grafo *di;
    if(GHash)   di = new GrafoHash(10);
    else        di = new GrafoLista();

    for(int i=1;i<=5;i++)
        di->insereNo(i);
    di->insereArcoID(1,2,1);
    di->insereArcoID(1,3,2);
    di->insereArcoID(1,5,3);
    di->insereArcoID(3,2,4);
    di->insereArcoID(3,4,5);
    di->insereArcoID(3,5,6);
    di->insereArcoID(4,5,7);
    di->insereArcoID(5,2,8);
    vector<No*> solucao=di->ordenacaoTopologicaDAG();
    cout<<"Ordenacao topologica do DAG por ID:"<<endl;
    for(uint m=0;m<solucao.size();m++){
        cout<<solucao[m]->getID()<<endl;
    }
    delete di;
}

void menorCaminho(bool GHash = false){
    Grafo* G = criarGrafoCompleto(GHash);
    int id1, id2;
    do{
        cout << "Digite o no inicial: ";
        cin >> id1;
        cout << "Digite o no final: ";
        cin >> id2;
        cout << G->consultaMenorCaminhoEntreDoisNos(id1, id2) << endl;
    }while(true);
}

uint testarDijkstra(uint n, bool GHash = false){
    /// Cria grafo com n > 0 vertices
    Grafo *G;
    if(GHash)   G = new GrafoHash(10);
    else        G = new GrafoLista();

    /// Dijkstra a partir de um (id) aleatorio
    uint id = rand()%(n+1)+1;
    uint t = clock();
    Dijkstra* resultado = G->algoritmoDijkstra(id);
    t = clock() - t;

    delete G;
    delete resultado;

    return t;
}

void imprimirArvoreMinima(vector<Arco*> arco, bool GHash = false){
    for(uint i = 0; i < arco.size(); i++)
        cout << "|A" << arco[i]->getID() << "|" << "\t";
    cout << endl;
}

uint arvoreGeradoraMinima(uint n, uint amostra, bool GHash = false){
    bool completo = false;
    Grafo *di;
    if(completo){
        if(GHash)   di = GrafoHash::grafoCompleto(n+1, true);
        else        di = GrafoLista::grafoCompleto(n+1, true);
    }
    else{
        if(GHash)   di = GrafoHash::grafoCompleto(n+1, true);
        else        di = GrafoLista::grafoCompleto(n+1, true);
        for(int i=1;i<=5;i++)
            di->insereNo(i);
        di->insereArcoID(1,2,1);
        di->insereArcoID(1,3,2);
        di->insereArcoID(1,5,3);
        di->insereArcoID(3,2,4);
        di->insereArcoID(3,4,5);
        di->insereArcoID(3,5,6);
        di->insereArcoID(4,5,7);
        di->insereArcoID(5,2,8);
        di->insereArcoID(5,1,9);
    }

    uint t;
    t = clock();
//    for (uint i=0; i < amostra; i++){
        vector<Arco*> arco = di->algoritmoPrim();
//    t = clock() - t;
//    }
    imprimirArvoreMinima(arco, false);

    return t;
}

uint testarKruskal(uint n, bool GHash = false){
    Grafo *di;

    if(GHash)   di = GrafoHash::grafoCompleto(10);
    else        di = GrafoLista::grafoCompleto(10);
    uint t;
    t = clock();
    vector<Arco*> arcosMin = di->algoritmoKruskal();
    t = clock() - t;
    return t;
}

void testarKruskalNaMao(bool GHash = false){
    Grafo *g, *arvMin;

    if(GHash){
        g = GrafoHash::grafoCompleto(10);
        arvMin = GrafoHash::grafoCompleto(10);
    }
    else{
        g = GrafoLista::grafoCompleto(10);
        arvMin = GrafoLista::grafoCompleto(10);
    }


    for(int i=1;i<=7;i++){
        g->insereNo(i);
        arvMin->insereNo(i);
    }

    g->insereArcoID(1,2,1);
    g->insereArcoID(2,1,1);

    g->insereArcoID(1,3,2);
    g->insereArcoID(3,1,2);

    g->insereArcoID(2,3,3);
    g->insereArcoID(3,2,3);

    g->insereArcoID(2,4,4);
    g->insereArcoID(4,2,4);

    g->insereArcoID(3,4,5);
    g->insereArcoID(4,3,5);

    g->insereArcoID(2,6,6);
    g->insereArcoID(6,2,6);

    g->insereArcoID(4,6,7);
    g->insereArcoID(6,4,7);

    g->insereArcoID(3,5,8);
    g->insereArcoID(5,3,8);

    g->insereArcoID(4,5,9);
    g->insereArcoID(5,4,9);

    g->insereArcoID(5,7,10);
    g->insereArcoID(7,5,10);

    g->insereArcoID(4,7,11);
    g->insereArcoID(7,4,11);

    g->insereArcoID(6,7,12);
    g->insereArcoID(7,6,12);

    cout<<"\n\n\ngrafo:\n\n"<<endl;
    g->imprimir();

    vector<Arco*> arcosMin = g->algoritmoKruskal();
    cout<<"quantidade de arcos da solucao:"<<arcosMin.size()<<endl;
    uint orig, dest, id;

    for(uint i=0;i<arcosMin.size();i++){
        id=arcosMin.at(i)->getID();
        orig=arcosMin.at(i)->getNoOrigem()->getID();
        dest=arcosMin.at(i)->getNoDestino()->getID();
        arvMin->insereArcoID(orig, dest, id);
        arvMin->insereArcoID(dest, orig, id);
    }

    cout<<"\n\n\narvMin:\n\n"<<endl;
    arvMin->imprimir();
}

uint testarProdutoCartesiano(uint n, uint amostra, bool GHash = false){
    Grafo *A, *B;

    if(GHash){
        A = GrafoHash::grafoCompleto(n+1);
        B = GrafoHash::grafoCompleto(n+1);
    }
    else{
        A = GrafoLista::grafoCompleto(n+1);
        B = GrafoLista::grafoCompleto(n+1);
    }

    uint t = 0, tAux;
    for (uint i=0; i < amostra; i++){
        tAux = clock();
        Grafo *C = A->produtoCartesiano(B);
        t += clock() - tAux;
        delete C;
    }

    delete A;
    delete B;
    return t;
}

uint testarGrafoEuleriano(uint n, uint amostra, bool GHash = false){
    Grafo *G;
    if(GHash)   G = new GrafoHash(10);
    else        G = new GrafoLista();

    uint t = clock();
    for (uint i=0; i < amostra; i++){
        cout << "\nGrafo " << (G->ehGrafoEuleriano() ? "" : "nao ") << "eh euleriano.\n";
    }
    t = clock() - t;
    delete G;

    return t;
}

uint testarEhArcoPonte(uint n, uint amostra, bool GHash = false){
    Grafo *G;
    if(GHash)   G = GrafoHash::grafoCompleto(n);
    else        G = GrafoLista::grafoCompleto(n);

    G = grafoExemplo(GHash);
    G->imprimir();

    uint idArco;
    while(cin >> idArco)
        cout << "\nArco " << (G->ehArcoPonte(idArco) ? "" : "nao ") << "eh ponte.\n";

    return 0;
}

void testeListaHashRidiculo(){
    GrafoHash *G = new GrafoHash(10);
    G->insereNo(5);
    G->insereNo(5);
    G->insereNo(6);
    G->insereNo(0);
    G->insereNo(0);
    G->insereNo(8);
    G->insereNo(16);
    G->insereArcoID(5, 8, 14);
    G->insereArcoID(5, 0, 14);
    G->insereArcoID(0, 16, 14);
    G->insereArcoID(8, 16, 14);
    G->insereArcoID(8, 0, 14);
    G->insereArcoID(16, 6, 14);
    G->imprimir();
    G->removeNo(16);
    G->removeArco(8, 16);
    G->imprimir();
    cout << G->buscaNo(5)->getID();
}

uint h(uint x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

void testarComponentesConexasNaMao(bool GHash = true){
    Grafo *g;

    if(GHash) g=new GrafoHash(10);
    else g=new GrafoLista();

    for(int i=0;i<=5;i++){
        g->insereNo(i);
    }
    g->insereArcoID(0,2,1);
    g->insereArcoID(2,0,2);

    g->insereArcoID(2,1,3);
    g->insereArcoID(1,2,4);

    g->insereArcoID(1,0,5);
    g->insereArcoID(0,1,6);

    g->insereArcoID(4,5,7);
    g->insereArcoID(5,4,8);

    vector<vector<No*>> componentes=g->retornarComponentesConexas();
    for(uint i=0;i<componentes.size();i++){
        cout<<"Componente "<<i<<endl;
        for(uint j=0;j<componentes[i].size();j++){
            cout<<componentes[i][j]->getID()<<endl;
        }
        cout<<endl;
    }
    delete g;
}

void testeKConexo(bool GHash = true){
    Grafo *g;
    g=criarGrafoCompleto(10);

    cout<<g->ehKConexo(3)<<endl;
}

void testeExemplosSteiner(){
    Grafo *g = new GrafoLista(false);
/** EXEMPLO 1*/
    for(int i=1; i<=7; i++)
        g->insereNo(i);

    g->insereArcoID(1 ,4 , 1 ,false, 4.0);
    g->insereArcoID(1 ,3 , 1 ,false, 3.0);
    g->insereArcoID(1 ,2 , 1 ,false, 2.0);
    g->insereArcoID(2 ,3 , 1 ,false, 8.0);
    g->insereArcoID(2 ,6 , 1 ,false, 2.0);
    g->insereArcoID(2 ,7 , 1 ,false, 4.0);
    g->insereArcoID(3 ,4 , 1 ,false, 1.0);
    g->insereArcoID(3 ,5 , 1 ,false, 2.0);
    g->insereArcoID(4 ,5 , 1 ,false, 5.0);
    g->insereArcoID(5 ,6 , 1 ,false, 3.0);
    g->insereArcoID(5 ,7 , 1 ,false, 6.0);
    g->insereArcoID(6 ,7 , 1 ,false, 5.0);
    uint ids[] = {3, 5, 7};
/**/

/** EXEMPLO 2 (bem bosta)*
    for(int i=1; i<=12; i++)
        g->insereNo(i);

    g->insereArcoID(1, 7, 1, false, 1.0);
    g->insereArcoID(2, 3, 1, false, 10.0);
    g->insereArcoID(2, 8, 1, false, 9.0);
    g->insereArcoID(3, 4, 1, false, 11.0);
    g->insereArcoID(5, 6, 1, false, 2.0);
    g->insereArcoID(6, 11, 1, false, 4.0);
    g->insereArcoID(7, 8, 1, false, 7.0);
    g->insereArcoID(7, 11, 1, false, 6.0);
    g->insereArcoID(7, 10, 1, false, 5.0);
    g->insereArcoID(8, 9, 1, false, 12.0);
    g->insereArcoID(8, 12, 1, false, 8.0);
    g->insereArcoID(10, 11, 1, true, 3.0);
    uint ids[] = {5, 7, 9};
/**/

/** EXEMPLO 3*
    for(int i=1; i<=8; i++)
        g->insereNo(i);

    g->insereArcoID(1, 2, 1, false, 2.0);
    g->insereArcoID(1, 3, 1, false, 1.0);
    g->insereArcoID(2, 3, 1, false, 3.0);
    g->insereArcoID(2, 4, 1, false, 1.0);
    g->insereArcoID(3, 4, 1, false, 2.0);
    g->insereArcoID(5, 3, 1, false, 4.0);
    g->insereArcoID(5, 7, 1, false, 5.0);
    g->insereArcoID(6, 7, 1, false, 3.0);
    uint ids[] = {1, 4, 7, 8};
/**/
    g->imprimir(true);
    double solucao;

    cout<<"GULOSO PURO:"<<endl;
    solucao = g->gulosoSteiner(ids, 3, true);

    cout<<"GULOSO RANDOMIZADO:"<<endl;
    solucao = g->gulosoRandomizadoSteiner(ids, 3, 0.5, 10, true);

    cout<<"GULOSO RANDOMIZADO REATIVO:"<<endl;
    solucao = g->gulosoRandomizadoReativoSteiner(ids, 3, true);

    cout<<"GULOSO RANDOMIZADO REATIVO 2:"<<endl;
    solucao = g->gulosoRandomizadoAdaptadoSteiner(ids, 3, true);

    delete  g;
}

vector<string> listarArquivosPasta(string nome){
    string pasta = nome;
    struct dirent *arquivo;
    DIR *dir = opendir(pasta.c_str());
    vector<string> arquivos;

    for(uint i=0; arquivo = readdir(dir); i++){
        if(i>1)
            arquivos.push_back(pasta + "/" + (string)arquivo->d_name);
    }
    return arquivos;
}

void testeGulosoSteiner(){
    string pasta = "instanciasTestesSteiner";
    vector<string> arquivos = listarArquivosPasta(pasta);

    ///armazenar tempo e valor da solucao do guloso
    double *temposGuloso = new double[10], *solucoesGuloso = new double[10];

    Grafo *g = new GrafoLista(false);

    for(uint idArquivo=0; idArquivo<arquivos.size(); idArquivo++){

        uint * infoTerminais = leituraIntanciaSteiner(arquivos[idArquivo], g, false);
        uint ids[infoTerminais[0]];
        for(uint j=0; j<infoTerminais[0]; j++)
            ids[j] = infoTerminais[j+1];

        double t = clock();

        srand(time(NULL));

        g->gulosoSteiner(ids, infoTerminais[0]);

        uint somaPesos = 0;
        somaPesos = temposGuloso[idArquivo] = (clock() - t) / CLOCKS_PER_SEC;

        solucoesGuloso[idArquivo] = somaPesos;

        cout << " solucao para instancia:" << arquivos[idArquivo] << ", foi " << solucoesGuloso[idArquivo]<<endl;
        cout << " tempo gasto no algoritmo:" << temposGuloso[idArquivo]<<endl;
    }

}

void testeGulosoRandomizadoSteiner(){
    string pasta = "instanciasTestesSteiner";
    vector<string> arquivos = listarArquivosPasta(pasta);

    ///armazenar tempo e valor da solucao do guloso
    double *temposGuloso = new double[10], *solucoesGuloso = new double[10];

    Grafo *g = new GrafoLista(false);

    for(uint idArquivo=0; idArquivo<arquivos.size(); idArquivo++){

        uint * infoTerminais = leituraIntanciaSteiner(arquivos[idArquivo], g, false);
        uint ids[infoTerminais[0]];
        for(uint j=0; j<infoTerminais[0]; j++)
            ids[j] = infoTerminais[j+1];

        double t = clock();

        srand(time(NULL));

        double somaPesos = 0;
        somaPesos = g->gulosoSteiner(ids, infoTerminais[0], true);

        temposGuloso[idArquivo] = (clock() - t) / CLOCKS_PER_SEC;

        solucoesGuloso[idArquivo] = somaPesos;

        cout << " solucao para instancia:" << arquivos[idArquivo] << ", foi " << solucoesGuloso[idArquivo]<<endl;
        cout << " tempo gasto no algoritmo:" << temposGuloso[idArquivo]<<endl;
    }

}

void testeInstanciasSteiner(){
    /**
    cout<<"LISTA\n"<<endl;
    for(int k=0;k<50;k++){
        int i=1;
        char nome[50];
        sprintf(nome, "instanciasSteiner/E/e0%d.stp", i);
        Grafo *g = new GrafoLista(false);
        uint *infoTerminais = g->leituraIntanciaSteiner(nome);

        srand(time(NULL));
        vector<Arco*> solucao = g->gulosoRandomizadoSteiner(infoTerminais, infoTerminais[0], 0.4);

        double peso=0;

        for(int i=0; i<solucao.size(); i++)
            peso += solucao[i]->getPeso();

        cout<<"peso obtido pelo guloso: "<<peso<<endl;
        delete g;
    }

    cout<<"HASH:\n"<<endl;
    for(int k=0;k<50;k++){
        int i=1;
        char nome[50];
        sprintf(nome, "instanciasSteiner/E/e0%d.stp", i);
        Grafo *g = new GrafoLista(false);
        uint *infoTerminais = g->leituraIntanciaSteiner(nome);

        srand(time(NULL));
        vector<Arco*> solucao = g->gulosoRandomizadoSteiner(infoTerminais, infoTerminais[0], 0.4);

        double peso=0;

        for(int i=0; i<solucao.size(); i++)
            peso += solucao[i]->getPeso();

        cout<<"peso obtido pelo guloso: "<<peso<<endl;
        delete g;
    }
    */
}

void testeHeuristicasGulosas(){
    double alpha = 0.25;
    int num_it = 30;
    vector<string> arquivos = listarInstanciasSteiner();
    Grafo* G;

    int semente = 1;
    ///para cada arquivo
    for(string arq : arquivos){
        cout<<"instancia:"<<arq<<endl;
        uint *infoTerminais = leituraIntanciaSteiner(arq, G, false);
        cout<<"\nGULOSO RANDOMIZADO: "
            << G->gulosoRandomizadoSteiner(infoTerminais+1, infoTerminais[0], alpha, num_it, semente) << endl;

        cout<<"\nGULOSO RANDOMIZADO REATIVO: "
            << G->gulosoRandomizadoReativoSteiner(infoTerminais+1, infoTerminais[0], semente) << endl;

        cout<<"\nGULOSO RANDOMIZADO ADAPTADO: "
            << G->gulosoRandomizadoAdaptadoSteiner(infoTerminais+1, infoTerminais[0], semente) << endl;

        delete G;
    }
}

void testarGulosoNaMao(){
    Grafo *g = new GrafoLista(false);

    for(int i=1; i<=7; i++)
        g->insereNo(i);

    g->insereArcoID(1 ,4 , 1 ,false, 4.0);
    g->insereArcoID(1 ,3 , 1 ,false, 3.0);
    g->insereArcoID(1 ,2 , 1 ,false, 2.0);
    g->insereArcoID(2 ,3 , 1 ,false, 8.0);
    g->insereArcoID(2 ,6 , 1 ,false, 2.0);
    g->insereArcoID(2 ,7 , 1 ,false, 4.0);
    g->insereArcoID(3 ,4 , 1 ,false, 1.0);
    g->insereArcoID(3 ,5 , 1 ,false, 2.0);
    g->insereArcoID(4 ,5 , 1 ,false, 5.0);
    g->insereArcoID(5 ,6 , 1 ,false, 3.0);
    g->insereArcoID(5 ,7 , 1 ,false, 6.0);
    g->insereArcoID(6 ,7 , 1 ,false, 5.0);
    uint ids[] = {3, 5, 7};

    g->gulosoSteiner(ids, 3, true);
}

/**
executa 1 vez algum algoritmo guloso para uma instancia e retorna a solucao
heuristica=1 executa guloso, =2 executa randomizado e =3 executa reativo
*/
double execucaoGuloso(Grafo* &g, string nomeInstancia, int heuristica, int semente = 1){
    double menorSolucao = INFINITY;

    uint * infoTerminais = leituraIntanciaSteiner(nomeInstancia, g, false);
    if(heuristica==1)
        menorSolucao = g->gulosoSteiner(infoTerminais + 1, infoTerminais[0]);
    if(heuristica==2)
        menorSolucao = g->gulosoRandomizadoSteiner(infoTerminais + 1, infoTerminais[0], 0.25, 30, semente);
    if(heuristica==3)
        menorSolucao = g->gulosoRandomizadoReativoSteiner(infoTerminais + 1, infoTerminais[0], semente);

    return menorSolucao;
}

///tabela1 para resultados e tabela2 para tempo
ofstream tabela1, tabela2;

/**
gera tabela de resultados e de tempo
*/
void gerarTabela(){

    tabela1.open("tabela1.csv");
    tabela2.open("tabela2.csv");

    tabela1<<"\xef\xbb\xbf"<<endl;
    tabela2<<"\xef\xbb\xbf"<<endl;

    ///primeira linha da tabela com os titulos das colunas
    tabela1<<"Nome instancia"<<";"<<"Melhor solucao"<<";"<<"Resultado Guloso"<<";"<<"Media Randomizado"
          <<";"<<"Desvio percentual da media Randomizado"<<";"<<"Media Reativo"<<";"<<"Desvio percentual da media Reativo"<<"\n";

    tabela2<<"Nome instancia"<<";"<<"Tempo medio Guloso"<<";"<<"Tempo medio Randomizado"<<";"<<"Tempo medio Reativo"<<"\n";

    int num_iteracoes = 30;

    string pasta = "instanciasTestesSteiner";
    vector<string> arquivos = listarArquivosPasta(pasta);

    ///armazenar tempos e tempo medio para cada abordagem
    double tempoGuloso[30], tempoMedioGuloso;
    double tempoGulosoRandomizado[30], tempoMedioGulosoRandomizado;
    double tempoGulosoRandomizadoReativo[30], tempoMedioGulosoRandomizadoReativo;

    ///armazenar resultado de cada abordagem para os 10 arquivos de entrada
    double *solucoesGuloso = new double[10];

    ///variavel para armazenar a menor solucao dentre todas as abordagens
    double menorSolucao = HUGE_VAL;

    ///2 medias e desvios padroes, para randomizada e reativa
    double media[2], desvioP[2];

    ///armazena todas as solucoes para as 30 execucoes
    double* solucoes = new double[num_iteracoes];

    char momeInstancia[100];

    Grafo *g = new GrafoLista(false);

    ///para cada arquivo temos uma linha da tabela
    for(uint idArquivo=0; idArquivo<arquivos.size(); idArquivo++){

        cout<<"\ngerando linha["<<idArquivo+2<<"] da tabela"<<endl;

        ///definir o nome da instancia que vai aparecer na tabela
        if(idArquivo<=3)
            sprintf(momeInstancia, "instancia %d (pequena)", idArquivo);
        if(idArquivo>=4 && idArquivo<=6)
            sprintf(momeInstancia, "instancia %d (media)", idArquivo);
        if(idArquivo>=7 && idArquivo<=9)
            sprintf(momeInstancia, "instancia %d (grande)", idArquivo);

        ///gerar primeira coluna da tabela temos que rodar o guloso, o randomizado e o reativo
        ///primeira coluna da tabela nos da a melhor solucao dos algoritmos (ver funcao "execucaoGuloso()")
        for(int i=1; i<=3; i++){

            ///menor valor obitido para uma execucao
            double menor;
            ///se executando randomizado ou reativo
            if(i>1){
                cout<<"\nrodando 30 vezes para calcular desvio padrao e media"<<endl;
                ///executar 30 vezes para calcular media e desvio padrao de randomizado e reativo
                for(int it=0; it<num_iteracoes; it++){
                    double t = clock();
                    ///menor valor obitido para uma execucao
                    menor = execucaoGuloso(g, arquivos[idArquivo], i);
                    solucoes[it] = menor;
                    if(menor<menorSolucao)
                        menorSolucao = menor;

                    if(i==2) tempoGulosoRandomizado[it] = (clock() - t) / CLOCKS_PER_SEC;
                    if(i==3) tempoGulosoRandomizadoReativo[it] = (clock() - t) / CLOCKS_PER_SEC;
                }
                /// media
                double somaSolucoes = accumulate(solucoes, solucoes+num_iteracoes, 0.0);
                double mediaSolucoes = somaSolucoes / num_iteracoes;

                /// desvio padrao
                double sq_sum = inner_product(solucoes, solucoes+num_iteracoes, solucoes, 0.0);
                double stdev = sqrt(sq_sum / num_iteracoes - mediaSolucoes * mediaSolucoes);

                ///armazena media e desvio padrao
                media[i-2] = mediaSolucoes;
                desvioP[i-2] = stdev / mediaSolucoes * 100;

                if(i==2) tempoMedioGulosoRandomizado = accumulate(tempoGulosoRandomizado, tempoGulosoRandomizado+num_iteracoes, 0.0) / num_iteracoes;
                if(i==3) tempoMedioGulosoRandomizadoReativo = accumulate(tempoGulosoRandomizadoReativo, tempoGulosoRandomizadoReativo+num_iteracoes, 0.0) / num_iteracoes;
            }
            else{
                ///rodar o guloso 30 vezes para se ter o tempo medio
                cout<<"\ncalculando resultado do guloso"<<endl;
                for(int it=0; it<num_iteracoes; it++){
                    double t = clock();
                    cout<<"\ncalculando resultado do guloso"<<endl;
                    menor = execucaoGuloso(g, arquivos[idArquivo], i);

                    solucoesGuloso[idArquivo] = menor;

                    if(menor<menorSolucao)
                        menorSolucao = menor;

                    tempoGuloso[it] = (clock() - t) / CLOCKS_PER_SEC;
                }
                tempoMedioGuloso = accumulate(tempoGuloso, tempoGuloso+num_iteracoes, 0.0) / num_iteracoes;
            }

        }
        tabela1<<momeInstancia<<";"<<menorSolucao<<";"<<solucoesGuloso[idArquivo]
        <<";"<<media[0]<<";"<<desvioP[0]<<";"<<media[1]<<";"<<desvioP[1]<<"\n";

        tabela2<<momeInstancia<<";"<<tempoMedioGuloso<<";"<<tempoMedioGulosoRandomizado
        <<";"<<tempoMedioGulosoRandomizadoReativo<<"\n";

        menorSolucao = HUGE_VAL;
        delete g;
        g = new GrafoLista(false);
    }

    tabela1.close();
    tabela2.close();
}

uint testarInsersao(uint n, uint amostra, bool GHash = false){
    Grafo* G;

    uint t = 0, tAux;
    for (uint i=0; i < amostra; i++){
        if(GHash)   G = new GrafoHash(n);
        else        G = new GrafoLista();

        tAux = clock();
        for(uint j = 0; j < n; j++)
            G->insereNo(j);
        t += clock() - tAux;
        delete G;
    }

    return t;
}

uint testarColisaoHash(uint n, uint amostra){
    GrafoHash* G;
    uint numColisoes = 0;

    for (uint i=0; i < amostra; i++){
        G = new GrafoHash(n);

        for(uint j = 0; j < n; j++)
            G->insereNo(j);

        numColisoes += G->getNumColisoes();

        delete G;
    }

    return numColisoes;
}

uint testarBusca(uint n, uint amostra, bool GHash = false){
    Grafo* G;

    if(GHash)   G = GrafoHash::grafoCompleto(n);
    else        G = GrafoLista::grafoCompleto(n);

    uint ids[amostra];
    for(uint i = 0; i < amostra; i++)
        ids[i] = rand()%(n+1)+1;

    uint t = 0, tAux;
    for (uint i=0; i < amostra; i++){
        tAux = clock();
        G->buscaNo(ids[i]);
        t += clock() - tAux;
    }

    delete G;
    return t;
}

uint testarRemocao(uint n, uint amostra, bool GHash = false){
    Grafo* G;

    uint t = 0, tAux;
    for (uint i=0; i < amostra; i++){
        if(GHash)   G = GrafoHash::grafoCompleto(n);
        else        G = GrafoLista::grafoCompleto(n);
        uint id = rand()%(n+1)+1;

        tAux = clock();
        G->removeNo(id);
        t += clock() - tAux;
        delete G;
    }

    return t;
}

void analiseDesempenhoEstruturas(uint n, uint passo, uint amostra){
    string subPasta = "Estrutural/";
    ///tempo de insercao de nos
    analiseDesempenho(testarInsersao, n, passo, amostra, false, "Teste Insercao Lista", subPasta + "Teste_Insercao_LISTA.csv");
    graficoPython(subPasta + "Teste_Insercao_LISTA.csv", "python3");
    analiseDesempenho(testarInsersao, n, passo, amostra, true, "Teste Insercao Hash", subPasta + "Teste_Insercao_HASH.csv");
    graficoPython(subPasta + "Teste_Insercao_HASH.csv", "python3");

    ///Numero de Colisoes na tabela de nos
    /*
    for (uint i=0; i<n; i+=passo){
        printf("\nn=%d \tamostra= %d", i, amostra);
        double colisoes = (double) testarColisaoHash(i, amostra) / amostra;
        printf("\tcolisoes= %f \t razao: %f", colisoes, colisoes/n);
    }
    */
//    analiseDesempenho(testarColisaoHash, n, passo, amostra, true/*, "Colisoes Hash", subPasta + "Colisoes_HASH.csv"*/);
//    graficoPython(subPasta + "Colisoes_HASH.csv", "python3");

    ///tempo de busca de nos
    analiseDesempenho(testarInsersao, n, passo, amostra, false, "Teste Busca Lista", subPasta + "Teste_Busca_LISTA.csv");
    graficoPython(subPasta + "Teste_Busca_LISTA.csv", "python3");
    analiseDesempenho(testarInsersao, n, passo, amostra, true, "Teste Busca Hash", subPasta + "Teste_Busca_HASH.csv");
    graficoPython(subPasta + "Teste_Busca_HASH.csv", "python3");

    ///tempo de insercao de arcos
    ///tempo de busca de arcos
        //sao da ordem de busca de nos

    ///tempo de remocao de no
    analiseDesempenho(testarInsersao, n, passo, amostra, false, "Teste Remocao Lista", subPasta + "Teste_Remocao_LISTA.csv");
    graficoPython(subPasta + "Teste_Remocao_LISTA.csv", "python3");
    analiseDesempenho(testarInsersao, n, passo, amostra, true, "Teste Remocao Hash", subPasta + "Teste_Remocao_HASH.csv");
    graficoPython(subPasta + "Teste_Remocao_HASH.csv", "python3");

    ///memoria alocada
}

/** Testes corriqueiros que eram feitos na main() */
void testesAvulsos(){
    ///testar na mao
//    testarGrandeInsersao();
//    testarGrafoCompleto();
//    testarGrafoInduzido(); ///entender
//    testarSequenciaNos();  ///entender o sort
//    testarNoArticulacao(); ///ta dando certo nao n�?
//    testarinstanciasArcoPonderados();
//    testeComponenteConexa();
//    testePercursoProfundidade();
//    testeBuscaProdundidadeLargura();
//    testeNoArticulacao();
//    testeRubustezVertice();

//    analiseDesempenho(testarDijkstra, 1000, 50, 5, false, "Teste Dijkstra", "teste_dijkstra.csv");
//    graficoPython("teste_dijkstra.csv");

//    verificaGrafoKRegular();
//    verificarGrafoConexo();
//    vizinhancaAberta();
//    vizinhancaFechada();
//    testeOrdenacaoTopologicaDAG();
//    menorCaminho();

//    analiseDesempenho(arvoreGeradoraMinima, 500, 50, 1, false, "Teste Prim Lista", "teste_prim_lista.csv");
//    graficoPython("teste_prim_lista.csv");
//    analiseDesempenho(arvoreGeradoraMinima, 500, 50, 1, true, "Teste Prim Hash", "teste_prim_hash.csv");
//    graficoPython("teste_prim_hash.csv");

//    testarKruskalNaMao();
//    arvoreGeradoraMinima();
//    grafoCompleto(5)->imprimir();
//
//    analiseDesempenho(testarProdutoCartesiano, 141, 10, 5, false, "Teste Produto Cartesiano Lista", "lista_teste_prod_cartesiano.csv");
//    analiseDesempenho(testarProdutoCartesiano, 141, 10, 5, true, "Teste Produto Cartesiano Hash", "hash_teste_prod_cartesiano.csv");
//    graficoPython("lista_teste_prod_cartesiano.csv");
//    graficoPython("hash_teste_prod_cartesiano.csv");

//    testeFechamentoTransitivoNaMao();

//    analiseDesempenho(testarGrafoEuleriano, 300000, 1001, 1, "Teste Grafo Euleriano", "teste_grafo_euleriano.csv");
//    graficoPython("teste_grafo_euleriano.csv");

//    analiseDesempenho(testarEhArcoPonte, 5001, 500, 5, false, "Teste Arco Ponte LISTA", "teste_arco_ponte_LISTA.csv");
//    graficoPython("teste_arco_ponte_LISTA.csv");
//    analiseDesempenho(testarEhArcoPonte, 5001, 500, 5, true, "Teste Arco Ponte HASH", "teste_arco_ponte_HASH.csv");
//    graficoPython("teste_arco_ponte_HASH.csv");

//    testeListaHashRidiculo();
//    testarEhArcoPonte(0, 0, false);

//    cout << THash<uint>::proxPrimo(11);
//    testarComponentesConexasNaMao();
//    testeKConexo();


///---------------------------------------------TESTES EMAIL DO STENIO------------------------------------------
//    gerarTabela();
///---------------------------------------------TESTES EMAIL DO STENIO------------------------------------------

//    testarGulosoNaMao();
//    cout<<"guloso:"<<endl<<endl<<endl;
//    testeGulosoSteiner();
    testeHeuristicasGulosas();

//    arvoreGeradoraMinima(30, 5, false);
//   vizinhancaAberta(false);
//    Grafo *G = GrafoLista::grafoCompleto(1000, true);
//    system("pause");
//    delete G;
//    system("pause");

//    testeExemplosSteiner();
//Grafo* g = GrafoHash::grafoCompleto(8000);
//    analiseDesempenhoEstruturas(1000, 10, 30);

//    cout << "memoria: " << getValue();
//    pauseGambiarra();

//    cout<<"guloso randomizado:"<<endl<<endl<<endl;
//    testeInstanciasSteiner();
//    Grafo *G = new GrafoHash(5, false);
//    for (int i=0; i < 5; i++)
//        G->insereNo(i);
//    G->imprimir(false);
//    G->insereArcoID(0, 2, 0);
//    G->insereArcoID(0, 4, 0);
//    G->insereArcoID(1, 0, 0);
//    G->insereArcoID(4, 1, 0);
//    G->imprimir(false);
//    G->buscaLargura(G->buscaNo(1))->imprimir(true);

//    exibirMenu();
}

#endif // TESTES_H_INCLUDED
