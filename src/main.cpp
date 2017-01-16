#include "GL/glut.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Circulo.h"
#include "GrafoHash.h"
#include "GrafoLista.h"

using namespace std;

int altura, largura;
Circulo *selecionado = NULL;
int pos[2];

int n_grafos = 3;
Grafo *A, *B, *C, *G;
Grafo *grafos[3];
map <No*, Circulo*> noCirculo;

void inserirCirculos(Grafo *G){
    double x, y, raio;

    GLfloat r, g, b;
    r = (GLfloat) (rand() % 101 / 100.0);
    g = (GLfloat) (rand() % 101 / 100.0);
    b = (GLfloat) (rand() % 101 / 100.0);

    for (G->itInicio(); G->getIt()!=NULL; G->itProx()){
        raio = min(altura, largura)/15;//fmod(rand(), altura/20 + 5);
        x= fmod(rand(), (largura-2*raio) + raio);
        y= fmod(rand(), (altura -2*raio) + raio);
        Circulo* noCG = new Circulo(raio, x, y);
//        noCG->getCx();
        noCG->setCor(r, g, b);
        noCG->setID(G->getIt()->getID());
        noCirculo[G->getIt()] = noCG;
//        G->getIt()->setCirculo(noCG);
//        G->getIt()->getCirculo()->getCx();
    }
}

// Inicializa opengl
void init(void){
    A = GrafoLista::grafoCompleto(4);
    A = A->buscaProfundidade(A->buscaNo(1));
    B = GrafoLista::grafoEscadinha(3);
    C = A->produtoCartesiano(B);

    grafos[0] = A;
    grafos[1] = B;
    grafos[2] = C;

//    C->imprime();
    srand((unsigned int) time(NULL));
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
                glVertex2f( noCirculo[no]->getCx(), noCirculo[no]->getCy());
                if (!ehReciproco) glColor3f(0.95, 0.95, 0.95);
                glVertex2f( noCirculo[arco->getNoDestino()]->getCx(), noCirculo[arco->getNoDestino()]->getCy());
            glEnd();
        }
    }

    ///desenha vertices
    for(G->itInicio(); G->getIt()!=NULL; G->itProx())
        noCirculo[G->getIt()]->Desenha();
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define visualizacao do canto superior esquerdo
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
        for (int i=0; i < n_grafos; i++){
            Grafo *G = grafos[i];
            for(G->itInicio(); G->getIt()!=NULL; G->itProx())
                if( noCirculo[G->getIt()]->Dentro(x, y) )
                    break;
            if(G->getIt()!=NULL)
                selecionado = noCirculo[G->getIt()];
        }
    }else{
        selecionado = NULL;
    }

    glutPostRedisplay();
}

void motion(int x, int y){
    y= altura-y;
    if(selecionado != NULL &&
            (x > 0 && x < largura) &&
            (y > 0 && y < altura) )
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
    altura = 900/2;
    largura = 1600/2;
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize((int)largura,(int)altura);
    glutInitWindowPosition (largura*0.05, 0);
    glutCreateWindow ("Grafos");
    init();

//    glutFullScreen();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc( motion );
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}