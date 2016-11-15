#include <map>


using namespace std;

class Grafo;

/**
 * Estrutura com informações do algoritmo de Dijkstra
*/
class Dijkstra{
private:
    map<u_int, u_int> pos;
    double* distancias;
    Grafo* grafo;
    No* noOrigem;
    Arco** percurso;

public:
    Dijkstra(Grafo* G, No* noOrigem, map<u_int, u_int> pos, double distancias[], Arco* proximo[]){
        this->grafo = G;
        this->noOrigem = noOrigem;
        this->pos = pos;
        this->distancias = distancias;
        this->percurso = proximo;
    };

    Arco** getPercurso(){  return this->percurso;   };

    void imprimePercurso(){
        for (u_int i=0; i < pos.size() ; i++){
            cout << "\n\t" << i << ": ";
            if(percurso[i] != NULL ){
                printf("(%d)", percurso[i]->getNoOrigem()->getID());
                percurso[i]->imprime();
            }
            else
                cout << "--";
        }
    };

    Grafo* getGrafo(){  return grafo;   };
    No* getNoOrigem(){  return noOrigem;};
    u_int getTam(){ return pos.size(); };

    double distancia(u_int destino){
        return distancias[ pos[destino] ];
    };

    void imprimeDistancias(){
        printf("\nDistancias de (%d) para:\n", noOrigem->getID());
        map<u_int, u_int>::iterator it = pos.begin();
        for (; it != pos.end(); ++it){
            printf("\t(%d):%f\n", it->first, distancias[it->second]);
        }
    };
};
