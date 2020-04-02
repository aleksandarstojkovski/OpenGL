#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
    // MacOS
    #include <GLUT/glut.h>
#else
    // Windows and linux
    #include <GL\glew.h>
    #include <GL\freeglut.h>
#endif

typedef struct {
    float x;
    float y;
    float z;
} Point;

typedef struct {
    float r;
    float g;
    float b;
} Color;

int i;
int SHOW_TRIANGLES=0;
int SPIN_SPEED=100;
int SPIN = 0;
int IS_SPINNING = 0;
int MAIN_WINDOW;
int SHOW_AXIS=1;
float X_POS=0;
float MAX_X_POS=6;
float Y_POS=0;
float MAX_Y_POS=3;
float Z_POS=4;
float MAX_Z_POS=10;
int DOOR_ANGLE=180;
Color BACKGROUND_COLOR={0.7f, 0.7f, 0.7f};
Color ROOF_COLOR={1, 0, 0};
Color DOOR_COLOR={0.5f, 0.25f, 0.25f};
Color WALL_COLOR_INTERIOR={0.5f, 0.5f, 0.5f};
Color WALL_COLOR_EXTERIOR={1, 1, 1};

void normal_calculator(Point a, Point b, Point c, Point * destination_normal){

    Point ab = {b.x - a.x, b.y - a.y, b.z - a.z};
    Point ac = {c.x - a.x, c.y - a.y, c.z - a.z};
    Point cross = {ab.y * ac.z - ab.z * ac.y,
                   ab.z*ac.x-ab.x*ac.z,
                   ab.x*ac.y-ab.y*ac.x};

    float modulo = (float)sqrt(pow(cross.x,2)+pow(cross.y,2)+pow(cross.z,2));

    cross.x = cross.x/modulo;
    cross.y = cross.y/modulo;
    cross.z = cross.z/modulo;

    destination_normal->x = cross.x;
    destination_normal->y = cross.y;
    destination_normal->z = cross.z;

}

