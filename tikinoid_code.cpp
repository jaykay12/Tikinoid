#include <GL/freeglut.h>
#include <stdio.h>
#include "math.h"
#include "iostream"
#include <GL/gl.h>
#define PI 3.1415926535898

int w_width=600,w_height=600;
int p,r;

void init(void)
{
glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(1,w_width,1,w_height,-1,1);
}



//::::::::::::::::DISPLAY FUNCTION::::::::::::::::://
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0,0.0,1.0);

GLint circle_points=100,i;
GLfloat angle;
glBegin(GL_POLYGON);
for(i=0;i<circle_points;i++) {
    angle=2*PI*i/circle_points;
    glVertex2f(300+w_width*cos(angle)/35,300+w_height*sin(angle)/35);
  }
glEnd();


//..........Separator...........//
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
{
  glVertex3i(0,70,0);
  glVertex3i(w_width,70,0);
  glVertex3i(w_width,73,0);
  glVertex3i(0,73,0);
}
glEnd();


//..........Target Blocks.........//
glColor3f(1.0,1.0,0.0);
glBegin(GL_QUADS);
{
  for(p=590;p>440;p-=50)
  {
    for(r=5;r<590;r+=50)
    {
      glVertex3f(r,p,0);
      glVertex3f(r+40,p,0);
      glVertex3f(r+40,p-40,0);
      glVertex3f(r,p-40,0);
    }
  }
}
glEnd();

//.........Block..........//

glColor3f(1.0,0.0,1.0);
glBegin(GL_QUADS);
{
  glVertex3i(300,30,0);
  glVertex3i(380,30,0);
  glVertex3i(380,60,0);
  glVertex3i(300,60,0);
}
glEnd();
glFinish();
glutSwapBuffers();
}


//::::::::::::::RESHAPE FUNCTION:::::::::::::::::://
void reshape(int w, int h)
{
	w_height=h;
	w_width=w;
glViewport(0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0,(GLdouble)w,0.0,(GLdouble)h,0.0,1.0);
}


int main(int argc,char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(w_width,w_height);
  glutInitWindowPosition(270,50);
  glutCreateWindow("Tikinoid by Jalaz");
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
