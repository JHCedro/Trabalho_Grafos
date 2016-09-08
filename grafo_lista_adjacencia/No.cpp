#include "No.h"
#include "Arco.h"
#include <iostream>

using namespace std;

void No::imprime(){
    cout<< this->getID();
    Arco *arc = this->getArco();

    while(arc!=0){
        cout<< " --|" << arc->getID() << "|--> " << arc->getParaOnde()->getID() << " ";
        arc = arc->getProxArco();
    }
    cout<<endl;
}
