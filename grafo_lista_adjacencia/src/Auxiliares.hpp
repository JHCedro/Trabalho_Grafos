//#ifndef AUXILIARES_H_INCLUDED
//#define AUXILIARES_H_INCLUDED
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>       ///funcoes de tempo
#include <algorithm>    ///sort do placar
#include <math.h>
    #define M_PI		3.14159265358979323846
    #define M_PI_2		1.57079632679489661923

using namespace std;

struct jogador{
    string nome;
    int tempo;
};

bool ranking(jogador *A, jogador *B){
    return A->tempo < B->tempo;
}

void ImprimeTexto(string texto, float x, float y, float esp=20,
                  void* fonte= GLUT_BITMAP_TIMES_ROMAN_24){
    for(int i=0; i<(int)texto.length(); i++){
        glRasterPos2f(x + i*esp, y);
        glutBitmapCharacter(fonte, texto[i]);
    }
}

float angulo(float x1, float y1, float x2, float y2){
    ///calcula a direcao do ponto (x2, y2) em relacao a (x1, x1) a partir da direita
    float dx= x2-x1;
    float dy= y2-y1;
    float theta=atan( dy / dx );

    ///corrige funcao atan() que esta definida de -pi/2 a pi/2
    if (dx < 0) theta+= M_PI;
    if (theta < 0) theta+= 2*M_PI;
    return theta;///retorna o angulo dentro do intervalo (0, 2 pi)
}

float distancia(float x1, float y1, float x2, float y2){
    return sqrt( pow(x1-x2, 2) + pow(y1-y2, 2) );
}

float modulo(float vx, float vy){
    return distancia(0, 0, vx, vy);
}

//#endif // AUXILIARES_H_INCLUDED
