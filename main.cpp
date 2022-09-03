#include<GL/gl.h>
#include<GL/glut.h>
#include "game.h"

#define COLUMNS 30
#define ROWS 30

void display_callback();
void reshape_callback(int w, int h);
void timer_callback(int);
void key_pressed(int,int,int);
void key_released(int,int,int);
void init();

int main(int argc, char **argv)
{
    
    glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Mine It Out");
    glutDisplayFunc(display_callback);
	//glutReshapeFunc(reshape_callback);
	glutTimerFunc(0,timer_callback,0);
	glutSpecialFunc(key_pressed);
	glutSpecialUpFunc(key_released);
	init();
    glutMainLoop();
    return 0;
}


void init(){
	glClearColor(0.2,0.4,0.8,1);
	initGrid(COLUMNS,ROWS);
}

void display_callback(){
	display();
    glutSwapBuffers();
}

void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/10,timer_callback,0);

}

void key_pressed(int key,int,int)
{
	switch(key){
	case GLUT_KEY_UP:
			UP = 1;
			break;
	case GLUT_KEY_DOWN:
			DOWN=1;
			break;
	case GLUT_KEY_LEFT:
			LEFT=1;
			break;
	case GLUT_KEY_RIGHT:
			RIGHT=1;
			break;
	}
		
}

void key_released(int key,int,int)
{
	switch(key){
	case GLUT_KEY_UP:
			UP = 0;
			break;
	case GLUT_KEY_DOWN:
			DOWN=0;
			break;
	case GLUT_KEY_LEFT:
			LEFT=0;
			break;
	case GLUT_KEY_RIGHT:
			RIGHT=0;
			break;
	}
}

void reshape_callback(int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);	
}