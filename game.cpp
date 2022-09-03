#include<GL/gl.h>
#include<GL/glut.h>
#include"game.h"

int gridX , gridY;
int posX=15,posY=15;

int UP = 0;
int DOWN = 0;
int LEFT = 0;
int RIGHT = 0;

void initGrid(int x , int y)
{
    gridX = x ;
    gridY = y ;

}


void unit(int x , int y)
{
    if( x==0 || y==0 || x==gridX-1 || y== gridY-1){
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }
    else{
        glLineWidth(1.0);
        glColor3f(1.0,1.0,1.0);
    }

    glBegin(GL_LINE_LOOP);
    glVertex2f(x,y);
    glVertex2f(x+1,y);
    glVertex2f(x+1,y+1);
    glVertex2f(x,y+1);
    glEnd();

}

void drawGrid()
{
    for(int i = 0 ; i < gridX ; i++)
    {
        for(int j = 0 ; j < gridY ; j++)
        {
            unit(i,j);
        }
    }
}

bool checkBoundary()
{
    if(posX >= gridX){
        posX=gridX-1;
        return false;
    }
    if(posX < 0){
        posX=0;
        return false;
    }
    if(posY >= gridY){
        posY=gridY-1;
        return false;
    }
    if(posY < 0){
        posY=0;
        return false;
    }
    return true;
}

void drawcharacter()
{
    if(UP==1){
        if(checkBoundary())
            posY++;
    }
    else if(DOWN==1){
        if(checkBoundary())
            posY--;
    }
    else if(LEFT==1){
        if(checkBoundary())
            posX--; 
    }
    else if(RIGHT==1){
        if(checkBoundary())
            posX++;
    }
    glRectd(posX,posY,posX+1,posY+1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,gridX,0.0,gridY,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);	

    drawGrid();   
    drawcharacter();
}