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
    grau = 0;
    numeroArcos = 0;
    numeroNos = 0;
    flagDir = true;
}

void Grafo::insereArco(No* noOrigem, No* noDestino, uint id, bool atualizarGrau){
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
void Grafo::insereArcoID(uint idOrigem, uint idDestino, uint id, bool atualizarGrau){
    No *noOrigem = buscaNo(idOrigem);
    No *noDestino = buscaNo(idDestino);
    this->insereArco(noOrigem, noDestino, id, atualizarGrau);
}

/** desmarcar os nos do grafo */
void Grafo::desmarcaNos(){
    for(itInicio(); !itEhFim(); itProx())
        this->getIt()->setMarcado(false);
}

bool Grafo::mesmaComponenteFortementeConexa(uint id1, uint id2){
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
            for(no->itInicio(); !no->itEhFim(); no->itProx())
                percursoProfundidade(no->getIt()->getNoDestino());
        }
    }
}

/**
 * Auxiliar para buscaProfundidade
 */
void Grafo::auxBuscaProfundidade(No* noGrafo, No* noArv, Grafo* Arv){
    noGrafo->setMarcado(true);

    /// percorre adjacencias do (noGrafo)
    for(noGrafo->itInicio(); !noGrafo->itEhFim(); noGrafo->itProx()){
//    for(Arco *a = noGrafo->getListaArcos(); a != NULL; a = a->getProxArco()){
        Arco *a = noGrafo->getIt();
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
    Grafo* Arv = this->novoGrafo(this->getNumeroNos());

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

    Grafo* Arv = novoGrafo(this->getNumeroNos());
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
        for(fila.front()->itInicio(); !fila.front()->itEhFim(); fila.front()->itProx()){//enquanto a lista de adjacencia do vertice1 nao acaba
            Arco *a = fila.front()->getIt();
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

Grafo *Grafo::subGrafoInduzido(uint E[], uint tam){
    Grafo *induzido = novoGrafo(tam);
    for(uint i=0; i<tam; i++)
        induzido->insereNo(E[i]);
    No *no;
    for(uint i=0; i<tam; i++){
        no=this->buscaNo(E[i]);
        ///procura Arcos do grafo que ligam os vertices do grafo induzido
        for(no->itInicio(); !no->itEhFim(); no->itProx()){
//        for(Arco *a=no->getListaArcos(); a!=NULL; a=a->getProxArco()){
            Arco *a = no->getIt();
            for(uint j=0; j<tam; j++){
//                if(a->getNoDestino() == this->buscaNo(E[j]))
                if(a->getNoDestino()->getID() == E[j])
                    induzido->insereArcoID(no->getID(), a->getNoDestino()->getID(), a->getID());
            }
        }
    }
    return induzido;
}

bool Grafo::ehGrafoKRegular(uint k){
    for(itInicio(); !itEhFim(); itProx()){
        if(getIt()->getGrau()!=k)
            return false;
    }
    return true;
}

///Funcao Iago
bool Grafo::ehGrafoKRegular(){
    this->itInicio();
    return ehGrafoKRegular(this->getIt()->getGrau());
}

bool Grafo::ehGrafoCompleto(){
    return ehGrafoKRegular(this->numeroNos-1);
}

void Grafo::removeArco(No* noOrigem, No* noDestino, bool atualizarGrau){
    if(noOrigem!=NULL && noDestino != NULL){
        noOrigem->removeArco(noDestino);
        noOrigem->setGrau(noOrigem->getGrau() - 1);
        this->numeroArcos--;
        if(atualizarGrau)
            atualizaGrau();
    }
//    if(noOrigem!=NULL && noDestino != NULL && noOrigem->getListaArcos()!=NULL){
//        Arco* arcoRemover = NULL;
//        ///se primeiro arco sera removido
//        if(noOrigem->getListaArcos()->getNoDestino() == noDestino){
//            arcoRemover = noOrigem->getListaArcos();
//            noOrigem->setListaArcos(arcoRemover->getProxArco());
//        }else{
//            Arco *anterior= noOrigem->getListaArcos();
//            while(anterior->getProxArco() != NULL &&
//                  anterior->getProxArco()->getNoDestino() != noDestino)
//                anterior=anterior->getProxArco();
//
//            /// arco existe no no
//            if(anterior->getProxArco()!=NULL){
//                Arco *sucessor = anterior->getProxArco()->getProxArco();
//                arcoRemover = anterior->getProxArco();
//                anterior->setProxArco(sucessor);
//            }
//        }
//        if(arcoRemover != NULL){
//            delete arcoRemover;
//            this->numeroArcos--;
//            noOrigem->setGrau(noOrigem->getGrau() - 1);
//
//            if(atualizarGrau)
//                this->atualizaGrau();
//            }
//    }
}

void Grafo::removeArco(uint idOrigem, uint idDestino){
    this->removeArco(buscaNo(idOrigem), buscaNo(idDestino));
}

void Grafo::removeArcosLigadasAoNo(No *no, bool atualizaGrau = true){
    for(itInicio(); !itEhFim(); itProx())
        this->removeArco(this->getIt(), no, false);

    if(atualizaGrau)
        this->atualizaGrau();
}

void Grafo::removeArcos(No *no, bool atualizarGrau = true){
    this->numeroArcos -= no->getGrau();
    no->removeArcos();
//    if(atualizarGrau)
//        this->atualizaGrau();
}

void Grafo::atualizaGrau(){
    this->grau=0;
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        printf("\ngrau do: grafo: %d\t no: %d\n", this->grau, no->getGrau());
        if(no->getGrau() > grau){
            grau = no->getGrau();
        }
    }
}

///Faz a atualiza��o dos graus de Entrada e Saida do digrafo para deteccao de n�s fonte e sinks
void Grafo::atualizaGrausEntradaSaidaDosNos(){
    ///Zerar todos os graus de entrada e de saida
    for(itInicio(); !itEhFim(); itProx()){
//    for(No *i=listaNos; i!=NULL; i=i->getProxNo()){
        getIt()->setGrauEntrada(0);
        getIt()->setGrauSaida(0);
    }

    ///Percorrer todos os nos e suas listas de adjacencia incrementando os graus de entrada e de saida
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        for(no->itInicio(); !no->itEhFim(); no->itProx()){
            Arco *a = no->getIt();
            no->setGrauSaida(no->getGrauSaida()+1);
            a->getNoDestino()->setGrauEntrada(a->getNoDestino()->getGrauEntrada()+1);
        }
    }
}

bool compareReverse(uint a, uint b){
    return a >= b;
}

/** retorna a sequencia de inteiros dos graus do no */
uint* Grafo::sequenciaGrau(){
    uint* seq = new uint [this->numeroNos];
    uint cont = 0;

    for(itInicio(); !itEhFim(); itProx())
        seq[cont++] = this->getIt()->getGrau();

    sort(seq, seq+cont, compareReverse);
    return seq;
}

void Grafo::imprimir(){
    cout<<"Grau do Grafo: "<<this->grau<<"\tnumero de nos: "<<this->numeroNos
    <<"\tnumero de arcos: "<<this->numeroArcos<<endl;

    for(itInicio(); !itEhFim(); itProx())
        this->getIt()->imprimir();
}

void Grafo::leArquivo(char nome[]){
    uint i,j,n_nos;
    ifstream arq;
    arq.open(nome);
    if(arq.good()==false)
        cout<<"arquivo nao encontrado"<<endl;
    arq>>n_nos;
    for(uint i=1;i<=n_nos;i++)
        insereNo(i);
    while(arq.good()){
        arq>>i>>j;
        insereArcoID(i,j, numeroArcos+1);
    }
}

bool Grafo::saoAdjacentes(uint id1, uint id2){
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
uint Grafo::numeroNosComponenteFortementeConexa(No *no1){
    uint n_nos=0;

    for(itInicio(); !itEhFim(); itProx()){
        No *no2 = this->getIt();
        if(this->mesmaComponenteFortementeConexa(no1, no2))// && this->mesmaComponenteFortementeConexa(no2, no1))
            n_nos++;
    }
    return n_nos;
}

int Grafo::auxEhNoArticulacao(No *no){
    ///Percurso em profundidade
    if(no->getMarcado()==false){
        no->setMarcado(true);
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            return 1+auxEhNoArticulacao(no->getIt()->getNoDestino());
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
        no->itInicio();
        Arco *arco = no->getIt();
        if(arco!=NULL){
            this->desmarcaNos();
            this->contAux=0;
            no->setMarcado(true);
    //    cout<<"busca em progundidade come�ando em:"<<no->getListaArcos()->getNoDestino()->getID()<<endl;
            this->percursoProfundidade(arco->getNoDestino());
        //    cout<<"cont de nos marcados:"<<cont<<endl;
        //    cout<<"numero de nos de "<< no->getID()<<" e:"<<NosComponenteConexa(no)<<endl;
            bool result = (this->contAux < this->numeroNosComponenteFortementeConexa(no));
            return result;
        }
    }

    return false;

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
//    uint cont=this->auxEhNoArticulacao(noAux);
//    ///tem que verificar no final se todos os n�s da mesma componente conexa estao marcados no final.
//    if(cont<this->NosComponenteConexa(no)) { cout<<"cont:"<<cont<<endl; return true;};
//    return false;
//    this->desmarcaNos();///MEL�O ESQUECEU DE DESMARCAR OS N�S DEPOIS
}

bool Grafo::ehNoArticulacao(uint id){
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
    for(itInicio(); !itEhFim(); itProx()){
        No *inicio1 = getIt();
        for(itInicio(); !itEhFim(); itProx()){
            No *inicio2 = getIt();
            if(!this->mesmaComponenteFortementeConexa(inicio1, inicio2))
                return false;
        }
        /// iterador (it) eh alterado em (for) interno
        this->it = inicio1;
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
uint Grafo::rubustezVertice(uint *ids){
    uint rubustez=this->numeroNos, i=0;
    ids=new uint[this->numeroNos];
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        cout<< ( (float)( 1001 - no->getID() )/this->numeroNos ) * 100 <<"%"<<endl;
        if(this->ehNoArticulacao(no)){
            cout<<"achou articulacao"<<endl;
            rubustez--;
            ids[i]=no->getID();///armazenar id dos nos de articula��o
            i++;
        }
    }

    return rubustez;
}

vector<No*>  Grafo::vizinhancaAberta(uint id, bool fechada){
    return vizinhancaFechada(id, fechada);
}

vector<No*> Grafo::vizinhancaFechada(uint id, bool fechada){
    No* no=buscaNo(id);
    vector<No*> nos;
    if(fechada)
        nos.push_back(no);
    if(no != NULL)
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            nos.push_back(no->getIt()->getNoDestino());
    return nos;
}

///Cria um novo Grafo, com os mesmos n�s e arestas (por id) do grafo atual
Grafo* Grafo::clone(){
    int idArvore=1;
    Grafo* G = novoGrafo(this->getNumeroNos());
    for(itInicio(); !itEhFim(); itProx()){
        G->insereNo(this->getIt()->getID())->setIdArvore(idArvore);///id auxiliar para algoritmo de kruskal
        idArvore++;
    }

    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        for(no->itInicio(); !no->itEhFim(); no->itProx()){
            Arco *a = no->getIt();
            G->insereArcoID(no->getID(), a->getNoDestino()->getID(), a->getID());
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
    vector<uint> candidatos;
    Grafo* G=this->clone();
    for(uint k=0;k<this->getNumeroNos();k++){
        G->atualizaGrausEntradaSaidaDosNos();
        for(itInicio(); !itEhFim(); itProx()){
            No *no = getIt();
            if(no->getGrauEntrada()==0){
                candidatos.push_back(no->getID());
                G->removeNo(no->getID());
            }
        }
        solucao.push_back(this->buscaNo(candidatos[0]));//Vou colocar na solucao ponteiros do grafo original(this)
        candidatos.erase(candidatos.begin());
    }
    cout<<"Ordenacao topologica do DAG por ID:"<<endl;
    for(uint m=0;m<this->getNumeroNos();m++){
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
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        if(no->getMarcado()==false){
            num++;
            percursoProfundidade(no);
        }
    }
    return num;
}

Arco* Grafo::buscaArco(uint noOrigem, uint noDestino){
    No *no1=buscaNo(noOrigem);
    No *no2=buscaNo(noDestino);
    return buscaArco(no1, no2);
}

Arco* Grafo::buscaArco(uint id){
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        for(no->itInicio(); !no->itEhFim(); no->itProx()){
            Arco *arco = no->getIt();
            if(arco->getID() == id)
                return arco;
        }
    }
    return NULL;
}

Arco* Grafo::buscaArco(No* no1, No* no2){
    for(no1->itInicio(); !no1->itEhFim(); no1->itProx()){
        if(no2 == no1->getIt()->getNoDestino())
            return no1->getIt();
    }

    return NULL;
}

double Grafo::consultaMenorCaminhoEntreDoisNos(uint i, uint j){
    double **menorCaminho = algoritmoFloyd();
    return menorCaminho[i][j];
}

double Grafo::dijkstra(No* origem, No* destino){
    if(origem != NULL && destino != NULL)
        return this->dijkstra(origem)->distancia(destino->getID());
    else
        return -1.0;
}

double Grafo::dijkstra(uint origem, uint destino){
    return this->dijkstra(buscaNo(origem), buscaNo(destino));
}

Dijkstra* Grafo::dijkstra(uint origem){
    return dijkstra( buscaNo(origem) );
}

/**
* Usa Algoritmo de Dijkstra para criar informa��es de menor dist�ncia (e se caminho)
* para todos oa nos do Grafo
*/
Dijkstra* Grafo::dijkstra(No* origem){
    this->desmarcaNos();
    ///mapeamento (id -> pos) nos vetores (distancias) e (naoVisitados)
    map<uint, uint> pos;
    double *distancias = new double [this->numeroNos];

    /*** LEMBRAR DE OTIMIZAR CONJUNTO DE NAO VISITADOS ***/
    uint s = 0;    ///numero de nos na solucao
    No* nos[this->numeroNos];

    /// Auxiliar para guardar o caminho
    Arco** proximo = new Arco*[this->numeroNos];

    ///Inicializa conjuntos
    uint i = 0;
    for(itInicio(); !itEhFim(); itProx(), i++){
        No *no = getIt();
        pos[no->getID()] = i;         ///mapeia ids com posicoes
        distancias[i] = INFINITO;     ///distancia "infinita"
        nos[i] = no;         ///todos os nos
        proximo[i] = NULL;
    }

    distancias[ pos[origem->getID()] ] = 0;

    ///enquanto solu��o n�o estiver completa
    while(s < this->numeroNos){

        ///busca vertice com menor distancia
        uint posMaisProx = 0;
        while(nos[posMaisProx] != NULL && nos[posMaisProx]->getMarcado()){
            posMaisProx++;  ///primeira posicao desmarcada
        }

        for (uint i=posMaisProx+1; i < this->numeroNos ; i++){
            if (!nos[i]->getMarcado() && distancias[i] < distancias[posMaisProx]){
                posMaisProx = i;
            }
        }

        ///"remove" dos na visitados
        No* maisProx = nos[posMaisProx];
        maisProx->setMarcado(true);
        s++;

        /// para cada adjacencia de (maisProx)
        for(maisProx->itInicio(); !maisProx->itEhFim(); maisProx->itProx()){
            Arco* arco = maisProx->getIt();
//        for (Arco* arco = maisProx->getListaArcos(); arco != NULL; arco = arco->getProxArco()){
            ///dist�ncia de (origem) passando por (maisProx)
            double auxDist = distancias[posMaisProx] + arco->getPeso();
            uint posAux = pos[arco->getNoDestino()->getID()];
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

    this->itInicio();
    No* nos = this->getIt();
    No *noDestinoSolucao, *noOrigemSolucao;

    this->desmarcaNos();
    nos->setMarcado(true);

    solucao.push_back(nos);
    uint qtdCandidatos = getNumeroNos()-solucao.size();

    while(qtdCandidatos > 0){
        valorMenorPeso = INFINITO;
        for(uint i = 0; i < solucao.size(); i++){
            for(solucao[i]->itInicio(); !solucao[i]->itEhFim(); solucao[i]->itProx()){
            Arco *a = solucao[i]->getIt();
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
    uint idArvore=1;

    ///joga todos os arcos no vector para depois ordenar
    for(itInicio(); !itEhFim(); itProx()){
        No *no = this->getIt();
        ///cada no esta inicialmente em uma arvore separada
        no->setIdArvore(idArvore);
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            arcos.push_back(no->getIt());
        idArvore++;
    }

    sort(arcos.begin(), arcos.end(), menorPeso);

    ///nos origem e destino para cada arco
    No *orig, *dest;
    uint id_orig, id_dest;

    for(uint pos=0; pos <arcos.size(); pos+=2){
        orig=arcos.at(pos)->getNoOrigem();
        dest=arcos.at(pos)->getNoDestino();

        id_orig=orig->getIdArvore();
        id_dest=dest->getIdArvore();

        ///se arco conecta nos de componentes conexas diferentes ele esta na solucao
        if(id_orig!=id_dest){
            solucao.push_back(arcos.at(pos));
            ///coloca ids iguais para nos em mesma componente conexa
            for(itInicio(); !itEhFim(); itProx()){
                No *no = getIt();
                if(no->getIdArvore()==id_orig)
                    no->setIdArvore(id_dest);
            }
        }
    }

    return solucao;
}

/**
 * Retorna o Grafo C resultado do produto cartesiano com (this x B)
 * ##############   FAZ ALGUM SENTIDO PARA DIGrafoS???  #################
*/
Grafo* Grafo::produtoCartesiano(Grafo* B){
    Grafo* A = this;    /// <------ pura didatica
    /// C = A x B
    uint nNosA = A->getNumeroNos();
    uint nNosB = B->getNumeroNos();
    uint idAresta = 0;

    map<uint, uint> posA; ///mapeia idA->posA
    map<uint, uint> posB; ///mapeia idB->posB

    ///matriz auxiliar de nos de C
    No ***nosC = new No**[nNosA];
    for(uint i = 0; i < nNosA; i++)
        nosC[i] = new No*[nNosB];

    Grafo* C = novoGrafo(nNosA * nNosB);
    /// Cria todos os nos de de C
    uint a = 0, b = 0;
    for(A->itInicio(); A->getIt()!=NULL; A->itProx(), a++){
        for(B->itInicio(); B->getIt()!=NULL; B->itProx(), b++){
            posA[A->getIt()->getID()] = a;  ///mapeia noA
            posB[B->getIt()->getID()] = b;  ///mapeia noB
            nosC[a][b] = C->insereNo(nNosB*a + b);
        }
        b = 0;
    }
//    C->imprimir();

    /// faz "conexoes B"
    for(B->itInicio(); B->getIt()!=NULL; B->itProx(), b++){
        No* noB = B->getIt();
        for(noB->itInicio(); noB->getIt()!= NULL; noB->itProx()){
            Arco* arcoB = noB->getIt();
            for(uint a = 0; a < nNosA; a++){
                uint auxPos1 = posB[ noB->getID() ];
                uint auxPos2 = posB[ arcoB->getNoDestino()->getID() ];
                C->insereArco( nosC[a][auxPos1], nosC[a][auxPos2], idAresta++, false);
            }

        }
    }

    /// faz "conexoes A"
    for(A->itInicio(); A->getIt()!=NULL; A->itProx(), a++){
        No* noA = A->getIt();
        for(noA->itInicio(); noA->getIt()!= NULL; noA->itProx()){
            Arco* arcoA = noA->getIt();
            for(uint b = 0; b < nNosB; b++){
                uint auxPos1 = posA[ noA->getID() ];
                uint auxPos2 = posA[ arcoA->getNoDestino()->getID() ];
                C->insereArco( nosC[auxPos1][b], nosC[auxPos2][b], idAresta++, false);
            }

        }
    }

    C->atualizaGrau();

    /// desaloca matriz auxiliar
    for(uint i = 0; i < nNosA; i++)
        delete [] nosC[i];
    delete [] nosC;

    return C;
}

vector<No*> Grafo::fechamentoTransitivoDireto(uint id){
    No *no=buscaNo(id);
    vector<No*> fechamentoDireto;
    for(no->itInicio(); !no->itEhFim(); no->itProx())
        fechamentoDireto.push_back(no->getIt()->getNoDestino());

    return fechamentoDireto;
}

vector<No*> Grafo::fechamentoTransitivoIndireto(uint id){
    No *no=buscaNo(id);
    vector<No*> fechamentoDireto=this->fechamentoTransitivoDireto(id), fechamentoIndireto;

    this->desmarcaNos();
    this->percursoProfundidade(no);

    bool contido;
    for(itInicio(); !itEhFim(); itProx()){
        No *i = getIt();
        if(i->getMarcado()==true){

            contido=false;
            for(int j=0; j<fechamentoDireto.size();j++){
                if(i==fechamentoDireto.at(j))
                    contido=true;
            }
            ///se o no esta marcado e nao esta no fechamento direto entao ele esta no fechamento indireto
            ///nao adicionar o proprio no no seu fechamento transitivo
            if(contido==false && i!=no)
                fechamentoIndireto.push_back(i);

        }
    }
    this->desmarcaNos();
    return fechamentoIndireto;
}

bool Grafo::ehGrafoConexo(){
    this->desmarcaNos();
    this->contAux = 0;

    this->itInicio();
    percursoProfundidade(this->getIt());

    if(this->contAux == this->numeroNos)
        return true;

    return false;
}

/**
* Verifica se multigrafo eh euleriano
*/
bool Grafo::ehGrafoEuleriano(){
    /**
        Grafo euleriano precida (ser conexo) E (n�o ter no de grau impar),
        portanto n�o vale a pena usar ehGrafoConexo
    */
    ///desmarca nos verificando se grau eh impar
    for(itInicio(); getIt()!=NULL; itProx()){
        if(getIt()->getGrau()%2 == 1)
            return false;
        getIt()->setMarcado(false);
    }

    ///Verifica conexidade
    this->contAux = 0;
    this->itInicio();
    percursoProfundidade(this->getIt());
    if(this->contAux != this->numeroNos)
        return false;

    return true;
}

void Grafo::percursoIgnorandoArco(No *no, Arco *arcoIgnorado){
    if(no->getMarcado() == false){
        no->setMarcado(true);
        this->contAux++;
        ///percorre arcos do (no)
        for(no->itInicio(); !no->itEhFim(); no->itProx()){
            Arco *arco = no->getIt();
            if(arco != arcoIgnorado)
                percursoIgnorandoArco(arco->getNoDestino(), arcoIgnorado);
        }
    }
}

bool Grafo::ehArcoPonte(uint id){
    Arco *a = buscaArco(id);
    return ehArcoPonte(a);
}

bool Grafo::ehArcoPonte(Arco* arco){
    if(arco == NULL)
        return false;

    this->desmarcaNos();
    this->contAux = 0;
    percursoProfundidade(arco->getNoOrigem());
    /// n: numero de nos na componente conexa do noOrigem do arco:
    uint n1 = this->contAux;
//    printf("\nn antes: %d", n1);

    this->desmarcaNos();
    this->contAux = 0;
    percursoIgnorandoArco(arco->getNoOrigem(), arco);
    /// m: numero de nos na componente conexa do noOrigem do arco desconsiderando o arco
    uint n2 = this->contAux;
//    printf("\tn depois: %d\n", n2);

    return n2 < n1;
}
