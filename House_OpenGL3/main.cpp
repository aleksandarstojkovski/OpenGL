#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <cstdio>
#include <cstdlib>
#include <cmath>

#ifdef __APPLE__
    // MacOS
    #include <GLUT/glut.h>
#else
    // Windows and linux
    #include <GL/glew.h>
    #include <GL/glut.h>
#endif

const char file_separator =
#ifdef _WIN32
        '\\';
#else
'/';
#endif

// common libraries
#include <ctime>
#include <unistd.h>
#include <climits>

#include "lib/RgbImage.h"

/* defines a point */
typedef struct {
    float x;
    float y;
    float z;
} Point3d;

typedef struct {
    float x;
    float y;
} Point2d;

/* defines an RGB color */
typedef struct {
    float r;
    float g;
    float b;
} Color;

/* GLOBAL SETTINGS AND POINTERS */

// timer speed in ms
int TIMER_SPEED_IN_MS=50;
// contains main window address
int MAIN_WINDOW;

/* FLAGS */

// door open true/false
int DOOR_OPEN=0;
// is the door opening or closing
int DOOR_MOVING=0;
// wind on true/false
int WIND_ON=1;
// 1 = ortographic projection, 0 = perspective projection
int PROJ_ORTHOGRAPHIC=1;
// show lines of primitive triangles used to draw
int SHOW_TRIANGLES=0;
// 1 = house is rotating, 0 = house is not rotating
int IS_SPINNING = 0;
// show axis true/false
int SHOW_AXIS=1;
// debug flag
int DEBUG=1;
// loght on/off
int LIGHT_LEFT_ON=1;
int LIGHT_RIGHT_ON=1;
int LIGHT_LEFT_STATIC=1;
int LIGHT_RIGHT_STATIC=1;
int SHOW_LIGHT_BULBS=1;
int CLIPPING_ON=0;
// textures on/off
int TEXTURES_ENABLED=1;

/* HOUSE POSITION */

// X position of the house
float X_POS=0;
// max X position of the house
float MAX_X_POS=6;
// Y position of the house
float Y_POS=0.1f;
// max Y position of the house
float MAX_Y_POS=3;
// Z position of the house
float Z_POS=0;
// max Z position of the house
float MAX_Z_POS=3;
// angle of the door
int DOOR_ANGLE=180;
// house rotation angle
int HOUSE_ANGLE=0;

/* ORTHOGRAPHIC PROJECTION PARAMETERS */

// left orthographic
float ORTHO_LEFT=-12;
// right orthographic
float ORTHO_RIGHT=12;
// bottom orthographic
float ORTHO_BOTTOM=-12;
// top orthographic
float ORTHO_TOP=12;
// near orthographic
float ORTHO_ZNERAR=-12;
// far orthographic
float ORTHO_ZFAR=9999;

/* PERSPECTIVE PROJECTION PARAMETERS */

// near perspective
float PERSPECTIVE_ZNERAR=0.1;
// far perspective
int PERSPECTIVE_ZFAR=9999;
// view angle of the eye in perspective mode
int PERSPECTIVE_FOVY=130;

/* EYE (CAMERA) PARAMETERS */

// eye X position
int EYE_X_POS=0;
int MAX_EYE_X_POS=150;
int MIN_EYE_X_POS=-150;
// eye Y position
int EYE_Y_POS=0;
int MAX_EYE_Y_POS=150;
int MIN_EYE_Y_POS=-150;
// eye Z position
int EYE_Z_POS=6;
int MAX_EYE_Z_POS=150;
int MIN_EYE_Z_POS=-150;

/* WIND PARAMETERS */

// wind current angle
int WIND_ANGLE=0;
// wind target angle to reach
int WIND_TARGET_RANDOM_ANGLE=0;
// wind needs to change every 5s, track the time passed
int TIME_PASSED=0;

/* LIGHTS PARAMETERS */
// left light position
float LIGHT_LEFT_POS_X = -6;
float LIGHT_LEFT_POS_Y = 3;
float LIGHT_LEFT_POS_Z = 8;
// right light position
float LIGHT_RIGHT_POS_X = 6;
float LIGHT_RIGHT_POS_Y = 3;
float LIGHT_RIGHT_POS_Z = 8;
float light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f };
float light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f };
float light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f };
float spot_direction[] = { 0.1f, 0.1f, -1.0f };

