#include <GL/freeglut.h>
#include <stdio.h>
#include "math.h"
#include "iostream"
#include <GL/gl.h>
#include <stdlib.h>
#define PI 3.1415926535898

int w_width=600,w_height=600;
int x=0,y=0;
int p,r;
float iball=300.0,jball=300.0,a=1.0,b=1.0;

float speed[5]={0.3,0.5,0.6,0.7,0.8};
int level=0;


void init(void)
{
glClearColor(1.0,1.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(1,w_width,1,w_height,-1,1);
}


//::::::::::::::::DISPLAY FUNCTION::::::::::://
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0,0.0,1.0);

GLint circle_points=100,i;
GLfloat angle;
glBegin(GL_POLYGON);
for(i=0;i<circle_points;i++) {
    angle=2*PI*i/circle_points;
    glVertex2f(iball+w_width*cos(angle)/35,jball+w_height*sin(angle)/35);
  }
glEnd();


//::::::::::::Separator:::::::::::://
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
{
  glVertex3i(0,70,0);
  glVertex3i(w_width,70,0);
  glVertex3i(w_width,73,0);
  glVertex3i(0,73,0);
}
glEnd();


//::::::::::Target Blocks::::::::::://

glBegin(GL_QUADS);
{
  for(p=590;p>440;p-=50)
  {
    for(r=5;r<590;r+=50)
    {

      glColor3f(0.0,1.0,0.0);
      glVertex3f(r,p,0);
      glVertex3f(r+40,p,0);
      glVertex3f(r+40,p-40,0);
      glVertex3f(r,p-40,0);
    }
  }
}
glEnd();

//:::::::::::::Block:::::::::::::::://

glColor3f(1.0,0.0,1.0);
glBegin(GL_QUADS);
{
  glVertex3i(300+x,30+y,0);
  glVertex3i(380+x,30+y,0);
  glVertex3i(380+x,60+y,0);
  glVertex3i(300+x,60+y,0);
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

void againDisplay()
{
  iball=iball+(a*speed[level]);
  jball=jball+(b*speed[level]);
  if((jball>=600.0-150.0)||(jball<=50.0) )
  b=-b ;
  else if((iball>=600-10.0)||(iball<=10.0))
  a=-a;
  glutPostRedisplay();
}

//::::::::::::::::::::keyboard function:::::::::::::::::://
void keyboard(unsigned char key, int xm, int ym)
{
  switch (key)
    {
      case 'i':y+=5;
      break;

      case 'j':x-=5;
      break;

      case 'k':y-=5;
      break;

      case 'l':x+=5;
      break;

      case 49:level=0;
      break;

      case 50:level=1;
      break;

      case 51:level=2;
      break;

      case 52:level=3;
      break;

      case 53:level=4;
      break;

      case 'p':glutIdleFunc(againDisplay);     //Start the game
      break;

      case 's':glutIdleFunc(NULL);            //Pause the game
      break;

      default:
      break;
    }
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
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
