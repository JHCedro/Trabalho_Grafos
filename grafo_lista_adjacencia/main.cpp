#include "Auxiliares.h"
#include "GrafoHash.h"
#include "GrafoLista.h"
#include <dirent.h>

using namespace std;

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

/** testar a inser��o de 100.000 nos e Arcos */
void testarGrandeInsersao(bool GHash = false){
    uint tam = 100000;
    cout<<"numero de nos e Arcos:"<<endl;
    //    cin>>tam;
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
    uint* seq = di->sequenciaGrau();
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

/*
///** nao faco ideia do que isso ta fazendo /
//void testarInstanciasStenio(bool GHash = false){
//    ///teste de leitura de instancias do stenio
//    Grafo *di=new Grafo();
//    char nome[50];
//    for(int i=1;i<=16;i++){
//        if(i<=8)sprintf(nome, "instancias/grafo_1000_%d.txt", i);
//        else sprintf(nome, "instancias/grafo_10000_%d.txt", i%9+1);
//        di->leArquivo(nome);
//        cout<<" arquivo:"<<nome<<" lido com sucesso!"<<endl;
//        cout<<" o grafo e completo?"  << di->ehGrafoCompleto()<<"   (0= nao completo, 1=completo)"<<endl;
//        system("pause");
////        cin>>i;
////        cout<<"O no:"<<i<<" tem grau:"<<di->buscaNo(i)->getGrau()<<endl;
////        system("pause");
////        for(int i=1;i<=10000;i++)
////            di->removeNoPorID(i);
////        system("pause");
//    }
//}*/

void testeComponenteConexa(bool GHash = false){
//    Grafo *di= grafoDuardo();
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
    Grafo *di=grafoDuardo();

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
    Grafo *di = grafoDuardo();
//    Grafo* di = grafoCompleto(5);
//    Grafo* di = grafoEscadinha(5);

    di->imprimir();
    cout<<"busca a partir de 1"<<endl;
//    Grafo* Arv = di->buscaProfundidade(di->buscaNo(1));
    Grafo* Arv = di->buscaLargura(di->buscaNo(1));
    Arv->imprimir();
    delete Arv;

    cout<<"busca a partir de 3"<<endl;
//    Arv = di->buscaProfundidade(di->buscaNo(3));
    Arv = di->buscaLargura(di->buscaNo(3));
    Arv->imprimir();

    cout<<"busca a partir de 8"<<endl;
//    Arv = di->buscaProfundidade(di->buscaNo(3));
    Arv = di->buscaLargura(di->buscaNo(8));
    Arv->imprimir();
}

void testeNoArticulacao(bool GHash = false){
    Grafo *di=grafoDuardo();

    for(int i=1;i<=8;i++)
        cout<<"numero de nos da componente fortemente conexa de "<<i<<":"<<di->numeroNosComponenteFortementeConexa(di->buscaNo(i))<<endl;

    for(int i=1;i<=8;i++)
        cout<<"O no:"<<i<<" e no de articulacao?"<<di->ehNoArticulacao(i)<<endl;
}

void testeRubustezVertice(bool GHash = false){
    Grafo *di;
    if(GHash)   di = new GrafoHash(10);
    else        di = new GrafoLista();

    uint *ids;
    char nome[50];
    sprintf(nome, "instancias/grafo_1000_%d.txt", 1);
    di->leArquivo(nome);
    cout<<"arquivo:"<<nome<<" lido"<<endl;
    cout<<" calculando a rubustez de vertices desse grafo enorme!!! vai demorar para um caralho!"<<endl;
    cout<<"rubustes de vertice:"<<di->rubustezVertice(ids);
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
    Grafo* G = criarGrafoEscadinha();
    int id;
    cout<<"Digite o id do no para verificar vizinhanca aberta: ";
    cin>>id;
    vector<No*> nos = G->vizinhancaAberta(id);///ver pq nao da pra usar o default nessa caralha

    imprimirVizinhanca(nos);
}

void vizinhancaFechada(bool GHash = false){
    Grafo* G = criarGrafoCompleto();
    int id;
    cout<<"Digite o id do no para verificar vizinhanca fechada: ";
    cin>>id;
    vector<No*> nos = G->vizinhancaFechada(id);///ver pq nao da pra usar o default nessa caralha

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

//    G->imprimir();

    /// Dijkstra a partir de um (id) aleatorio
    uint id = rand()%(n+1)+1;
    uint t = clock();
    Dijkstra* resultado = G->dijkstra(id);
    t = clock() - t;
//    resultado->imprimirDistancias();

//    G->insereArcoID(8,1,22);
//    G->insereArcoID(1,8,21);
//    cout << "menor percurso de "<< 4 << ":\n";// << " para "<< 2 << ":\n\t";
//    Dijkstra* resultado = G->dijkstra(4);
//    cout << resultado->distancia(6);
//    resultado->imprimirDistancias();
//    resultado->imprimirPercurso();

    delete G;

    return t;
}

void imprimirArvoreMinima(vector<Arco*> arco, bool GHash = false){
    for(uint i = 0; i < arco.size(); i++)
        cout << "|A" << arco[i]->getID() << "|" << "\t";
    cout << endl;
}

uint arvoreGeradoraMinima(uint n, uint amostra, bool GHash = false){
    bool completo = true;
    Grafo *di;
    if(completo){
        if(GHash)   di = GrafoHash::grafoCompleto(n+1);
        else        di = GrafoLista::grafoCompleto(n+1);
    }
    else{
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
        di->insereArcoID(5,1,9);
    }

//    di->imprimir();
    uint t;
    t = clock();
    for (uint i=0; i < amostra; i++)
        vector<Arco*> arco = di->algorimoPrim();
    t = clock() - t;

    return t;
//    imprimirArvoreMinima(arco);
}

uint testarKruskal(uint n, bool GHash = false){
    Grafo *di;
//    Grafo *g=new Grafo(), *arvMin=new Grafo();
//    int tam;
//    cout<<"\n\n\TESTE MUITOS NOS:\n\nnnumero de nos:"<<endl;
//    cin>>tam;
//    cout<<"Criando grafo..."<<endl;

    if(GHash)   di = GrafoHash::grafoCompleto(10);
    else        di = GrafoLista::grafoCompleto(10);
//    for(int i=1;i<=n;i++)
//        di->insereNo(i);
//
//    for(int i=1;i<n;i++){
//        for(int j=1;j<n;j++){
//            if(i!=j)
//                di->insereArcoID(i,j,i, false);
//        }
//    }

//    cout<<"\n\nassim que apertar qualquer tecla kruskal comeca a rodar!"<<endl;
//    system("pause");
//    clock_t begin = clock();
//    Grafo* di = grafoCompleto(n+1);
    uint t;
    t = clock();
    vector<Arco*> arcosMin = di->Kruskal();
    t = clock() - t;
    return t;
//    cout<<"quantidade de arcos da solucao:"<<arcosMin.size()<<endl;

//    clock_t end = clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//    cout<<"tempo gasto com kruskal para grafo de:"<<tam<<" nos e "<<tam-1<<" arestas:"<<elapsed_secs<<" segundos!"<<endl;

//    system("pause");

//    uint orig, dest, id;
//
//    for(int i=0;i<arcosMin.size();i++){
//        id=arcosMin.at(i)->getID();
//        orig=arcosMin.at(i)->getNoOrigem()->getID();
//        dest=arcosMin.at(i)->getNoDestino()->getID();
//        arvMin->insereArcoID(orig, dest, id);
//        arvMin->insereArcoID(dest, orig, id);
//    }
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

    vector<Arco*> arcosMin = g->Kruskal();
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
//    cout << "Grafo A:" << endl;
//    A->imprimir();
//    cout << "Grafo A:" << endl;
//    B->imprimir();
//    cout << "Grafo C:" << endl;
//    Grafo *C = A->produtoCartesiano(B);
//    C->imprimir();

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
//    Grafo *A = grafoCompleto(6);
//
//    A->imprimir();
//    cout << "\nGrafo " << (A->ehGrafoEuleriano() ? "" : "nao ") << "eh euleriano.\n";

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

//    G->insereNo(0);
//    G->insereNo(1);
//    G->insereNo(2);
//    G->insereNo(3);
//    G->insereArcoID(0, 1, 0);
//    G->insereArcoID(1, 0, 1);
//    G->insereArcoID(1, 2, 2);
//    G->insereArcoID(2, 1, 3);
//    G->insereArcoID(1, 3, 4);
//    G->insereArcoID(3, 1, 5);
//    G->insereArcoID(3, 2, 6);
//    G->insereArcoID(2, 3, 7);
    G = grafoDuardo(GHash);
    G->imprimir();

    uint idArco;
    while(cin >> idArco)
        cout << "\nArco " << (G->ehArcoPonte(idArco) ? "" : "nao ") << "eh ponte.\n";
    n = n+2;
    return 0;

//
//
//    uint t, id[amostra];
//    for (uint i=0; i < amostra; i++)
//       id[i] = rand()%(n*(n-1));
//
////    cout << "\ntestando arco: " << id << endl;
//
//    t = clock();
//    for (uint i=0; i < amostra; i++){
//        G->ehArcoPonte(id[i]);
//    }
//    t = clock() - t;
//
//    delete G;
//
//    return t;
}

void testeListaHashRidiculo(){
    GrafoHash *G = new GrafoHash(10);
//    GrafoLista *G = new GrafoLista();
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

/** Para Linux */
void pauseGambiarra(){
    char _;
    cout << "\npause gambiarra\t";
    cin >> _;
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
    for(int i=0;i<componentes.size();i++){
        cout<<"Componente "<<i<<endl;
        for(int j=0;j<componentes[i].size();j++){
            cout<<componentes[i][j]->getID()<<endl;
        }
        cout<<endl;
    }
    delete g;
}

void testeKConexo(bool GHash = true){
    Grafo *g;
    g=criarGrafoCompleto(10);
//    if(GHash) g=new GrafoHash(10);
//    else g=new GrafoLista();


//    for(int i=1;i<=6;i++){
//        g->insereNo(i);
//    }
//
//    g->insereArcoID(1,2,1);
//    g->insereArcoID(2,1,2);
//
//    g->insereArcoID(3,2,3);
//    g->insereArcoID(2,3,4);
//
//    g->insereArcoID(3,4,5);
//    g->insereArcoID(4,3,6);
//
//    g->insereArcoID(4,6,7);
//    g->insereArcoID(6,4,8);
//
//    g->insereArcoID(5,6,9);
//    g->insereArcoID(6,5,10);
//
//    g->insereArcoID(1,3,11);
//    g->insereArcoID(3,1,12);
//
//    g->insereArcoID(3,6,13);
//    g->insereArcoID(6,3,14);
//
//    g->insereArcoID(1,6,15);
//    g->insereArcoID(6,1,16);
//
//    g->insereArcoID(5,2,17);
//    g->insereArcoID(2,5,18);
//
//    g->insereArcoID(5,4,19);
//    g->insereArcoID(4,5,20);
//
//    g->insereArcoID(4,2,21);
//    g->insereArcoID(2,4,22);
//
//    g->insereArcoID(5,1,23);
//    g->insereArcoID(1,5,24);

    cout<<g->ehKConexo(3)<<endl;
}

void testeGulosoSteiner(){
    Grafo *g = new GrafoLista(false);
/** EXEMPLO 1*
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
/** EXEMPLO 2 (bem bosta)*/
/**
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
*/
/**/

/** EXEMPLO 3
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

//    g->imprimir(true);

//    vector<Arco*> solucao = g->gulosoSteiner(ids, 3);
//    vector<Arco*> solucao = g->gulosoRandomizadoSteiner(ids, 3, 0.5);

    string pasta = "instanciasTestesSteiner";
    struct dirent *arquivo;
    DIR *dir = opendir(pasta.c_str());
    vector<string> arquivos;

    for(int i=0; arquivo = readdir(dir); i++){
        if(i>1)
            arquivos.push_back(pasta + "/" + (string)arquivo->d_name);
    }

    for(int idArquivo=0; idArquivo<arquivos.size(); idArquivo++){

        cout<<arquivos[idArquivo]<<endl;

        uint * terminais = g->leituraIntanciasSteiner(arquivos[idArquivo]);
        uint ids[terminais[0]];
        for(int j=0; j<terminais[0]; j++)
            ids[j] = terminais[j+1];

        srand(time(NULL));
        vector<Arco*> solucao = g->gulosoSteiner(ids, terminais[0]);

//        cout<<"\nRESULTADO FINAL ARCOS:"<<endl;
        uint somaPesos = 0;
        for(int i=0; i<solucao.size(); i++){
//            cout<<"("<<solucao[i]->getNoOrigem()->getID()<<","<<solucao[i]->getNoDestino()->getID()<<")"<<endl;
            somaPesos += solucao[i]->getPeso();
        }
        cout << "Soma dos pesos: " << somaPesos << endl << endl;
//        system("pause");
    }
//    g->imprimir(true);

}

void testeInstanciasSteiner(){
    cout<<"LISTA\n"<<endl;
    for(int k=0;k<50;k++){
        int i=1;
        char nome[50];
        sprintf(nome, "instanciasSteiner/E/e0%d.stp", i);
        Grafo *g = new GrafoLista(false);
        uint *terminais = g->leituraIntanciasSteiner(nome);

        srand(time(NULL));
        vector<Arco*> solucao = g->gulosoRandomizadoSteiner(terminais, terminais[0], 0.4);

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
        uint *terminais = g->leituraIntanciasSteiner(nome);

        srand(time(NULL));
        vector<Arco*> solucao = g->gulosoRandomizadoSteiner(terminais, terminais[0], 0.4);

        double peso=0;

        for(int i=0; i<solucao.size(); i++)
            peso += solucao[i]->getPeso();

        cout<<"peso obtido pelo guloso: "<<peso<<endl;
        delete g;
    }

}

void testeGulosoRandomizado(){
    srand(time(NULL));
    double menorPeso = HUGE_VAL;
    double alpha = 0.25;
    int it = 30;
    string pasta = "instanciasTestesSteiner";
    struct dirent *arquivo;
    DIR *dir = opendir(pasta.c_str());
    vector<string> arquivos;

    for(int i=0; arquivo = readdir(dir); i++){
        if(i>1)
            arquivos.push_back(pasta + "/" + (string)arquivo->d_name);
    }

    ///apra cada arquivo
    for(int idArquivo=0; idArquivo<arquivos.size(); idArquivo++){

//        system("pause");
        cout<<"instancia:"<<arquivos[idArquivo]<<endl;
        ///para cada iteração com o alpha dado
        for(int k=0;k<it;k++){
            Grafo *g = new GrafoLista(false);
            uint *terminais = g->leituraIntanciasSteiner(arquivos[idArquivo]);
            uint ids[terminais[0]];

    //        cout<<"ids:"<<endl;
            ///iniciar vetor de ids dos terminais comecando do 1, pois a posicao 0 e o numero de terminais
            for(int j=0; j<terminais[0]; j++){
                ids[j] = terminais[j+1];
    //            cout<<ids[j]<<endl;
            }

            vector<Arco*> solucao = g->gulosoRandomizadoSteiner(ids, terminais[0], alpha);

            double peso=0;

            for(int i=0; i<solucao.size(); i++)
                peso += solucao[i]->getPeso();

//            cout<<"peso obtido pelo guloso randomico : "<<peso<<endl;
            if(peso<menorPeso) menorPeso = peso;
            delete g;
        }
        cout<<"melhor solucao obtida:"<<menorPeso<<endl<<endl;
        menorPeso = HUGE_VAL;
    }
}

int main(){
    ///testar na mao
//    testarGrandeInsersao();
//    testarGrafoCompleto();
//    testarGrafoInduzido(); ///entender
//    testarSequenciaNos();  ///entender o sort
//    testarNoArticulacao(); ///ta dando certo nao n�?
//    testarInstanciasStenio();
//    testeComponenteConexa();
//    testePercursoProfundidade();
//    testeBuscaProdundidadeLargura();
//    testeNoArticulacao();
//    testeRubustezVertice();

//    analiseDesempenho(testarDijkstra, 1000, 50, 5, "Teste Dijkstra", "teste_dijkstra.csv");
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

//    cout << THash<uint>::NextPrime(11);
//    testarComponentesConexasNaMao();
//    testeKConexo();




    cout<<"guloso:"<<endl<<endl<<endl;
    testeGulosoSteiner();
    cout<<"guloso randomizado:"<<endl<<endl<<endl;
    testeGulosoRandomizado();



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

    return 0;
}
