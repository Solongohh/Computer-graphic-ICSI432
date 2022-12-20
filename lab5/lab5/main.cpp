#ifdef __APPLE__
#include <GLUT/glut.h>
#include <window.h>
#else
#include <GL/glut.h>
#endif



#include<math.h>
#include <stdlib.h>
#include<stdio.h>
#define pi 3.14

int i,x,y,j,n=60,state=1;
float t=0;
float a[60][2];
float b[64][2];
float a1[60][2];
float b1[64][2];

void shape1(void){
        float x,y,r1=0.09;
        int k=0;
        for(i=0;i<n;i++){
            x=r1*cos(2*pi/n*i);
            y=r1*sin(2*pi/n*i)+0.9;
            a[i][0]=x;
            a[i][1]=y;
                //glVertex2f(x,y+0.8);
        }

        float r=0.4;
        for(i=0;i<=n;i++){
            x=r*cos(pi*i/n);
            y=r*sin(pi*i/n);
            b[i][0]=x;
            b[i][1]=y;
        }
}
void shape2(void){
    float x,y,r1=0.09;
    int k=0;
    for(i=0;i<n;i++){
        x=r1*cos(2*i*pi/n);
        y=r1*sin(2*i*pi/n)+0.2;
        a1[i][0] = x;
        a1[i][1] = y;
    }

    float r3=0.14;
    for(i=0;i<=n/3;i++, k++){
        x=r3*cos(pi*i/(n/3))+0.25;
        y=r3*sin(pi*i/(n/3))+0.03;
        b1[k][0] = x;
        b1[k][1] = y;
    }
    //glVertex2f(0.4,0.0);
    //glVertex2f(-0.4,0.0);

    float r=0.1;
    for(i=0;i<=n/3;i++,k++){
        x=r*cos(pi*i/(n/3));
        y=-r*sin(pi*i/(n/3))+0.02;
        b1[k][0] = x;
        b1[k][1] = y;
    }

    float r4=0.14;
    for(i=0;i<=n/3;i++, k++){
        x=r4*cos(pi*i/(n/3))-0.25;
        y=r4*sin(pi*i/(n/3))+0.03;
        b1[k][0] = x;
        b1[k][1] = y;
    }
    //glVertex2f(-0.17,0.2);
}
void draw(void){
    shape1();
    shape2();
    printf("t: %f\n", t);
    float p[60][2];
    glColor3d(0.5,0,0.5);
    glPointSize(5.0);
    glBegin(GL_POLYGON);
        for(i=0;i<n;i++){
            p[i][0]=(1-t)*a[i][0]+t*a1[i][0];
            p[i][1]=(1-t)*a[i][1]+t*a1[i][1];
            glVertex2f(p[i][0],p[i][1]);
        }
    glEnd();
    glBegin(GL_LINE_STRIP);
        for(i=0;i<n;i++){
            p[i][0]=(1-t)*b[i][0]+t*b1[i][0];
            p[i][1]=(1-t)*b[i][1]+t*b1[i][1];
            glVertex2f(p[i][0],p[i][1]);
        }
    glEnd();
}
/*void test(void){
    shape2();
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.5,0,0.5);
    glPointSize(5.0);
    glBegin(GL_LINE_STRIP);
        for(i=0;i<n;i++){
            glVertex2f(b[i][0],b[i][1]);
        }
    glEnd();
}*/

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw();
    //test();
    glColor3d(0.5,0,0.5);
    glPointSize(5.0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(0.4,0.03);
        glVertex2f(0.1,-0.27);
        glVertex2f(0.3,-0.47);
        glVertex2f(-0.3,-0.47);
        glVertex2f(-0.1,-0.27);
        glVertex2f(-0.4,0.03);
    glEnd();
    glFlush();
}
void timer(int value){
    if(t > 1)
        state = 0;
    if(t < 0)
        state = 1;

    if(state == 1)
        t+=0.01;
    else
        t-=0.01;
    glutPostRedisplay();
    glutTimerFunc(33,timer,0);
}
/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutTimerFunc(33, timer, 0);
    glutCreateWindow("animation");
    glutDisplayFunc(display);
    glClearColor(0,0,0,0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
