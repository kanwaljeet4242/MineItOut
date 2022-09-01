#include<GL/gl.h>
#include<GLFW/glfw3.h>
#include "game.h"

#define COLUMNS 40
#define ROWS 40

void display_callback();
void reshape_callback(GLFWwindow* window,int w, int h);
void init();

int main(int argc, char **argv)
{
    GLFWwindow *window;
    if(!glfwInit())
		return -1;
	window=glfwCreateWindow(500,500,"Snake",NULL,NULL);
	if(!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, reshape_callback);
	init();
	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		drawGrid();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
    return 0;
}


void init(){
	glClearColor(0.2,0.4,0.8,1);
	initGrid(COLUMNS,ROWS);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);	
	glMatrixMode(GL_MODELVIEW);
}

void reshape_callback(GLFWwindow* window,int w, int h){
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);	
	glMatrixMode(GL_MODELVIEW);
}