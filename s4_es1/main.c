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

int livello,  cull_face=GL_FALSE;

typedef struct {
    float x;
    float y;
    float z;
} point;

void draw_triangle(point points[3]){
    glPolygonMode(GL_FRONT ,GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);
        glVertex3f(points[0].x,points[0].y,points[0].z);
        glVertex3f(points[1].x,points[1].y,points[1].z);
        glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();
}

void draw_rectangle(point points[4]){

    int i;

    // triangoli che creano la piramide

    // GL_FRONT perche' vediamo solo il "front" delle facciate
    // GL_FILL per fare in modo che il triangolo sia riempito di colore
    glPolygonMode(GL_FRONT ,GL_FILL);

    glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 0);
        for (i=0;i<3;i++){
            glVertex3f(points[i].x,points[i].y,points[i].z);
        }
        glVertex3f(points[0].x,points[0].y,points[0].z);
        glVertex3f(points[2].x,points[2].y,points[2].z);
        glVertex3f(points[3].x,points[3].y,points[3].z);
    glEnd();

    glPolygonMode(GL_FRONT ,GL_LINE);

    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    for (i=0;i<3;i++){
        glVertex3f(points[i].x,points[i].y,points[i].z);
    }
    glVertex3f(points[0].x,points[0].y,points[0].z);
    glVertex3f(points[2].x,points[2].y,points[2].z);
    glVertex3f(points[3].x,points[3].y,points[3].z);
    glEnd();

}

void draw_rectangle_back(point points[4]){

    int i;

    // triangoli che creano la piramide

    // GL_FRONT perche' vediamo solo il "front" delle facciate
    // GL_FILL per fare in modo che il triangolo sia riempito di colore
    glPolygonMode(GL_FRONT ,GL_FILL);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 1);
    for (i=2;i>=0;i--){
        glVertex3f(points[i].x,points[i].y,points[i].z);
    }
    glVertex3f(points[0].x,points[0].y,points[0].z);
    glVertex3f(points[3].x,points[3].y,points[3].z);
    glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();

    glPolygonMode(GL_FRONT ,GL_LINE);

    glBegin(GL_TRIANGLES);
    glColor3f(0, 0, 0);
    for (i=2;i>=0;i--){
        glVertex3f(points[i].x,points[i].y,points[i].z);
    }
    glVertex3f(points[0].x,points[0].y,points[0].z);
    glVertex3f(points[3].x,points[3].y,points[3].z);
    glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();

}

void draw_pol(point points[4], float depth){
    int i, j;
    point translated_in_z[4];
    point right_face[4];
    point left_face[4];
    point top_face[4];
    point bottom_face[4];

    // calcolo rettangolo spostano nell'asse Z
    for (i=0;i<4;i++){
        translated_in_z[i]=points[i];
        translated_in_z[i].z=translated_in_z[i].z + depth;
    }

    right_face[0]=points[1];
    right_face[1]=translated_in_z[1];
    right_face[2]=translated_in_z[2];
    right_face[3]=points[2];

    left_face[0]=points[0];
    left_face[1]=points[3];
    left_face[2]=translated_in_z[3];
    left_face[3]=translated_in_z[0];

    top_face[0]=points[3];
    top_face[1]=points[2];
    top_face[2]=translated_in_z[2];
    top_face[3]=translated_in_z[3];

    bottom_face[0]=points[0];
    bottom_face[1]=translated_in_z[0];
    bottom_face[2]=translated_in_z[1];
    bottom_face[3]=points[1];

    draw_rectangle(points);
    draw_rectangle_back(translated_in_z);
    draw_rectangle(right_face);
    draw_rectangle(left_face);
    draw_rectangle(top_face);
    draw_rectangle(bottom_face);
}

