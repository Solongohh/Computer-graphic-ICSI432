#ifdef __APPLE__
#include <GLUT/glut.h>
#include <window.h>
#else
#include <GL/glut.h>
#endif




#include <stdlib.h>

int i,x=0,y=0,j;

void SetWindow(float left, float right, float bottom, float top)
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(left, right, bottom, top, 1.0f, -1.0f);
}
void drawHexagon(){
            glPointSize(5.0);
            glBegin(GL_LINES);

        glVertex2f(1,1);
        glVertex2f(-1,-1);

        glVertex2f(0.8,1);
        glVertex2f(-0.8,-1);

        glVertex2f(0.6,1);
        glVertex2f(-0.6,-1);

        glVertex2f(0.4,1);
        glVertex2f(-0.4,-1);

        glVertex2f(0.2,1);
        glVertex2f(-0.2,-1);

        glVertex2f(0.0,1);
        glVertex2f(0.0,-1);

        glVertex2f(-0.2,-1);
        glVertex2f(0.2,1);

        glVertex2f(-0.4,-1);
        glVertex2f(0.4,1);

        glVertex2f(-0.6,-1);
        glVertex2f(0.6,1);

        glVertex2f(-0.8,-1);
        glVertex2f(0.8,1);

        glVertex2f(-1,-1);
        glVertex2f(1,1);

        glVertex2f(-1,-0.8);
        glVertex2f(1,0.8);

        glVertex2f(-1,-0.6);
        glVertex2f(1,0.6);

        glVertex2f(-1,-0.4);
        glVertex2f(1,0.4);

        glVertex2f(-1,-0.2);
        glVertex2f(1,0.2);

        glVertex2f(-1,0.4);
        glVertex2f(-0.4,1);
        glVertex2f(-1,0.6);
        glVertex2f(-0.6,1);
        glVertex2f(-1,0.7);
        glVertex2f(-0.7,1);
        glVertex2f(-1,0.8);
        glVertex2f(-0.8,1);
        glVertex2f(-1,0.9);
        glVertex2f(-0.9,1);

        glVertex2f(1,-0.4);
        glVertex2f(0.4,-1);
        glVertex2f(1,-0.6);
        glVertex2f(0.6,-1);
        glVertex2f(1,-0.7);
        glVertex2f(0.7,-1);
        glVertex2f(1,-0.8);
        glVertex2f(0.8,-1);
        glVertex2f(1,-0.9);
        glVertex2f(0.9,-1);


            glEnd();

        glFlush();
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.5,0,0.5);
        int i,j,p=10,q=10,pix=1,w=50,h=50;
        for(i=0;i<p;i++)
            {
                for(j=0;j<q;j++)
                    {

                        if((i+j)%2==0)
                                SetWindow(-pix, pix, pix, -pix);
                        else
                                SetWindow(-pix, pix, -pix, pix);

                        glViewport(i*w,j*h,w,h);
                        drawHexagon();
                }
        }
}

/* Program entry point */


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("pattern");
    glutDisplayFunc(display);
    glClearColor(1,1,1,1);
    glutMainLoop();




    return EXIT_SUCCESS;
}
