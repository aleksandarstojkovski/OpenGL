#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Headers richiesti da OSX
#ifdef __APPLE__
//#include <OpenGL/gl3.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <iostream>

// headers richiesti da Windows e linux
#else
#include <windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#endif


void draw() {

    // definisce con quale colore cancellare la scena (con openGL 2.0 il nero e' default)
    glClearColor(0.5, 0.5, 0.5, 0.0); // grigio
    // cancella la scena con colore definito sopra
    glClear(GL_COLOR_BUFFER_BIT);

    // vertici dei quattro triangoli
    GLfloat vertici_triangoli[][4]={
            {-1,0,1},
            {1,0,1},
            {0,3,0},

            {1,0,1},
            {1,0,-1},
            {0,3,0},

            {1,0,-1},
            {-1,0,-1},
            {0,3,0},

            {-1,0,-1},
            {-1,0,1},
            {0,3,0},
    };

    // triangoli che creano la piramide

    // GL_FRONT perche' vediamo solo il "front" delle facciate
    // GL_FILL per fare in modo che il triangolo sia riempito di colore
    glPolygonMode(GL_FRONT ,GL_FILL);
    glBegin(GL_TRIANGLES);

        // vertici in senso antiorario

        glColor3f(1, 0, 0);
        glVertex3fv(vertici_triangoli[0]);
        glVertex3fv(vertici_triangoli[1]);
        glVertex3fv(vertici_triangoli[2]);

        glColor3f(0, 1, 0);
        glVertex3fv(vertici_triangoli[3]);
        glVertex3fv(vertici_triangoli[4]);
        glVertex3fv(vertici_triangoli[5]);

        glColor3f(0, 0, 1);
        glVertex3fv(vertici_triangoli[6]);
        glVertex3fv(vertici_triangoli[7]);
        glVertex3fv(vertici_triangoli[8]);

        glColor3f(0, 1, 1);
        glVertex3fv(vertici_triangoli[9]);
        glVertex3fv(vertici_triangoli[10]);
        glVertex3fv(vertici_triangoli[11]);

    glEnd();


    // bordi neri dei triangoli

    // GL_FRONT perche' vediamo solo il "front" delle facciate
    // GL_LINE per fare in modo che il triangolo non sia riempito di colore

    glPolygonMode(GL_FRONT,GL_LINE);
    glLineWidth(3.0);

    glBegin(GL_TRIANGLES);

        glColor3f(0, 0, 0);

        glVertex3fv(vertici_triangoli[0]);
        glVertex3fv(vertici_triangoli[1]);
        glVertex3fv(vertici_triangoli[2]);

        glVertex3fv(vertici_triangoli[3]);
        glVertex3fv(vertici_triangoli[4]);
        glVertex3fv(vertici_triangoli[5]);

        glVertex3fv(vertici_triangoli[6]);
        glVertex3fv(vertici_triangoli[7]);
        glVertex3fv(vertici_triangoli[8]);

        glVertex3fv(vertici_triangoli[9]);
        glVertex3fv(vertici_triangoli[10]);
        glVertex3fv(vertici_triangoli[11]);

    glEnd();

    // esegue i comandi
    glFlush();
}


void init(){
    // abilita il fatto di poter eliminare le facce che non si vedono
    // senza glEnable(GL_CULL_FACE) non si puo' utilizzare glPolygonMode(GL_FRONT,GL_LINE)
    glEnable(GL_CULL_FACE);
    // quando si setta zoom, ertho ecc bisogna mettere GL_PROJECTION
    glMatrixMode(GL_PROJECTION);
    // definisce l'area visualizzabile
    glOrtho(-5, 5, -5, 4, -5, 5);
    // modalita' standard di trasformazione, non va piu cambiata
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // cambia la prospettiva
    // gluPerspective(100,1,1,10);
    gluLookAt(1.5, 1, 3, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);				// Inizializza libreria glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Singolo buffer con modello colore RGBA
    // grandezza finestra
    glutInitWindowSize(800,600);
    // titolo finestra
    glutCreateWindow("Piramide");
    //glutReshapeFunc(reshape);
    // funzione che disegna
    glutDisplayFunc(draw);
    init();
    glutMainLoop();					// loop infinito
}

