#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Headers richiesti da OSX
#ifdef __APPLE__
//#include <Graphics/gl3.h>
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
    glClearColor(1.0, 1.0, 1.0, 0.0);  	//definisce con quale colore cancellare la scena
    //con openGL 2.0 il nero e' lo stato di default iniziale
    glClear(GL_COLOR_BUFFER_BIT);		//cancella la scena
    glLoadIdentity();					//Matrice di trasformazione: identita'
    glColor3ub(15, 32, 112);			//Definisce il colore degli oggetti da disegnare
    //glColor3i(INT_MAX , 0, 0);
    glOrtho(0, 10.0, 0, 10.0, -10.0, 10.0);	 //definisce l'area visualizzabile

    glBegin(GL_TRIANGLES);				//definisce il poligono e i 3 vertici
    glVertex2i(1, 0);
    glVertex2i(5, 4);
    glVertex2i(9, 0);
    glEnd();

    glBegin(GL_TRIANGLES);				//definisce il poligono e i 3 vertici
    glVertex2i(1, 10);
    glVertex2i(5, 6);
    glVertex2i(9, 10);
    glEnd();

    glBegin(GL_TRIANGLES);				//definisce il poligono e i 3 vertici
    glVertex2i(0, 1);
    glVertex2i(4, 5);
    glVertex2i(0, 9);
    glEnd();

    glBegin(GL_TRIANGLES);				//definisce il poligono e i 3 vertici
    glVertex2i(10, 9);
    glVertex2i(6, 5);
    glVertex2i(10, 1);
    glEnd();

    glColor3ub(0, 0, 0);			//Definisce il colore degli oggetti da disegnare
    glLineWidth(4.0);
    glBegin(GL_LINE_STRIP);				//definisce il poligono e i 3 vertici
    glVertex2i(0, 0);
    glVertex2i(10, 0);
    glVertex2i(10, 10);
    glVertex2i(0, 10);
    glEnd();

    glFlush();							//esegue i comandi
}


void reshape(int w, int h) {
    // printf("reshape: w=%d, h=%d\n",w,h); // debug print size
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (0, 0, -1.5*(GLfloat)h/(GLfloat)w,
                 1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
                 1.5*(GLfloat)w/(GLfloat)h, 0, 0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);				// Inizializza libreria glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Singolo buffer con modello colore RGBA
    glutInitWindowSize(524,311);
    glutCreateWindow("Bandiera Scozzese");  // Crea finestra (dimensioni e posizione di default) e definisce titolo
    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);			// Rendering function
    glutMainLoop();					// loop infinito
}

