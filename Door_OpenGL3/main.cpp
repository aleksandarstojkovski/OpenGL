#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <iostream>
#else
// headers richiesti da Windows e linuxö
#include <GL/glew.h>
#include <GL/glut.h>
#endif

// Funzioni per caricare, inizializzare e compilare gli shader
#include "shaders_loader.h"
#include "lib/RgbImage.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib>

// -------------------------------- STRUTTURE GLOBALI ------------------------------- //

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TexCoords;
};

// -------------------------------- VARIABILI GLOBALI ------------------------------- //

GLuint VAO;
GLuint VBO;
GLuint EBO;
GLfloat DOOR_ANGLE = 0.0;
GLboolean DOOR_OPEN = false;
GLfloat PI_HALF = glm::pi<float>() / 2;
GLfloat DOOR_STEP = 1 / 180.0f * glm::pi<float>();
GLuint textures_ids[1];
int ANIM_MSEC = 10;

std::vector<GLuint> indices;
std::vector<Vertex> vertices;

GLint projectionPos, modelviewPos;
glm::mat4 projection, modelview;
int mouseoldx, mouseoldy ;

glm::vec3 EYE_POSITION = glm::vec3(0.0, -2.0, 6.0);
glm::vec3 DIRECTION = glm::vec3(0.0, 0.0, 0.0);;
glm::vec3 eyeloc = EYE_POSITION;
static const GLfloat SW = 5.0f; //SCENE WIDTH

const float DOOR_THINK = 1.0f / SW;
const float HALF_DOOR_WIDTH = 2.0f / SW;
const float WALL_THICK = 10.1f / SW;
const float WALL_HEIGHT = 6.0f / SW;

const char * textureFiles[1] = {
        "images/door.bmp",
};

int n_textures = sizeof(textures_ids)/sizeof(GLuint);

