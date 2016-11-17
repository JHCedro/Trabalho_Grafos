#ifndef ELIPSE_H_INCLUDED
#define ELIPSE_H_INCLUDED
#include "Auxiliares.hpp"
#include <math.h>
#include <string>
#define v_max 5

using namespace std;

//double angulo(double x1, double y1, double x2, double y2){
//    ///calcula a direcao do ponto (x2, y2) em relacao a (x1, x1) a partir da direita
//    double dx= x2-x1;
//    double dy= y2-y1;
//    double theta=atan( dy / dx );
//
//    ///corrige funcao atan() que esta definida de -pi/2 a pi/2
//    if (dx < 0) theta+= M_PI;
//    if (theta < 0) theta+= 2*M_PI;
//    //double raio = (a*b)/sqrt(pow(a*sin(theta), 2) + pow(b*cos(theta), 2));
//    return theta;
//}
//
//double distancia(double x1, double y1, double x2, double y2){
//    return sqrt( pow(x1-x2, 2) + pow(y1-y2, 2) );
//}
//
//double modulo(double vx, double vy){
//    return distancia(0, 0, vx, vy);
//}
//
//void ImprimeTexto(string texto, double x, double y, double esp=20,
//                  void* fonte= GLUT_BITMAP_TIMES_ROMAN_24){
//    for(int i=0; i<(int)texto.length(); i++){
//        glRasterPos2f(x + i*esp, y);
//        glutBitmapCharacter(fonte, texto[i]);
//    }
//}

class Circulo{
private:
    double cx, cy, raio;
    double prec, cor[3];
    int ID;
public:
    Circulo(double raio, double x, double y, double seg=50.0){
        cx = x;        cy = y;
        this->raio= raio;
        prec = seg;
    };

    double getRaio() {   return raio;  }
    double setRaio(double raio) {   this->raio = raio;  }
    double getCx(){   return cx; }
    double getCy(){   return cy; }
    int getID(){    return this->ID; }
    void setID(int ID){     this->ID = ID; }

    void setCor(double R, double G, double B){
        cor[0]=R;   cor[1]=G;   cor[2]=B;
    }

    void Desenha(){
        glBegin(GL_POLYGON);
            glColor3f(cor[0], cor[1], cor[2]);
            ///circulo parametrizado [0, 2*pi]
            for (double t = 0; t <= 1; t+=1.0/prec)
                glVertex2f(raio*cos(2*M_PI*t)+cx, raio*sin(2*M_PI*t)+cy);
        glEnd();

        glColor3f(1.0 - cor[0], 1.0 - cor[1], 1.0 - cor[2]);

        char aux[100];
        string s;
        sprintf(aux, "%d", this->ID);
        s.assign(aux);
        ImprimeTexto(s, cx-10, cy, 20);
    }

    bool Dentro(double x, double y){
        ///verifica se um ponto (x, y) está no circulo
        ///distancia de (x, y) a cada foco, f1 e f2
        if( distancia(x, y, this->cx, this->cy) < this->raio )
            return true;
        return false;
    }

    double Colisao(Circulo *circulo){
        ///verifica se a distância eh menor que a soma dos raios
        if (distancia(this->cx, this->cy, circulo->getCx(), circulo->getCy()) < this->raio + circulo->getRaio() ){
            ///contornar a situacao de uma circulo dentro de outra
            if (circulo->Dentro(this->cx, this->cy))
                return M_PI_2;
            return angulo(circulo->getCx(), circulo->getCy(), this->cx, this->cy);
            ///retorna o angulo da normal
        }
        return -1;
    }

    void mover(double x, double y){
        cx = x;        cy = y;
    }

    ~Circulo(){};
};

#endif // ELIPSE_H_INCLUDED