/* all the changeable colors */
Color BACKGROUND_COLOR={0.7f, 0.7f, 0.7f};
Color ROOF_COLOR={255.0f, 255.0f, 255.0f};
Color DOOR_COLOR={255.0f, 255.0f, 255.0f};
Color WALL_COLOR_INTERIOR={127.5f, 127.5f, 127.5f};
Color WALL_COLOR_EXTERIOR={255, 255, 255};
Color FLAG_COLOR={255, 255, 255};
Color CHIMMEY_UPPER_COLOR={127.5f, 63.75f, 63.75f};
Color CHIMMEY_LOWER_COLOR={63.75f, 63.75f, 51.0f};

/* clip pane used for clipping */
double clip_plane_0[4]={0.0,0.0,-4.0,0};

/* saved images file name */
char saved_image_filename[]="saved_image.bmp";

/* TEXTURE PARAMETERS */

// default texture for first triangle
Point2d deafult_first_triang_texture_coord[3] = {{0, 0}, {1, 0}, {1, 1}};
// default texture for second triangle
Point2d deafult_second_triang_texture_coord[3] = {{0, 0}, {1, 1}, {0, 1}};
// default coordinates for no texture
Point2d deafult_no_texture_coord[3] = {{0, 0}, {0, 0}, {0, 0}};

// defines array of textures
GLuint textures_ids[4];
// number of textures
int n_textures = sizeof(textures_ids)/sizeof(GLuint);
// texture files
char texture_files[][PATH_MAX]={{"images/wall.bmp"},{"images/roof.bmp"},{"images/door.bmp"},{"images/flag.bmp"}};
// wall texture id
int WALL_TEXTURE=1;
// roof texture id
int ROOF_TEXTURE=2;
// door texture id
int DOOR_TEXTURE=3;
int FLAG_TEXTURE=4;

void loadTextureFromFile(){

    glGenTextures (n_textures, textures_ids);

    for (int i=1;i<=n_textures;i++){

        RgbImage theTexMap(texture_files[i-1]);

        // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
        // Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );

        glBindTexture(GL_TEXTURE_2D, i);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        //gluBuild2DMipmaps(GL_TEXTURE_2D, 3,theTexMap.GetNumCols(), theTexMap.GetNumRows(),
        //				 GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

    }

}

/* displays the usage of the app */
void displayUsage(){

    FILE *fptr;
    int file_found=0;
    int array_size=4;

    // in windows and mac README.txt path is different
    char files[][PATH_MAX] = {"./README.txt"};

    for (int i=0;i<array_size;i++){
        if( access( files[i], F_OK ) != -1 ) {
            fptr = fopen(files[i], "r");
            file_found=1;
            break;
        }
    }

    // close the file
    if (fptr == nullptr || ! file_found) {
        printf("Cannot open README.txt file. Skipping.\n");
        return;
    }

    // read the content
    char c = fgetc(fptr);
    while (c != EOF) {
        printf ("%c", c);
        c = fgetc(fptr);
    }

    // close the file
    fclose(fptr);

}

/* prints the time */
void printTime(){
    char buff[100];
    time_t now = time(nullptr);
    strftime(buff, 100, "%d-%m-%Y %H:%M:%S.000", localtime(&now));
    printf("%s  -  ", buff);
}

/* save images of current window */
void saveImage(char* fileName){

    RgbImage theTexMap;
    char current_dir[PATH_MAX];

    theTexMap.LoadFromOpenglBuffer();
    theTexMap.WriteBmpFile(saved_image_filename);

    if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
        printTime();
        printf("Image saved: %s%c%s\n", current_dir, file_separator, fileName);
    }

}

/* returns random number in the specified range */
int getRandoms(int lower, int upper){
    return (rand() %(upper - lower + 1)) + lower;
}

