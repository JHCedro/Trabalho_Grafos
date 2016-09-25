#include "No.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

void No::imprime(){
    cout<<"( "<<"id:"<<this->getID()<<"\tgrau:"<<this->grau<<"\tpeso:"<<this->peso<<" )";
    Aresta *arc = this->getAresta();

    while(arc!=0){
        cout<< " --|A" << arc->getID() << "|--> " << arc->getParaOnde()->getID() << " ";
        arc = arc->getProxAresta();
    }
    cout<<endl;
}
