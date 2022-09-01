#include<GL/glut.h>
#include"game.h"

int gridX , gridY;

void initGrid(int x , int y)
{
    gridX = x ;
    gridY = y ;

}


void unit(int x , int y)
{
    glLineWidth(1.0);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x,y);
    glVertex2f(x+10,y);
    glVertex2f(x+10,y+10);
    glVertex2f(x,y+10);

    glEnd();

}

void drawGrid()
{
    for(int i = 0 ; i < 30 ; i++)
    {
        for(int j = 0 ; j < 30 ; j++)
        {
            unit(i,j);
        }
    }
}