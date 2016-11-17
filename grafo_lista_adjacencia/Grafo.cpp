#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <math.h>
#include <map>
#include <set>
#define INFINITO HUGE_VAL

using namespace std;

Grafo::Grafo(){
    listaNos = NULL;
    grau = 0;
    numeroArcos = 0;
    numeroNos = 0;
    flagDir = true;
}

///Fun��o que insere n� no inicio(cabe�a) do grafo
No *Grafo::insereNo(u_int id){
    No *no=new No(id);
    no->setProxNo(listaNos);
    listaNos=no;  ///nao deveria ser um setListaDeNos(this->listaNos)???
    this->numeroNos++;///atualiza numero de vertices(nos)
    return no;
}

/*
/**
 *   Insere no em um no pai
 *   Consequentemente insere aresta
*
NoArv *Arvore::insereNo(NoArv* pai, u_int id){
    NoArv *no = new NoArv(id);
    this->insereArco(pai, no, this->numeroArcos);
    no->setProxNo(listaNos);
    no->setNivel(pai->getNivel()+1);

    ///atualiza numero de vertices(nos) e arcos
    this->numeroNos++;
    this->numeroArcos++;
    return no;
}*/

No *Grafo::buscaNo(u_int id){
    No *no = listaNos;
    while(no!=NULL){
        if(no->getID() == id)
            return no;
        no = no->getProxNo();
    }
    return 0;
}

void Grafo::insereArco(No* noOrigem, No* noDestino, u_int id, bool atualizarGrau){
    noOrigem->insereArco(noDestino, id);
    this->numeroArcos++;
    if (atualizarGrau)
        this->atualizaGrau();
}

/**
Fun��o que insere arco na estrutura:

faz a busca do no entrada(idOrigem) do arco no grafo [arco:(idOrigem----->praOnde)]
cria o arco que sera inserido como arco desse no encontrado na busca
define para onde(saida) no arco com o no idDestino
arco inserido com sucesso
**/
void Grafo::insereArcoID(u_int idOrigem, u_int idDestino, u_int id, bool atualizarGrau){
    No *noOrigem = buscaNo(idOrigem);
    No *noDestino = buscaNo(idDestino);
    this->insereArco(noOrigem, noDestino, id, atualizarGrau);
}

/** desmarcar os nos do grafo */
void Grafo::desmarcaNos(){
    for(No *i = listaNos; i != NULL; i = i->getProxNo())
        i->setMarcado(false);
}

bool Grafo::mesmaComponenteFortementeConexa(u_int id1, u_int id2){
    No *i1 = buscaNo(id1), *i2 = buscaNo(id2);
    if(i1!=NULL && i2!=NULL)
        return mesmaComponenteFortementeConexa(i1, i2);
    else
        return false;
}

bool Grafo::mesmaComponenteFortementeConexa(No *i1, No *i2){
    ///Se existe caminho de i1 pra i2
    this->desmarcaNos();
    percursoProfundidade(i1);
    bool result1=i2->getMarcado();

    ///Se existe caminho de i2 pra i1
    this->desmarcaNos();
    percursoProfundidade(i2);
    bool result2=i1->getMarcado();

    this->desmarcaNos();
    return result1 && result2;
}

/**
Percorre grafo a partir de um n� e sai marcando todo mundo da mesma componente conexa
*/
//void Grafo::percursoProfundidade(No *no,  void(Grafo::*funcao)(No*)){
void Grafo::percursoProfundidade(No *no){
    if(no == NULL)
        cout<<"\n No NULL \n"<<endl;
    else{
        if(no->getMarcado() == false){
//            cout<<"marcando: "<<no->getID()<<endl;
            no->setMarcado(true);
            this->contAux++;
//            if (funcao != NULL)
//                (this->*funcao)(no);
            for(Arco *a=no->getListaArcos(); a!=NULL; a=a->getProxArco())
                    percursoProfundidade(a->getNoDestino());
        }
    }
}
/**
 * Auxiliar pata buscaProfundidade
 */
