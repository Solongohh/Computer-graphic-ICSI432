#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define n 150000

GLuint model;
float rot;
char ch='1';
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// Reduces a normal vector specified as a set of three coordinates,
// to a unit normal vector of length one.
void ReduceToUnit(float vector[3])
	{
	float length;

	// Calculate the length of the vector
	length = (float)sqrt((vector[0]*vector[0]) +
						(vector[1]*vector[1]) +
						(vector[2]*vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if(length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	}

// Points p1, p2, & p3 specified in counter clock-wise order
void calcNormal(float v[3][3], float out[3])
	{
	float v1[3],v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y]*v2[z] - v1[z]*v2[y];
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
	}

void loadObj(char *fname)
{
    FILE *fp;
    int read;
    float x, y, z, angle;
    float normal[3], corners[4][3];
    float step = (3.1415f/32.0f);
    float zstep = .125f;

    float x1[n];
    float y1[n];
    float z1[n];

    char ch;
    model=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(1.0);
    glNewList(model, GL_COMPILE);
    {
        glPushMatrix();
        int i = 0, j = 0;
        glBegin(GL_TRIANGLE_FAN);
        while(!(feof(fp)))
        {
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v')
            {
                x1[i]=x;
                y1[i]=y;
                z1[i]=z;
                i++;
            } else if(read==4&&ch=='f')
            {
                int x2=int(x-1);
                int y2=int(y-1);
                int z2=int(z-1);
                glBegin(GL_TRIANGLES);
                    corners[0][0] = x1[x2];
                    corners[0][1] = y1[x2];
                    corners[0][2] = z1[x2];

                    corners[1][0] = x1[y2];
                    corners[1][1] = y1[y2];
                    corners[1][2] = z1[y2];

                    corners[2][0] = x1[z2];
                    corners[2][1] = y1[z2];
                    corners[2][2] = z1[z2];

                    corners[3][0] = x1[z2];
                    corners[3][1] = y1[z2];
                    corners[3][2] = z1[z2] + zstep;

                glFrontFace(GL_CCW);
                glBegin(GL_TRIANGLES);

                calcNormal(corners, normal);
                glNormal3fv(normal);
                    glVertex3f(x1[x2],y1[x2],z1[x2]);
                    glVertex3f(x1[y2],y1[y2],z1[y2]);
                    glVertex3f(x1[z2],y1[z2],z1[z2]);
                    glEnd();

                calcNormal(corners, normal);
                normal[0] = -normal[0];
                normal[1] = -normal[1];
                normal[2] = -normal[2];

                glFrontFace(GL_CW);

                glBegin(GL_TRIANGLES);
                glNormal3fv(normal);
                    glVertex3f(x1[x2],y1[x2],z1[x2]);
                    glVertex3f(x1[y2],y1[y2],z1[y2]);
                    glVertex3f(x1[z2],y1[z2],z1[z2]);
                    glEnd();

            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}

void ChangeSize(int w, int h)
    {
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    fAspect = (GLfloat)w/(GLfloat)h;

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Produce the perspective projection
    gluPerspective(35.0f, fAspect, 1.0, 40.0);
	//glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, -5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    }
void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

        xRot = (GLfloat)((const int)xRot % 360);
        yRot = (GLfloat)((const int)yRot % 360);

	// Refresh the Window
	glutPostRedisplay();
	}
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective ( 60, (GLfloat)w / (GLfloat)h, 0.5, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}
void drawModel()
{
    glPushMatrix();
    glTranslatef(0,0,-2);
    glColor3f(1.0,1.0,1.0);
    glScalef(0.9,0.9,0.9);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glCallList(model);
    glPopMatrix();
}
void SetupRC()
	{
	GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
   GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat position[] = {0.0, 3.0, 3.0, 0.0};

   GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat local_view[] = {0.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   glFrontFace(GL_CW);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);
   glEnable(GL_DEPTH_TEST);

   model = glGenLists(1);
   glNewList (model, GL_COMPILE);
   glEndList ();
	}
void renderModel(GLfloat x, GLfloat y,
   GLfloat ambr, GLfloat ambg, GLfloat ambb,
   GLfloat difr, GLfloat difg, GLfloat difb,
   GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine)
{
   GLfloat mat[4];

   glPushMatrix();
   glTranslatef(x, y, 0.0);
   mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
   mat[0] = difr; mat[1] = difg; mat[2] = difb;
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
   mat[0] = specr; mat[1] = specg; mat[2] = specb;
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
   glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
   glCallList(model);
   glPopMatrix();
}
void display(void)
{
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderModel(6.0, 17.0, 0.329412, 0.223529, 0.027451,
      0.780392, 0.568627, 0.113725, 0.992157, 0.941176, 0.807843,
      0.21794872);
    glLoadIdentity();
    drawModel();
    glutSwapBuffers();
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(450,450);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Lab10");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    SetupRC();
    //glutIdleFunc(display);
    loadObj("D:/hiceel/Computer graphic/lab8/lab8/dragon.obj");
    glutMainLoop();
    return 0;
}
