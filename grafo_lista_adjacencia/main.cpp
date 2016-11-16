#include <iostream>
#include "Grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

bool buscaVetor(u_int j, u_int aux[], u_int tam){
    cout<<"busca:"<<j<<endl;
    for(u_int y=0; y<tam; y++){
        if(aux[y]==j)
            return true;
    }
    return false;
}

void geraArquivoDeEntrada(u_int tam){
    cout<<"GERACAO DE ARQUIVO DE ENTRADA"<<endl;
    u_int i,j,porcento=0;
    ofstream arq;
    arq.open("data.g");
    arq<<tam<<endl;
    for(u_int k=0; k< tam; k++){
        if( (int)(100.0 * k/tam) > porcento ){
            porcento = (int)(100.0 * k/tam);
            cout<<"#";
        }
        i = k + 1;
        j = tam - k;
        arq<< i << " " << j << endl;
    }
    arq.close();
}

/** retorna grafo escadinha com n vertices */
Grafo* grafoEscadinha(u_int n){
    Grafo* G= new Grafo();
    vector<No*> nos;
    for(u_int i=0; i < n; i++){
        nos.push_back(G->insereNo(i));
        for (u_int j=0; j < i; j++)
            G->insereArco(nos.back(), nos[j], i+j, false);
    }
    G->atualizaGrau();
    return G;
}

Grafo* criarGrafoEscadinha(){
    u_int n_nos;
    cout << "numero de nos(gerar em escadinha de forma cadaga):" << endl;
    cin >> n_nos;
    Grafo *G = grafoEscadinha(n_nos);
    G->imprime();

    return G;
}

Grafo* grafoCompleto(u_int n){
    Grafo* G= new Grafo();
    vector<No*> nos;
    for(u_int i=0; i < n; i++)
        nos.push_back(G->insereNo(i));

    for (u_int i=0; i < n; i++){
        for (u_int j=0; j < n; j++){
            if( i != j )
                G->insereArco(nos[i], nos[j], i*n+j, false);
        }
    }
    G->atualizaGrau();
    return G;
}

Grafo* criarGrafoCompleto(){
    u_int n_nos;
    cout << "numero de nos(gerar grafo completo):" << endl;
    cin >> n_nos;
    Grafo *G = grafoCompleto(n_nos);
    G->imprime();

    return G;
}

Grafo* grafoCircular(u_int n){
    Grafo* G= new Grafo();
    No *aux, *primeiro, *ultimo;
    primeiro = ultimo = G->insereNo(0);
    for(u_int i=1; i < n; i++){
        aux = G->insereNo(i);
        G->insereArco(ultimo, aux, 2*i);
        G->insereArco(aux, ultimo, 2*i+1);
        ultimo = aux;
    }
    if(ultimo != primeiro){
        G->insereArco(ultimo, primeiro, 2*n);
        G->insereArco(primeiro, ultimo, 2*n+1);
    }

    G->atualizaGrau();
    return G;
}

Grafo* grafoDuardo(){
    /// GrafoDuardo.png
    Grafo *di=new Grafo();
    for(int i=1;i<=8;i++)
        di->insereNo(i);

    di->insereArcoID(1,2,1);
    di->insereArcoID(2,1,1);

    di->insereArcoID(1,4,2);
    di->insereArcoID(4,1,2);

    di->insereArcoID(2,4,3);
    di->insereArcoID(4,2,3);

//    di->insereArcoID(2,3,4);
//    di->insereArcoID(3,2,4);
//
//    di->insereArcoID(3,4,5);
//    di->insereArcoID(4,3,5);

    di->insereArcoID(3,5,6);
    di->insereArcoID(5,3,6);

    di->insereArcoID(3,6,7);
    di->insereArcoID(6,3,7);

    di->insereArcoID(5,8,8);
    di->insereArcoID(8,5,8);

    di->insereArcoID(6,7,9);
    di->insereArcoID(7,6,9);

    di->insereArcoID(7,3,10);
    di->insereArcoID(3,7,10);

    di->insereArcoID(6,7,11);
    di->insereArcoID(7,6,11);

    return di;
}