void Grafo::auxBuscaProfundidade(No* noGrafo, No* noArv, Grafo* Arv){
    noGrafo->setMarcado(true);

    /// percorre adjacencias do (noGrafo)
    for(Arco *a = noGrafo->getListaArcos(); a != NULL; a = a->getProxArco()){
        No* proxNo = a->getNoDestino();
        if (!proxNo->getMarcado()){
            ///Insere proximo (no) na arvore
            No* novoNoArv = Arv->insereNo(proxNo->getID());
            Arv->insereArco(noArv, novoNoArv, a->getID());
            novoNoArv->setNivel(noArv->getNivel()+1);

            auxBuscaProfundidade(proxNo, novoNoArv, Arv);
        }
    }
}

/**
 * Constroi a arvore (Arv) a partir da busca em profundidade em (noGrafo)
 */
Grafo* Grafo::buscaProfundidade(No *no){
    if(no == NULL)
        return NULL;

    this->desmarcaNos();
    Grafo* Arv = new Grafo();

    ///raiz da arvore
    No* raiz = Arv->insereNo(no->getID());
    raiz->setNivel(0);
    auxBuscaProfundidade(no, raiz, Arv);

    return Arv;
}

/**
 * Constroi a arvore (Arv) a partir da busca em largura em (noGrafo)
 */
Grafo* Grafo::BuscaEmLargura(No *noGrafo){
    this->desmarcaNos();
    queue<No*> fila;

    Grafo* Arv = new Grafo();
    ///raiz da arvore (Arv)
    No* noArv = Arv->insereNo(noGrafo->getID());
    noArv->setNivel(0);

    noGrafo->setMarcado(true);
    fila.push(noGrafo);

    ///enquanto a fila nao esta vazia
    while(!fila.empty()){
        ///vertice que esta no inicio da fila
        noArv = Arv->buscaNo(fila.front()->getID());

        /// percorre adjacencias do (noGrafo)
        for(Arco *a = fila.front()->getListaArcos(); a != NULL; a = a->getProxArco()){//enquanto a lista de adjacencia do vertice1 nao acaba
            No* proxNo = a->getNoDestino();
            if(!proxNo->getMarcado()){
                ///Marca vertice e o poe na fila
                proxNo->setMarcado(true);
                fila.push(proxNo);

                ///Insere proximo (no) na arvore
                No* novoNo = Arv->insereNo(proxNo->getID());
                Arv->insereArco(noArv, novoNo, a->getID());
                novoNo->setNivel(noArv->getNivel()+1);
            }
        }
        ///retira vertice da fila
        fila.pop();
    }

    return Arv;
}

Grafo *Grafo::subGrafoInduzido(u_int E[], u_int tam){
    Grafo *induzido=new Grafo();
    for(u_int i=0; i<tam; i++)
        induzido->insereNo(E[i]);
    No *no;
    for(u_int i=0; i<tam; i++){
        no=this->buscaNo(E[i]);
        ///procura Arcos do grafo que ligam os vertices do grafo induzido
        for(Arco *a=no->getListaArcos(); a!=NULL; a=a->getProxArco()){
            for(u_int j=0; j<tam; j++){
//                if(a->getNoDestino() == this->buscaNo(E[j]))
                if(a->getNoDestino()->getID() == E[j])
                    induzido->insereArcoID(no->getID(), a->getNoDestino()->getID(), a->getID());
            }
        }
    }
    return induzido;
}

bool Grafo::ehGrafoKRegular(u_int k){
    for(No *i=listaNos; i!=NULL; i=i->getProxNo()){
        if(i->getGrau()!=k)
            return false;
    }
    return true;
}

///Funcao Iago
bool Grafo::ehGrafoKRegular(){
    No* inicio = this->listaNos;
    return ehGrafoKRegular(inicio->getGrau());
}

bool Grafo::ehGrafoCompleto(){
    return ehGrafoKRegular(this->numeroNos-1);
}

