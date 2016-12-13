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
#define inf HUGE_VAL

using namespace std;

Grafo::Grafo(bool direcionado){
    grau = 0;
    numeroArcos = 0;
    numeroNos = 0;
    flagDir = direcionado;
}

///Função para inserção de arco
void Grafo::insereArco(No* noOrigem, No* noDestino, uint id, bool atualizarGrau, double peso){
    Arco *novoArco = noOrigem->insereArco(noDestino, id, peso);
    if(!flagDir){
        Arco* dual = noDestino->insereArco(noOrigem, id, peso);
        novoArco->setDual(dual);
        dual->setDual(novoArco);
    }
    this->numeroArcos++;
    if (atualizarGrau)
        this->atualizaGrau();
}

/**
Função que insere arco na estrutura:

faz a busca do no entrada(idOrigem) do arco no grafo [arco:(idOrigem----->praOnde)]
cria o arco que sera inserido como arco desse no encontrado na busca
define para onde(saida) no arco com o no idDestino
arco inserido com sucesso
**/
void Grafo::insereArcoID(uint idOrigem, uint idDestino, uint id, bool atualizarGrau, double peso){
    No *noOrigem = buscaNo(idOrigem);
    No *noDestino = buscaNo(idDestino);
    this->insereArco(noOrigem, noDestino, id, atualizarGrau, peso);
}

/** desmarcar os nos do grafo */
void Grafo::desmarcaNos(){
    for(itInicio(); !itEhFim(); itProx())
        this->getIt()->setMarcado(false);
}

///Verifica se dois nós, pelos seus indices, estão na mesma componente fortemente conexa
bool Grafo::mesmaComponenteFortementeConexa(uint id1, uint id2){
    if(!flagDir)
        cout << "\nUSANDO COMPONENTE CONEXA EM GRAFO NAO DIRECIONADO!" << endl;

    No *i1 = buscaNo(id1), *i2 = buscaNo(id2);
    if(i1!=NULL && i2!=NULL)
        return mesmaComponenteFortementeConexa(i1, i2);
    else
        return false;
}