/** testes sucessivos de remove Arco e no em grafo escadinha */
void testeGeral(){
    u_int i, j;
    Grafo *di= criarGrafoEscadinha();

    while(true){
        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->removeArco(i,j);
        di->imprime();

        cout<<"remover no: ";   cin >> i;
        di->removeNo(i);
        system("pause");
    }
}

/** testar a inserção de 100.000 nos e Arcos */
void testarGrandeInsersao(){
    u_int tam = 100000;
    cout<<"numero de nos e Arcos:"<<endl;
    //    cin>>tam;
    geraArquivoDeEntrada(tam);
    Grafo *di= new Grafo();
    char nome[]={"data.g"};
    di->leArquivo(nome);
    delete di;
}

void testarGrafoCompleto(){
    u_int i, j;
    Grafo *di= criarGrafoCompleto();

    while(true){
        cout<<" o grafo " << (di->ehGrafoCompleto() ? "eh " : "nao eh ") << "completo"<<endl;
        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->imprime();
        di->removeArco(i,j);
    }
}

void testarGrafoInduzido(){
    u_int i, j;
    Grafo *induzido, *di= criarGrafoCompleto();

    u_int v[3]={1,2,3};

    while(true){
        induzido = di->subGrafoInduzido(v, 3);
        cout<<" grafo induzido:"<<endl;
        induzido->imprime();

        cout<<"remover Arco de:"; cin>>i;
        cout<<"para:";  cin>>j;
        di->removeArco(i,j);
        di->imprime();

        system("pause");
    }
}

void testarSequenciaNos(){
    Grafo *di= criarGrafoEscadinha();

    cout << "Sequencia de nos:\n\t";
    u_int* seq = di->sequenciaGrau();
    for (u_int i=0; i < di->getNumeroNos(); i++){
        cout << seq[i] << ", ";
    }
    delete di;
}

void testarNoArticulacao(){
    Grafo *di= criarGrafoEscadinha();
    di->insereNo(3);
    di->insereNo(4);
    di->insereArcoID(2,3,4);
    di->insereArcoID(3,4,5);
    di->imprime();
    int id;
    cout<<"Digite o id do no para testar se eh de articulacao:";
    while(true){
        cin>>id;
        cout<<di->ehNoArticulacao(id)<<endl;
        cout<<"Digite o id do no para testar se eh de articulacao:";
    }
}

/** nao faco ideia do que isso ta fazendo */
void testarInstanciasStenio(){
    ///teste de leitura de instancias do stenio
    Grafo *di=new Grafo();
    char nome[50];
    for(int i=1;i<=16;i++){
        if(i<=8)sprintf(nome, "instancias/grafo_1000_%d.txt", i);
        else sprintf(nome, "instancias/grafo_10000_%d.txt", i%9+1);
        di->leArquivo(nome);
        cout<<" arquivo:"<<nome<<" lido com sucesso!"<<endl;
        cout<<" o grafo e completo?"  << di->ehGrafoCompleto()<<"   (0= nao completo, 1=completo)"<<endl;
        system("pause");
//        cin>>i;
//        cout<<"O no:"<<i<<" tem grau:"<<di->buscaNo(i)->getGrau()<<endl;
//        system("pause");
//        for(int i=1;i<=10000;i++)
//            di->removeNoPorID(i);
//        system("pause");
    }
}

void testeComponenteConexa(){
//    Grafo *di= grafoDuardo();
    Grafo* di = grafoEscadinha(8);

    di->imprime();

    for(int i=1;i<=8;i++){
        for(int j=1;j<=i;j++){
            if(i!=j && di->mesmaComponenteFortementeConexa(i,j))
                cout<<i<<"e "<<j<<" estao na mesma componente fortemente conexa"<<endl;
        }
    }
}

