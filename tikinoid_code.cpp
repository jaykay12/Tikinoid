#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include <stdlib.h>
#define PI 3.1415926535898

float w_width=600.0,w_height=600.0;
float x=0.0,y=0.0;
int s;
int r;
float xball=300.0,yball=300.0,a=1.0,b=1.0;

float speed[5]={0.05,0.08,0.1,0.14,0.18};
int level=0;

float xver,yver;
int target[600][600];

int flag=1;

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
    xver=xball+w_width*cos(angle)/35;
    yver=yball+w_height*sin(angle)/35;
    glVertex2f(xver,yver);
  }
glEnd();


//::::::::::::Separator:::::::::::://
glColor3f(0.0,0.0,0.0);
glBegin(GL_POLYGON);
{
  glVertex3f(0.0,50.0,0.0);
  glVertex3f(w_width,50.0,0.0);
  glVertex3f(w_width,53.0,0.0);
  glVertex3f(0.0,53.0,0.0);
}
glEnd();

glBegin(GL_POLYGON);
{
  glVertex3f(0.0,17.0,0.0);
  glVertex3f(w_width,17.0,0.0);
  glVertex3f(w_width,20.0,0.0);
  glVertex3f(0.0,20.0,0.0);
}
glEnd();


//::::::::::Target Blocks::::::::::://
if(flag==1)
{
  for(s=590;s>440;s-=50)
    {
      for(r=5;r<590;r+=50)
        {
          target[r][s]=1;
        }
    }
  flag=0;
}



glBegin(GL_QUADS);
{
  for(s=590;s>440;s-=50)
  {
    for(r=5;r<590;r+=50)
    {
      if(target[r][s]==1)
      {
        glColor3f(0.0,1.0,0.0);
        glVertex3f(r,s,0.0);
        glVertex3f(r+40.0,s,0.0);
        glVertex3f(r+40.0,s-40.0,0.0);
        glVertex3f(r,s-40.0,0.0);
      }
    }
  }
}
glEnd();

//:::::::::::::Block:::::::::::::::://

glColor3f(1.0,0.0,1.0);
glBegin(GL_QUADS);
{
  glVertex3f(260.0+x,20.0,0.0);
  glVertex3f(340.0+x,20.0,0.0);
  glVertex3f(340.0+x,50.0,0.0);
  glVertex3f(260.0+x,50.0,0.0);
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
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0.0,(GLdouble)w,0.0,(GLdouble)h,0.0,1.0);
}


void againDisplay()
{
  xball=xball+(a*speed[level]);
  yball=yball+(b*speed[level]);

for(s=590;s>=490;s-=50)
   {
    for(r=5;r<590;r+=50)
     {
      if(target[r][s]==1)
      {
        if((yball<=s-32)&&(yball>=s-58)&&(xball>=r-2)&&(xball<=r+42)&&(b==1))
        {
          b=-b;
          target[r][s]=0;
        }
      }
    }
  }



  if(((xball<=340.0+x)&&(xball>=260.0+x))&&((yball>=55.0)&&(yball<=70.0)))
  b=-b ;
  if(yball>600.0)
  b=-b;

  if((xball>=600-10.0)||(xball<=10.0))
  a=-a;

  if(yball<=-30.0)
  glutIdleFunc(NULL);
  else
  glutPostRedisplay();
}

//::::::::::::::::::::keyboard function:::::::::::::::::://
void keyboard(unsigned char key, int xm, int ym)
{
  switch (key)
    {

      case 'a':x-=10;if(x<-260)x=-260;
      break;

      case 'd':x+=10; if(x>260)x=260;
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