void mainMenuCB(int value) {
    switch (value) {
        case 1:
            SHOW_AXIS = !SHOW_AXIS;
            break;
        case 2:
            if (DOOR_ANGLE == 180){
                DOOR_ANGLE=125;
            } else {
                DOOR_ANGLE = 180;
            }
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void transMenuCB(int value){
    switch (value) {
        case 1:
            if (fabsf(X_POS) >= MAX_X_POS) return;
            X_POS++;
            break;
        case 2:
            if (fabsf(X_POS) >= MAX_X_POS) return;
            X_POS--;
            break;
        case 3:
            if (fabsf(Y_POS) >= MAX_Y_POS) return;
            Y_POS++;
            break;
        case 4:
            if (fabsf(Y_POS) >= MAX_Y_POS) return;
            Y_POS--;
            break;
        case 5:
            if (fabsf(Z_POS) >= MAX_Z_POS) return;
            Z_POS++;
            break;
        case 6:
            if (fabsf(Z_POS) >= MAX_Z_POS) return;
            Z_POS--;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void colorMenuCB(int value) {
    switch (value) {
        case 1:
            ROOF_COLOR.r=1;
            ROOF_COLOR.g=0;
            ROOF_COLOR.b=0;
            break;
        case 2:
            ROOF_COLOR.r=0;
            ROOF_COLOR.g=0;
            ROOF_COLOR.b=1;
            break;
        case 3:
            ROOF_COLOR.r=1;
            ROOF_COLOR.g=1;
            ROOF_COLOR.b=1;
            break;
        case 4:
            WALL_COLOR_EXTERIOR.r=1;
            WALL_COLOR_EXTERIOR.g=0;
            WALL_COLOR_EXTERIOR.b=0;
            break;
        case 5:
            WALL_COLOR_EXTERIOR.r=0;
            WALL_COLOR_EXTERIOR.g=0;
            WALL_COLOR_EXTERIOR.b=1;
            break;
        case 6:
            WALL_COLOR_EXTERIOR.r=1;
            WALL_COLOR_EXTERIOR.g=1;
            WALL_COLOR_EXTERIOR.b=1;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void createMenu() {
    int translationMenu = glutCreateMenu(transMenuCB);
    glutAddMenuEntry("Translate +X",1);
    glutAddMenuEntry("Translate -X",2);
    glutAddMenuEntry("Translate +Y",3);
    glutAddMenuEntry("Translate -Y",4);
    glutAddMenuEntry("Translate +Z",5);
    glutAddMenuEntry("Translate -Z",6);

    int colorMenu = glutCreateMenu(colorMenuCB);
    glutAddMenuEntry("Roof Red",1);
    glutAddMenuEntry("Roof Blue",2);
    glutAddMenuEntry("Roof White",3);
    glutAddMenuEntry("Wall Red",4);
    glutAddMenuEntry("Wall Blue",5);
    glutAddMenuEntry("Wall White",6);

    int mainMenu = glutCreateMenu(mainMenuCB);
    glutAddMenuEntry("Show/Hide Axis", 1);
    glutAddMenuEntry("Open/Close Door", 2);
    glutAddSubMenu("Translation", translationMenu);
    glutAddSubMenu("Color", colorMenu);

    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void draw_triangle(Point points[3], Color color){
    glPolygonMode(GL_FRONT ,GL_FILL);
    glBegin(GL_TRIANGLES);
    glColor3f(color.r,color.g,color.b);
    glVertex3f(points[0].x,points[0].y,points[0].z);
    glVertex3f(points[1].x,points[1].y,points[1].z);
    glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();
}

void draw_rectangle(Point points[4], Color color){

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

void draw_rectangle_back(Point points[4], Color color){

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

void draw_pol(Point points[4], float depth, Color external_color, Color internal_color){

    Point translated_in_z[4];
    Point right_face[4];
    Point left_face[4];
    Point top_face[4];
    Point bottom_face[4];

    Point normal = {0, 0, 0};

    normal_calculator(points[0], points[1], points[2], &normal);

    // calcolo rettangolo spostano nell'asse Z
    for (i=0;i<4;i++){
        translated_in_z[i]=points[i];
        translated_in_z[i].x=translated_in_z[i].x + depth*normal.x;
        translated_in_z[i].y=translated_in_z[i].y + depth*normal.y;
        translated_in_z[i].z=translated_in_z[i].z + depth*normal.z;
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

    draw_rectangle(points, external_color);
    draw_rectangle_back(translated_in_z, internal_color);
    draw_rectangle(right_face, external_color);
    draw_rectangle(left_face, external_color);
    draw_rectangle(top_face, external_color);
    draw_rectangle(bottom_face, external_color);
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

void draw() {

    // Background Color
    glClearColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 0.0);
    // Delete scene and apply defined Color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)

    Point rect_front_right[4]={{0.5f, 0, 0}, {4, 0, 0}, {4, 2, 0}, {0.5f, 2, 0}};
    Point rect_front_left[4]={{-4, 0, 0}, {-0.5f, 0, 0}, {-0.5f, 2, 0}, {-4, 2, 0}};
    Point rect_front_center[4]={{-4, 2, 0}, {4, 2, 0}, {4, 4, 0}, {-4, 4, 0}};
    Point rect_back[4]={{-4, 4, -8}, {4, 4, -8}, {4, 0, -8}, {-4, 0, -8}};
    Point rect_right[4]={{4, 0, 0}, {4, 0, -8}, {4, 4, -8}, {4, 4, 0}};
    Point rect_left[4]={{-4, 4, 0}, {-4, 4, -8}, {-4, 0, -8}, {-4, 0, 0}};
    Point rect_bottom[4]={{-4, 0, 0}, {-4, 0, -8}, {4, 0, -8}, {4, 0, 0}};
    Point front_triangle[3]={{-4, 4, 0}, {4, 4, 0}, {0, 6.4f, 0}};
    Point back_triangle[3]={{-4, 4, -8}, {0, 6.4f, -8}, {4, 4, -8}};
    Point roof_left[4]={{-4.8f, 3.8f, 0.5f}, {0, 6.8f, 0.5f}, {0, 6.8f, -8.5f}, {-4.8f, 3.8f, -8.5f}};
    Point roof_right[4]={{4.8f, 3.8f, 0.5f}, {4.8f, 3.8f, -8.5f}, {0, 6.8f, -8.5f}, {0, 6.8f, 0.5f}};
    Point comignolo_pz1[4]={{-3, 4, -4}, {-2, 4, -4}, {-2, 7, -4}, {-3, 7, -4}};
    Point comignolo_pz2[4]={{-3.2f, 7, -3.8f}, {-1.8f, 7, -3.8f}, {-1.8f, 7.5f, -3.8f}, {-3.2f, 7.5f, -3.8f}};
    Point porta[4]={{0.5f, 0, 0.1f}, {0.5f, 2, 0.1f}, {-0.5f, 2, 0.1f}, {-0.5f, 0, 0.1f}};

    // DRAW

    draw_axis();

    // Trasla la casa
    glPushMatrix();

    glTranslatef(X_POS,Y_POS,Z_POS);

    glRotatef(SPIN, 0.0, 1.0, 0.0);

    draw_pol(rect_front_right,-0.3f,WALL_COLOR_EXTERIOR,WALL_COLOR_INTERIOR);
    draw_pol(rect_front_left,-0.3f,WALL_COLOR_EXTERIOR,WALL_COLOR_INTERIOR);
    draw_pol(rect_front_center,-0.3f,WALL_COLOR_EXTERIOR,WALL_COLOR_INTERIOR);
    draw_pol(rect_back,-0.3f,WALL_COLOR_EXTERIOR,WALL_COLOR_INTERIOR);
    draw_pol(rect_right,-0.3f,WALL_COLOR_EXTERIOR,WALL_COLOR_INTERIOR);
    draw_pol(rect_left,-0.3f,WALL_COLOR_EXTERIOR,WALL_COLOR_INTERIOR);
    draw_pol(rect_bottom,0.0f,WALL_COLOR_EXTERIOR,WALL_COLOR_INTERIOR);
    draw_triangle(front_triangle, WALL_COLOR_EXTERIOR);
    draw_triangle(back_triangle, WALL_COLOR_EXTERIOR);
    draw_pol(roof_left,-0.3f,ROOF_COLOR,ROOF_COLOR);
    draw_pol(roof_right,-0.3f,ROOF_COLOR,ROOF_COLOR);
    draw_pol(comignolo_pz1, -1, WALL_COLOR_EXTERIOR, WALL_COLOR_EXTERIOR);
    draw_pol(comignolo_pz2, -1.4f, WALL_COLOR_EXTERIOR, WALL_COLOR_EXTERIOR);


    glPushMatrix();
    glTranslatef(0.5,0,0);
    glRotatef(DOOR_ANGLE,0,1,0);
    glTranslatef(0.5,0,0);
    draw_pol(porta,-0.1f,DOOR_COLOR,DOOR_COLOR);
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
    //glMatrixMode(GL_PROJECTION);
    // definisce l'area visualizzabile
    //glOrtho(-12, 12, -12, 12, -12, 12);
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
        default:
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
void keyboard(unsigned char key, int x, int y) {
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
        default:
            break;
    }
}

void reshapeCB(int w, int h) {
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-12, 12, -12*(GLfloat)h/(GLfloat)w,12*(GLfloat)h/(GLfloat)w, -12.0, 12.0);
    else
        glOrtho (-12*(GLfloat)w/(GLfloat)h,12*(GLfloat)w/(GLfloat)h, -12, 12, -12.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // Init glut library and window management
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // NOLINT(hicpp-signed-bitwise)
    // grandezza finestra
    glutInitWindowSize(1000,750);
    // Title function
    MAIN_WINDOW = glutCreateWindow("House by Aleksandar Stojkovski");
    // init
    init();
    // Reshape
    glutReshapeFunc(reshapeCB);
    // Draw function
    glutDisplayFunc(draw);
    glutSpecialFunc(keyboardS);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(SPIN_SPEED, spinDisplay, 1);
    glutMainLoop();					// loop infinito
}