void loadTextureFromFile()  {
    glGenTextures (n_textures, textures_ids);
    for (int i = 0; i < n_textures; ++i) {
        // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
        // Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );
        RgbImage rgbImg(textureFiles[i]);
        glBindTexture(GL_TEXTURE_2D, textures_ids[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     rgbImg.GetNumCols(), rgbImg.GetNumRows(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, rgbImg.ImageData());
    }
}

void enableTexture(bool enable) {
    if(enable)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
}

void menuCallback(int value) {
    switch (value) {
        case 1:
            DOOR_OPEN = !DOOR_OPEN;
            break;
    }
}

// -------------------------------- INIZIALIZZAZIONI ------------------------------- //

void initMenu() {
    int menuAnimation = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Open/Close Door", 1);
    glutCreateMenu(menuCallback);

    glutAddSubMenu("Animation", menuAnimation);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init() {

    initMenu();
    glEnable(GL_DEPTH_TEST);
    loadTextureFromFile();

    vertices = {
            {{ -HALF_DOOR_WIDTH, 0, -WALL_THICK },{1.0f, 1.0f, 1.0f},   {0.0f, 0.0f} },
            {{ HALF_DOOR_WIDTH, 0, -WALL_THICK },{1.0f, 1.0f, 1.0f},   {1.0f, 0.0f}},
            {{ HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_THICK },{1.0f, 1.0f, 1.0f},   {1.0f, 1.0f}},
            {{ -HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_THICK },{1.0f, 1.0f, 1.0f},   {0.0f, 1.0f}},

            {{ HALF_DOOR_WIDTH, 0, -(WALL_THICK+DOOR_THINK) }, { 1.0f, 1.0f, 1.0f},   {0.0f, 0.0f}},
            {{ -HALF_DOOR_WIDTH, 0, -(WALL_THICK+DOOR_THINK) }, { 1.0f, 1.0f, 1.0f},   {1.0f, 0.0f}},
            {{ -HALF_DOOR_WIDTH, WALL_HEIGHT, -(WALL_THICK+DOOR_THINK) }, { 1.0f, 1.0f, 1.0f},   {1.0f, 1.0f}},
            {{ HALF_DOOR_WIDTH, WALL_HEIGHT, -(WALL_THICK+DOOR_THINK) }, { 1.0f, 1.0f, 1.0f},   {0.0f, 1.0f}},
    };

    indices = {
            0, 1, 2, 0, 2, 3, // front
            1, 4, 7, 1, 7, 2, // right
            4, 5, 6, 4, 6, 7, // back
            5, 0, 3, 5, 3, 6, // left
            0, 1, 4, 0, 4, 5, // bottom
            3, 2, 7, 3, 7, 6, // top
    };

    glGenVertexArrays(1, &VAO); // Vertex Array Object
    glGenBuffers(1, &VBO);      // Vertex Buffer Object
    glGenBuffers(1, &EBO);      // Element Buffer Object

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,    // indice dell’attributo
                          3,                  // n. di componenti (1..4)
                          GL_FLOAT,           // tipo di dato
                          GL_TRUE,            // se da normalizzare
                          sizeof(Vertex),     // offset (in byte) fra dati consecutivi
                          (void*)0);

    // color attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    // texture coord attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    // Carica gli shaders dai rispettivi files, inizializza, linka e compila
    GLuint vertexShader = initshaders(GL_VERTEX_SHADER, "shaders/shader.vert") ;
    GLuint fragmentShader = initshaders(GL_FRAGMENT_SHADER, "shaders/shader.frag") ;
    GLuint shaderProgram = initprogram(vertexShader, fragmentShader) ;
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    // Inizializza la matrice di proiezione con la matrice di identità
    projection = glm::mat4(1.0f);

    // Definisce il punto di vista (posizione, dove guarda, upvector)
    modelview = glm::lookAt(EYE_POSITION, DIRECTION, glm::vec3(0, 1, 1));

    // Leggi le posizioni delle variabili uniform
    projectionPos = glGetUniformLocation(shaderProgram, "projection_matrix");
    modelviewPos = glGetUniformLocation(shaderProgram, "modelview_matrix");

    // Passa le matrici di proiezione e modelview allo shader
    glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
}


void rotateDoor() {
    if(DOOR_OPEN && DOOR_ANGLE < PI_HALF) {
        DOOR_ANGLE += DOOR_STEP;
    } else if(!DOOR_OPEN && DOOR_ANGLE > 0) {
        DOOR_ANGLE -= DOOR_STEP;
    }
}


// -------------------------------- DISPLAY ------------------------------- //
void display() {

    // Cancella il color buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 ori = modelview;

    // Rotazione intorno ad uno dei vertici. Notare che l'angolo va passato in radianti. Rotazione di 1 grado
    modelview  = glm::translate(modelview, glm::vec3(-HALF_DOOR_WIDTH, 0.f, -WALL_THICK));
    modelview = glm::rotate(modelview, DOOR_ANGLE, glm::vec3(0.0f, 1.0f, 0.0f));
    modelview  = glm::translate(modelview, glm::vec3(HALF_DOOR_WIDTH, 0.f, WALL_THICK));

    // Passa la matrice di modelview allo shader
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

    // render container
    glBindVertexArray(VAO);

    // draw door
    enableTexture(true);
    glBindTexture(GL_TEXTURE_2D, textures_ids[0]);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    enableTexture(false);

    modelview = ori;
    // Passa la matrice di modelview allo shader
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

    glFlush();
}

// -------------------------------- TIMER ------------------------------- //
void TimerFunc(int value) {
    rotateDoor();
    glutPostRedisplay();
    glutTimerFunc(ANIM_MSEC, TimerFunc, 1);
}

// -------------------------------- RESHAPE ------------------------------- //
void reshape(int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    // Imposta la matrice di proiezione di tipo prospettica
    // notare che l'angolo va passato in radianti
    projection = glm::perspective(30.0f / 180.0f * glm::pi<float>(), (GLfloat)w / (GLfloat)h, 1.0f, 10.0f);
    glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
}


// -------------------------------- EVENTI DEL MOUSE ------------------------------- //


void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            // Do Nothing ;
        }
        else if (state == GLUT_DOWN) {
            mouseoldx = x ; mouseoldy = y ; // so we can move wrt x , y
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

        // Resetta gluLookAt al valore iniziale
        eyeloc = EYE_POSITION;
        modelview = glm::lookAt(eyeloc, glm::vec3(0, 0, 0), glm::vec3(0, 1, 1));

        // Invia la matrice aggiornata allo shader e ridisegna
        glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
        glutPostRedisplay() ;
    }
}

void mousedrag(int x, int y) {
    int xloc = x - mouseoldx;
    int yloc = y - mouseoldy;    // si usa la coordinata y per definire lo zoom in/out

    // Sposta il punto di vista di un fattore proporzionale allo spostamento del mouse
    eyeloc += glm::vec3(-0.005*xloc, -0.005*yloc, +0.005*yloc);

    if (yloc<0) yloc = 0;
    mouseoldy = y ;

    /* imposta nella modelview il nuovo punto di vista */
    modelview = glm::lookAt(eyeloc, DIRECTION, glm::vec3(0, 1, 1));

    // Invia la matrice aggiornata allo shader e ridisegna
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
    glutPostRedisplay() ;
}

// -------------------------------- EVENTI DEL MOUSE E TASTIERA ------------------------------- //
void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        case 27:  // Tasto Escape per uscire

            // Cancella tutti i buffers allocati
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);

            exit(0) ;
        default:
            break ;
    }
}

// -------------------------------- MAIN ------------------------------- //
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // OSX richiede una chiamata specifica
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_SINGLE | GLUT_RGB);
#else
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ;
#endif
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Hello world Shaders");

    // Inizializza Glew
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetString(err) << std::endl;
    }

    init();

    // Vari callback.
    glutDisplayFunc(display);
    glutReshapeFunc(reshape) ;
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse) ;
    glutMotionFunc(mousedrag) ;

    glutTimerFunc(1000, TimerFunc, 1);

    glutMainLoop();

    return 0;   /* ANSI C richiede che si ritorni un int */
}