/* calculates the normal vector of the surface given three points */
void normal_vector_calculator(Point3d a, Point3d b, Point3d c, Point3d * destination_normal){

    Point3d ab = {b.x - a.x, b.y - a.y, b.z - a.z};
    Point3d ac = {c.x - a.x, c.y - a.y, c.z - a.z};
    Point3d cross = {ab.y * ac.z - ab.z * ac.y,
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

/* translation menu callback */
void transMenuCB(int value){

    if (DEBUG) { printTime(); printf("Command received: translation\n"); }

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
            if (DEBUG) printf("not implemented!\n");
            break;
    }
    glutPostRedisplay();
}

/* light menu callback */
void lightMenuCB(int value){

    if (DEBUG) { printTime(); printf("Command received: light\n"); }

    // translation menu callback
    switch (value) {
        case 1:
            LIGHT_LEFT_ON = !LIGHT_LEFT_ON;
            break;
        case 2:
            LIGHT_RIGHT_ON = !LIGHT_RIGHT_ON;
            break;
        case 3:
            LIGHT_LEFT_STATIC = !LIGHT_LEFT_STATIC;
            break;
        case 4:
            LIGHT_RIGHT_STATIC = !LIGHT_RIGHT_STATIC;
            break;
        case 5:
            SHOW_LIGHT_BULBS = !SHOW_LIGHT_BULBS;
            break;
        default:
            if (DEBUG) printf("not implemented!\n");
            break;
    }

    glutPostRedisplay();

}

/* color menu callback */
void colorMenuCB(int value) {

    if (DEBUG) { printTime(); printf("Command received: color change\n"); }

    // color menu callback
    switch (value) {
        case 1:
            ROOF_COLOR={255,0,0};
            break;
        case 2:
            ROOF_COLOR={0,0,255};
            break;
        case 3:
            ROOF_COLOR={255,255,255};
            break;
        case 4:
            WALL_COLOR_EXTERIOR={255,0,0};
            break;
        case 5:
            WALL_COLOR_EXTERIOR={0,0,255};
            break;
        case 6:
            WALL_COLOR_EXTERIOR={255,255,255};
            break;
        case 7:
            DOOR_COLOR={255,0,0};
            break;
        case 8:
            DOOR_COLOR={0,0,255};
            break;
        case 9:
            DOOR_COLOR={255,255,255};
            break;
        default:
            if (DEBUG) printf("not implemented!\n");
            break;
    }
    glutPostRedisplay();
}

/* main menu callback */
void mainMenuCB(int value) {

    // main menu callback
    switch (value) {
        case 1:
            if (DEBUG) { printTime(); printf("Command received: show/hide axis\n"); }
            SHOW_AXIS = !SHOW_AXIS;
            break;
        case 2:
            if (DEBUG) { printTime(); printf("Command received: open/close door\n"); }
            DOOR_MOVING=1;
            DOOR_OPEN = !DOOR_OPEN;
            break;
        case 3:
            if (DEBUG) { printTime(); printf("Command received: static/changing wind\n"); }
            WIND_TARGET_RANDOM_ANGLE=getRandoms(0,360);
            WIND_ON=!WIND_ON;
            break;
        case 4:
            if (DEBUG) { printTime(); printf("Command received: clipping ON/OFF\n"); }
            CLIPPING_ON=!CLIPPING_ON;
            if(CLIPPING_ON)
                glEnable(GL_CLIP_PLANE0);
            else
                glDisable(GL_CLIP_PLANE0);
            break;
        case 5:
            if (DEBUG) { printTime(); printf("Command received: save images\n"); }
            saveImage(saved_image_filename);
            break;
        case 6:
            if (DEBUG) { printTime(); printf("Command received: texture ON/OFF\n"); }
            TEXTURES_ENABLED = !TEXTURES_ENABLED;
            if (TEXTURES_ENABLED)
                glEnable(GL_TEXTURE_2D);
            else
                glDisable(GL_TEXTURE_2D);
            break;
        case 7:
            if (DEBUG) { printTime(); printf("Command received: debug ON/OFF\n"); }
            DEBUG = !DEBUG;
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

/* create menu function */
void createMenu() {

    // lights menu
    int lightsMenu = glutCreateMenu(lightMenuCB);
    glutAddMenuEntry("Left Light ON/OFF",1);
    glutAddMenuEntry("Right Light ON/OFF",2);
    glutAddMenuEntry("Left Light Static/Dynamic", 3);
    glutAddMenuEntry("Right Light Static/Dynamic", 4);
    glutAddMenuEntry("Show/Hide Light Bulbs", 5);

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
    glutAddMenuEntry("Door Red",7);
    glutAddMenuEntry("Door Blue",8);
    glutAddMenuEntry("Door White",9);

    // main menu
    int mainMenu = glutCreateMenu(mainMenuCB);
    glutAddMenuEntry("Show/Hide Axis", 1);
    glutAddMenuEntry("Open/Close Door", 2);
    glutAddMenuEntry("Static Wind/Changing Wind", 3);
    glutAddMenuEntry("Clipping ON/OFF", 4);
    glutAddMenuEntry("Save Image", 5);
    glutAddMenuEntry("Textures ON/OFF", 6);
    glutAddMenuEntry("Debug ON/OFF", 7);
    glutAddSubMenu("Light", lightsMenu);
    glutAddSubMenu("Translation", translationMenu);
    glutAddSubMenu("Color", colorMenu);

    // attach the menu to the right button
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

/* draws a triangle given three points and a color */
void draw_triangle(Point3d points[3], Color color, Point2d first_triang_texture_coord[3]){

    // normal vector of the triangle
    Point3d normal = {0, 0, 0};

    // calculate normal
    normal_vector_calculator(points[0], points[1], points[2], &normal);

    glPolygonMode(GL_FRONT ,GL_FILL);

    glBegin(GL_TRIANGLES);
        glColor3ub(color.r,color.g,color.b);
        glNormal3f(normal.x, normal.y, normal.z);
        // first vertex
        glTexCoord2f(first_triang_texture_coord[0].x, first_triang_texture_coord[0].y);
        glVertex3f(points[0].x,points[0].y,points[0].z);
        // second vertex
        glTexCoord2f(first_triang_texture_coord[1].x, first_triang_texture_coord[1].y);
        glVertex3f(points[1].x,points[1].y,points[1].z);
        // third vertex
        glTexCoord2f(first_triang_texture_coord[2].x, first_triang_texture_coord[2].y);
        glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();

}

/* draws a rectangle by drawing two triangles given four points and a color */
void draw_rectangle(Point3d points[4], Color color, Point2d first_triang_texture_coord[3], Point2d second_triang_texture_coord[3]){

    // normal vector of first triangle of the rectangle
    Point3d normal1 = {0, 0, 0};
    // normal vector of second triangle of the rectangle
    Point3d normal2 = {0, 0, 0};

    // calculate normals
    normal_vector_calculator(points[0], points[1], points[2], &normal1);
    normal_vector_calculator(points[0], points[2], points[3], &normal2);

    // GL_FRONT because we only see the front of the triangle
    // GL_FILL to fill the color of the rectangle
    glPolygonMode(GL_FRONT ,GL_FILL);

    // draw first triangle
    glBegin(GL_TRIANGLES);
        glColor3ub(color.r,color.g,color.b);
        glNormal3f(normal1.x, normal1.y, normal1.z);
        // first vertex
        glTexCoord2f(first_triang_texture_coord[0].x, first_triang_texture_coord[0].y);
        glVertex3f(points[0].x,points[0].y,points[0].z);
        // second vertex
        glTexCoord2f(first_triang_texture_coord[1].x, first_triang_texture_coord[1].y);
        glVertex3f(points[1].x,points[1].y,points[1].z);
        // third vertex
        glTexCoord2f(first_triang_texture_coord[2].x, first_triang_texture_coord[2].y);
        glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();

    // draw second triangle
    glBegin(GL_TRIANGLES);
        glColor3ub(color.r,color.g,color.b);
        glNormal3f(normal2.x, normal2.y, normal2.z);
        // first vertex
        glTexCoord2f(second_triang_texture_coord[0].x, second_triang_texture_coord[0].y);
        glVertex3f(points[0].x,points[0].y,points[0].z);
        // second vertex
        glTexCoord2f(second_triang_texture_coord[1].x, second_triang_texture_coord[1].y);
        glVertex3f(points[2].x,points[2].y,points[2].z);
        // third vertex
        glTexCoord2f(second_triang_texture_coord[2].x, second_triang_texture_coord[2].y);
        glVertex3f(points[3].x,points[3].y,points[3].z);
    glEnd();

    // draw triangles border
    if (SHOW_TRIANGLES){
        glPolygonMode(GL_FRONT ,GL_LINE);
        glBegin(GL_TRIANGLES);
            glColor3ub(0,0,0);
            // first triangle
            glVertex3f(points[0].x,points[0].y,points[0].z);
            glVertex3f(points[1].x,points[1].y,points[1].z);
            glVertex3f(points[2].x,points[2].y,points[2].z);
            // second triangle
            glVertex3f(points[0].x,points[0].y,points[0].z);
            glVertex3f(points[2].x,points[2].y,points[2].z);
            glVertex3f(points[3].x,points[3].y,points[3].z);
        glEnd();
    }

}

/* draws a rectangle by drawing two triangles given four points and a color */
void draw_rectangle_back(Point3d points[4], Color color, Point2d front_texture_coord[3]){

    // normal vector of first triangle of the rectangle
    Point3d normal1 = {0, 0, 0};
    // normal vector of second triangle of the rectangle
    Point3d normal2 = {0, 0, 0};

    // calculate normals
    normal_vector_calculator(points[2], points[1], points[0], &normal1);
    normal_vector_calculator(points[0], points[3], points[2], &normal2);

    // GL_FRONT because we only see the front of the triangle
    // GL_FILL to fill the color of the rectangle
    glPolygonMode(GL_FRONT ,GL_FILL);

    // draw first triangle
    glBegin(GL_TRIANGLES);
        glColor3ub(color.r,color.g,color.b);
        glNormal3f(normal1.x, normal1.y, normal1.z);
        glTexCoord2f(front_texture_coord[0].x,front_texture_coord[0].y);
        glVertex3f(points[2].x,points[2].y,points[2].z);
        glTexCoord2f(front_texture_coord[1].x,front_texture_coord[1].y);
        glVertex3f(points[1].x,points[1].y,points[1].z);
        glTexCoord2f(front_texture_coord[2].x,front_texture_coord[2].y);
        glVertex3f(points[0].x,points[0].y,points[0].z);
    glEnd();

    // draw second triangle
    glBegin(GL_TRIANGLES);
        glColor3ub(color.r,color.g,color.b);
        glNormal3f(normal2.x, normal2.y, normal2.z);
        glTexCoord2f(front_texture_coord[0].x,front_texture_coord[0].y);
        glVertex3f(points[0].x,points[0].y,points[0].z);
        glTexCoord2f(front_texture_coord[1].x,front_texture_coord[1].y);
        glVertex3f(points[3].x,points[3].y,points[3].z);
        glTexCoord2f(front_texture_coord[2].x,front_texture_coord[2].y);
        glVertex3f(points[2].x,points[2].y,points[2].z);
    glEnd();


    // draw triangles border
    if (SHOW_TRIANGLES) {
        glPolygonMode(GL_FRONT, GL_LINE);
        glBegin(GL_TRIANGLES);
            glColor3ub(0, 0, 0);
            // first triangle
            glVertex3f(points[2].x, points[2].y, points[2].z);
            glVertex3f(points[1].x, points[1].y, points[1].z);
            glVertex3f(points[0].x, points[0].y, points[0].z);
            // second triangle
            glVertex3f(points[0].x, points[0].y, points[0].z);
            glVertex3f(points[3].x, points[3].y, points[3].z);
            glVertex3f(points[2].x, points[2].y, points[2].z);
        glEnd();
    }

}

/* draws a parallelepiped given four points and internal/external colours */
void draw_parallelepiped(Point3d points[4], float depth, Color external_color, Color internal_color, Point2d first_triang_texture_coord[3], Point2d seoncd_triang_texture_coord[3]){

    // points translated trough normal
    Point3d translated_trough_normal[4];
    // faces of the
    Point3d right_face[4];
    Point3d left_face[4];
    Point3d front_face[4];
    Point3d back_face[4];

    // calculate normal vector
    Point3d normal = {0, 0, 0};
    normal_vector_calculator(points[0], points[1], points[2], &normal);

    // calculate points translated trough normal
    for (int i=0;i<4;i++){
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
    draw_rectangle(points, external_color, first_triang_texture_coord, seoncd_triang_texture_coord);
    draw_rectangle_back(translated_trough_normal, internal_color, first_triang_texture_coord);
    draw_rectangle(right_face, external_color, first_triang_texture_coord, seoncd_triang_texture_coord);
    draw_rectangle(left_face, external_color, first_triang_texture_coord, seoncd_triang_texture_coord);
    draw_rectangle(front_face, external_color, first_triang_texture_coord, seoncd_triang_texture_coord);
    draw_rectangle(back_face, external_color, first_triang_texture_coord, seoncd_triang_texture_coord);

}

/* function that drwas the three axis */
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
        glVertex3f(-100, 0, 0);
        glVertex3f(100, 0, 0);
        // sraw a green y-axis
        glColor3ub(0, 255, 0);
        glVertex3f(0, -100, 0);
        glVertex3f(0, 100, 0);
        // sraw a blue z-axis
        glColor3ub(0, 0, 255);
        glVertex3f(0, 0, -100);
        glVertex3f(0, 0, 100);
    glEnd();

    glDisable(GL_LINE_STIPPLE);

}

void draw_house(){

    // 3d vertexes of all the pieces of the house
    Point3d rect_front_right[4]={{0.5f, 0, 0}, {4, 0, 0}, {4, 2, 0}, {0.5f, 2, 0}};
    Point3d rect_front_left[4]={{-4, 0, 0}, {-0.5f, 0, 0}, {-0.5f, 2, 0}, {-4, 2, 0}};
    Point3d rect_front_center[4]={{-4, 2, 0}, {4, 2, 0}, {4, 4, 0}, {-4, 4, 0}};
    Point3d rect_back[4]={{-4, 4, -8}, {4, 4, -8}, {4, 0, -8}, {-4, 0, -8}};
    Point3d rect_right[4]={{4, 0, 0}, {4, 0, -8}, {4, 4, -8}, {4, 4, 0}};
    Point3d rect_left[4]={{-4, 4, 0}, {-4, 4, -8}, {-4, 0, -8}, {-4, 0, 0}};
    Point3d rect_bottom[4]={{-4, -0.1f, 0}, {-4, -0.1f, -8}, {4, -0.1f, -8}, {4, -0.1f, 0}};
    Point3d front_triangle[3]={{-4, 4, 0}, {4, 4, 0}, {0, 6.5f, 0}};
    Point3d back_triangle[3]={{-4, 4, -8}, {0, 6.5f, -8}, {4, 4, -8}};
    Point3d roof_left[4]={{-4.8f, 3.8f, 0.5f}, {0, 6.8f, 0.5f}, {0, 6.8f, -8.5f}, {-4.8f, 3.8f, -8.5f}};
    Point3d roof_right[4]={{4.8f, 3.8f, 0.5f}, {4.8f, 3.8f, -8.5f}, {0, 6.8f, -8.5f}, {0, 6.8f, 0.5f}};
    Point3d comignolo_pz1[4]={{-3, 4, -4}, {-2, 4, -4}, {-2, 7, -4}, {-3, 7, -4}};
    Point3d comignolo_pz2[4]={{-3.2f, 7, -3.8f}, {-1.8f, 7, -3.8f}, {-1.8f, 7.5f, -3.8f}, {-3.2f, 7.5f, -3.8f}};
    Point3d door[4]={{0.5f, 0, 0.1f}, {0.5f, 2, 0.1f}, {-0.5f, 2, 0.1f}, {-0.5f, 0, 0.1f}};
    Point3d flag_triangle_front[3]={{0, -1, 0}, {1.5f, -0.5f, 0}, {0, 0, 0}};
    Point3d flag_triangle_back[3]={flag_triangle_front[0], flag_triangle_front[2], flag_triangle_front[1]};

    // custom texture mappings
    Point2d roof_front_right_texture[] = {{0.0,0.0},{0.0,1.0},{1.0,1.0}};
    Point2d roof_back_right_texture[] = {{0.0,0.0},{1.0,1.0},{1.0,0.0}};
    Point2d back_triangle_texture[] = {{0.0,0.0},{1.0,1.0},{1.0,0.0}};

    // use wall texture for next drawings
    glBindTexture(GL_TEXTURE_2D, WALL_TEXTURE);

    draw_parallelepiped(rect_front_right, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_parallelepiped(rect_front_left, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_parallelepiped(rect_front_center, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_parallelepiped(rect_back, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_parallelepiped(rect_right, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_parallelepiped(rect_left, -0.3f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_parallelepiped(rect_bottom, -0.1f, WALL_COLOR_EXTERIOR, WALL_COLOR_INTERIOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_triangle(front_triangle, WALL_COLOR_EXTERIOR, deafult_first_triang_texture_coord);
    draw_triangle(back_triangle, WALL_COLOR_EXTERIOR,back_triangle_texture);
    draw_parallelepiped(comignolo_pz1, -1, CHIMMEY_LOWER_COLOR, CHIMMEY_LOWER_COLOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_parallelepiped(comignolo_pz2, -1.4f, CHIMMEY_UPPER_COLOR, CHIMMEY_UPPER_COLOR, deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);

    // use roof texture for next drawings
    glBindTexture(GL_TEXTURE_2D, ROOF_TEXTURE);

    draw_parallelepiped(roof_left, -0.3f, ROOF_COLOR, ROOF_COLOR,deafult_first_triang_texture_coord, deafult_second_triang_texture_coord);
    draw_parallelepiped(roof_right, -0.3f, ROOF_COLOR, ROOF_COLOR, roof_front_right_texture, roof_back_right_texture);

    // use door texture for next drawings
    glBindTexture(GL_TEXTURE_2D, DOOR_TEXTURE);

    // open/close door based on DOOR_ANGLE
    glPushMatrix();
        glTranslatef(0.5,0,0);
        glRotatef(DOOR_ANGLE,0,1,0);
        glTranslatef(0.5,0,0);
        draw_parallelepiped(door, -0.15f, DOOR_COLOR, DOOR_COLOR,deafult_second_triang_texture_coord,deafult_first_triang_texture_coord);
    glPopMatrix();

    // use wall texture for next drawings
    glBindTexture(GL_TEXTURE_2D, FLAG_TEXTURE);

    // draw the flag
    glPushMatrix();
        glTranslatef(0,8.5f,0);
        // rotate cilynder
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glColor3ub(0, 0, 0);
        // draw lower part of flag (cylinder)
        gluCylinder(gluNewQuadric(), 0.08f, 0.08f, 2, 30, 30);
        // rotate back in order to draw the triangle
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        // apply wind rotation
        glRotatef(WIND_ANGLE, 0.0f, 1.0f, 0.0f);
        // flag must be independent from the rotation of the house
        glRotatef(-HOUSE_ANGLE, 0.0, 1.0, 0.0);
        // draw upper part of flag - front
        draw_triangle(flag_triangle_front,FLAG_COLOR,back_triangle_texture);
        // draw upper part of flag - back
        draw_triangle(flag_triangle_back,FLAG_COLOR,deafult_first_triang_texture_coord);
    glPopMatrix();

}

void set_ambient_light(){

    GLfloat ambientLight[] = {0.15f, 0.15f, 0.15f, 0.15f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

}

void set_light_right(){

    if (SHOW_LIGHT_BULBS) {
        glPushMatrix();
        glTranslatef(LIGHT_RIGHT_POS_X, LIGHT_RIGHT_POS_Y, LIGHT_RIGHT_POS_Z);
        glDisable(GL_LIGHTING);
        glColor3ub(255.0, 255.0, 0.0);
        glutWireCube(0.5);
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }

    if (LIGHT_RIGHT_ON)
        glEnable(GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);

    GLfloat light_right_position[] = {LIGHT_RIGHT_POS_X, LIGHT_RIGHT_POS_Y, LIGHT_RIGHT_POS_Z, 1.0 };

    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_right_position);

    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);


}

void set_light_left(){

    if (SHOW_LIGHT_BULBS) {
        glPushMatrix();
        glTranslatef(LIGHT_LEFT_POS_X, LIGHT_LEFT_POS_Y, LIGHT_LEFT_POS_Z);
        glDisable(GL_LIGHTING);
        glColor3ub(255.0, 255.0, 0.0);
        glutWireCube(0.5);
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }

    if (LIGHT_LEFT_ON)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);


    // Seconda sorgente luminosa (spot)
    GLfloat light_left_position[] = {LIGHT_LEFT_POS_X, LIGHT_LEFT_POS_Y, LIGHT_LEFT_POS_Z, 1.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_left_position);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

}

/* main draw function */
void draw() {

    // background color r,g,b from 0 to 1 not from 0 to 255
    glClearColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, 0.0);

    // delete scene and apply defined Color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)

    // textures
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // set the modelview for drawing purposes
    glMatrixMode(GL_MODELVIEW);

    // clear all with identity matrix
    glLoadIdentity();

    // change perspective
    gluLookAt(EYE_X_POS, EYE_Y_POS, EYE_Z_POS, 0, 0, 0, 0, 1, 0);

    // sets and turns on the ambient light
    set_ambient_light();

    // if light are configured as static (not mooving), then draw them
    if (LIGHT_LEFT_STATIC)
        set_light_left();
    if (LIGHT_RIGHT_STATIC)
        set_light_right();

    // START DRAWING

    // draw the axis
    draw_axis();

    // translate the house
    glPushMatrix();

        // translate to X_POS Y_POS Z_POS
        glTranslatef(X_POS,Y_POS,Z_POS);

        //if (IS_SPINNING)
        glRotatef(HOUSE_ANGLE, 0.0, 1.0, 0.0);

        // draw house
        draw_house();

        // if light are configured as dynamic (mooving), then draw them
        if (!LIGHT_LEFT_STATIC)
            set_light_left();
        if (!LIGHT_RIGHT_STATIC)
            set_light_right();

    glPopMatrix();

    // display everything
    glutSwapBuffers();

}

/* init function */
void init(){
    // abilita il fatto di poter eliminare le facce che non si vedono
    // senza glEnable(GL_CULL_FACE) non si puo' utilizzare glPolygonMode(GL_FRONT,GL_LINE)
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    // enable lightning
    glEnable(GL_LIGHTING);
    // enbale automatic vector normalization
    glEnable(GL_NORMALIZE);
    // enable textures
    glEnable(GL_TEXTURE_2D);
    // create menu (right click)
    createMenu();
    // init random
    srand(time(0));
    // display application usage
    displayUsage();
    if (DEBUG) printf("\n**** APPLICATION IS IN DEBUG MODE ****\n");
}

/* keyboardCB arrow callback */
void keyboard_arrows_cb(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            // glRotatef(1.0,0.0,1.0,0.0);
            if (EYE_X_POS > MIN_EYE_X_POS)
                EYE_X_POS--;
            break;
        case GLUT_KEY_RIGHT:
            // glRotatef(-1.0,0.0,1.0,0.0);
            if (EYE_X_POS < MAX_EYE_X_POS)
                EYE_X_POS++;
            break;
        case GLUT_KEY_UP:
            // glRotatef(1.0,1.0,0.0,0.0);
            if (EYE_Y_POS < MAX_EYE_Y_POS)
                EYE_Y_POS++;
            break;
        case GLUT_KEY_DOWN:
            // glRotatef(1.0,-1.0,0.0,0.0);
            if (EYE_Y_POS > MIN_EYE_Y_POS)
                EYE_Y_POS--;
            break;
        default:
            break;
    }
    if (DEBUG) { printTime() ; printf("Eye position changed: (%d, %d, %d)\n", EYE_X_POS, EYE_Y_POS, EYE_Z_POS); }
    glutPostRedisplay();
}

/* timer function, it runs every TIMER_SPEED_IN_MS ms*/
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
        if (HOUSE_ANGLE < 360) {
            HOUSE_ANGLE++;
        } else {
            HOUSE_ANGLE = 0;
        }
    }

    if (WIND_ON) {
        if (WIND_ANGLE < WIND_TARGET_RANDOM_ANGLE)
            WIND_ANGLE += 1;
        if (WIND_ANGLE > WIND_TARGET_RANDOM_ANGLE)
            WIND_ANGLE -= 1;
    }

    if (TIME_PASSED == 100) {
        if (WIND_ON){
            if (DEBUG) { printTime(); printf("5 seconds passed -> new wind angle: %d\n",WIND_TARGET_RANDOM_ANGLE); }
            WIND_TARGET_RANDOM_ANGLE=getRandoms(0,360);
        }
    }

    glutPostRedisplay();
    glutTimerFunc(TIMER_SPEED_IN_MS, timer_function, 1);
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(PROJ_ORTHOGRAPHIC) {
        if (w <= h)
            glOrtho (ORTHO_LEFT, ORTHO_RIGHT, ORTHO_BOTTOM*(GLfloat)h/(GLfloat)w,ORTHO_TOP*(GLfloat)h/(GLfloat)w, ORTHO_ZNERAR, ORTHO_ZFAR);
        else
            glOrtho (ORTHO_LEFT*(GLfloat)w/(GLfloat)h,ORTHO_RIGHT*(GLfloat)w/(GLfloat)h, ORTHO_BOTTOM, ORTHO_TOP, ORTHO_ZNERAR, ORTHO_ZFAR);
    } else {
        double proportion = (double) w / (double) h;
        gluPerspective(PERSPECTIVE_FOVY, proportion, PERSPECTIVE_ZNERAR, PERSPECTIVE_ZFAR);
    }
    glMatrixMode(GL_MODELVIEW);
}

/* reshape callback, triggered when window gets resized */
void reshapeCB(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    reshape(w, h);
}

/* keyboard callback, traps keyboard keys */
void keyboardCB(unsigned char key, int x, int y) {
    switch (key) {
        case 114:
            // r key
            if (!IS_SPINNING) {
                if (DEBUG) { printTime(); printf("Command received: start rotation\n"); }
                IS_SPINNING = 1;
            }
            break;
        case 115:
            // s key
            if (DEBUG) { printTime(); printf("Command received: stop rotation\n"); }
            IS_SPINNING = 0;
            break;
        case 27:
            // esc key
            glutDestroyWindow(MAIN_WINDOW);
            exit(0);
        case 97:
            // a key
            if (DEBUG) { printTime(); printf("Projection mode changed: orthographic\n"); }
            PROJ_ORTHOGRAPHIC=1;
            reshapeCB(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case 112:
            // p key
            if (DEBUG) { printTime(); printf("Projection mode changed: perspective\n"); }
            PROJ_ORTHOGRAPHIC=0;
            reshapeCB(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case 56:
            // 8 key
            if (EYE_Z_POS > MIN_EYE_Z_POS)
                EYE_Z_POS--;
            if (DEBUG) { printTime() ; printf("Eye position changed: (%d, %d, %d)\n", EYE_X_POS, EYE_Y_POS, EYE_Z_POS); }
            glutPostRedisplay();
            break;
        case 50:
            // 2 key
            if (EYE_Z_POS < MAX_EYE_Z_POS)
                EYE_Z_POS++;
            if (DEBUG) { printTime() ; printf("Eye position changed: (%d, %d, %d)\n", EYE_X_POS, EYE_Y_POS, EYE_Z_POS); }
            glutPostRedisplay();
            break;
        default:
            if (DEBUG) { printTime() ; printf("Unrecognized key: %d\n", key); }
            break;
    }
}

/* main function */
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
    // catch keyboardCB arrows
    glutSpecialFunc(keyboard_arrows_cb);
    // catch keyboardCB keys
    glutKeyboardFunc(keyboardCB);
    // start timer
    glutTimerFunc(TIMER_SPEED_IN_MS, timer_function, 1);
    // clip pane
    glClipPlane(GL_CLIP_PLANE0,clip_plane_0);
    // load textures
    loadTextureFromFile();
    // start main infinite loop
    glutMainLoop();
}
