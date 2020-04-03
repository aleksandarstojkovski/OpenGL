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
#include <time.h>

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
int SPIN_SPEED=50;
int IS_SPINNING = 0;
int MAIN_WINDOW;
int SHOW_AXIS=1;
float X_POS=0;
float MAX_X_POS=6;
float Y_POS=0.1f;
float MAX_Y_POS=3;
float Z_POS=4;
float MAX_Z_POS=10;
int DOOR_ANGLE=180;
int DOOR_OPEN=0;
int DOOR_MOVING=0;
int WIND_ON=0;
int WIND_ANGLE=0;
int WIND_TARGET_RANDOM_ANGLE=0;
int TIME_PASSED=0;

/* all the used and changable colors */
Color BACKGROUND_COLOR={0.7f, 0.7f, 0.7f};
Color ROOF_COLOR={1, 0, 0};
Color DOOR_COLOR={0.5f, 0.25f, 0.25f};
Color WALL_COLOR_INTERIOR={0.5f, 0.5f, 0.5f};
Color WALL_COLOR_EXTERIOR={1, 1, 1};
Color FLAG_COLOR={0, 0, 1};
Color COMIGNOLO_UPPER_COLOR={0.5f, 0.25f, 0.25f};
Color COMIGNOLO_LOWER_COLOR={0.25f, 0.25f, 0.20f};

/* prints the time */
void printTime(){
    char buff[100];
    time_t now = time(0);
    strftime(buff, 100, "%Y-%m-%d %H:%M:%S.000", localtime(&now));
    printf("%s\n", buff);
}

/* returns random number in the specified range */
int getRandoms(int lower, int upper){
        return (rand() %(upper - lower + 1)) + lower;
}

/* calculates the normal vector of the surface given three points */
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


