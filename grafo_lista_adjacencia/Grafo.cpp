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

//void Grafo::leDataArquivo(unsigned int nome[]){
//    cout<<"\n\nLEITURA DE ARQUIVO INICIADA..."<<endl;
//    unsigned int i, j, n, maior=0, porcento = 0;
//    ifstream arq;
//    arq.open(nome);
//    arq>>n;
//
//    cout<<"\nPRE-PROCESSAMENTO DO ARQUIVO:"<<endl;
//    porcento=0;
//    for(unsigned int k=0; k<2*n; k++){
//        arq>>i;
//        if(i>maior)
//            maior=i;
//        if( (int)(100.0 * k/(2*n)) > porcento ){
//            porcento = (int)(100.0 * k/(2*n));
//            cout<<"#";
//        }
//    }
//
//    arq.close();
//
//    ifstream arq2;
//    arq2.open(nome);
//
//    cout<<"\nINSERCAO DE NOS NO GRAFO"<<endl;
//    porcento=0;
//    for(unsigned int k=1; k<=maior; k++){
//        insereNo(k);
//        if( (int)(100.0 * k/maior) > porcento ){
//            porcento = (int)(100.0 * k/maior);
//            cout<<"#";
//        }
//    }
///*
//    arq2>>n;
//    porcento=0;
//    cout<<"\nINSERCAO DE ARCOS NO GRAFO"<<endl;
//    for(unsigned int k=0; k<n; k++){
//        cout<<"";
//        if( (int)(100.0 * k/n) > porcento ){
//            porcento = (int)(100.0 * k/n);
//            cout<<"#";
//        }
//
//        arq2>>i>>j;
//
//        insereAresta('-', i, j);
//    }
//*/
//
//}

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

void Grafo::removeArestaPorID(unsigned int deOnde, unsigned int paraOnde){

    ///ELSES estao comentados

    No *no = buscaNoPorID(deOnde);
    ///se o no nao e nulo
    if(no!=NULL){
        Aresta *arc = no->getAresta();
        ///se existe arco no no origem do arco buscado
        if(arc!=NULL){
            ///se o primeiro arco do no e o arco buscado
            if(arc->getParaOnde()->getID() == paraOnde){
                Aresta *aux = arc->getProxAresta();
                no->setAresta(aux);
                delete arc;
                no->alteraGrau(-1);///atualiza grau do no
                this->numeroArestas--;///atualiza numero de arestas
                ///atualiza grau do grafo
                this->grau=0;
                for(No *i=cabeca; i!=NULL; i=i->getProxNo()){
                    if(i->getGrau() > grau)
                        grau=i->getGrau();
                }
            }
            else{
                ///percorrer arcos do no origem do arco buscado
                while(arc->getProxAresta()!=NULL && arc->getProxAresta()->getParaOnde()->getID() != paraOnde){
                    arc = arc->getProxAresta();
                }
                if(arc->getProxAresta()!=NULL){
                    Aresta *aux = arc->getProxAresta();
                    arc->setProxAresta(aux->getProxAresta());
                    delete aux;
                    no->alteraGrau(-1);///atualiza grau do no
                    this->numeroArestas--;///atualiza numero de arestas
                    ///atualiza grau do grafo
                    this->grau=0;
                    for(No *i=cabeca; i!=NULL; i=i->getProxNo()){
                        if(i->getGrau() > grau)
                            grau=i->getGrau();
                    }
                }
                //else
                    //cout<< "arco nao existe no grafo(percurso total)" << endl;
            }
        }
        //else
            //cout<< "arco nao existe no grafo(nao tem arco)" << endl;
    }
    //else
        //cout<< "arco nao existe no grafo(no vazio)" << endl;
}

void Grafo::removeNoPorID(unsigned int id){
    if(cabeca!=NULL){
        No *no = cabeca;

        ///se o no a ser removido é a cabeca do grafo
        if(no->getID() == id){
            cabeca = cabeca->getProxNo();

            ///remove todas os arcos que estao conectados ao no removido
            for(No *i=cabeca; i!=NULL; i = i->getProxNo())
                removeArestaPorID(i->getID(), no->getID());

            delete no;
            this->numeroNos--;///atualiza numero de vertices(nos)
        }
        else{

            ///procurar o proximo no do grafo que tenha o id buscado
            while(no->getProxNo()!=NULL && no->getProxNo()->getID() != id){
                no = no->getProxNo();
            }

            ///se o no a ser removido existe no grafo
            if(no->getProxNo()!=NULL){
                No *aux = no->getProxNo()->getProxNo();

                ///remove todas os arcos que estao conectados ao no removido
                for(No *i=cabeca; i!=NULL; i = i->getProxNo())
                    removeArestaPorID(i->getID(), no->getProxNo()->getID());

                delete no->getProxNo();
                no->setProxNo(aux);
                this->numeroNos--;///atualiza numero de vertices(nos)
            }
            ///se o no a ser removido nao existe no grafo
            else
                cout << "no nao encontrado no grafo!" <<endl;
        }
    }
    else
        cout<< "grafo vazio!" <<endl;

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
    unsigned int i,j;
    ifstream arq;
    arq.open(nome);
    if(arq.good()==false)
        cout<<"arquivo nao encontrado"<<endl;
    while(arq.good()){
        arq>>i>>j;
        if(buscaNoPorID(i)==NULL)
            insereNo(i);
        if(buscaNoPorID(j)==NULL)
            insereNo(j);
        insereArestaPorID(numeroArestas+1,i,j);
    }
}
