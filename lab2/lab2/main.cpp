#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define pi 3.14

#include <stdlib.h>
#include <math.h>
#include<stdio.h>

int n = 2;
float red=1, green=1, blue=1;

    void display(void){

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3d(red,green,blue);
        glPointSize(5.0);
        glBegin(GL_TRIANGLE_FAN);
        float r=0.5;
        float i;
        for(i=0;i<2*pi;i+=2*pi/n){
            float x=r*cos(i);
            float y=r*sin(i);
            glVertex2f(x,y);
        }
        glEnd();
        glFlush();
    }
    void mouse (int key, int x, int y){
        if(key == GLUT_KEY_DOWN){
            n--;
        }else if(key == GLUT_KEY_UP){
            n++;
        }
        glutPostRedisplay();
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
        }
    }

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(480,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("GLUT Shapes");

    glutSpecialFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glClearColor(0,0,0,1);
    glutMainLoop();

    return EXIT_SUCCESS;
}
