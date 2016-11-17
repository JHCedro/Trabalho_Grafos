#include "Arco.h"

void Arco::imprime(){
    printf(" --|A%2d: peso: %2.1f|--> (%d) ", id, peso, noDestino->getID());
}