void testePercursoProfundidade(){
    Grafo *di=grafoDuardo();

    di->imprime();
    cout<<"busca a partir de 1"<<endl;
    di->percursoProfundidade(di->buscaNo(1));
    di->desmarcaNos();

    cout<<"busca a partir de 3"<<endl;
    cout<<"busca a partir de 3 marcando o 5"<<endl;
    di->buscaNo(5)->setMarcado(true);
    di->percursoProfundidade(di->buscaNo(3));
    di->desmarcaNos();
}

void testeBuscaProdundidadeLargura(){
    Grafo *di = grafoDuardo();
//    Grafo* di = grafoCompleto(5);
//    Grafo* di = grafoEscadinha(5);

    di->imprime();
    cout<<"busca a partir de 1"<<endl;
//    Grafo* Arv = di->buscaProfundidade(di->buscaNo(1));
    Grafo* Arv = di->BuscaEmLargura(di->buscaNo(1));
    Arv->imprime();
    delete Arv;

    cout<<"busca a partir de 3"<<endl;
//    Arv = di->buscaProfundidade(di->buscaNo(3));
    Arv = di->BuscaEmLargura(di->buscaNo(3));
    Arv->imprime();

    cout<<"busca a partir de 8"<<endl;
//    Arv = di->buscaProfundidade(di->buscaNo(3));
    Arv = di->BuscaEmLargura(di->buscaNo(8));
    Arv->imprime();
}

void testeNoArticulacao(){
    Grafo *di=grafoDuardo();

    for(int i=1;i<=8;i++)
        cout<<"numero de nos da componente fortemente conexa de "<<i<<":"<<di->numeroNosComponenteFortementeConexa(di->buscaNo(i))<<endl;

    for(int i=1;i<=8;i++)
        cout<<"O no:"<<i<<" e no de articulacao?"<<di->ehNoArticulacao(i)<<endl;
}

void testeRubustezVertice(){
    Grafo *di=new Grafo();
    u_int *ids;
    char nome[50];
    sprintf(nome, "instancias/grafo_1000_%d.txt", 1);
    di->leArquivo(nome);
    cout<<"arquivo:"<<nome<<" lido"<<endl;
    cout<<" calculando a rubustez de vertices desse grafo enorme!!! vai demorar para um caralho!"<<endl;
    cout<<"rubustes de vertice:"<<di->rubustezVertice(ids);
}

void verificaGrafoKRegular(){
    Grafo *G = criarGrafoEscadinha();
    cout << endl << "Grafo completo? " << G->ehGrafoKRegular() << endl;
}

void verificarGrafoConexo(){
    Grafo *G = criarGrafoCompleto();
    cout << endl << "Grafo conexo? " << G->ehFortementeConexo() << endl;
}

void imprimeVizinhanca(vector<No*> nos){
    for(u_int i = 0; i< nos.size(); i++)
        cout << nos[i]->getID() << "\t";
    cout << endl;
}

void vizinhancaAberta(){
    Grafo* G = criarGrafoEscadinha();
    int id;
    cout<<"Digite o id do no para verificar vizinhanca aberta: ";
    cin>>id;
    vector<No*> nos = G->vizinhancaAberta(id, false);///ver pq nao da pra usar o default nessa caralha

    imprimeVizinhanca(nos);
}

void vizinhancaFechada(){
    Grafo* G = criarGrafoCompleto();
    int id;
    cout<<"Digite o id do no para verificar vizinhanca fechada: ";
    cin>>id;
    vector<No*> nos = G->vizinhancaFechada(id, true);///ver pq nao da pra usar o default nessa caralha

    imprimeVizinhanca(nos);
}

void testeOrdenacaoTopologicaDAG(){
    Grafo *di=new Grafo();
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
    di->ordenacaoTopologicaDAG();
    delete di;
}

void menorCaminho(){
    Grafo* G = criarGrafoCompleto();
    int id1, id2;
    do{
        cout << "Digite o no inicial: ";
        cin >> id1;
        cout << "Digite o no final: ";
        cin >> id2;
        cout << G->consultaMenorCaminhoEntreDoisNos(id1, id2) << endl;
    }while(true);
}

