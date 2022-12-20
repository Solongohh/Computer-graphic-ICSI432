/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <windows.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<stdio.h>
float x_check, y_check;
float x1,y1,x2,y2,red,blue,green;
void drawing(float x1,float x2,float y1,float y2,float red,float green,float blue){


        /*glColor3d(1,0,0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.9, 0.9);
            glVertex2f(0.9, 0.8);
            glVertex2f(0.8, 0.8);
            glVertex2f(0.8, 0.9);

        glEnd();
        glColor3d(0,1,0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.7, 0.9);
            glVertex2f(0.7, 0.8);
            glVertex2f(0.6, 0.8);
            glVertex2f(0.6, 0.9);

        glEnd();
        glColor3d(0,0,1);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.5, 0.9);
            glVertex2f(0.5, 0.8);
            glVertex2f(0.4, 0.8);
            glVertex2f(0.4, 0.9);

        glEnd();

        glFlush();*/

        printf("%f %f %f \n",red,blue,green);
        glColor3d(red,green,blue);
        glPointSize(5.0);

        glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();

        glFlush();
}
void display(void){
    drawing(x1,x2,y1,y2,red,green,blue);
}
void mouse(int button,int state,int x,int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            switch(state){
                case GLUT_DOWN:
                        x1 = (x-239.0)/239.0;
                        y1 = (239.0-y)/239.0;
                        printf("%f, %f\n", x1, y1);
                        break;

                case GLUT_UP:
                    x2=(x-239.0)/239.0;
                    y2=(239.0-y)/239.0;
                    printf("%f, %f\n", x2, y2);
                    break;
            }
    }

    //glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){
        if(key=='r' || key == 'R'){
            red=1.0;
            green=0.0;
            blue=0.0;
        }else if(key=='g' || key=='G'){
            red=0.0;
            green=1.0;
            blue=0.0;
        }else if(key=='b' || key=='B'){
            red=0.0;
            green=0.0;
            blue=1.0;
        }else if(key=='d' || key=='D'){
            red=0.0;
            green=0.0;
            blue=0.0;
        }
    }
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(480,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Paint");

    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glutMainLoop();

    return EXIT_SUCCESS;
}
