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

typedef struct {
    float x;
    float y;
    float z;
} point;

typedef struct {
    float r;
    float g;
    float b;
} color;

int i;
int SHOW_TRIANGLES=1;
int SPIN_SPEED=100;
int SPIN = 0;
int IS_SPINNING = 0;
int MAIN_WINDOW;
int SHOW_AXIS=1;
int X_POS=0;
int MAX_X_POS=6;
int Y_POS=0;
int MAX_Y_POS=3;
int Z_POS=4;
int MAX_Z_POS=10;
int DOOR_ANGLE=180;

void mainMenuCB(int value) {
    switch (value) {
        case 1:
            SHOW_AXIS = !SHOW_AXIS;
            break;
        case 2:
            SHOW_TRIANGLES = !SHOW_TRIANGLES;
            break;
        case 3:
            if (abs(X_POS) >= MAX_X_POS) return;
            X_POS++;
            break;
        case 4:
            if (abs(X_POS) >= MAX_X_POS) return;
            X_POS--;
            break;
        case 5:
            if (abs(Y_POS) >= MAX_Y_POS) return;
            Y_POS++;
            break;
        case 6:
            if (abs(Y_POS) >= MAX_Y_POS) return;
            Y_POS--;
            break;
        case 7:
            if (abs(Z_POS) >= MAX_Z_POS) return;
            Z_POS++;
            break;
        case 8:
            if (abs(Z_POS) >= MAX_Z_POS) return;
            Z_POS--;
            break;
        case 9:
            if (DOOR_ANGLE == 180){
                DOOR_ANGLE=125;
            } else {
                DOOR_ANGLE = 180;
            }
            break;
    }
    glutPostRedisplay();
}