void Grafo::removeArco(No* noOrigem, No* noDestino, bool atualizarGrau){
    if(noOrigem!=NULL && noDestino != NULL && noOrigem->getListaArcos()!=NULL){
        Arco* arcoRemover = NULL;
        ///se primeiro arco sera removido
        if(noOrigem->getListaArcos()->getNoDestino() == noDestino){
            arcoRemover = noOrigem->getListaArcos();
            noOrigem->setListaArcos(arcoRemover->getProxArco());
        }else{
            Arco *anterior= noOrigem->getListaArcos();
            while(anterior->getProxArco() != NULL &&
                  anterior->getProxArco()->getNoDestino() != noDestino)
                anterior=anterior->getProxArco();

            /// arco existe no no
            if(anterior->getProxArco()!=NULL){
                Arco *sucessor = anterior->getProxArco()->getProxArco();
                arcoRemover = anterior->getProxArco();
                anterior->setProxArco(sucessor);
            }
        }
        if(arcoRemover != NULL){
            delete arcoRemover;
            this->numeroArcos--;
            noOrigem->setGrau(noOrigem->getGrau() - 1);

            if(atualizarGrau)
                this->atualizaGrau();
            }
    }
}

void Grafo::removeArco(u_int idOrigem, u_int idDestino){
    this->removeArco(buscaNo(idOrigem), buscaNo(idDestino));
}

void Grafo::removeArcosLigadasAoNo(No *no, bool atualizaGrau = true){
    No *aux=this->listaNos;
    while(aux != NULL){
        this->removeArco(aux, no, false);
        aux=aux->getProxNo();
    }
    if(atualizaGrau)
        this->atualizaGrau();
}

void Grafo::removeArcos(No *no, bool atualizarGrau = true){
    this->numeroArcos -= no->getGrau();
    no->removeArcos();
    if(atualizarGrau)
        this->atualizaGrau();
}

void Grafo::atualizaGrau(){
    this->grau=0;
    for(No *i=listaNos; i!=NULL; i=i->getProxNo()){
        if(i->getGrau() > grau)
            grau=i->getGrau();
    }
}

///Faz a atualiza��o dos graus de Entrada e Saida do digrafo para deteccao de n�s fonte e sinks
void Grafo::atualizaGrausEntradaSaidaDosNos(){
    ///Zerar todos os graus de entrada e de saida
    for(No *i=listaNos; i!=NULL; i=i->getProxNo()){
        i->setGrauEntrada(0);
        i->setGrauSaida(0);
    }

    ///Percorrer todos os nos e suas listas de adjacencia incrementando os graus de entrada e de saida
    for(No *i=listaNos; i!=NULL; i=i->getProxNo()){
        for(Arco *j=i->getListaArcos(); j!=NULL; j=j->getProxArco()){
            i->setGrauSaida(i->getGrauSaida()+1);
            j->getNoDestino()->setGrauEntrada(j->getNoDestino()->getGrauEntrada()+1);
        }
    }
}

void Grafo::removeNo(u_int id){
    No *noRemover=NULL;

    ///se a listaNos eh o no a ser removido
    if(listaNos->getID()==id){
        noRemover = listaNos;
        listaNos = listaNos->getProxNo();
    }
    else{
        No *anterior= listaNos;
        while(anterior->getProxNo()!=NULL &&
              anterior->getProxNo()->getID()!=id)
            anterior=anterior->getProxNo();

        /// no existe no grafo
        if(anterior->getProxNo() != NULL){
            No *sucessor = anterior->getProxNo()->getProxNo();
            noRemover = anterior->getProxNo();
            anterior->setProxNo(sucessor);
        }
    }
    if(noRemover!=NULL){
//        cout <<"\nremovendo no com id:" << noRemover->getID()<<endl;
        this->removeArcos(noRemover, false);
        this->removeArcosLigadasAoNo(noRemover, false);
        this->atualizaGrau();
        delete noRemover;
        this->numeroNos--;
    }
}

bool compareReverse(u_int a, u_int b){
    return a >= b;
}

/** retorna a sequencia de inteiros dos graus do no */
u_int* Grafo::sequenciaGrau(){
    u_int* seq = new u_int [this->numeroNos];
    u_int cont = 0;
    No* noAux = listaNos;
    while(noAux != NULL){
        seq[cont] = noAux->getGrau();
        noAux = noAux->getProxNo();
        cont++;
    }

    sort(seq, seq+cont, compareReverse);
    return seq;
}

void Grafo::imprime(){
    cout<<"Grau do Grafo: "<<this->grau<<"\tnumero de nos: "<<this->numeroNos
    <<"\tnumero de arcos: "<<this->numeroArcos<<endl;
    No *no=listaNos;
    while(no!=NULL){
        no->imprime();
        no=no->getProxNo();
    }
}

