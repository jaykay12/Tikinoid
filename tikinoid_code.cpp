#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/gl.h>
#include <stdlib.h>
#define PI 3.1415926535898

float w_width=700.0,w_height=700.0;
float x=0.0,y=0.0;
int s;
int r;
float xball=350.0,yball=350.0,a=1.0,b=1.0;

float speed[5]={0.1,0.15,0.18,0.22,0.25};
float speed1=0.08;
int level=0;

float xver,yver;
int target[700][700];
int font=0;
int flag=1;
int score1=0,score2=0;
int play=1;

char sc1[4];
char sc2[4];

int option=0;


void init(void)
{
  glClearColor(0.52,0.80,1.0,0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(1,700,1,700,-1,1);
}



//::::::::::::::::TEXT FUNCTION:::::::::::::://
void drawBitmapText(const char *string,float x,float y,float z)
{
    const char *c;
    glRasterPos3f(x,y,z);

    for (c=string; *c != '\0'; c++)
    {
      if(font==0)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
      else if(font==1)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
      else if(font==2)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
      else if(font==3)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
      else if(font==4)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
      else if(font==5)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
      else if(font==6)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);

    }
}



//::::::::::::::::Display Function::::::::::://
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
  if(option==0)
  { glClearColor(0.52,0.80,1.0,0.0);
    glColor3f(0.0,0.0,0.0);
    font=1;
    drawBitmapText("Press L for Level Mode",220,450,0);
    drawBitmapText("Press T for Target Mode",218,400,0);
    drawBitmapText("Press C for Credits",248,350,0);
    drawBitmapText("Press Q for Quit Game",230,300,0);
    glFinish();
    glutSwapBuffers();

  }

  else if(option==3)
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,0.75,0.14,0.0);
    glColor3f(0.0,0.0,0.0);
    font=1;
    drawBitmapText("Graphics Project",250,500,0);
    font=5;
    drawBitmapText("Integrated Gaming Console Development using openGL",140,470,0);
    font=4;
    drawBitmapText("Developer : Jalaz Kumar    NIT Hamirpur",125,400,0);
    font=1;
    drawBitmapText("Special Thanks to:",240,300,0);
    font=4;
    drawBitmapText("Debugger : Sukhbir Singh         NIT Hamirpur",125,250,0);
    drawBitmapText("Tester :   Narendra Dodwaria     NIT Hamirpur",125,200,0);
    glFinish();
    glutSwapBuffers();
  }

  else
  {
      //:::::::::::Ball:::::::::::://
      glColor3f(0.0,0.0,1.0);
      GLint circle_points=100,i;
      GLfloat angle;
      glBegin(GL_POLYGON);
      for(i=0;i<circle_points;i++)
        {
          angle=2*PI*i/circle_points;
          xver=xball+w_width*cos(angle)/35;
          yver=yball+w_height*sin(angle)/35;
          glVertex2f(xver,yver);
        }
      glEnd();


      //::::::::::::Separator:::::::::::://
      glColor3f(1.0,1.0,1.0);
      //glRectf(50.0,70.0,641.0,73.0);
      glRectf(50.0,37.0,641.0,40.0);

      //::::::::::External Boundary::::::::::://
      glColor3f(0.44,0.44,0.77);
      glRectf(10.0,10.0,690.0,12.0);
      glRectf(10.0,10.0,12.0,690.0);
      glRectf(10.0,690.0,690.0,688.0);
      glRectf(690.0,690.0,688.0,10.0);

      //:::::::::::Internal Gaming Platform Boundary:::::::::::::::://

      glColor3f(0.66,0.66,0.66);
      glRectf(50.0,594.0,641.0,591.0);
      glRectf(50.0,594.0,47.0,37.0);
      glRectf(641.0,594.0,644.0,37.0);


  if(option==1)
    {
      //::::::::::Target Blocks::::::::::://
      if(flag==1)
      {
        for(s=590;s>440;s-=50)
          {
            for(r=50;r<650;r+=50)
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
          for(r=50;r<650;r+=50)
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
    }

      //::::::::::::Text:::::::::::://
      glColor3f(1.0,1.0,1.0);
      font=1;
      drawBitmapText("  Tik-i-noids",260,665,0);

      font=5;
      drawBitmapText("Project: Contributed for Integrated Console Development Project Using openGL",60,650,0);
      drawBitmapText("Developer: Jalaz Kumar",60,638,0);

      font=2;
      drawBitmapText("Instructions:",60,618,0);
      drawBitmapText("PRESS:  S-Start   P-Pause   A-Left Shift  D-Right Shift",60,608,0);

      font=4;

      if(option==2)
      {
        drawBitmapText("Score:",500,610,0);
        drawBitmapText(sc2,560,610,0);
      }
      else if(option==1)
      {
        drawBitmapText("Score:",500,610,0);
        drawBitmapText(sc1,560,610,0);

      }


      glColor3f(1.0,0.0,0.0);
        if(play==2)
          {
            font=1;
            drawBitmapText("!!!!GAME OVER!!!!",220,350,0);
            if(option==1)
            {
              drawBitmapText("Your Score :- ",230,300,0);
              drawBitmapText(sc1,370,300,0);
            }
            else if(option==2)
            {
              drawBitmapText("Your Score :- ",230,300,0);
              drawBitmapText(sc2,370,300,0);

            }
            font=3;
            drawBitmapText("Press R to Restart the game",250,250,0);
          }


      //:::::::::::::Block:::::::::::::::://
      glColor3f(1.0,0.0,1.0);
      glBegin(GL_QUADS);
      {
        glVertex3f(310.0+x,40.0,0.0);
        glVertex3f(390.0+x,40.0,0.0);
        glVertex3f(390.0+x,70.0,0.0);
        glVertex3f(310.0+x,70.0,0.0);
      }
      glEnd();
      glFinish();
      glutSwapBuffers();

    }
  }



//::::::::::::::Reshape Function:::::::::::::::::://
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
  if(option==2)
  {
    xball=xball+(a*speed1);
    yball=yball+(b*speed1);
    speed1+=0.00001;
  }
  else
  {
    xball=xball+(a*speed[level]);
    yball=yball+(b*speed[level]);
  }


  if(option==1)
  {
    for(s=590;s>=490;s-=50)
      {
        for(r=50;r<650;r+=50)
          {
            if(target[r][s]==1)
              {
                if((yball<=s-32)&&(yball>=s-58)&&(xball>=r-2)&&(xball<=r+42)&&(b==1))
                  {
                    b=-b;
                    target[r][s]=0;
                    score1+=10;
                  }
              }
          }
      }
  }


  if(((xball<=400.0+x)&&(xball>=300.0+x))&&((yball>=75.0)&&(yball<=90.0)))
  {
    b=-b ;
    if(option==2)
    score2+=10;
  }

  if(yball>570.0)
  b=-b;

  if((xball>=620.0)||(xball<=65.0))
  a=-a;



  int s11,s12,s13,s14;
  s11=score1/1000;
  s12=(score1%1000)/100;
  s13=(score1%100)/10;
  s14=score1%10;
  sc1[0]=s11+48;
  sc1[1]=s12+48;
  sc1[2]=s13+48;
  sc1[3]=s14+48;

  if(option==2)
    {
      int s21,s22,s23,s24;
      s21=score2/1000;
      s22=(score2%1000)/100;
      s23=(score2%100)/10;
      s24=score2%10;
      sc2[0]=s21+48;
      sc2[1]=s22+48;
      sc2[2]=s23+48;
      sc2[3]=s24+48;
    }




  if(yball<=10.0)
  play=2;

  if(yball<=-20.0)
  glutIdleFunc(NULL);

  glutPostRedisplay();

}

//::::::::::::Restart Function::::::::::::::://
void restart(void)
{
  play=1;
  flag=1;
  x=0.0,y=0.0;
  xball=350.0,yball=350.0,a=1.0,b=1.0;
  score1=0;
  level=0;

  glutPostRedisplay();
}

//::::::::::::::::::::keyboard function:::::::::::::::::://
void keyboard(unsigned char key, int xm, int ym)
{
  if(option==0)
  {
    switch(key)
    {

      case 'l':option=1; glutPostRedisplay();
      break;

      case 't':option=2; glutPostRedisplay();
      break;

      case 'c':option=3; glutPostRedisplay();
      break;

      case 'q':exit(0);
    }
  }
  else
  {
  switch (key)
    {

      case 'a':x-=15;if(x<-260)x=-260;
      break;

      case 'd':x+=15; if(x>251)x=251;
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

      case 's':glutIdleFunc(againDisplay);     //Start the game
      break;

      case 'p':glutIdleFunc(NULL);            //Pause the game
      break;

      case 'r':glutIdleFunc(restart);
      default:
      break;
    }
  }
}



int main(int argc,char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(w_width,w_height);
  glutInitWindowPosition(270,20);
  glutCreateWindow("Tik-i-noids by Jalaz");
  init();
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
