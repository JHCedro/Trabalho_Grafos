#include "Arco.h"

void Arco::imprimir(){
    printf(" --|A%2d: peso: %2.1f|--> (%d) ", id, peso, noDestino->getID());
}