void Grafo::leArquivo(char nome[]){
    u_int i,j,n_nos;
    ifstream arq;
    arq.open(nome);
    if(arq.good()==false)
        cout<<"arquivo nao encontrado"<<endl;
    arq>>n_nos;
    for(u_int i=1;i<=n_nos;i++)
        insereNo(i);
    while(arq.good()){
        arq>>i>>j;
        insereArcoID(i,j, numeroArcos+1);
    }
}

bool Grafo::saoAdjacentes(u_int id1, u_int id2){
    No *no1=buscaNo(id1);
    No *no2=buscaNo(id2);
    return saoAdjacentes(no1, no2);
}

bool Grafo::saoAdjacentes(No *no1, No *no2){
    ///ser ou n�o digrafo n�o interfere na resposta
    return no1->ehAdjacente(no2)||no2->ehAdjacente(no1);
}

/**
FUN��O AUXILIAR PARA FAZER A FUN��O DO DUARDO FUNCIONAR.
Recebe um n� e retorna o numero de nos da componente conexa que o n� esta presente.
*/
u_int Grafo::numeroNosComponenteFortementeConexa(No *no1){
    u_int n_nos=0;
    for(No *no2=this->listaNos; no2!=NULL; no2=no2->getProxNo()){
        if(this->mesmaComponenteFortementeConexa(no1, no2))// && this->mesmaComponenteFortementeConexa(no2, no1))
            n_nos++;
    }
    return n_nos;
}

int Grafo::auxEhNoArticulacao(No *no){
    ///Percurso em profundidade
    if(no->getMarcado()==false){
            no->setMarcado(true);
            for(Arco *a=no->getListaArcos(); a!=NULL; a=a->getProxArco())
                return 1+auxEhNoArticulacao(a->getNoDestino());
    }
    return 0;
}
//void Grafo::incrementaContador(No* n){
//    this->contAux++;
//}

/**
ESSA FUN��O DO JEITO QUE ESTAVA ANTES N�O FUNCIONAVA!!!!!
Marca o n�, faz a busca em profundidade e ve se o numero de nos marcados e menor do que o numero de nos da componente conexa,
se for verdade o no e de articulacao.
*/
bool Grafo::ehNoArticulacao(No *no){
    if(no!=NULL){
        u_int cont=0;
        this->desmarcaNos();
        no->setMarcado(true);
    //    cout<<"busca em progundidade come�ando em:"<<no->getListaArcos()->getNoDestino()->getID()<<endl;
        if(no->getListaArcos()!=NULL){
            this->percursoProfundidade(no->getListaArcos()->getNoDestino());
            for(No *i=this->getListaNos(); i!=NULL; i=i->getProxNo()){
                if(i->getMarcado()==true)
                    cont++;
            }
        //    cout<<"cont de nos marcados:"<<cont<<endl;
        //    cout<<"numero de nos de "<< no->getID()<<" e:"<<NosComponenteConexa(no)<<endl;
            bool result = (cont<this->numeroNosComponenteFortementeConexa(no));
            this->desmarcaNos();
            return result;
        }
        else
            return false;
    }
    else return false;

    ///COMO O MELAO TINHA FEITO2
//    ///Marca o no como visitado e faz busca em profundidade
//    ///no seu primeiro adjacente, contando os nos visitados.
//    ///Se o numero de nos for menor que n-1, significa que
//    ///aquele no marcado no inicio eh de articulacao.
//
//    this->desmarcaNos();
//    no->setMarcado(true);
//    Arco *a=no->getListaArcos();
//    if(a==NULL) return false;
//    No *noAux=a->getNoDestino();
//    u_int cont=this->auxEhNoArticulacao(noAux);
//    ///tem que verificar no final se todos os n�s da mesma componente conexa estao marcados no final.
//    if(cont<this->NosComponenteConexa(no)) { cout<<"cont:"<<cont<<endl; return true;};
//    return false;
//    this->desmarcaNos();///MEL�O ESQUECEU DE DESMARCAR OS N�S DEPOIS
}

bool Grafo::ehNoArticulacao(u_int id){
    No* no=buscaNo(id);
    if(no != NULL)
        return this->ehNoArticulacao(buscaNo(id));
    return false;
}

