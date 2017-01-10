#include <map>
#include <iostream>

using namespace std;

class Grafo;

/**
 * Estrutura com informacoes do algoritmo de Dijkstra
*/
class Dijkstra{
private:
    map<uint, uint> pos;
    double* distancias;
    Grafo* grafo;
    No* noOrigem;
    Arco** percurso;

public:
    Dijkstra(Grafo* G, No* noOrigem, map<uint, uint> pos, double distancias[], Arco* proximo[]){
        this->grafo = G;
        this->noOrigem = noOrigem;
        this->pos = pos;
        this->distancias = distancias;
        this->percurso = proximo;
    };

    Arco** getPercurso(){  return this->percurso;   };

    void imprimirPercurso(){
//        for (uint i=0; i < pos.size() ; i++){
        cout << "Arcos do menor caminho: ";
        for (auto p : pos){
            if(percurso[p.second] != NULL ){
                printf("\n\t(%2d)", percurso[p.second]->getNoOrigem()->getID());
                percurso[p.second]->imprimir();
            }
        }
    };

    Grafo* getGrafo(){  return grafo;   };
    No* getNoOrigem(){  return noOrigem;};
    uint getTam(){ return (uint) pos.size(); };

    /** Retorna a distancia do noOrigem ao destino*/
    double distancia(uint destino){
        return distancias[ pos[destino] ];
    };

    void imprimirDistancias(){
        printf("\nDistancias de (%d) para:\n", noOrigem->getID());
        map<uint, uint>::iterator it = pos.begin();
        for (; it != pos.end(); ++it){
            printf("\t(%d) : %f\n", it->first, distancias[it->second]);
        }
    };
};
