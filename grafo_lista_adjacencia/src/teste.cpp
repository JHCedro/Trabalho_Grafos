#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "wtypes.h"
#include "Circulo.h"
#include "Grafo/Grafo.h"
#include "Grafo/AuxTestes.h"
#define rando

using namespace std;

void GetDesktopResolution(int& horizontal, int& vertical){
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

int altura=700, largura=600, L_nos=50, n_nos=20;
Circulo **nos, *selecionado = NULL;
int pos[2];
Grafo *G;
int n = 5;

// Inicializa opengl
void init(void){
    GetDesktopResolution(largura, altura);
    double x, y, r;
    G = grafoEscadinha(n);
    nos = new Circulo*[n];

    srand(time(NULL));
    for (int i = 0; i < n; i++){
        r= 30;//fmod(rand(), altura/20 + 5);
        x= fmod(rand(), (largura-2*r) + r);
        y= fmod(rand(), (altura -2*r) + r);
        nos[i] = new Circulo(r, x, y);
        nos[i]->setCor(0.7, 0.8, 0.3);
        nos[i]->setID(i);
        for (int j=0; j < i; j++){
            if (nos[i]->Colisao(nos[j]) != -1){
                delete nos[i];
                i--;
                break;
            }
        }
    }

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

/** Desenha vertices e arestas
    Arestas unidirecional: claro ---> escuro
    Aresta bidirecional: verde
*/
void desenhaGrafo(Grafo *G){
    /// desenha arestas
    No *noAux = G->getListaNos();
    bool ehReciproco = false;
    while(noAux != NULL){
        Arco *arcoAux = noAux->getListaArcos();
        while(arcoAux != NULL){
            ehReciproco = arcoAux->getNoDestino()->ehAdjacente(noAux);
            glLineWidth(3.0);
            glBegin(GL_LINES);
                ehReciproco ? glColor3f(0,1,0) : glColor3f(0.5,0.5,0.5);
                glVertex2f( nos[noAux->getID()]->getCx(), nos[noAux->getID()]->getCy());
                if (!ehReciproco) glColor3f(0.95, 0.95, 0.95);
                glVertex2f( nos[arcoAux->getNoDestino()->getID()]->getCx(), nos[arcoAux->getNoDestino()->getID()]->getCy());
            glEnd();
            arcoAux = arcoAux->getProxArco();
        }
        noAux = noAux->getProxNo();
    }

    ///desenha vertices
    for (int i = 0; i < n; i++)
        nos[i]->Desenha();
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define visualização do canto superior esquerdo
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, largura, 0, altura, -1, 1);

//    desenhaGrafo(grafoEscadinha(n));
    desenhaGrafo(grafoCircular(n));

///   escrever algum texto na tela
//    char aux[100];
//    string s;
//    sprintf(aux, "selecionado %d", selecionado == NULL ? -1 : selecionado->getID());
//    s.assign(aux);
//    glColor3f(0,1,0);
//    ImprimeTexto(s, largura*0.3, 10);

    glutSwapBuffers();
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
    y= altura-y;
    if(state == GLUT_DOWN){
        int i = 0;
        while(i < n && !nos[i]->Dentro(x, y))
            i++;
        if(i < n)
            selecionado = nos[i];
    }else{
        selecionado = NULL;
    }

    glutPostRedisplay();
}

void motion(int x, int y){
    y= altura-y;
    if(selecionado != NULL)
        selecionado->mover(x, y);

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
   switch (key){
      case 27 :
         exit(0);
      break;
      case 'r' :
        for (int i=0; i<n_nos; i++)
            delete nos[i];
        init();
      break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize ((int)largura,(int)altura);
    glutInitWindowPosition (100,100);
    glutCreateWindow ("Pong 2D");
    init ();
    glutFullScreen();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc( motion );
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}