/** PENSANDO...
bool Grafo::ehArcoPonte(Arco* arco){
    this->desmarcaNos();
    ///Verificar se componente fortemente conexa tem ordem = 2
    arco->getNoDestino()->setMarcado(true);
    this->setContAux(0);
    this->percursoProfundidade(arco->getNoOrigem());
    bool 2_conexo = this->contAux == 0;


    return ehNoArticulacao(arco->getNoDestino());
}
*/

/**
Se o grafo � fortemente conexo cada par de vertice (a,b) estao na mesma conponente conexa.
*/
bool Grafo::ehFortementeConexo(){
    for(No *inicio1=listaNos; inicio1!=NULL; inicio1=inicio1->getProxNo()){
        for(No *inicio2=listaNos; inicio2!=NULL; inicio2=inicio2->getProxNo()){
            if(!this->mesmaComponenteFortementeConexa(inicio1, inicio2))
                return false;
        }
    }
    return true;
}

/**
Fun��o para retornar a rubustez de um grafo baseado nas vertices.
A rubustez baseada em vertices indica o numero maximo de vertices que podem ser removidos do grafo mantendo a conexividade.
Se o no a ser removido nao for no de articula��o entao o numero de componentes conexas apos a remo��o do n� se mantem.
Assim qualquer no que nao seja de articula��o pode ser removido e o grafo ainda se mantem conexo, a rubustez e entao
o numero maximo de nos menos o numero de nos de articulacao.
Coloquei pra receber os ids dos nos de articulacao pra conferir na fun��o '' do main se esta funcionando.

IMPORTANTE!!!!
No caso a fun��o retorna o numero de nos que voce pode retirar considerando todas as componentes conexas.
Se uma componente conexa pode ter 5 nos removidos e a outra pode ter 6 a fun��o retorna 11.
recebe um vetor de ids pra salvar os ids daqueles nos que nao podem ser removidos e sao de articulacao
*/
u_int Grafo::rubustezVertice(u_int *ids){
    u_int rubustez=this->numeroNos, i=0;
    ids=new u_int[this->numeroNos];
    for(No *inicio=this->listaNos; inicio!=NULL; inicio=inicio->getProxNo()){
        cout<< ( (float)( 1001 - inicio->getID() )/this->numeroNos ) * 100 <<"%"<<endl;
        if(this->ehNoArticulacao(inicio)){
            cout<<"achou articulacao"<<endl;
            rubustez--;
            ids[i]=inicio->getID();///armazenar id dos nos de articula��o
            i++;
        }
    }

    return rubustez;
}

vector<No*>  Grafo::vizinhancaAberta(u_int id, bool fechada){
    return vizinhancaFechada(id, fechada);
}

vector<No*> Grafo::vizinhancaFechada(u_int id, bool fechada){
    No* no=buscaNo(id);
    vector<No*> nos;
    if(fechada)
        nos.push_back(no);
    if(no != NULL)
        for(Arco *a=no->getListaArcos(); a!=NULL; a=a->getProxArco())
            nos.push_back(a->getNoDestino());
    return nos;
}

///Cria um novo Grafo, com os mesmos n�s e arestas (por id) do grafo atual
Grafo* Grafo::clone(){
    int idArvore=1;
    Grafo* G=new Grafo();
    for(No *i=listaNos; i!=NULL; i=i->getProxNo()){
        G->insereNo(i->getID())->setIdArvore(idArvore);///id auxiliar para algoritmo de kruskal
        idArvore++;
    }
    for(No *i=listaNos; i!=NULL; i=i->getProxNo()){
        for(Arco *j=i->getListaArcos(); j!=NULL; j=j->getProxArco()){
            G->insereArcoID(i->getID(), j->getNoDestino()->getID(), j->getID());
        }
    }

    ///Precisa retirar algumas atribuicoes redundantes?
    G->setFlagDir(this->flagDir);
    G->grau=this->grau;
    G->numeroNos=this->getNumeroNos();
    G->numeroArcos=this->getNumeroArcos();
    return G;
}

/**
 * Detecta todos os n�s fonte e adiciona aos candidatos.
 * A cada iteracao, pega um candidato, coloca na solucao,
 * remove ele do grafo e verifica novos candidatos.
 */