void createMenu() {
    int menu = glutCreateMenu(mainMenuCB);
    glutAddMenuEntry("Show/Hide Axes", 1);
    glutAddMenuEntry("Show/Hide Triangles", 2);
    glutAddMenuEntry("Open/Close Door", 9);
    glutAddMenuEntry("Translate +X", 3);
    glutAddMenuEntry("Translate -X", 4);
    glutAddMenuEntry("Translate +Y", 5);
    glutAddMenuEntry("Translate -Y", 6);
    glutAddMenuEntry("Translate +Z", 7);
    glutAddMenuEntry("Translate -Z", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void draw_triangle(point points[3], color color){
    glPolygonMode(GL_FRONT ,GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(color.r,color.g,color.b);
    glVertex3f(points[0].x,points[0].y,points[0].z);
    glVertex3f(points[1].x,points[1].y,points[1].z);
    glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();
}

void draw_rectangle(point points[4], color color){

    // triangoli che creano la piramide

    // GL_FRONT perche' vediamo solo il "front" delle facciate
    // GL_FILL per fare in modo che il triangolo sia riempito di colore
    glPolygonMode(GL_FRONT ,GL_FILL);

    glBegin(GL_TRIANGLES);
    glColor3f(color.r,color.g,color.b);
    for (i=0;i<3;i++){
        glVertex3f(points[i].x,points[i].y,points[i].z);
    }
    glVertex3f(points[0].x,points[0].y,points[0].z);
    glVertex3f(points[2].x,points[2].y,points[2].z);
    glVertex3f(points[3].x,points[3].y,points[3].z);
    glEnd();

    if (SHOW_TRIANGLES){
        glPolygonMode(GL_FRONT ,GL_LINE);
        glBegin(GL_TRIANGLES);
        glColor3f(0,0,0);
        for (i=0;i<3;i++){
            glVertex3f(points[i].x,points[i].y,points[i].z);
        }
        glVertex3f(points[0].x,points[0].y,points[0].z);
        glVertex3f(points[2].x,points[2].y,points[2].z);
        glVertex3f(points[3].x,points[3].y,points[3].z);
        glEnd();
    }

}

void draw_rectangle_back(point points[4], color color){

    int i;

    // triangoli che creano la piramide

    // GL_FRONT perche' vediamo solo il "front" delle facciate
    // GL_FILL per fare in modo che il triangolo sia riempito di colore
    glPolygonMode(GL_FRONT ,GL_FILL);

    glBegin(GL_TRIANGLES);
    glColor3f(color.r,color.g,color.b);
    for (i=2;i>=0;i--){
        glVertex3f(points[i].x,points[i].y,points[i].z);
    }
    glVertex3f(points[0].x,points[0].y,points[0].z);
    glVertex3f(points[3].x,points[3].y,points[3].z);
    glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();

    if (SHOW_TRIANGLES) {
        glPolygonMode(GL_FRONT, GL_LINE);
        glBegin(GL_TRIANGLES);
        glColor3f(0, 0, 0);
        for (i = 2; i >= 0; i--) {
            glVertex3f(points[i].x, points[i].y, points[i].z);
        }
        glVertex3f(points[0].x, points[0].y, points[0].z);
        glVertex3f(points[3].x, points[3].y, points[3].z);
        glVertex3f(points[2].x, points[2].y, points[2].z);
        glEnd();
    }

}

void draw_pol(point points[4], float depth, color front_color, color back_color){

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

    draw_rectangle(points, front_color);
    draw_rectangle_back(translated_in_z, back_color);
    draw_rectangle(right_face, front_color);
    draw_rectangle(left_face, front_color);
    draw_rectangle(top_face, front_color);
    draw_rectangle(bottom_face, front_color);
}

void draw_axis() {

    if (SHOW_AXIS != 1 )
        return;

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
void animazioneRotateCasa() {
    glRotatef(SPIN, 0.0, 1.0, 0.0);
}

void draw() {

    // definisce con quale colore cancellare la scena (con openGL 2.0 il nero e' default)
    glClearColor(1, 1, 1, 0.0); // grigio
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
    point comignolo[4]={{2,4,-4},{3,4,-4},{3,7,-4},{2,7,-4}};
    point porta[4]={{0.5,0,0.1},{0.5,2,0.1},{-0.5,2,0.1},{-0.5,0,0.1}};

    color front_color ={0.7,0.7,0.7};
    color back_color = {0.4,0.4,0.4};
    color marron_color = {0.5,0.25,0.25};

    // DISEGNO

    draw_axis();

    // Trasla la casa
    glPushMatrix();

        glTranslatef(X_POS,Y_POS,Z_POS);

        glRotatef(SPIN, 0.0, 1.0, 0.0);

        draw_pol(rect_front_right,-0.1,front_color,back_color);
        draw_pol(rect_front_left,-0.1,front_color,back_color);
        draw_pol(rect_front_center,-0.1,front_color,back_color);
        draw_pol(rect_back,-0.1,front_color,back_color);
        draw_pol(rect_right,-0.1,front_color,back_color);
        draw_pol(rect_left,-0.1,front_color,back_color);
        draw_pol(rect_bottom,-0.1,front_color,back_color);
        draw_triangle(front_rect,front_color);
        draw_triangle(back_rect,front_color);
        draw_pol(roof_left,-0.1,front_color,back_color);
        draw_pol(roof_right,-0.1,front_color,back_color);
        draw_pol(comignolo,-1,back_color,back_color);


        glPushMatrix();
            glTranslatef(0.5,0,0);
            glRotatef(DOOR_ANGLE,0,1,0);
            glTranslatef(0.5,0,0);
            draw_pol(porta,-0.1,marron_color,marron_color);
        glPopMatrix();

    glPopMatrix();

    if (IS_SPINNING) {
        glRotatef(SPIN, 0.0, 1.0, 0.0);
    }

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
    createMenu();
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

void spinDisplay(int id)
{
    SPIN = 1;
    glutPostRedisplay();
    if (IS_SPINNING) glutTimerFunc(SPIN_SPEED, spinDisplay, id);
}


// Ruota con r e ferma con s
void keyboard(int key, int x, int y) {
    switch (key) {
        //r
        case 114:
            if (!IS_SPINNING) {
                IS_SPINNING = 1;
                glutTimerFunc(SPIN_SPEED, spinDisplay, 1);
            }
            break;
            //s
        case 115:
            IS_SPINNING = 0;
            SPIN=0;
            break;
            // esc
        case 27:
            glutDestroyWindow(MAIN_WINDOW);
            exit(0);
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);				// Inizializza libreria glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // grandezza finestra
    glutInitWindowSize(800,600);
    // titolo finestra
    MAIN_WINDOW = glutCreateWindow("Casa by Aleksandar Stojkovski");
    // funzione che disegna
    init();
    glutDisplayFunc(draw);
    glutSpecialFunc(keyboardS);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(SPIN_SPEED, spinDisplay, 1);
    glutMainLoop();					// loop infinito
}

