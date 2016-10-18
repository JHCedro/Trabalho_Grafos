#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

Grafo::Grafo(){
    listaNos = NULL;
    grau = 0;
    numeroArcos = 0;
    numeroNos = 0;
    flagDir = true;
}

///Função que insere nó no inicio(cabeça) do grafo
No *Grafo::insereNo(unsigned int id){
    No *no=new No(id);
    no->setProxNo(listaNos);
    listaNos=no;
    this->numeroNos++;///atualiza numero de vertices(nos)
    return listaNos;
}

No *Grafo::buscaNo(unsigned int id){
    No *no = listaNos;
    while(no!=NULL){
        if(no->getID() == id)
            return no;
        no = no->getProxNo();
    }
    return 0;
}

void Grafo::insereArco(No* noOrigem, No* noDestino, unsigned int id, bool atualizarGrau = true){
    noOrigem->insereArco(noDestino, id);
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
void Grafo::insereArco(unsigned int idOrigem, unsigned int idDestino, unsigned int id){
    No *noOrigem = buscaNo(idOrigem);
    No *noDestino = buscaNo(idDestino);
    this->insereArco(noOrigem, noDestino, id, true);
}

/** desmarcar os nos do grafo */
void Grafo::desmarcaNos(){
    for(No *i = listaNos; i != NULL; i = i->getProxNo())
        i->setMarcado(false);
}

bool Grafo::mesmaComponenteConexa(unsigned int id1, unsigned int id2){
    No *i1 = buscaNo(id1), *i2 = buscaNo(id2);
    if(i1!=NULL && i2!=NULL)
        return mesmaComponenteConexa(i1, i2);
    else
        return false;
}

bool Grafo::mesmaComponenteConexa(No *i1, No *i2){
    this->desmarcaNos();
    return auxMesmaComponenteConexa(i1,i2);
}

bool Grafo::auxMesmaComponenteConexa(No *i1, No *i2){
    if(i1->getID()==i2->getID()){
        cout<<"i1:"<<i1->getID()<<" e i2:"<<i2->getID()<<endl;
        return true;
    }

    /// se o no nao esta marcado pular para ele
    if(i1->getMarcado()==false){
        i1->setMarcado(true);
        for(Arco *a=i1->getListaArcos(); a!=NULL; a=a->getProxArco())
            return auxMesmaComponenteConexa(a->getNoDestino(), i2);
    }
}

Grafo *Grafo::subGrafoInduzido(unsigned int E[], unsigned int tam){
    Grafo *induzido=new Grafo();
    for(unsigned int i=0; i<tam; i++)
        induzido->insereNo(E[i]);
    No *no;
    for(unsigned int i=0; i<tam; i++){
        no=this->buscaNo(E[i]);
        ///procura Arcos do grafo que ligam os vertices do grafo induzido
        for(Arco *a=no->getListaArcos(); a!=NULL; a=a->getProxArco()){
            for(unsigned int j=0; j<tam; j++){
                if(a->getNoDestino()==buscaNo(E[j]))
                    induzido->insereArco(no->getID(), a->getNoDestino()->getID(), 99);
            }
        }
    }
    return induzido;
}

bool Grafo::ehGrafoKReguar(unsigned int k){
    for(No *i=listaNos; i!=NULL; i=i->getProxNo()){
        if(i->getGrau()!=k)
            return false;
    }
    return true;
}

bool Grafo::ehGrafoCompleto(){
    return ehGrafoKReguar(this->numeroNos-1);
}

void Grafo::removeArco(No* noOrigem, No* noDestino, bool atualizarGrau = true){
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

void Grafo::removeArco(unsigned int idOrigem, unsigned int idDestino){
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

void Grafo::removeNo(unsigned int id){
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

bool compareReverse(unsigned int a, unsigned int b){
    return a >= b;
}

/** retorna a sequencia de inteiros dos graus do no */
unsigned int* Grafo::sequenciaGrau(){
    unsigned int* seq = new unsigned int [this->numeroNos];
    unsigned int cont = 0;
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
    unsigned int i,j,n_nos;
    ifstream arq;
    arq.open(nome);
    if(arq.good()==false)
        cout<<"arquivo nao encontrado"<<endl;
    arq>>n_nos;
    for(unsigned int i=1;i<=n_nos;i++)
        insereNo(i);
    while(arq.good()){
        arq>>i>>j;
        insereArco(i,j, numeroArcos+1);
    }
}

bool Grafo::saoAdjacentes(unsigned int id1, unsigned int id2){
    No *no1=buscaNo(id1);
    No *no2=buscaNo(id2);
    return saoAdjacentes(no1, no2);
}

bool Grafo::saoAdjacentes(No *no1, No *no2){
    ///ser ou não digrafo não interfere na resposta
    return no1->ehAdjacente(no2)||no2->ehAdjacente(no1);
}

bool Grafo::ehNoArticulacao(unsigned int id){
    No* no=buscaNo(id);
    if(no != NULL)
        return this->ehNoArticulacao(buscaNo(id));
    return false;
}

bool Grafo::ehNoArticulacao(No *no){
    ///Marca o no como visitado e faz busca em profundidade
    ///no seu primeiro adjacente, contando os nos visitados.
    ///Se o numero de nos for menor que n-1, significa que
    ///aquele no marcado no inicio eh de articulacao.

    this->desmarcaNos();
    no->setMarcado(true);
    Arco *a=no->getListaArcos();
    if(a==NULL) return false;
    No *noAux=a->getNoDestino();
    int cont=this->auxEhNoArticulacao(noAux);
    if(cont!=this->getNumeroNos()-1) return true;
    return false;
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


/** IMPLEMENTAR DESTRUTOR */
Grafo::~Grafo(){}