vector<No*> Grafo::ordenacaoTopologicaDAG(){
    vector<No*> solucao;
    vector<u_int> candidatos;
    Grafo* G=this->clone();
    for(u_int k=0;k<this->getNumeroNos();k++){
        G->atualizaGrausEntradaSaidaDosNos();
        for(No *i=G->listaNos; i!=NULL; i=i->getProxNo()){
            if(i->getGrauEntrada()==0){
                candidatos.push_back(i->getID());
                G->removeNo(i->getID());
            }
        }
        solucao.push_back(this->buscaNo(candidatos[0]));//Vou colocar na solucao ponteiros do grafo original(this)
        candidatos.erase(candidatos.begin());
    }
    cout<<"Ordenacao topologica do DAG por ID:"<<endl;
    for(u_int m=0;m<this->getNumeroNos();m++){
        cout<<solucao[m]->getID()<<endl;
    }
    delete G;
    return solucao;
}

/**
 * Percorre todos os n�s do grafo e, para cada n�, incrementa o contador e
 * realiza a busca em profundidade caso ele n�o esteja marcado. A busca em profundidade marca
 * os n�s pertencentes a uma mesma componente conexa, logo o contator n�o vai ser incrementado ao passar por um n� j� percorrido.
*/
int Grafo::numeroComponentesConexas(){
    this->desmarcaNos();
    int num=0;
    for(No *i=this->getListaNos(); i!=NULL; i=i->getProxNo()){
        if(i->getMarcado()==false){
            num++;
            percursoProfundidade(i);
        }
    }
    return num;
}

Arco* Grafo::buscaArco(u_int id1, u_int id2){
    No *no1=buscaNo(id1);
    No *no2=buscaNo(id2);
    return buscaArco(no1, no2);
}

Arco* Grafo::buscaArco(No* no1, No* no2){
    Arco *aux = no1->getListaArcos();
    while(aux!=NULL){
        if(no2 == aux->getNoDestino())
            return aux;
        aux = aux->getProxArco();
    }
    return NULL;
}

double Grafo::consultaMenorCaminhoEntreDoisNos(u_int i, u_int j){
    double **menorCaminho = algoritmoFloyd();
    return menorCaminho[i][j];
}

double Grafo::dijkstra(No* origem, No* destino){
    if(origem != NULL && destino != NULL)
        return this->dijkstra(origem)->distancia(destino->getID());
    else
        return -1.0;
}

double Grafo::dijkstra(u_int origem, u_int destino){
    return this->dijkstra(buscaNo(origem), buscaNo(destino));
}

Dijkstra* Grafo::dijkstra(u_int origem){
    return dijkstra( buscaNo(origem) );
}

/**
* Usa Algoritmo de Dijkstra para criar informa��es de menor dist�ncia (e se caminho)
* para todos oa nos do Grafo
*/
Dijkstra* Grafo::dijkstra(No* origem){
    this->desmarcaNos();
    ///mapeamento (id -> pos) nos vetores (distancias) e (naoVisitados)
    map<u_int, u_int> pos;
    double *distancias = new double [this->numeroNos];

    /*** LEMBRAR DE OTIMIZAR CONJUNTO DE NAO VISITADOS ***/
    u_int s = 0;    ///numero de nos na solucao
    No* nos[this->numeroNos];

    /// Auxiliar para guardar o caminho
    Arco** proximo = new Arco*[this->numeroNos];

    ///Inicializa conjuntos
    u_int i = 0;
    for( No* no=listaNos; no != NULL; no = no->getProxNo(), i++){
        pos[no->getID()] = i;         ///mapeia ids com posicoes
        distancias[i] = INFINITO;     ///distancia "infinita"
        nos[i] = no;         ///todos os nos
        proximo[i] = NULL;
    }

    distancias[ pos[origem->getID()] ] = 0;

    ///enquanto solu��o n�o estiver completa
    while(s < this->numeroNos){

        ///busca vertice com menor distancia
        u_int posMaisProx = 0;
        while(nos[posMaisProx] != NULL && nos[posMaisProx]->getMarcado()){
            posMaisProx++;  ///primeira posicao desmarcada
        }

        for (u_int i=posMaisProx+1; i < this->numeroNos ; i++){
            if (!nos[i]->getMarcado() && distancias[i] < distancias[posMaisProx]){
                posMaisProx = i;
            }
        }

        ///"remove" dos na visitados
        No* maisProx = nos[posMaisProx];
        maisProx->setMarcado(true);
        s++;

        /// para cada adjacencia de (maisProx)
        for (Arco* arco = maisProx->getListaArcos(); arco != NULL; arco = arco->getProxArco()){
            ///dist�ncia de (origem) passando por (maisProx)
            double auxDist = distancias[posMaisProx] + arco->getPeso();
            u_int posAux = pos[arco->getNoDestino()->getID()];
            ///se (auxDist) for menor que o caminho atual
            if ( auxDist < distancias[posAux] ){
                distancias[posAux] = auxDist;
                proximo[posAux] = arco;
            }
        }
    }

    ///Retorna estrutura Dijkstra
    return new Dijkstra(this, origem, pos, distancias, proximo);
}

