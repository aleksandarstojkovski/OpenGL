#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
//#include <GL/gl.h>
#include <GLUT/glut.h>

void draw() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  	
  	glClear(GL_COLOR_BUFFER_BIT);
	 glLoadIdentity();		
   
	glColor3f(1.0, 1.0, 1.0);			
    glOrtho(0.0, 30.0, 0.0, 30.0, -1.0, 1.0);	 
    
    GLint v0[] = {8,19};
    GLint v1[] = {6,14};
 	GLint v2[] = {14,21};
 	GLint v3[] = {14,13};
 	GLint v4[] = {19,21};
	GLint v5[] = {20,11};
	
	glPolygonMode(GL_FRONT, GL_LINE);

	glBegin(GL_TRIANGLES);		
		glVertex2iv(v0);
		glEdgeFlag(GL_FALSE);	
    	glVertex2iv(v1);
		glEdgeFlag(GL_TRUE);
    	glVertex2iv(v2);
		
    glEnd();
  
	glBegin(GL_TRIANGLES);
		glVertex2iv(v1);
		glVertex2iv(v3);
		glEdgeFlag(GL_FALSE);
		glVertex2iv(v2);
		glEdgeFlag(GL_TRUE);
	glEnd();

    
    glFlush();							
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);				// chiamate glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("whitesquare");
    glutDisplayFunc(draw);
    glutMainLoop();
}

