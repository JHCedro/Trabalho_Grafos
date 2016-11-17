#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "wtypes.h"
#include "Circulo.h"
#include "Grafo/AuxTestes.h"

using namespace std;

void GetDesktopResolution(int& horizontal, int& vertical){
   RECT desktop;
   const HWND hDesktop = GetDesktopWindow();
   GetWindowRect(hDesktop, &desktop);
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

int altura=700, largura=600, L_nos=50, n_nos=20;
Circulo *selecionado = NULL;
int pos[2];

int n_grafos = 3;
Grafo *A, *B, *C, *G;
Grafo *grafos[3];

void inserirCirculos(Grafo *G){
    double x, y, raio;

    GLfloat r, g, b;
    r = rand()%101 / 100.0;
    g = rand()%101 / 100.0;
    b = rand()%101 / 100.0;

    for (G->itInicio(); G->getIt()!=NULL; G->itProx()){
        raio= 30;//fmod(rand(), altura/20 + 5);
        x= fmod(rand(), (largura-2*raio) + raio);
        y= fmod(rand(), (altura -2*raio) + raio);
        Circulo* noCG = new Circulo(raio, x, y);
//        noCG->getCx();
        noCG->setCor(r, g, b);
        noCG->setID(G->getIt()->getID());
        G->getIt()->setCirculo(noCG);
        G->getIt()->getCirculo()->getCx();
    }
}

// Inicializa opengl
void init(void){
    GetDesktopResolution(largura, altura);
    A = GrafoCompleto(4);
    A = A->buscaProfundidade(A->buscaNo(1));
    B = GrafoEscadinha(3);
    C = A->produtoCartesiano(B);

    grafos[0] = A;
    grafos[1] = B;
    grafos[2] = C;

//    C->imprime();
    srand(time(NULL));
    for (int i=0; i < n_grafos; i++){
        inserirCirculos(grafos[i]);
    }


    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

/** Desenha vertices e arestas
    Arestas unidirecional: claro ---> escuro
    Aresta bidirecional: verde
*/
void desenhaGrafo(Grafo *G){
    bool ehReciproco = false;
    for(G->itInicio(); G->getIt()!=NULL; G->itProx()){
        No *no = G->getIt();
        for(no->itInicio(); no->getIt()!=NULL; no->itProx()){
            Arco* arco = no->getIt();
            ehReciproco = arco->getNoDestino()->ehAdjacente(no);
            glLineWidth(3.0);
            glBegin(GL_LINES);
                ehReciproco ? glColor3f(0,1,0) : glColor3f(0.5,0.5,0.5);
                glVertex2f( no->getCirculo()->getCx(), no->getCirculo()->getCy());
                if (!ehReciproco) glColor3f(0.95, 0.95, 0.95);
                glVertex2f( arco->getNoDestino()->getCirculo()->getCx(), arco->getNoDestino()->getCirculo()->getCy());
            glEnd();
        }
    }

    ///desenha vertices
    for(G->itInicio(); G->getIt()!=NULL; G->itProx())
        G->getIt()->getCirculo()->Desenha();
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define visualização do canto superior esquerdo
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, largura, 0, altura, -1, 1);

//    desenhaGrafo(GrafoEscadinha(n));

    desenhaGrafo(A);
    desenhaGrafo(B);
    desenhaGrafo(C);

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
        for (int i=0; i < n_grafos; i++){
            Grafo *G = grafos[i];
            for(G->itInicio(); G->getIt()!=NULL; G->itProx())
                if( G->getIt()->getCirculo()->Dentro(x, y) )
                    break;
            if(G->getIt()!=NULL)
                selecionado = G->getIt()->getCirculo();
        }
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
        delete G;
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