double** Grafo::algoritmoFloyd(){
    double infinito = INFINITO;
    Arco *aux;
    int n = this->getNumeroNos();
    double **mat = new double*[n];
    for(int i = 0; i < n; i++){
        mat[i] = new double[n];
        for(int j = 0; j < n; j++){
            if(i == j) ///Assumindo que nao vai existir selfie loop
                mat[i][j] = 0;
            else{
                aux = buscaArco(i, j);
                if(aux != NULL)
                    mat[i][j] = aux->getPeso();
                else
                    mat[i][j] = infinito;
            }
        }
    }
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(mat[i][j] > mat[i][k] + mat[k][j])
                    mat[i][j] = mat[i][k] + mat[k][j];
            }
        }
    }
    return mat;
}

/***
funcionando parciamente para grafos direcioandos. Internet diz que o algoritmo so serve para grafos nao direcionado. Verificar.
Verificar complexidade do algoritmo.
***/
vector<Arco*> Grafo::algorimoPrim(){
///tratar caso onde um v�rtice tem dois outros vertices com os pesos as arestas iguais
    vector<No*> solucao;
    vector<Arco*> arcosSolucao;

    double valorMenorPeso = INFINITO;

    No* nos = this->listaNos;
    No *noDestinoSolucao, *noOrigemSolucao;

    this->desmarcaNos();
    nos->setMarcado(true);

    solucao.push_back(nos);
    u_int qtdCandidatos = getNumeroNos()-solucao.size();

    while(qtdCandidatos > 0){
        valorMenorPeso = INFINITO;
        for(u_int i = 0; i < solucao.size(); i++){
            for(Arco *a=solucao[i]->getListaArcos(); a!=NULL; a=a->getProxArco()){
                if(a->getPeso() < valorMenorPeso && !a->getNoDestino()->getMarcado()){
                    valorMenorPeso = a->getPeso();
                    noOrigemSolucao = solucao[i];
                    noDestinoSolucao = a->getNoDestino();
                }
            }
        }
        if(valorMenorPeso != INFINITO){
            noDestinoSolucao->setMarcado(true);
            solucao.push_back(noDestinoSolucao);
            arcosSolucao.push_back(buscaArco(noOrigemSolucao, noDestinoSolucao));
            qtdCandidatos--;
        }
        else qtdCandidatos = 0;
   }
//    cout << arcosSolucao.size() << endl;
   return arcosSolucao;
}

///operador para ordenar as arestas por peso (Usado no algoritmo de Kruskal)
bool menorPeso(Arco *a1, Arco *a2){return ( a1->getPeso() < a2->getPeso() );};