void draw_axis() {
    glLineWidth(1.0f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xf0f0);
    // axes are ten units long.
    glBegin(GL_LINES);
    // Draw a red x-axis
    glColor3ub(255, 0, 0);
    glVertex3f(-10, 0, 0);
    glVertex3f(10, 0, 0);
    // Draw a green y-axis
    glColor3ub(0, 255, 0);
    glVertex3f(0, -10, 0);
    glVertex3f(0, 10, 0);
    // Draw a blue z-axis
    glColor3ub(0, 0, 255);
    glVertex3f(0, 0, -10);
    glVertex3f(0, 0, 10);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void draw() {

    // definisce con quale colore cancellare la scena (con openGL 2.0 il nero e' default)
    glClearColor(0.5, 0.5, 0.5, 0.0); // grigio
    // cancella la scena con colore definito sopra
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    point rect_front_right[4]={{0.5,0,0},{4,0,0},{4,2,0},{0.5,2,0}};
    point rect_front_left[4]={{-4,0,0},{-0.5,0,0},{-0.5,2,0},{-4,2,0}};
    point rect_front_center[4]={{-4,2,0},{4,2,0},{4,4,0},{-4,4,0}};
    point rect_back[4]={{-4,4,-8},{4,4,-8},{4,0,-8},{-4,0,-8}};
    point rect_right[4]={{4,0,0},{4,0,-8},{4,4,-8},{4,4,0}};
    point rect_left[4]={{-4,4,0},{-4,4,-8},{-4,0,-8},{-4,0,0}};
    point rect_bottom[4]={{-4,0,0},{-4,0,-8},{4,0,-8},{4,0,0}};
    point front_rect[3]={{-4,4,0},{4,4,0},{0,7,0}};
    point back_rect[3]={{-4,4,-8.1},{0,7,-8.1},{4,4,-8.1}};
    point roof_left[4]={{-4,4,0},{0,7,0},{0,7,-8},{-4,4,-8}};
    point roof_right[4]={{4,4,0},{4,4,-8},{0,7,-8},{0,7,0}};

    point comignolo1[4]={{2,4,-4},{3,4,-4},{3,7,-4},{2,7,-4}};

    // DISEGNO

    // disgna assi
    draw_axis();

    // Trasla la casa
    glTranslatef(0.0,1.0,4.0);

    // dissegna la casa
    draw_pol(rect_front_right,-0.1);
    draw_pol(rect_front_left,-0.1);
    draw_pol(rect_front_center,-0.1);
    draw_pol(rect_back,-0.1);
    draw_pol(rect_right,-0.1);
    draw_pol(rect_left,-0.1);
    draw_pol(rect_bottom,-0.1);
    draw_triangle(front_rect);
    draw_triangle(back_rect);
    draw_pol(roof_left,-0.1);
    draw_pol(roof_right,-0.1);
    draw_pol(comignolo1,-1);

    glTranslatef(0.0,-1.0,-4.0);

    // esegue i comandi
    glutSwapBuffers();
}

void init(){
    // abilita il fatto di poter eliminare le facce che non si vedono
    // senza glEnable(GL_CULL_FACE) non si puo' utilizzare glPolygonMode(GL_FRONT,GL_LINE)
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    // quando si setta zoom, ertho ecc bisogna mettere GL_PROJECTION
    glMatrixMode(GL_PROJECTION);
    // definisce l'area visualizzabile
    glOrtho(-12, 12, -12, 12, -12, 12);
    // modalita' standard di trasformazione, non va piu cambiata
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // cambia la prospettiva
    // gluPerspective(100,1,1,10);
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
}

void keyboardS(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            glRotatef(1.0,0.0,1.0,0.0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            glRotatef(-1.0,0.0,1.0,0.0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            glRotatef(1.0,1.0,0.0,0.0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            glRotatef(1.0,-1.0,0.0,0.0);
            glutPostRedisplay();
            break;
    }

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);				// Inizializza libreria glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // grandezza finestra
    glutInitWindowSize(800,600);
    // titolo finestra
    glutCreateWindow("Piramide");
    // funzione che disegna
    init();
    glutDisplayFunc(draw);
    glutSpecialFunc(keyboardS);
    glutMainLoop();					// loop infinito
}

