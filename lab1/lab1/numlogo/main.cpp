/*
 * GLUT Shapes Demo Updated
 */





#ifdef __APPLE__
#include <GLUT/glut.h>
#include <window.h>
#else
#include <GL/glut.h>
#endif




#include <stdlib.h>
#include <math.h>

#define pi 3.14


/* GLUT callback Handlers */




static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);




    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0,0,1);



    //tug
    glPointSize(5.0);
    glBegin(GL_QUADS);
        glVertex2f(0.0,0.7);
        glVertex2f(0.0,0.6);
        glVertex2f(0.2,0.5);
        glVertex2f(0.2,0.6);
    glEnd();

    //tugnii ish
    glPointSize(5.0);
        glBegin(GL_QUADS);
        glVertex2f(0.0,0.6);
        glVertex2f(0.02,0.6);
        glVertex2f(0.02,0.3);
        glVertex2f(0.0,0.3);
    glEnd();


    //booronhii
    glBegin(GL_POLYGON);
    float r1 = 0.15;
    float i;
    for(i=-0.1;i<pi+0.1;i+=0.1){
            float x=r1*cos(i);
            float y=r1*sin(i);
            glVertex2f(x,y+0.23);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3d(0,0,0);
    float r2 = 0.12;
    for(i=0;i<pi;i+=0.1){
            float x=r2*cos(i);
            float y=r2*sin(i);
            glVertex2f(x,y+0.21);
    }
    glEnd();


    glColor3d(0,0,1);
    glPointSize(5.0);
        glBegin(GL_QUADS);
        glVertex2f(-0.55,0.1);
        glVertex2f(-0.4,0.0);
        glVertex2f(-0.4,-0.1);
        glVertex2f(-0.55,0.0);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-0.55,0.0);
        glVertex2f(-0.55,-0.3);
        glVertex2f(-0.50,-0.3);
        glVertex2f(-0.50,0.05);
    glEnd();


    glBegin(GL_QUADS);
        glVertex2f(-0.4,0.2);
        glVertex2f(-0.25,0.1);
        glVertex2f(-0.25,0.0);
        glVertex2f(-0.4,0.1);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-0.4,0.1);
        glVertex2f(-0.4,-0.3);
        glVertex2f(-0.35,-0.3);
        glVertex2f(-0.35,0.08);
    glEnd();


    glBegin(GL_QUADS);
        glVertex2f(-0.25,0.3);
        glVertex2f(-0.0,0.15);
        glVertex2f(-0.0,0.05);
        glVertex2f(-0.25,0.2);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-0.25,0.25);
        glVertex2f(-0.25,-0.3);
        glVertex2f(-0.20,-0.3);
        glVertex2f(-0.20,0.22);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-0.15,0.1);
        glVertex2f(0.0,0.0);
        glVertex2f(0.0,-0.1);
        glVertex2f(-0.15,0.0);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(-0.15,0.0);
        glVertex2f(-0.15,-0.3);
        glVertex2f(-0.1,-0.3);
        glVertex2f(-0.1,0.0);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-0.55,-0.3);
        glVertex2f(-0.55,-0.35);
        glVertex2f(0.55,-0.35);
        glVertex2f(0.55,-0.3);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.15,0.0);
        glVertex2f(0.15,-0.3);
        glVertex2f(0.1,-0.3);
        glVertex2f(0.1,0.0);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.15,0.1);
        glVertex2f(0.0,0.0);
        glVertex2f(0.0,-0.1);
        glVertex2f(0.15,0.0);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.25,0.25);
        glVertex2f(0.25,-0.3);
        glVertex2f(0.20,-0.3);
        glVertex2f(0.20,0.22);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.25,0.3);
        glVertex2f(0.0,0.15);
        glVertex2f(0.0,0.05);
        glVertex2f(0.25,0.2);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.4,0.1);
        glVertex2f(0.4,-0.3);
        glVertex2f(0.35,-0.3);
        glVertex2f(0.35,0.08);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.4,0.2);
        glVertex2f(0.25,0.1);
        glVertex2f(0.25,0.0);
        glVertex2f(0.4,0.1);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.55,0.0);
        glVertex2f(0.55,-0.3);
        glVertex2f(0.50,-0.3);
        glVertex2f(0.50,0.05);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.55,0.1);
        glVertex2f(0.4,0.0);
        glVertex2f(0.4,-0.1);
        glVertex2f(0.55,0.0);
    glEnd();

    glFlush();




    glFlush();
}




/* Program entry point */




int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("GLUT Shapes");
    glutDisplayFunc(display);
    glClearColor(0,0,0,1);
    glutMainLoop();




    return EXIT_SUCCESS;
}