vector<Arco*> Grafo::Kruskal(){
    ///todos os arcos para ordenacao e 'solucao' que e a solucao (os arcos que forma as arvore/floresta)
    vector<Arco*> arcos, solucao;
    u_int idArvore=1;

    ///joga todos os arcos no vector para depois ordenar
    for(No *i=this->getListaNos(); i!=NULL; i=i->getProxNo()){
        ///cada no esta inicialmente em uma arvore separada
        i->setIdArvore(idArvore);
        for(Arco *a=i->getListaArcos(); a!=NULL; a=a->getProxArco())
                arcos.push_back(a);
        idArvore++;
    }

    sort(arcos.begin(), arcos.end(), menorPeso);

    ///nos origem e destino para cada arco
    No *orig, *dest;
    u_int id_orig, id_dest;

    for(u_int pos=0; pos <arcos.size(); pos+=2){
        orig=arcos.at(pos)->getNoOrigem();
        dest=arcos.at(pos)->getNoDestino();

        id_orig=orig->getIdArvore();
        id_dest=dest->getIdArvore();

        ///se arco conecta nos de componentes conexas diferentes ele esta na solucao
        if(id_orig!=id_dest){
            solucao.push_back(arcos.at(pos));
            ///coloca ids iguais para nos em mesma componente conexa
            for(No *i=this->getListaNos(); i!=NULL; i=i->getProxNo()){
                if(i->getIdArvore()==id_orig)
                    i->setIdArvore(id_dest);
            }
        }
    }

    return solucao;
}

/**
 * Retorna o grafo C resultado do produto cartesiano com (this x B)
 * ##############   FAZ ALGUM SENTIDO PARA DIGRAFOS???  #################
*/
Grafo* Grafo::produtoCartesiano(Grafo* B){
    Grafo* A = this;    /// <------ pura didatica
    /// C = A x B
    u_int nNosA = A->getNumeroNos();
    u_int nNosB = B->getNumeroNos();
    u_int idAresta = 0;

    map<u_int, u_int> posB; ///mapeia idB->posB

    ///matriz auxiliar de nos de C
    No ***nosC = new No**[nNosA];
    for(u_int i = 0; i < nNosA; i++)
        nosC[i] = new No*[nNosB];

    Grafo* C = new Grafo();
    /// Cria todos os nos de de C
    u_int a = 0, b = 0;
    for(A->itInicio(); A->getIt()!=NULL; A->itProx(), a++){
        for(B->itInicio(); B->getIt()!=NULL; B->itProx(), b++){
//            printf("\na=%d  b=%d", a, b);
            posB[B->getIt()->getID()] = b;  ///mapeia noB
            nosC[a][b] = C->insereNo(nNosB*a + b);
            /// faz "conexao vertical"
            if( a > 0 ){
                C->insereArco(nosC[a-1][b], nosC[a][b], idAresta++, false);
                C->insereArco(nosC[a][b], nosC[a-1][b], idAresta++, false);
            }
        }
        b = 0;
    }
//    C->imprime();

    /// faz "conexoes tranversais"
    for(B->itInicio(); B->getIt()!=NULL; B->itProx(), b++){
        No* noB = B->getIt();
        for(noB->itInicio(); noB->getIt()!= NULL; noB->itProx()){
            Arco* arcoB = noB->getIt();
            for(u_int a = 0; a < nNosA; a++){
                u_int auxPos1 = posB[ noB->getID() ];
                u_int auxPos2 = posB[ arcoB->getNoDestino()->getID() ];
//                printf("criando aresta entre %d e %d", nosC[a][auxPos1]->getID(), nosC[a][auxPos2]->getID());
                C->insereArco( nosC[a][auxPos1], nosC[a][auxPos2], idAresta++, false);
//                C->insereArco( nosC[a][auxPos2], nosC[a][auxPos1], idAresta++, false);
//                C->imprime()
;            }

        }
    }

    C->atualizaGrau();

    /// desaloca matriz auxiliar
    for(u_int i = 0; i < nNosA; i++)
        delete [] nosC[i];
    delete [] nosC;

    return C;
}

/***
prim(G) # G eh grafo
    # Escolhe qualquer v�rtice do grafo como vertice inicial/de partida
    s <- seleciona-um-elemento(vertices(G))

    para todo v E vertices(G)
        pi[v] <- nulo
    Q <- {(0, s)}
    S <- nulo

    enquanto Q != nulo
        v <- extrair-m�n(Q)
        S <- S U {v}

        para cada u adjacente a v
            se u !E S e pesoDaAresta(pi[u]->u) > pesoDaAresta(v->u)
                Q <- Q \ {(pesoDaAresta(pi[u]->u), u)}
                Q <- Q U {(pesoDaAresta(v->u), u)}
                pi[u] <- v

    retorna {(pi[v], v) | v E vertices(G) e pi[v] != nulo}
***/

/** IMPLEMENTAR DESTRUTOR */
Grafo::~Grafo(){}
