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

void Grafo::insereArco(No* noOrigem, No* noDestino, uint id, bool atualizarGrau, double peso){
//    printf("\nInserindo arco entre (%d) e (%d):", noOrigem->getID(), noDestino->getID());
    Arco *novoArco = noOrigem->insereArco(noDestino, id, peso);
//    this->imprimir();
    if(!flagDir){
        Arco* dual = noDestino->insereArco(noOrigem, id, peso);
        novoArco->setDual(dual);
        dual->setDual(novoArco);
//        printf("arco: (%d, %d)\n", novoArco->getNoOrigem()->getID(), novoArco->getNoDestino()->getID());
//        printf("dual: (%d, %d)\n", dual->getNoOrigem()->getID(), dual->getNoDestino()->getID());
    }
//    this->imprimir();
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

bool Grafo::mesmaComponenteFortementeConexa(uint id1, uint id2){
    if(!flagDir)
        cout << "\nUSANDO COMPONENTE CONEXA EM GRAFO NAO DIRECIONADO!" << endl;

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
Percorre grafo a partir de um nó e sai marcando todo mundo da mesma componente conexa
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
    Grafo *induzido = novoGrafo(tam, this->flagDir);
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

bool Grafo::removeArco(uint idOrigem, uint idDestino){
    return this->removeArco(buscaNo(idOrigem), buscaNo(idDestino));
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
    if(atualizarGrau)
        this->atualizaGrau();
}

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
    ///ser ou não digrafo não interfere na resposta
    return no1->ehAdjacente(no2)||no2->ehAdjacente(no1);
}

/**
FUNÇÃO AUXILIAR PARA FAZER A FUNÇÃO DO DUARDO FUNCIONAR.
Recebe um nó e retorna o numero de nos da componente conexa que o nó esta presente.
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
ESSA FUNÇÃO DO JEITO QUE ESTAVA ANTES NÃO FUNCIONAVA!!!!!
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
    //    cout<<"busca em progundidade começando em:"<<no->getListaArcos()->getNoDestino()->getID()<<endl;
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
//    ///tem que verificar no final se todos os nós da mesma componente conexa estao marcados no final.
//    if(cont<this->NosComponenteConexa(no)) { cout<<"cont:"<<cont<<endl; return true;};
//    return false;
//    this->desmarcaNos();///MELÃO ESQUECEU DE DESMARCAR OS NÓS DEPOIS
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

    ///Precisa retirar algumas atribuicoes redundantes?
//    G->setFlagDir(this->flagDir);
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
* Usa Algoritmo de Dijkstra para criar informações de menor distância (e se caminho)
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

        ///"remove" dos na visitados
        No* maisProx = nos[posMaisProx];
        maisProx->setMarcado(true);
        s++;

        /// para cada adjacencia de (maisProx)
        for(maisProx->itInicio(); !maisProx->itEhFim(); maisProx->itProx()){
            Arco* arco = maisProx->getIt();
//        for (Arco* arco = maisProx->getListaArcos(); arco != NULL; arco = arco->getProxArco()){
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
///tratar caso onde um vértice tem dois outros vertices com os pesos as arestas iguais
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
//    C->imprimir();

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

void Grafo::desmarcaArcos(){
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            no->getIt()->setMarcado(false);
    }
}

void Grafo::calculaMediaPesosArcos(){
    double peso=0;
    for(itInicio(); !itEhFim(); itProx()){
        No *no = getIt();
        for(no->itInicio(); !no->itEhFim(); no->itProx())
            peso+=no->getIt()->getPeso();
    }
    this->mediaPesosArcos = peso/this->numeroArcos;
}

double Grafo::funcaoCriterio(Arco *a){
    double result = mediaPesosArcos/a->getPeso();

    double gamma = (1.0/3.0);
    if(a->getNoOrigem()->ehTerminal() || a->getNoDestino()->ehTerminal())
        result += gamma*this->mediaPesosArcos;

    return result;
}

void Grafo::iniciaIdArvore(){
    for(itInicio(); !itEhFim(); itProx()){
        getIt()->setIdArvore(getIt()->getID());
    }
}

vector<Arco*> Grafo::arcosAdjacentesDesmarcados(vector<No*> nos){
    vector<Arco*> arcos;
    for(int i = 0; i < nos.size(); i++){
        for(nos[i]->itInicio(); !nos[i]->itEhFim(); nos[i]->itProx()){
            Arco *a = nos[i]->getIt();
            if(!a->getMarcado()){
                a->setMarcado(true);
                a->getDual()->setMarcado(true);
                arcos.push_back(a);
            }
        }
    }
    return arcos;
}

vector<Arco*> Grafo::arcosAdjacentesDesmarcados(No *no){
    vector<Arco*> arcos;
    for(no->itInicio(); !no->itEhFim(); no->itProx()){
        Arco *arco = no->getIt();
        if(!arco->getMarcado()){
            /// marca arco e se oposto
            arco->setMarcado(true);
            arco->getDual()->setMarcado(true);

            ///so um dos arcos eh marcado
            arcos.push_back(arco);
        }
    }
    return arcos;
}

bool Grafo::comparaCriterioSteiner(Arco *a1, Arco *a2){
    return funcaoCriterio(a1) > funcaoCriterio(a2);
}

vector<Arco*> Grafo::bubbleSort(vector<Arco*> arcos){
    Arco *aux;
    // coloca em ordem crescente (1,2,3,4,5...)
    for( int x = 0; x < arcos.size(); x++ )
    {
        for( int y = x + 1; y < arcos.size(); y++ ) // sempre 1 elemento à frente
        {
            // se o (x > (x+1)) então o x passa pra frente (ordem crescente)
            if ( !comparaCriterioSteiner(arcos[x], arcos[y]) )
            {
             aux = arcos[x];
             arcos[x] = arcos[y];
             arcos[y] = aux;
            }
        }
    } // fim da ordenação
    return arcos;
}

void Grafo::quickSort(vector<Arco*> arr, int left, int right) {
      int i = left, j = right;
      Arco *tmp;
      Arco *pivot = arr[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while (comparaCriterioSteiner(arr[i], pivot))
                  i++;
            while (!comparaCriterioSteiner(arr[j], pivot))
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}

bool Grafo::nosMesmaComponenteConexa(vector<No*> nos){
    int idAux = nos[0]->getIdArvore();
    for(int i=1; i<nos.size(); i++){
        if(nos[i]->getIdArvore() != idAux)
            return false;
    }
    return true;
}

void Grafo::imprimirIdsArvore(){
    for(itInicio(); !itEhFim(); itProx()){
        cout<<getIt()->getIdArvore()<<endl;
    }
}

void Grafo::imprimirGraus(){
    for(itInicio(); !itEhFim(); itProx()){
        cout<<getIt()->getGrau()<<endl;
    }
}

void imprimeVectorArco(vector<Arco*> vet){
    for(int i=0; i<vet.size(); i++)
        cout<<"("<<vet[i]->getNoOrigem()->getID()<<","<<vet[i]->getNoDestino()->getID()<<")"<<endl;
}

void imprimeVectorNo(vector<No*> vet){
    for(int i=0; i<vet.size(); i++)
        cout<<"i:"<<vet[i]->getID()<<endl;
}

/**
Guloso Steiner:
Recebe um vetor de indices e o tamanho do vetor, entao cria um vector de nos para os nos terminais do grafo com ids do vetor.
Retorna conjunto de arcos que forma a solucao da arvore de Steiner para esses nos terminais
*/
vector<Arco*> Grafo::gulosoSteiner(uint ids[], uint tam){
    return this->gulosoRandomizadoSteiner(ids, tam, 0.0);
}

vector<Arco*> Grafo::gulosoRandomizadoSteiner(uint idTerminais[], uint nTerminais, double alpha){
    if(flagDir)
        cout << "\nUSANDO ARVORE DE STEINER EM GRAFO DIRECIONADO!" << endl;


    this->iniciaIdArvore();
    this->desmarcaArcos();
    this->desmarcaNos();
    this->calculaMediaPesosArcos();
    this->zeraGraus();
    this->zeraTerminais();

//    cout<<"tempo pre-processamento guloso:"<<( clock() - t ) / CLOCKS_PER_SEC<<endl;

//    cout << "\nnumero de arcos: "<<this->numeroArcos<<"\tMedia dos pesos: " << this->mediaPesosArcos << endl;

    vector<No*> terminais;
    vector<Arco*> arcosSolucao;
    vector<Arco*> candidatosArco;

    ///criar nos terminais com indices
    for(int i=0; i < nTerminais; i++){
        No *no = this->buscaNo(idTerminais[i]);
        no->setTerminal(true);///define nos como terminais
        no->setMarcado(true);
        terminais.push_back(no);
    }

    ///arcos marcados são candidatos ou solucao
    candidatosArco = arcosAdjacentesDesmarcados(terminais);

    ///idArvore do no origem e do no destino do melhor candidato
    uint idOrig, idDestino;

    ///enquanto terminais nao estao na mesma componente conexa
    while(!nosMesmaComponenteConexa(terminais) && !candidatosArco.empty()){
        candidatosArco = bubbleSort(candidatosArco);    ///  <----------------------- CONSERTAR ORDENACAO CADAGA ###############

        ///  PARTE RANOMIZADA
        uint idCandidato = rand() % (uint)(alpha * candidatosArco.size() + 1);
//        cout << "candidatosArco.size() =  " << candidatosArco.size() << "\t";
//        cout << "idCandidato: " << idCandidato << endl;
        Arco *arco = candidatosArco[idCandidato];
        No *no;

        if(arco->getNoDestino()->getMarcado() == false)
            no = arco->getNoDestino();
        else
            no = arco->getNoOrigem();

        ///se o no nao esta marcado insere na solucao de nos
        if( !no->getMarcado() ){
            no->setMarcado(true);
            vector<Arco*> adjacentes = arcosAdjacentesDesmarcados(no);

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

//    imprimeVectorArco(arcosSolucao);
    arcosSolucao = podarArcosSteiner(arcosSolucao);
//    cout << "\ndepois da poda" <<endl;
//    imprimeVectorArco(arcosSolucao);
    this->atualizaGrau(true);


    return arcosSolucao;
}

vector<Arco*> Grafo::gulosoRandomizadoReativoSteiner(uint idTerminais[], uint tam){
    /// espaco amostral de alpha
    uint bloco_iteracoes = 10;      /// intervalo no qual distribuicao sera atualizada
    uint max_iteracoes = 100;       /// total de iteracoes do algoritmo

    uint m = 10;            /// numero de amostras utiizadas
    double sigma = 1.0;     /// o quanto o melhor resultado altera a novas distribuicoes
    double soma_i[m];       /// soma dos resultados obtidos com de alpha = alphas[i]
    uint n_i[m];            /// numero de resultados obtidos com de alpha = alphas[i]
    double q_i[m];          /// auxiliar para recalcular distribuicoes

    /// alphas a serem testados
    double alphas[m];       /// = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};

    /// distribuicao inicialmente uniforme
    double dUniforme[m];    /// = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

    vector<Arco*> melhorSolucao;

    /// inicializa variaveis
    for (int i=0; i < m; i++){
        soma_i[i] = 0.0;
        n_i[i] = 0;
        q_i[i] = 0.0;

        alphas[i] = 0.05*(i+1);
        dUniforme[i] = 1.0;
    }

    /// gerador de inteiros [0, m) a partir de distribuicao
    default_random_engine generator;
    discrete_distribution<int> distribuicao(dUniforme, dUniforme+m);

    double melhorResultado = INFINITO;  /// F(S*)

    /// para cada alpha
    for (int i = 0; i < max_iteracoes; i++){
        printf("\n\ni = %d", i);
        cout << "\nDistribuicao:\n\t";
        for (double p : distribuicao.probabilities()){
            cout << p << "  ";
        }

        /// escolha alpha aleatoriaente com distribuicao atual
        uint alpha = distribuicao(generator);

        printf("\nalpha escolhido: alpha[%d] = %f", alpha, alphas[alpha]);

        /// testa o guloso randomizado para este alpha
        vector<Arco*> solucao = this->gulosoRandomizadoSteiner(idTerminais, tam, alphas[alpha]);

        /// calcula soma dos pesos da solucao
        double somaPesos = 0;
        for(Arco *arco : solucao)
            somaPesos += arco->getPeso();

        soma_i[alpha] += somaPesos;    /// soma dos pesos das execucoes deste alpha
        n_i[alpha]++;                  /// numero de execucoes deste alpha

        ///atualiza melhor resultado F(S*)
        if(somaPesos < melhorResultado){
            melhorResultado = somaPesos;
            melhorSolucao = solucao;
        }

        printf("\nMelhor resultado ate i = %d : %f", i, melhorResultado);

        /// ##########  PARTE REATIVA   ##########
        if((i+1) % bloco_iteracoes == 0){
            /// a cada bloco de iteracoes
            double soma_q = 0;
            double A_i = 0;     /// media dos resultados para alpha = alphas[i]

            for (int j = 0; j < m ; j++){
                if(n_i[j] > 0){
                    double A_i = soma_i[j] / n_i[j];
                    q_i[j] = pow(melhorResultado / A_i, sigma);
                    soma_q += q_i[j];
                }
            }

            cout << "\n\nNova Distribuicao:\n";
            double auxNovaDistribuicao[m];
            for (int j=0; j < m; j++){
                auxNovaDistribuicao[j] = q_i[j] / soma_q;
                cout << auxNovaDistribuicao[j] << "  ";
            }
            cout << endl;
//            system("pause");

            /// atualiza distribuicao
            discrete_distribution<int> novaDistribuicao(auxNovaDistribuicao, auxNovaDistribuicao+m);
            distribuicao = novaDistribuicao;
        }
    }

    return melhorSolucao;
}

vector<Arco*> Grafo::podarArcosSteiner(vector<Arco*> solucao){
    No *orig, *dest;
    int tam = solucao.size();

    for(int i=0; i<solucao.size(); i++){
        orig = solucao[i]->getNoOrigem();
        dest = solucao[i]->getNoDestino();

        ///se alguma ponta do arco tem grau 1 e essa ponta nao e um ponto terminal
        if((orig->getGrau() == 1 && !orig->ehTerminal()) || (dest->getGrau() == 1 && !dest->ehTerminal())){
            orig->setGrau(orig->getGrau()-1);
            dest->setGrau(dest->getGrau()-1);

            solucao.erase(solucao.begin() + i);
            i=0;
        }
    }
    return solucao;
}

void Grafo::zeraGraus(){
    for(itInicio(); !itEhFim(); itProx())
        getIt()->setGrau(0);
}

void Grafo::zeraTerminais(){
    for(itInicio(); !itEhFim(); itProx())
        getIt()->setTerminal(false);
}

/**
RETORNA UM VETOR DE INTEIROS EM QUE A PRIMEIRA POSIÇÃO É O NÚMERO DE NÓS TERMINAIS
AS DEMAIS POSIÇÕES SÃO OS IDS DOS TERMINAIS
*/
uint *Grafo::leituraIntanciasSteiner(char nome[]){
    ifstream entrada;
    entrada.open(nome);

//    cout<<"abriu arquivo"<<endl;
//    cout<<nome<<endl;
//    system("pause");

    uint n_nos, n_arcos;
    char aux[50];
    entrada>>aux;
    while(((string)aux) != "SECTION Graph"){
        entrada.getline(aux, 50);
//        cout<<(string)aux<<endl;
    }
    entrada>>aux>>n_nos;
    entrada>>aux>>n_arcos;
//    cout<<"numero de nos: "<<n_nos<<endl;
//    cout<<"numero de arcos: "<<n_arcos<<endl;

    ///insere todos os nos
    for(uint i=1; i<=n_nos; i++)
        this->insereNo(i);

    ///indices de origem e destino dos arcos
    uint i, j;
    double peso;

    ///PERCORRER TODOS OS ARCOS DA ENTRADA
    while((string)aux != "END"){
        entrada>>aux;
        if((string)aux != "END"){
            entrada >> i >> j >> peso;
            this->insereArcoID(i, j, 1, false, peso);
//            system("pause");
        }
    }

    entrada>>aux>>aux>>aux;

    uint n_terminais, *terminais, idx=0;
    entrada>>n_terminais;

//    cout<<"numero de terminais: "<<n_terminais<<endl;

    terminais = new uint[n_terminais + 1];
    terminais[0] = n_terminais;

    ///leitura de terminais
    while((string)aux != "END"){
        entrada>>aux;
        if((string)aux != "END"){
            entrada>>i;
            terminais[idx + 1] = i;
            idx++;
        }
    }

    return terminais;
}