void transMenuCB(int value){
    // translation menu callback
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
    // color menu callback
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

void mainMenuCB(int value) {
    // main menu callback
    switch (value) {
        case 1:
            SHOW_AXIS = !SHOW_AXIS;
            break;
        case 2:
            DOOR_MOVING=1;
            DOOR_OPEN = !DOOR_OPEN;
            break;
        case 3:
            TODO:
            WIND_TARGET_RANDOM_ANGLE=getRandoms(0,360);
            WIND_ON=!WIND_ON;
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

void createMenu() {

    // translation menu
    int translationMenu = glutCreateMenu(transMenuCB);
    glutAddMenuEntry("Translate +X",1);
    glutAddMenuEntry("Translate -X",2);
    glutAddMenuEntry("Translate +Y",3);
    glutAddMenuEntry("Translate -Y",4);
    glutAddMenuEntry("Translate +Z",5);
    glutAddMenuEntry("Translate -Z",6);

    // color menu
    int colorMenu = glutCreateMenu(colorMenuCB);
    glutAddMenuEntry("Roof Red",1);
    glutAddMenuEntry("Roof Blue",2);
    glutAddMenuEntry("Roof White",3);
    glutAddMenuEntry("Wall Red",4);
    glutAddMenuEntry("Wall Blue",5);
    glutAddMenuEntry("Wall White",6);

    // main menu
    int mainMenu = glutCreateMenu(mainMenuCB);
    glutAddMenuEntry("Show/Hide Axis", 1);
    glutAddMenuEntry("Open/Close Door", 2);
    glutAddMenuEntry("Wind On/Off", 3);
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

    // GL_FRONT because we only see the front of the triangle
    // GL_FILL to fill the color of the rectangle
    glPolygonMode(GL_FRONT ,GL_FILL);

    // draw triangles
    glBegin(GL_TRIANGLES);
    glColor3f(color.r,color.g,color.b);
    for (i=0;i<3;i++){
        glVertex3f(points[i].x,points[i].y,points[i].z);
    }
    glVertex3f(points[0].x,points[0].y,points[0].z);
    glVertex3f(points[2].x,points[2].y,points[2].z);
    glVertex3f(points[3].x,points[3].y,points[3].z);
    glEnd();

    // draw triangles border
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

    // GL_FRONT because we only see the front of the triangle
    // GL_FILL to fill the color of the rectangle
    glPolygonMode(GL_FRONT ,GL_FILL);

    // draw triangles
    glBegin(GL_TRIANGLES);
        glColor3f(color.r,color.g,color.b);
        for (i=2;i>=0;i--){
            glVertex3f(points[i].x,points[i].y,points[i].z);
        }
        glVertex3f(points[0].x,points[0].y,points[0].z);
        glVertex3f(points[3].x,points[3].y,points[3].z);
        glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();

    // draw triangles border
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

void draw_parallelepiped(Point *points, float depth, Color external_color, Color internal_color){

    // points translated trough normal
    Point translated_trough_normal[4];
    // faces of the
    Point right_face[4];
    Point left_face[4];
    Point front_face[4];
    Point back_face[4];

    // calculate normal vector
    Point normal = {0, 0, 0};
    normal_calculator(points[0], points[1], points[2], &normal);

    // calculate points translated trough normal
    for (i=0;i<4;i++){
        translated_trough_normal[i]=points[i];
        translated_trough_normal[i].x= translated_trough_normal[i].x + depth * normal.x;
        translated_trough_normal[i].y= translated_trough_normal[i].y + depth * normal.y;
        translated_trough_normal[i].z= translated_trough_normal[i].z + depth * normal.z;
    }

    // right face
    right_face[0]=points[1];
    right_face[1]=translated_trough_normal[1];
    right_face[2]=translated_trough_normal[2];
    right_face[3]=points[2];

    // left face
    left_face[0]=points[0];
    left_face[1]=points[3];
    left_face[2]=translated_trough_normal[3];
    left_face[3]=translated_trough_normal[0];

    // front face
    front_face[0]=points[3];
    front_face[1]=points[2];
    front_face[2]=translated_trough_normal[2];
    front_face[3]=translated_trough_normal[3];

    // back face
    back_face[0]=points[0];
    back_face[1]=translated_trough_normal[0];
    back_face[2]=translated_trough_normal[1];
    back_face[3]=points[1];

    // draw all the pieces of the parallelepiped
    draw_rectangle(points, external_color);
    draw_rectangle_back(translated_trough_normal, internal_color);
    draw_rectangle(right_face, external_color);
    draw_rectangle(left_face, external_color);
    draw_rectangle(front_face, external_color);
    draw_rectangle(back_face, external_color);

}

void draw_axis() {

    if (SHOW_AXIS != 1 )
        return;

    glLineWidth(1.0f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xf0f0);
    // axes are ten units long.
    glBegin(GL_LINES);
    // sraw a red x-axis
    glColor3ub(255, 0, 0);
    glVertex3f(-10, 0, 0);
    glVertex3f(10, 0, 0);
    // sraw a green y-axis
    glColor3ub(0, 255, 0);
    glVertex3f(0, -10, 0);
    glVertex3f(0, 10, 0);
    // sraw a blue z-axis
    glColor3ub(0, 0, 255);
    glVertex3f(0, 0, -10);
    glVertex3f(0, 0, 10);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

}

void draw() {

    // background Color
    glClearColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 0.0);

    // delete scene and apply defined Color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)

    // 3d vertexes of all the pieces of the house
    Point rect_front_right[4]={{0.5f, 0, 0}, {4, 0, 0}, {4, 2, 0}, {0.5f, 2, 0}};
    Point rect_front_left[4]={{-4, 0, 0}, {-0.5f, 0, 0}, {-0.5f, 2, 0}, {-4, 2, 0}};
    Point rect_front_center[4]={{-4, 2, 0}, {4, 2, 0}, {4, 4, 0}, {-4, 4, 0}};
    Point rect_back[4]={{-4, 4, -8}, {4, 4, -8}, {4, 0, -8}, {-4, 0, -8}};
    Point rect_right[4]={{4, 0, 0}, {4, 0, -8}, {4, 4, -8}, {4, 4, 0}};
    Point rect_left[4]={{-4, 4, 0}, {-4, 4, -8}, {-4, 0, -8}, {-4, 0, 0}};
    Point rect_bottom[4]={{-4, -0.1f, 0}, {-4, -0.1f, -8}, {4, -0.1f, -8}, {4, -0.1f, 0}};
    Point front_triangle[3]={{-4, 4, 0}, {4, 4, 0}, {0, 6.5f, 0}};
    Point back_triangle[3]={{-4, 4, -8}, {0, 6.5f, -8}, {4, 4, -8}};
    Point roof_left[4]={{-4.8f, 3.8f, 0.5f}, {0, 6.8f, 0.5f}, {0, 6.8f, -8.5f}, {-4.8f, 3.8f, -8.5f}};
    Point roof_right[4]={{4.8f, 3.8f, 0.5f}, {4.8f, 3.8f, -8.5f}, {0, 6.8f, -8.5f}, {0, 6.8f, 0.5f}};
    Point comignolo_pz1[4]={{-3, 4, -4}, {-2, 4, -4}, {-2, 7, -4}, {-3, 7, -4}};
    Point comignolo_pz2[4]={{-3.2f, 7, -3.8f}, {-1.8f, 7, -3.8f}, {-1.8f, 7.5f, -3.8f}, {-3.2f, 7.5f, -3.8f}};
    Point porta[4]={{0.5f, 0, 0.1f}, {0.5f, 2, 0.1f}, {-0.5f, 2, 0.1f}, {-0.5f, 0, 0.1f}};
    Point flag_triangle_front[3]={{0, -1, 0}, {1.5f, -0.5f, 0}, {0, 0, 0}};
    Point flag_triangle_back[3]={flag_triangle_front[0],flag_triangle_front[2],flag_triangle_front[1]};

    // START DRAWING

    draw_axis();

    // Trasla la casa
    glPushMatrix();

        // translate to X_POS Y_POS Z_POS
        glTranslatef(X_POS,Y_POS,Z_POS);

        // draw house
        draw_parallelepiped(rect_front_right, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR);
        draw_parallelepiped(rect_front_left, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR);
        draw_parallelepiped(rect_front_center, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR);
        draw_parallelepiped(rect_back, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR);
        draw_parallelepiped(rect_right, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR);
        draw_parallelepiped(rect_left, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR);
        draw_parallelepiped(rect_bottom, -0.1f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR);
        draw_triangle(front_triangle, WALL_COLOR_EXTERIOR);
        draw_triangle(back_triangle, WALL_COLOR_EXTERIOR);
        draw_parallelepiped(roof_left, -0.3f, ROOF_COLOR, ROOF_COLOR);
        draw_parallelepiped(roof_right, -0.3f, ROOF_COLOR, ROOF_COLOR);
        draw_parallelepiped(comignolo_pz1, -1, COMIGNOLO_LOWER_COLOR, COMIGNOLO_LOWER_COLOR);
        draw_parallelepiped(comignolo_pz2, -1.4f, COMIGNOLO_UPPER_COLOR, COMIGNOLO_UPPER_COLOR);

        // open/close door based on DOOR_ANGLE
        glPushMatrix();
            glTranslatef(0.5,0,0);
            glRotatef(DOOR_ANGLE,0,1,0);
            glTranslatef(0.5,0,0);
            draw_parallelepiped(porta, -0.1f, DOOR_COLOR, DOOR_COLOR);
        glPopMatrix();

    glPopMatrix();

    // flag
    glPushMatrix();
        glTranslatef(X_POS+3,Y_POS+7,Z_POS-4);
        // rotate cilynder
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0, 0, 0);
        // draw lower part of flag (cylinder)
        gluCylinder(gluNewQuadric(), 0.08f, 0.08f, 3, 30, 30);
        // rotate back in order to draw the triangle
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        // apply wind toration
        glRotatef(WIND_ANGLE, 0.0f, 1.0f, 0.0f);
        // draw upper part of flag - front
        draw_triangle(flag_triangle_front,FLAG_COLOR);
        // draw upper part of flag - back
        draw_triangle(flag_triangle_back,FLAG_COLOR);
    glPopMatrix();

    // display everything
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
    // change perspective
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);
    // create menu (right click)
    createMenu();
    // init random
    srand(time(0));
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

void timer_function(int id){

    if (TIME_PASSED <100)
        TIME_PASSED++;
    else
        TIME_PASSED=0;

    if (DOOR_MOVING) {
        if (DOOR_OPEN == 1) {
            if (DOOR_ANGLE > 125) {
                DOOR_ANGLE -= 5;
            } else {
                DOOR_MOVING = 0;
            }
        }
        if (DOOR_OPEN == 0) {
            if (DOOR_ANGLE < 180) {
                DOOR_ANGLE += 5;
            } else {
                DOOR_MOVING = 0;
            }
        }
    }

    if (IS_SPINNING) {
        glRotatef(1, 0.0, 1.0, 0.0);
    }

    if (WIND_ON) {
        if (WIND_ANGLE < WIND_TARGET_RANDOM_ANGLE)
            WIND_ANGLE += 1;
        if (WIND_ANGLE > WIND_TARGET_RANDOM_ANGLE)
            WIND_ANGLE -= 1;
    }

    if (TIME_PASSED == 100) {
        printTime();
        if (WIND_ON){
            printf("5 seconds passed -> new wind angle: %d\n",WIND_TARGET_RANDOM_ANGLE);
            WIND_TARGET_RANDOM_ANGLE=getRandoms(0,360);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(SPIN_SPEED, timer_function, 1);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 114:
            // r key
            if (!IS_SPINNING) {
                IS_SPINNING = 1;
            }
            break;
        case 115:
            // s key
            IS_SPINNING = 0;
            break;
        case 27:
            // esc key
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
    // init glut library and window management
    glutInit(&argc, argv);
    // set double buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // NOLINT(hicpp-signed-bitwise)
    // window size
    glutInitWindowSize(1000,750);
    // set title of window
    MAIN_WINDOW = glutCreateWindow("House by Aleksandar Stojkovski");
    // init all the variables
    init();
    // reshape for window resizing
    glutReshapeFunc(reshapeCB);
    // draw function
    glutDisplayFunc(draw);
    // catch keyboard arrows
    glutSpecialFunc(keyboardS);
    // catch keyboard keys
    glutKeyboardFunc(keyboard);
    // start timer
    glutTimerFunc(SPIN_SPEED, timer_function, 1);
    // start main infinite loop
    glutMainLoop();
}