void testarDijkstra(){
    Grafo* G = grafoDuardo();
//    G->insereArcoID(8,1,22);
    G->insereArcoID(1,8,21);
    G->imprime();

    cout << "menor percurso de "<< 4 << ":\n";// << " para "<< 2 << ":\n\t";
    Dijkstra* resultado = G->dijkstra(4);
//    cout << resultado->distancia(6);
    resultado->imprimeDistancias();
    resultado->imprimePercurso();
}

void imprimeArvoreMinima(vector<Arco*> arco){
    for(u_int i = 0; i < arco.size(); i++)
        cout << "|A" << arco[i]->getID() << "|" << "\t";
    cout << endl;
}

void arvoreGeradoraMinima(){
    bool completo = true;
    Grafo *di=new Grafo();
    if(completo)
        di = grafoCompleto(6);
    else{
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

    di->imprime();
    vector<Arco*> arco = di->algorimoPrim();
    imprimeArvoreMinima(arco);
}

void testarKruskalMuitosNos(){
    Grafo *g=new Grafo(), *arvMin=new Grafo();
    int tam;
    cout<<"\n\n\TESTE MUITOS NOS:\n\nnnumero de nos:"<<endl;
    cin>>tam;
    cout<<"Criando grafo..."<<endl;
    for(int i=1;i<=tam;i++){
        g->insereNo(i);
        arvMin->insereNo(i);
    }
    for(int i=1;i<tam;i++){
        g->insereArcoID(i,i+1,i);
        g->insereArcoID(i+1,i,i);
    }
    cout<<"\n\nassim que apertar qualquer tecla kruskal comeca a rodar!"<<endl;
    system("pause");
    clock_t begin = clock();

    vector<Arco*> arcosMin = g->Kruskal();
    cout<<"quantidade de arcos da solucao:"<<arcosMin.size()<<endl;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout<<"tempo gasto com kruskal para grafo de:"<<tam<<" nos e "<<tam-1<<" arestas:"<<elapsed_secs<<" segundos!"<<endl;

    system("pause");

    u_int orig, dest, id;

    for(int i=0;i<arcosMin.size();i++){
        id=arcosMin.at(i)->getID();
        orig=arcosMin.at(i)->getNoOrigem()->getID();
        dest=arcosMin.at(i)->getNoDestino()->getID();
        arvMin->insereArcoID(orig, dest, id);
        arvMin->insereArcoID(dest, orig, id);
    }
}

void testarKruskalNaMao(){
    Grafo *g=new Grafo(), *arvMin=new Grafo();

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
    g->imprime();

    vector<Arco*> arcosMin = g->Kruskal();
    cout<<"quantidade de arcos da solucao:"<<arcosMin.size()<<endl;
    u_int orig, dest, id;

    for(int i=0;i<arcosMin.size();i++){
        id=arcosMin.at(i)->getID();
        orig=arcosMin.at(i)->getNoOrigem()->getID();
        dest=arcosMin.at(i)->getNoDestino()->getID();
        arvMin->insereArcoID(orig, dest, id);
        arvMin->insereArcoID(dest, orig, id);
    }


    cout<<"\n\n\narvMin:\n\n"<<endl;
    arvMin->imprime();
}

int main(){
    ///testar na mao
//    testarGrandeInsersao();
//    testarGrafoCompleto();
//    testarGrafoInduzido(); ///entender
//    testarSequenciaNos();  ///entender o sort
//    testarNoArticulacao(); ///ta dando certo nao né?
//    testarInstanciasStenio();
//    testeComponenteConexa();
//    testePercursoProfundidade();
//    testeBuscaProdundidadeLargura();
//    testeNoArticulacao();
//    testeRubustezVertice();
//    testarDijkstra();
//    verificaGrafoKRegular();
//    verificarGrafoConexo();
//    vizinhancaAberta();
//    vizinhancaFechada();
//    testeOrdenacaoTopologicaDAG();
//    menorCaminho();
//    arvoreGeradoraMinima();
//    testarKruskalNaMao();
    testarKruskalMuitosNos();
    return 0;
}
