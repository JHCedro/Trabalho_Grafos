#include "DiGrafo.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

///Função que insere nó no inicio(cabeça) do grafo
void DiGrafo::insereNo(unsigned int id){
    No *no=new No(id);
    no->setProxNo(cabeca);
    cabeca=no;
}

///Função imprime percorre todos os nós e chama á função imprime de cada nó

void DiGrafo::imprime(){
    No *no=cabeca;
    while(no!=0){
        no->imprime();
        no=no->getProxNo();
    }
}

No *DiGrafo::buscaNoPorPosicao(unsigned int pos){
    No *no = cabeca;
    for(unsigned int i=0;i<pos;i++){
        no = cabeca->getProxNo();
    }
    return no;
}

No *DiGrafo::buscaNoPorID(unsigned int id){
    No *no = cabeca;
    while(no!=0){
        if(no->getID() == id)
            return no;
        no = no->getProxNo();
    }
    return 0;
}

void DiGrafo::leDataArquivo(char nome[]){
    cout<<"\n\nLEITURA DE ARQUIVO INICIADA..."<<endl;
    unsigned int i, j, n, maior=0, porcento = 0;
    ifstream arq;
    arq.open(nome);
    arq>>n;

    cout<<"\nPRE-PROCESSAMENTO DO ARQUIVO:"<<endl;
    porcento=0;
    for(unsigned int k=0; k<2*n; k++){
        arq>>i;
        if(i>maior)
            maior=i;
        if( (int)(100.0 * k/(2*n)) > porcento ){
            porcento = (int)(100.0 * k/(2*n));
            cout<<"#";
        }
    }

    arq.close();

    ifstream arq2;
    arq2.open(nome);

    cout<<"\nINSERCAO DE NOS NO GRAFO"<<endl;
    porcento=0;
    for(unsigned int k=1; k<=maior; k++){
        insereNo(k);
        if( (int)(100.0 * k/maior) > porcento ){
            porcento = (int)(100.0 * k/maior);
            cout<<"#";
        }
    }

    arq2>>n;
    porcento=0;
    cout<<"\nINSERCAO DE ARCOS NO GRAFO"<<endl;
    for(unsigned int k=0; k<n; k++){
        cout<<"";
        if( (int)(100.0 * k/n) > porcento ){
            porcento = (int)(100.0 * k/n);
            cout<<"#";
        }

        arq2>>i>>j;

        insereArco('-', i, j);
    }
}

/**
Função que insere arco na estrutura:

faz a busca do no entrada(deOnde) do arco no grafo [arco:(deOnde----->praOnde)]
cria o arco que sera inserido como arco desse no encontrado na busca
define para onde(saida) no arco com o no paraOnde
arco inserido com sucesso
**/
void DiGrafo::insereArco(char id, unsigned int deOnde, unsigned int paraOnde){
    No *no = buscaNoPorID(deOnde);
    Arco *arc = no->getArco();

    Arco *aux = new Arco(id);
    aux->setProxArco(arc);
    aux->setParaOnde(buscaNoPorID(paraOnde));
    no->setArco(aux);
}

void DiGrafo::removeArco(unsigned int deOnde, unsigned int paraOnde){

    ///ELSES estao comentados

    No *no = buscaNoPorID(deOnde);
    ///se o no nao e nulo
    if(no!=0){
        Arco *arc = no->getArco();
        ///se existe arco no no origem do arco buscado
        if(arc!=0){
            ///se o primeiro arco do no e o arco buscado
            if(arc->getParaOnde()->getID() == paraOnde){
                Arco *aux = arc->getProxArco();
                no->setArco(aux);
                delete arc;
            }
            else{
                ///percorrer arcos do no origem do arco buscado
                while(arc->getProxArco()!=0 && arc->getProxArco()->getParaOnde()->getID() != paraOnde){
                    cout<< "paraOnde:" << arc->getProxArco()->getParaOnde()->getID() << endl;
                    arc = arc->getProxArco();
                }
                if(arc->getProxArco()!=0){
                    Arco *aux = arc->getProxArco();
                    arc->setProxArco(aux->getProxArco());
                    delete aux;
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

void DiGrafo::removeNoPorID(unsigned int id){
    if(cabeca!=0){
        No *no = cabeca;

        ///se o no a ser removido é a cabeca do grafo
        if(no->getID() == id){
            cabeca = cabeca->getProxNo();

            ///remove todas os arcos que estao conectados ao no removido
            for(No *i=cabeca; i!=0; i = i->getProxNo())
                removeArco(i->getID(), no->getID());

            delete no;
        }
        else{

            ///procurar o proximo no do grafo que tenha o id buscado
            while(no->getProxNo()!=0 && no->getProxNo()->getID() != id){
                no = no->getProxNo();
            }

            ///se o no a ser removido existe no grafo
            if(no->getProxNo()!=0){
                No *aux = no->getProxNo()->getProxNo();

                ///remove todas os arcos que estao conectados ao no removido
                for(No *i=cabeca; i!=0; i = i->getProxNo())
                    removeArco(i->getID(), no->getProxNo()->getID());

                delete no->getProxNo();
                no->setProxNo(aux);
            }
            ///se o no a ser removido nao existe no grafo
            else
                cout << "no nao encontrado no grafo!" <<endl;
        }
    }
    else
        cout<< "grafo vazio!" <<endl;

}

