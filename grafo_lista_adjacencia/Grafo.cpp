#include "Grafo.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

///Função que insere nó no inicio(cabeça) do grafo
void Grafo::insereNo(unsigned int id){
    No *no=new No(id);
    no->setProxNo(cabeca);
    cabeca=no;
    this->numeroNos++;///atualiza numero de vertices(nos)
}

///Função imprime percorre todos os nós e chama á função imprime de cada nó


No *Grafo::buscaNoPorPosicao(unsigned int pos){
    No *no = cabeca;
    for(unsigned int i=0;i<pos;i++){
        no = cabeca->getProxNo();
    }
    return no;
}

No *Grafo::buscaNoPorID(unsigned int id){
    No *no = cabeca;
    while(no!=NULL){
        if(no->getID() == id)
            return no;
        no = no->getProxNo();
    }
    return 0;
}

/**
Função que insere arco na estrutura:

faz a busca do no entrada(deOnde) do arco no grafo [arco:(deOnde----->praOnde)]
cria o arco que sera inserido como arco desse no encontrado na busca
define para onde(saida) no arco com o no paraOnde
arco inserido com sucesso
**/
void Grafo::insereArestaPorID(unsigned int id, unsigned int deOnde, unsigned int paraOnde){
    No *no = buscaNoPorID(deOnde);///busca o no na lista de nos para inserir aresta
    Aresta *arc = no->getAresta();///salva o primeiro arco do no encontrado

    ///insere arco no inicio da lista de adjacencias do no
    Aresta *aux = new Aresta(id);
    aux->setProxAresta(arc);
    aux->setParaOnde(buscaNoPorID(paraOnde));
    no->setAresta(aux);
    no->alteraGrau(1);///atualiza o grau do vertice(no)
    if(no->getGrau()>this->grau)///atualiza grau do grafo
        this->grau=no->getGrau();
    this->numeroArestas++;///atualiza numero de arestas
}

void Grafo::removeAresta(No* deOnde, No* paraOnde, bool atualizarGrau = true){
    if(deOnde!=NULL && paraOnde != NULL && deOnde->getAresta()!=NULL){
        Aresta* arcoRemover = NULL;
        ///se primeiro arco sera removido
        if(deOnde->getAresta()->getParaOnde() == paraOnde){
            arcoRemover = deOnde->getAresta();
            deOnde->setAresta(arcoRemover->getProxAresta());
        }else{
            Aresta *anterior= deOnde->getAresta();
            while(anterior->getProxAresta() != NULL &&
                  anterior->getProxAresta()->getParaOnde() != paraOnde)
                anterior=anterior->getProxAresta();

            /// arco existe no no
            if(anterior->getProxAresta()!=NULL){
                Aresta *sucessor = anterior->getProxAresta()->getProxAresta();
                arcoRemover = anterior->getProxAresta();
                anterior->setProxAresta(sucessor);
            }
        }
        if(arcoRemover != NULL){
            delete arcoRemover;
            this->numeroArestas--;
            deOnde->setGrau(deOnde->getGrau() - 1);

            if(atualizarGrau)
                this->atualizaGrau();
            }
    }
}

void Grafo::removeArestaPorID(unsigned int deOnde, unsigned int paraOnde){
    this->removeAresta(buscaNoPorID(deOnde), buscaNoPorID(paraOnde));
}

void Grafo::removeArestasLigadasAoNo(No *no, bool atualizaGrau = true){
    No *aux=this->cabeca;
    while(aux != NULL){
        this->removeAresta(aux, no, false);
        aux=aux->getProxNo();
    }
    if(atualizaGrau)
        this->atualizaGrau();
}

void Grafo::removeArestas(No *no, bool atualizarGrau = true){
    this->numeroArestas -= no->getGrau();
    no->removeArestas();
    if(atualizarGrau)
        this->atualizaGrau();
}

void Grafo::atualizaGrau(){
    this->grau=0;
    for(No *i=cabeca; i!=NULL; i=i->getProxNo()){
        if(i->getGrau() > grau)
            grau=i->getGrau();
    }
}

void Grafo::removeNoPorID(unsigned int id){
    No *noRemover=NULL;
    ///se a cabeca eh o no a ser removido
    if(cabeca->getID()==id){
        noRemover = cabeca;
        cabeca = cabeca->getProxNo();
    }
    else{
        No *anterior= cabeca;
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
        this->removeArestas(noRemover, false);
        this->removeArestasLigadasAoNo(noRemover, false);
        this->atualizaGrau();
        delete noRemover;
        this->numeroNos--;
    }
}

void Grafo::imprime(){
    cout<<"Grau do Grafo:"<<this->grau<<"\tnumero de nos:"<<this->numeroNos
    <<"\tnumero de arestas"<<this->numeroArestas<<endl;
    No *no=cabeca;
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
        insereArestaPorID(numeroArestas+1,i,j);
    }
}