///Verifica se dois nós estão na mesma componente fortemente conexa
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
Percorre grafo a partir de um nó e sai marcando todo mundo da mesma componente conexa
*/
void Grafo::percursoProfundidade(No *no){
    if(no == NULL)
        cout<<"\n No NULL \n"<<endl;
    else{
        if(no->getMarcado() == false){
            no->setMarcado(true);
            this->contAux++;
            for(no->itInicio(); !no->itEhFim(); no->itProx())
                percursoProfundidade(no->getIt()->getVizinho(no));
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
        Arco *a = noGrafo->getIt();
        No* proxNo = a->getVizinho(noGrafo);
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
    Grafo* Arv = this->novoGrafo(this->getNumeroNos(), flagDir);

    ///raiz da arvore
    No* raiz = Arv->insereNo(no->getID());
    raiz->setNivel(0);
    auxBuscaProfundidade(no, raiz, Arv);

    return Arv;
}

/**
 * Constroi a arvore (Arv) a partir da busca em largura em (noGrafo)
 */
Grafo* Grafo::buscaLargura(No *noGrafo){
    this->desmarcaNos();
    queue<No*> fila;

    Grafo* Arv = novoGrafo(this->getNumeroNos(), this->flagDir);
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
        for(fila.front()->itInicio(); !fila.front()->itEhFim(); fila.front()->itProx()){//enquanto a lista de adjacencia do vertice nao acabar
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

/**
Controi um subgrafo H de um grafo G onde toda aresta de G tem ambas as pontas em H também é aresta de H.
**/
Grafo *Grafo::subGrafoInduzido(uint E[], uint tam){
    Grafo *induzido = novoGrafo(tam, this->flagDir);
    for(uint i=0; i<tam; i++)
        induzido->insereNo(E[i]);
    No *no;
    for(uint i=0; i<tam; i++){
        no=this->buscaNo(E[i]);
        ///procura Arcos do grafo que ligam os vertices do grafo induzido
        for(no->itInicio(); !no->itEhFim(); no->itProx()){
            Arco *a = no->getIt();
            for(uint j=0; j<tam; j++){
                if(a->getNoDestino()->getID() == E[j])
                    induzido->insereArcoID(no->getID(), a->getNoDestino()->getID(), a->getID());
            }
        }
    }
    return induzido;
}

///Verifica se todos os nós do grafo tem grau k
bool Grafo::ehGrafoKRegular(uint k){
    for(itInicio(); !itEhFim(); itProx()){
        if(getIt()->getGrau()!=k)
            return false;
    }
    return true;
}

///Verifica se todos os nós do grafo tem o mesmo grau K do primeiro vértice
bool Grafo::ehGrafoKRegular(){
    this->itInicio();
    return ehGrafoKRegular(this->getIt()->getGrau());
}

///Verifica se o grafo é completo
bool Grafo::ehGrafoCompleto(){
    return ehGrafoKRegular(this->numeroNos-1);
}

///Remove, se existir, o arco formado por dois nos recebidos
bool Grafo::removeArco(No* noOrigem, No* noDestino, bool atualizarGrau){
    if(noOrigem!=NULL && noDestino != NULL){
        if(noOrigem->removeArco(noDestino)){
            this->numeroArcos--;
            if(atualizarGrau)
                atualizaGrau();
        }

        return true;
    }
    return false;
}

/**
Remoçao de arco através de seus ids de origem e destino.
A função recebe apenas os ids e busca os nós orig e destino referentes a ele
**/
bool Grafo::removeArco(uint idOrigem, uint idDestino){
    return this->removeArco(buscaNo(idOrigem), buscaNo(idDestino));
}

///Remove arcos ligados a um nó especifico
void Grafo::removeArcosLigadasAoNo(No *no, bool atualizaGrau = true){
    for(itInicio(); !itEhFim(); itProx())
        this->removeArco(this->getIt(), no, false);

    if(atualizaGrau)
        this->atualizaGrau();
}

///Remove os arcos de um dado nó
void Grafo::removeArcos(No *no, bool atualizarGrau = true){
    this->numeroArcos -= no->getGrau();
    no->removeArcos();
    if(atualizarGrau)
        this->atualizaGrau();
}

///Atualiza o grau  do grafo
void Grafo::atualizaGrau(bool completamente){
    this->grau=0;
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        if(completamente)
            no->atualizaGrau();
        if(no->getGrau() > grau){
            grau = no->getGrau();
        }
    }
}

///Faz a atualização dos graus de Entrada e Saida do digrafo para deteccao de nós fonte e sinks
void Grafo::atualizaGrausEntradaSaidaDosNos(){
    ///Zerar todos os graus de entrada e de saida
    for(itInicio(); !itEhFim(); itProx()){
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

///Função de comparação
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

///Impressão
void Grafo::imprimir(bool detalhado){
    printf("[%seh direcionado] ", flagDir ? "" : "NAO ");
    cout<<"Grau do Grafo: "<<this->grau<<"\tnumero de nos: "<<this->numeroNos
    <<"\tnumero de arcos: "<<this->numeroArcos<<endl;
    for(itInicio(); !itEhFim(); itProx()){
        if(itEhFim())
            cout << "FIM!" << endl;
        if(detalhado)
            this->getIt()->imprimirDetelhado(flagDir);
        else
            this->getIt()->imprimir(flagDir);
    }
}

///Leitura de arquivos
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

///Verifica se dois nós são adjacentes a partir de seus indices
bool Grafo::saoAdjacentes(uint id1, uint id2){
    No *no1=buscaNo(id1);
    No *no2=buscaNo(id2);
    return saoAdjacentes(no1, no2);
}

///Verificação de adjacencia dos nós
bool Grafo::saoAdjacentes(No *no1, No *no2){
    ///ser ou não digrafo não interfere na resposta
    return no1->ehAdjacente(no2)||no2->ehAdjacente(no1);
}

/**
Recebe um nó e retorna o numero de nos da componente conexa que o nó esta presente.
*/
uint Grafo::numeroNosComponenteFortementeConexa(No *no1){
    uint n_nos=0;

    for(itInicio(); !itEhFim(); itProx()){
        No *no2 = this->getIt();
        if(this->mesmaComponenteFortementeConexa(no1, no2))
            n_nos++;
    }
    return n_nos;
}

///Função auxiliar para verificação se um nó é de articulação
int Grafo::auxEhNoArticulacao(No *no){
    ///Percurso em profundidade
    if(no->getMarcado()==false){
        no->setMarcado(true);
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            return 1+auxEhNoArticulacao(no->getIt()->getNoDestino());
    }
    return 0;
}

/**
Marca o nó, faz a busca em profundidade e ve se o numero de nos marcados e menor do que o numero de nos da componente conexa,
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
            this->percursoProfundidade(arco->getNoDestino());
            bool result = (this->contAux < this->numeroNosComponenteFortementeConexa(no));
            return result;
        }
    }

    return false;
}

///Função inicial para verificação se um nó é de articulação através de seu id
bool Grafo::ehNoArticulacao(uint id){
    No* no=buscaNo(id);
    if(no != NULL)
        return this->ehNoArticulacao(buscaNo(id));
    return false;
}

/**
Se o grafo é fortemente conexo cada par de vertice (a,b) estao na mesma conponente conexa.
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
Função para retornar a rubustez de um grafo baseado nas vertices.
A rubustez baseada em vertices indica o numero maximo de vertices que podem ser removidos do grafo mantendo a conexividade.
Se o no a ser removido nao for no de articulação entao o numero de componentes conexas apos a remoção do nó se mantem.
Assim qualquer no que nao seja de articulação pode ser removido e o grafo ainda se mantem conexo, a rubustez e entao
o numero maximo de nos menos o numero de nos de articulacao.
Coloquei pra receber os ids dos nos de articulacao pra conferir na função '' do main se esta funcionando.

IMPORTANTE!!!!
No caso a função retorna o numero de nos que voce pode retirar considerando todas as componentes conexas.
Se uma componente conexa pode ter 5 nos removidos e a outra pode ter 6 a função retorna 11.
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
            ids[i]=no->getID();///armazenar id dos nos de articulação
            i++;
        }
    }

    return rubustez;
}

///Função auxiliar para retornar a vizinhança aberta de de nó pelo seu id
vector<No*>  Grafo::vizinhancaAberta(uint id, bool fechada){
    return vizinhancaFechada(id, fechada);
}

///Função para retornar a vizinhança fechada (nós) de um dado nó
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

///Cria um novo Grafo, com os mesmos nós e arestas (por id) do grafo atual
Grafo* Grafo::clone(){
    int idArvore=1;
    Grafo* G = novoGrafo(this->getNumeroNos(), flagDir);
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

    G->grau=this->grau;
    G->numeroNos=this->getNumeroNos();
    G->numeroArcos=this->getNumeroArcos();
    return G;
}

/**
 * Detecta todos os nós fonte e adiciona aos candidatos.
 * A cada iteracao, coloca na solucao os nós fontes, marca eles e
 * subtrai 1 dos adjacentes, como se o nó marcado tivesse sido removido do grafo.
 */
vector<No*> Grafo::ordenacaoTopologicaDAG(){
    vector<No*> solucao;
    this->atualizaGrausEntradaSaidaDosNos();
    for(uint k=0;solucao.size()<this->getNumeroNos();k++){
        for(itInicio(); !itEhFim(); itProx()){
            No *no = getIt();
            if(no->getGrauEntrada()==0&&no->getMarcado()==false){
                solucao.push_back(no);
                no->setMarcado(true);
                for(no->itInicio(); !no->itEhFim(); no->itProx()){
                    Arco *a = no->getIt();
                    a->getNoDestino()->setGrauEntrada(a->getNoDestino()->getGrauEntrada()-1);
                }
            }
        }
    }
    return solucao;
}

/**Verificação de é k-conexo: k é o numero máximo de nós que pode ser removido
  * sem que o grafo fique desconexo. O algoritmo faz combinações de todos os
  * nós k a k e testa se a busca em profundidade na árvore com esses nós já marcados
  * atinge todos os nós do grafo. Se sim, o grafo não se tornará desconexo ao serem
  * removidos k vértices.
  * Testa também se o grafo fica conexo removendo k+1 vértices quaisquer. Se sim, ele
  * não é k conexo, mas k+1 (ou maior) conexo.
  */
bool Grafo::ehKConexo(int k){
    if(k>=this->numeroNos) return false; ///Tratamento para remoção de todos os nós.

    vector<No*> people;

    ///Adiciona todos os nós ao vetor people
    for(itInicio(); !itEhFim(); itProx())
        people.push_back(getIt());

    vector<No*> combination;

     if(auxKConexo(0, k, people, combination))
        return !auxKConexo(0, k+1, people, combination);
     return false;
}

/**Gerador de combinações para teste do K-Conexo*/
bool Grafo::auxKConexo(uint offset, int k, vector<No*> people, vector<No*> combination){
    if(k==0){
        return this->verificaSeEhConexoSemOsNos(combination);
    }
    for(uint i=offset; i<=people.size() - k; i++){
        combination.push_back(people[i]);
        if(!auxKConexo(i+1, k-1, people, combination))
            return false;
        combination.pop_back();
    }
    return true;
}

/**Teste para ver se ele continua conexo ao se remover o conjunto de nós*/
bool Grafo::verificaSeEhConexoSemOsNos(vector<No*> nos){
    this->desmarcaNos();
    this->contAux=0;
    for(uint i=0;i<nos.size();i++){
        nos[i]->setMarcado(true);
        this->contAux++;
    }
    No* aux=NULL;
    for(nos[0]->itInicio(); !nos[0]->itEhFim(); nos[0]->itProx()){
        Arco *a = nos[0]->getIt();
        if(!a->getNoDestino()->getMarcado())
            aux=a->getNoDestino();
    }
    if(aux!=NULL){
        this->percursoProfundidade(aux);
    }
    return (this->contAux==this->numeroNos);
}

/**
 * Percorre todos os nós do grafo e, para cada nó, incrementa o contador e
 * realiza a busca em profundidade caso ele não esteja marcado. A busca em profundidade marca
 * os nós pertencentes a uma mesma componente conexa, logo o contator não vai ser incrementado ao passar por um nó já percorrido.
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

/**
 * Percorre todos os nós do grafo e, para cada nó, incrementa o contador e
 * realiza a busca em profundidade caso ele não esteja marcado. A busca em profundidade marca
 * os nós pertencentes a uma mesma componente conexa e os coloca em um vetor. É semelhante a
 *
*/
vector<vector<No*>> Grafo::retornarComponentesConexas(){
    this->desmarcaNos();
    int num=0;
    vector<vector<No*>> componentes;
    for(itInicio(); !itEhFim(); itProx()){
        No *i = getIt();
        if(i->getMarcado()==false){
            vector<No*> no;     //objeto para inicializar uma posição no vector de componentes
            i->setMarcado(true);
            componentes.push_back(no);
            componentes[num].push_back(i);
            for(i->itInicio(); !i->itEhFim(); i->itProx()){
                Arco *a = i->getIt();
                componentes=auxRetornarComponentesConexas(a->getNoDestino(), componentes, num);
            }
            num++;
        }
    }
    return componentes;
}

///Função auxiliar para unção que retorna as componentes conexas
vector<vector<No*>> Grafo::auxRetornarComponentesConexas(No* no, vector<vector<No*>> componentes, int num){
    if(no != NULL){
        if(no->getMarcado()==false){
            no->setMarcado(true);
            componentes[num].push_back(no);
            for(no->itInicio(); !no->itEhFim(); no->itProx()){
                Arco *a = no->getIt();
                componentes=auxRetornarComponentesConexas(a->getNoDestino(), componentes, num);
            }
        }
    }
    return componentes;
}

///Busca do arco através de seu id de nó origem e destino
Arco* Grafo::buscaArco(uint noOrigem, uint noDestino){
    No *no1=buscaNo(noOrigem);
    No *no2=buscaNo(noDestino);
    return buscaArco(no1, no2);
}

///Busca e retorna o arco através de seu id, se existir
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

///Busca arco a partir de dois nós
Arco* Grafo::buscaArco(No* no1, No* no2){
    for(no1->itInicio(); !no1->itEhFim(); no1->itProx()){
        if(no2 == no1->getIt()->getNoDestino())
            return no1->getIt();
    }

    return NULL;
}

/**
* Funções auxiliares para o algoritmo de Dijkstra
**/

///Retorna o menor caminho entre dois indices.
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

Dijkstra* Grafo::dijkstra(uint origem, bool imprimeSolucao){
    return dijkstra( buscaNo(origem) );
}

/**
* Usa Algoritmo de Dijkstra para criar informações de menor distância (e se caminho)
* para todos oa nos do Grafo
*/
Dijkstra* Grafo::dijkstra(No* origem, bool imprimeSolucao){
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
        nos[i] = no;                  ///todos os nos
        proximo[i] = NULL;
    }

    distancias[ pos[origem->getID()] ] = 0;

    ///enquanto solução não estiver completa
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

        ///"remove" nos não visitados
        No* maisProx = nos[posMaisProx];
        maisProx->setMarcado(true);
        s++;

        /// para cada adjacencia de (maisProx)
        for(maisProx->itInicio(); !maisProx->itEhFim(); maisProx->itProx()){
            Arco* arco = maisProx->getIt();
            ///distância de (origem) passando por (maisProx)
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
    Dijkstra *solucao = new Dijkstra(this, origem, pos, distancias, proximo);
    if(imprimeSolucao)
        solucao->imprimirDistancias();

    return solucao;
}

/***
O algoritmo de Floyd é um algoritmo que resolve o problema de calcular o caminho mais curto entre todos
os pares de vértices em um grafo orientado (com direção) ou não e valorado (com peso).
O algoritmo de Floyd recebe como entrada uma matriz de adjacência que representa um grafo valorado.
O valor de um caminho entre dois vértices é a soma dos valores de todas as arestas ao longo desse caminho.
As arestas do grafo podem ter valores negativos, mas o grafo não pode conter nenhum ciclo de valor negativo.
***/
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
O algoritmo de Prim é um algoritmo guloso utilizado para encontrar uma árvore
geradora mínima em um grafo conectado, valorado e não direcionado. Isso
significa que o algoritmo encontra um subgrafo no qual a soma total das arestas
seja mínima e todos os vértices sejam interligados.
O algoritmo de prim se inicia com um vértice qualquer do grafo como ponto de partida
e enquanto houver vértice do grafo fora da solução, ele procura a aresta de menor
peso partindo de um vértice da solução para um vértice fora da solução considerando
não formar ciclos.
***/
vector<Arco*> Grafo::algorimoPrim(){
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
   return arcosSolucao;
}

///operador para ordenar as arestas por peso (Usado no algoritmo de Kruskal)
bool menorPeso(Arco *a1, Arco *a2){return ( a1->getPeso() < a2->getPeso() );};

/**
O algoritmo de Kruskal é um algoritmo que busca uma árvore geradora mínima para um grafo conexo e com pesos.
Isto significa que ele encontra um subconjunto das arestas que forma uma árvore que inclui todos os vértices,
onde o peso total, dado pela soma dos pesos das arestas da árvore, é minimizado. Se o grafo não for conexo,
então ele encontra uma floresta geradora mínima (uma árvore geradora mínima para cada componente conexo do grafo).
O algoritmo de Kruskal é um exemplo de um algoritmo guloso.
**/
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
 * Retorno serah um Grafo do tipo de (this)
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

    Grafo* C = novoGrafo(nNosA * nNosB, this->flagDir);
    /// Cria todos os nos de de C
    uint a = 0, b = 0;
    for(A->itInicio(); !A->itEhFim(); A->itProx(), a++){
        for(B->itInicio(); !B->itEhFim(); B->itProx(), b++){
            posA[A->getIt()->getID()] = a;  ///mapeia noA
            posB[B->getIt()->getID()] = b;  ///mapeia noB
            nosC[a][b] = C->insereNo(nNosB*a + b);
        }
        b = 0;
    }

    /// faz "conexoes B"
    for(B->itInicio(); !B->itEhFim(); B->itProx(), b++){
        No* noB = B->getIt();
        for(noB->itInicio(); !noB->itEhFim(); noB->itProx()){
            Arco* arcoB = noB->getIt();
            for(uint a = 0; a < nNosA; a++){
                uint auxPos1 = posB[ noB->getID() ];
                uint auxPos2 = posB[ arcoB->getNoDestino()->getID() ];
                C->insereArco( nosC[a][auxPos1], nosC[a][auxPos2], idAresta++, false);
            }

        }
    }

    /// faz "conexoes A"
    for(A->itInicio(); !A->itEhFim(); A->itProx(), a++){
        No* noA = A->getIt();
        for(noA->itInicio(); !noA->itEhFim(); noA->itProx()){
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

/**
* Dado um nó, retorna todos os nós que consegue-se chegar diretamente a partir desse nó.
* Ou seja, todos os nós adjacentes a ele.
**/
vector<No*> Grafo::fechamentoTransitivoDireto(uint id){
    No *no=buscaNo(id);
    vector<No*> fechamentoDireto;
    for(no->itInicio(); !no->itEhFim(); no->itProx())
        fechamentoDireto.push_back(no->getIt()->getNoDestino());

    return fechamentoDireto;
}

/**
* Dado um nó, retorna todos os nós que consegue-se chegar, por intemedio de outros nós, a partir desse nó.
* Ou seja, todos os nós que têm canho a partir dele.
**/
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
            for(uint j=0; j<fechamentoDireto.size();j++){
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

///Verifica se o grafo é conexo
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
* Verifica se grafo eh euleriano
*/
bool Grafo::ehGrafoEuleriano(){
    /**
        Grafo euleriano precida (ser conexo) E (não ter no de grau impar),
        portanto não vale a pena usar ehGrafoConexo
    */
    ///desmarca nos verificando se grau eh impar
    for(itInicio(); !itEhFim(); itProx()){
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

///Faz um percurso ignorando um arco especifico
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

///Verifica se é um arco Ponte através do id
bool Grafo::ehArcoPonte(uint id){
    Arco *a = buscaArco(id);
    return ehArcoPonte(a);
}

///Verifica se é um arco Ponte através do arco
bool Grafo::ehArcoPonte(Arco* arco){
    if(arco == NULL)
        return false;

    this->desmarcaNos();
    this->contAux = 0;
    percursoProfundidade(arco->getNoOrigem());
    /// n: numero de nos na componente conexa do noOrigem do arco:
    uint n1 = this->contAux;

    this->desmarcaNos();
    this->contAux = 0;
    percursoIgnorandoArco(arco->getNoOrigem(), arco);
    /// m: numero de nos na componente conexa do noOrigem do arco desconsiderando o arco
    uint n2 = this->contAux;

    return n2 < n1;
}

/** desmarcar os arcos do grafo **/
void Grafo::desmarcaArcos(){
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            no->getIt()->setMarcado(false);
    }
}

///Calculo a media dos pesoas de todos os arcos do grafo
void Grafo::calculaMediaPesosArcos(){
    double peso=0;
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            peso+=no->getIt()->getPeso();
    }
    this->mediaPesosArcos = peso/this->numeroArcos;
}

/**
* Calculo da função critério utilizada para rankear as arestas da solução
**/
double Grafo::funcaoCriterio(Arco *a){
    double result = mediaPesosArcos/a->getPeso();

    double gamma = 0.3;
    double bonus = ((double) a->getNoDestino()->getNivel() / this->maiorNivel)*gamma;

    result += bonus;

    return result;
}

///Inicia id da árvore
void Grafo::iniciaIdArvore(){
    for(itInicio(); !itEhFim(); itProx()){
        getIt()->setIdArvore(getIt()->getID());
    }
}

///Retorna os arcos adjacentes a um conjunto de nós
vector<pair<double, Arco*>> Grafo::arcosAdjacentesDesmarcados(vector<No*> nos){
    vector<pair<double, Arco*>> arcos;
    for(int i = 0; i < nos.size(); i++){
        for(nos[i]->itInicio(); !nos[i]->itEhFim(); nos[i]->itProx()){
            Arco *a = nos[i]->getIt();
            if(!a->getMarcado()){
                a->setMarcado(true);
                a->getDual()->setMarcado(true);
                arcos.push_back(make_pair(this->funcaoCriterio(a), a));
            }
        }
    }
    return arcos;
}

///Retorna os arcos adjacentes a um nó
vector<pair<double, Arco*>> Grafo::arcosAdjacentesDesmarcados(No *no){
    vector<pair<double, Arco*>> arcos;
    for(no->itInicio(); !no->itEhFim(); no->itProx()){
        Arco *arco = no->getIt();
        if(!arco->getMarcado()){
            /// marca arco e se oposto
            arco->setMarcado(true);
            arco->getDual()->setMarcado(true);

            ///so um dos arcos eh marcado
            arcos.push_back(make_pair(this->funcaoCriterio(arco), arco));
        }
    }
    return arcos;
}

///Compara arcos para o criterio da árvore de Steiner
bool Grafo::comparaCriterioSteiner(pair<double, Arco*> p1, pair<double, Arco*> p2){
    return p1.first > p2.first;
}

///Verifica se um conjunto de nós estão na mesma componente fortemente conexa
bool Grafo::nosMesmaComponenteConexa(vector<No*> nos){
    int idAux = nos[0]->getIdArvore();
    for(int i=1; i<nos.size(); i++){
        if(nos[i]->getIdArvore() != idAux)
            return false;
    }
    return true;
}

///Define os niveis dos nós da árvore de Steiner
void Grafo::definirNivelNos(){
    this->maiorNivel = 0;

    /// nos terminais terao nivel 1
    /// demais nos terao nivel 0
    for(itInicio(); !itEhFim(); itProx())
        getIt()->setNivel(getIt()->ehTerminal() ? 1 : 0);

    /// novo nivel depende do nivel os vizinhos
    vector<pair<No*, uint>> nosNiveis;
    for(itInicio(); !itEhFim(); itProx()){
        No* no = getIt();
        uint novoNivel = no->getNivel();
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            novoNivel +=  no->getIt()->getNoDestino()->getNivel();

        nosNiveis.push_back( make_pair(no, novoNivel) );

        ///atualiza maior nivel do grafo
        if(novoNivel > this->maiorNivel)
            this->maiorNivel = novoNivel;
    }

    for(auto p : nosNiveis)
        p.first->setNivel(p.second);
}

///Impressão dos ids da árvore de Steiner
void Grafo::imprimirIdsArvore(){
    for(itInicio(); !itEhFim(); itProx()){
        cout<<getIt()->getIdArvore()<<endl;
    }
}

///Impressão de graus da árvore de Steiner
void Grafo::imprimirGraus(){
    for(itInicio(); !itEhFim(); itProx()){
        cout<<getIt()->getGrau()<<endl;
    }
}

///Impressão de um vetor de arcos
void imprimeVectorArco(vector<Arco*> vet){
    for(int i=0; i<vet.size(); i++)
        cout<<"("<<vet[i]->getNoOrigem()->getID()<<","<<vet[i]->getNoDestino()->getID()<<")"<<endl;
}

///impressão de um vetor de nós
void imprimeVectorNo(vector<No*> vet){
    for(int i=0; i<vet.size(); i++)
        cout<<"i:"<<vet[i]->getID()<<endl;
}

/**
Guloso Steiner:
Recebe um vetor de indices e o tamanho do vetor, entao cria um vector de nos para os nos terminais do grafo com ids do vetor.
Retorna conjunto de arcos que forma a solucao da arvore de Steiner para esses nos terminais
*/
double Grafo::gulosoSteiner(uint ids[], uint tam, bool imprimeSolucao){
    vector<Arco*> conjuntoSolucao = this->auxGulosoRandomizadoSteiner(ids, tam, 0.0, 0);

    double solucao = 0;
    for(Arco* arco : conjuntoSolucao)
        solucao += arco->getPeso();

    if(imprimeSolucao){
        cout << "\nsolucao: " << solucao << endl;
        imprimeVectorArco(conjuntoSolucao);
    }

    return solucao;
}

/**
Guloso Randomizado Steiner:
Execução do algoritmo guloso passando como parâmetro uma constante alpha e um número de iterações.
**/
double Grafo::gulosoRandomizadoSteiner(uint idTerminais[], uint nTerminais, double alpha, int num_iteracoes, bool imprimeSolucao){
    double* solucoes = new double[num_iteracoes];
    double melhorSolucao = INFINITO;
    vector<Arco*> conjuntoSolucao, melhorSolucaoArcos;

    ///executa guloso randomizado (num_iteracoes) vezes
    for (int i=0; i < num_iteracoes; i++){
        conjuntoSolucao = this->auxGulosoRandomizadoSteiner(idTerminais, nTerminais, alpha, i);
        solucoes[i] = 0;
        for(Arco* arco : conjuntoSolucao)
            solucoes[i] += arco->getPeso();

        if(solucoes[i] < melhorSolucao){
            melhorSolucao = solucoes[i];
            melhorSolucaoArcos = conjuntoSolucao;
        }
    }

    if(imprimeSolucao){
        cout << "\nsolucao: " << melhorSolucao << endl;
        imprimeVectorArco(melhorSolucaoArcos);
    }

    delete [] solucoes;
    return melhorSolucao;
}

///Função auxiliar para o Guloso Randomizado de Steiner
vector<Arco*> Grafo::auxGulosoRandomizadoSteiner(uint idTerminais[], uint nTerminais, double alpha, uint semente){
    if(flagDir)
        cout << "\nUSANDO ARVORE DE STEINER EM GRAFO DIRECIONADO!" << endl;

    this->iniciaIdArvore();
    this->desmarcaArcos();
    this->desmarcaNos();
    this->calculaMediaPesosArcos();
    this->zeraGraus();
    this->zeraTerminais();

    vector<No*> terminais;
    vector<Arco*> arcosSolucao;
    vector<pair<double , Arco*>> candidatosArco;

    ///criar nos terminais com indices
    for(int i=0; i < nTerminais; i++){
        No *no = this->buscaNo(idTerminais[i]);
        no->setTerminal(true);///define nos como terminais
        no->setMarcado(true);
        terminais.push_back(no);
    }

    definirNivelNos();

    ///arcos marcados são candidatos ou solucao
    candidatosArco = arcosAdjacentesDesmarcados(terminais);

    ///idArvore do no origem e do no destino do melhor candidato
    uint idOrig, idDestino;

    ///enquanto terminais nao estao na mesma componente conexa
    while(!nosMesmaComponenteConexa(terminais) && !candidatosArco.empty()){
        sort(candidatosArco.begin(), candidatosArco.end(), comparaCriterioSteiner);

        ///  PARTE RANOMIZADA
        uint idCandidato = rand() % (uint)(alpha * candidatosArco.size() + 1);
        Arco *arco = candidatosArco[idCandidato].second;
        No *no;

        if(arco->getNoDestino()->getMarcado() == false)
            no = arco->getNoDestino();
        else
            no = arco->getNoOrigem();

        ///se o no nao esta marcado insere na solucao de nos
        if( !no->getMarcado() ){
            no->setMarcado(true);
            vector<pair<double, Arco*>> adjacentes = arcosAdjacentesDesmarcados(no);

            for(int i=0; i<adjacentes.size(); i++)
                candidatosArco.push_back(adjacentes[i]);
        }

        ///se os nos origem e destino do arco candidado estao em componentes conexas diferentes
        if(arco->getNoOrigem()->getIdArvore() != arco->getNoDestino()->getIdArvore()){
            arcosSolucao.push_back(arco);
            arco->getNoOrigem()->setGrau(arco->getNoOrigem()->getGrau() + 1);
            arco->getNoDestino()->setGrau(arco->getNoDestino()->getGrau() + 1);
        }

        uint idArvOrig = arco->getNoOrigem()->getIdArvore();
        uint idArvDest = arco->getNoDestino()->getIdArvore();

        ///coloca ids iguais para nos em mesma componente conexa
        for(itInicio(); !itEhFim(); itProx()){
            No *no = getIt();
            if(no->getIdArvore()==idArvOrig)
                no->setIdArvore(idArvDest);
        }

        candidatosArco.erase(candidatosArco.begin()+idCandidato);
    }
    if(!nosMesmaComponenteConexa(terminais)){
        cout << "\nTERMINAIS NAO ESTAO NA MESMA COMPONENTE CONEXA" << endl;
        vector<Arco*> vazio;
        return vazio;
    }

    arcosSolucao = podarArcosSteiner(arcosSolucao);
    this->atualizaGrau(true);

    cout<<".";
    return arcosSolucao;
}

/**
Guloso Randomizado Reativo de Steiner
Baseado em ponderacao da escolha dos melhores alphas
*/
double Grafo::gulosoRandomizadoReativoSteiner(uint idTerminais[], uint tam, bool imprimeSolucao){
    uint m = 10;                    /// numero de amostras utiizadas
    uint bloco_iteracoes = 3*m;      /// intervalo no qual distribuicao sera atualizada
    uint max_iteracoes = 30*m;       /// total de iteracoes do algoritmo

    double sigma = 5.0;     /// o quanto o melhor resultado altera a novas distribuicoes
    double soma_i[m];       /// soma dos resultados obtidos com de alpha = alphas[i]
    uint n_i[m];            /// numero de resultados obtidos com de alpha = alphas[i]
    double q_i[m];          /// auxiliar para recalcular distribuicoes

    /// alphas a serem testados
    double alphas[m];       /// = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};

    /// distribuicao inicialmente uniforme
    double dUniforme[m];    /// = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    vector<Arco*> melhorConjuntoSolucao;
    double melhorSolucao = INFINITO;

    /// inicializa variaveis
    for (int i=0; i < m; i++){
        soma_i[i] = 0.0;
        n_i[i] = 0;
        q_i[i] = 0.0;

        alphas[i] = 0.05*(i+1);
        dUniforme[i] = 1.0;
    }

    discrete_distribution<int> distribuicao(dUniforme, dUniforme+m);

    /// para cada alpha
    for (int i = 0; i < max_iteracoes; i++){
        /// gerador de inteiros [0, m) a partir de distribuicao
        default_random_engine generator(i);

        /// escolha alpha aleatoriaente com distribuicao atual
        uint alpha;
        if( i < bloco_iteracoes )
            alpha = i % m;
        else
            alpha = distribuicao(generator);

        /// testa o guloso randomizado para este alpha
        vector<Arco*> conjuntoSsolucao = this->auxGulosoRandomizadoSteiner(idTerminais, tam, alphas[alpha], i);

        /// calcula soma dos pesos da solucao
        double somaPesos = 0;
        for(Arco *arco : conjuntoSsolucao)
            somaPesos += arco->getPeso();

        soma_i[alpha] += somaPesos;    /// soma dos pesos das execucoes deste alpha
        n_i[alpha]++;                  /// numero de execucoes deste alpha

        ///atualiza melhor resultado F(S*)
        if(somaPesos < melhorSolucao){
            melhorSolucao = somaPesos;
            melhorConjuntoSolucao = conjuntoSsolucao;
        }

        /// ##########  PARTE REATIVA   ##########
        if((i+1) % bloco_iteracoes == 0){
            /// a cada bloco de iteracoes
            double soma_q = 0;
            double A_i = 0;     /// media dos resultados para alpha = alphas[i]

            for (int j = 0; j < m ; j++){
                if(n_i[j] > 0){
                    double A_i = soma_i[j] / n_i[j];
                    q_i[j] = pow(melhorSolucao / A_i, sigma);
                }
            }

            /// atualiza distribuicao
            discrete_distribution<int> novaDistribuicao(q_i, q_i+m);
            distribuicao = novaDistribuicao;

            ///para ver se ta rodando e nao em loop infinito
        }
    }

    if(imprimeSolucao){
        cout << "\nsolucao: " << melhorSolucao << endl;
        imprimeVectorArco(melhorConjuntoSolucao);
    }

    return melhorSolucao;
}

template <class T>
void imprimeArray(T* v, uint tam, string titulo){
    cout << titulo << endl << "[";
    for (int i=0; i < tam; i++){
        cout << v[i] << (i < tam-1 ? ", " : "");
    }
    cout << "]" << endl;
}

///Comparação entre alphas
bool comparaAlphasPesos(pair<double, double> p1, pair<double, double> p2){
    return p1.second > p2.second;
}

/**
*   Refina os melhores alphas pata seus vizinhos
**/
void atualizaAlfas(double* alphas, double* pesos, uint tam, double* prec){
    vector<pair<double, double>> alphasPesos;

    for (int i=0; i < tam; i++)
        alphasPesos.push_back( make_pair(alphas[i], pesos[i]) );

    /// seleciona melhores alphas
    sort(alphasPesos.begin(), alphasPesos.end(), comparaAlphasPesos);
    alphasPesos.erase(alphasPesos.begin()+tam/3, alphasPesos.end());

    /// insere melhores vizinhos
    (*prec) /= 4.0;
    for (int i=0; i < tam/3; i++){
        alphasPesos.push_back( make_pair(alphasPesos[i].first - (*prec), alphasPesos[i].second) );
        alphasPesos.push_back( make_pair(alphasPesos[i].first + (*prec), alphasPesos[i].second) );
    }

    for (int i=0; i < tam; i++){
        alphas[i] = alphasPesos[i].first;
        pesos[i] = alphasPesos[i].second;
    }
}

/**
* Guloso Randomizado Reativo baseado em refinamento para os vizinhos dos melhores alphas
**/
double Grafo::gulosoRandomizadoReativoSteiner2(uint idTerminais[], uint tam, bool imprimeSolucao){
    /// espaco amostral de alpha
    uint m = 12;             /// numero de amostras utiizadas
    uint max_iteracoes = 30*m;       /// total de iteracoes do algoritmo
    uint bloco_iteracoes = 3*m;      /// intervalo no qual distribuicao sera atualizada

    double prec = 0.05;     /// intervalos entre alphas
    double soma_i[m];       /// soma dos resultados obtidos com de alpha = alphas[i]

    /// alphas a serem testados
    double alphas[m];       /// = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};

    vector<Arco*> melhorConjuntoSolucao;
    double melhorSolucao = INFINITO;

    /// inicializa variaveis
    for (int i=0; i < m; i++)
        alphas[i] = 0.05*(i+1);

    /// para cada alpha
    for (uint i = 0; i < max_iteracoes; i++){
        uint alpha = i % m;

        /// testa o guloso randomizado para este alpha
        vector<Arco*> conjuntoSolucao = this->auxGulosoRandomizadoSteiner(idTerminais, tam, alphas[alpha], i);

        /// calcula soma dos pesos da solucao
        double somaPesos = 0;
        for(Arco *arco : conjuntoSolucao)
            somaPesos += arco->getPeso();

        soma_i[alpha] += somaPesos;    /// soma dos pesos das execucoes deste alpha

        ///atualiza melhor resultado F(S*)
        if(somaPesos < melhorSolucao){
            melhorSolucao = somaPesos;
            melhorConjuntoSolucao = conjuntoSolucao;
        }

        /// ##########  PARTE REATIVA   ##########
        if((i+1) % bloco_iteracoes == 0){
            /// a cada bloco de iteracoes
            atualizaAlfas(alphas, soma_i, m, &prec);

            ///para ver se ta rodando e nao em loop infinito
            cout<<".";
        }
    }
    cout<<endl;

    if(imprimeSolucao){
        cout << "\nsolucao:" << endl;
        imprimeVectorArco(melhorConjuntoSolucao);
    }

    return melhorSolucao;
}

///Comparação entre graus
bool comparaGrau(Arco *a1, Arco* a2){
    No* orig1 = a1->getNoOrigem();
    No* dest1 = a1->getNoDestino();
    No* orig2 = a2->getNoOrigem();
    No* dest2 = a2->getNoDestino();

    uint menorGrau1 = min(orig1->getGrau(), dest1->getGrau());
    uint menorGrau2 = min(orig2->getGrau(), dest2->getGrau());

    ///se alguma ponta for terminal e tem grau1 o arco tem que ficar por ultimo na ordenacao
    if( (orig1->ehTerminal() && orig1->getGrau()==1) || (dest1->ehTerminal() && dest1->getGrau()==1) || (orig1->ehTerminal() && dest1->ehTerminal()) )
        menorGrau1 = HUGE_VAL;
    if( (orig2->ehTerminal() && orig2->getGrau()==1) || (dest2->ehTerminal() && dest2->getGrau()==1) || (orig1->ehTerminal() && dest1->ehTerminal()) )
        menorGrau2 = HUGE_VAL;

    return menorGrau1 < menorGrau2;
}

/**
ordena arestas da solução em ordem crescente de acordo com o menor grau de seus nós e colocando em último arestas que ligam nós terminais que têm grau 1
**/
vector<Arco*> Grafo::podarArcosSteiner(vector<Arco*> solucao){
    No *orig, *dest;
    sort(solucao.begin(), solucao.end(), comparaGrau);

    ///enquanto ainda existem arcos para serem podados
    while((solucao[0]->getNoOrigem()->ehTerminal()==false && solucao[0]->getNoOrigem()->getGrau()==1)
       || (solucao[0]->getNoDestino()->ehTerminal()==false && solucao[0]->getNoDestino()->getGrau()==1)){

        orig = solucao[0]->getNoOrigem();
        dest = solucao[0]->getNoDestino();

        orig->setGrau(orig->getGrau()-1);
        dest->setGrau(dest->getGrau()-1);
        solucao.erase(solucao.begin());

        sort(solucao.begin(), solucao.end(), comparaGrau);
    }
    return solucao;
}

///Função para zerar graus
void Grafo::zeraGraus(){
    for(itInicio(); !itEhFim(); itProx())
        getIt()->setGrau(0);
}

///Função para zerar terminais
void Grafo::zeraTerminais(){
    for(itInicio(); !itEhFim(); itProx())
        getIt()->setTerminal(false);
}
