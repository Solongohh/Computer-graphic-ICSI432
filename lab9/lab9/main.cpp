#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

int num_texture=-1; //Counter to keep track of the last loaded texture
GLuint model;

#define MAX_VERTICES 2000 // Max number of vertices (for each object)
#define MAX_POLYGONS 2000 // Max number of polygons (for each object)
#define n 3000
float x1[n],xn[n];
float y1[n],yn[n];
float z1[n],zn[n],m1[n],m2[n];
// Our vertex type
typedef struct{
    float x,y,z;
}vertex_type;

// The polygon (triangle), 3 numbers that aim 3 vertices
typedef struct{
    int a,b,c;
}polygon_type;

// The mapcoord type, 2 texture coordinates for each vertex
typedef struct{
    float u,v;
}mapcoord_type;

// The object type
typedef struct {
    vertex_type vertex[MAX_VERTICES];
    polygon_type polygon[MAX_POLYGONS];
    mapcoord_type mapcoord[MAX_VERTICES];
    int id_texture;
} obj_type, *obj_type_ptr;

// The width and height of your window, change them as you like
int screen_width;
int screen_height;

// Absolute rotation values (0-359 degrees) and rotation increments for each frame
double xRot=0, rotation_x_increment=0.1;
double yRot=0, rotation_y_increment=0.05;
//double rotation_z=0, rotation_z_increment=0.03;

// Flag for rendering as lines or filled polygons
int filling=1; //0=OFF 1=ON

// And, finally our first object!
obj_type cube =
{
    {
        -10, -10, 10,   // vertex v0
        10,  -10, 10,   // vertex v1
        10,  -10, -10,  // vertex v2
        -10, -10, -10,  // vertex v3
        -10, 10,  10,   // vertex v4
        10,  10,  10,   // vertex v5
        10,  10,  -10,  // vertex v6
        -10, 10,  -10   // vertex v7
    },
    {
        0, 1, 4,  // polygon v0,v1,v4
        1, 5, 4,  // polygon v1,v5,v4
        1, 2, 5,  // polygon v1,v2,v5
        2, 6, 5,  // polygon v2,v6,v5
        2, 3, 6,  // polygon v2,v3,v6
        3, 7, 6,  // polygon v3,v7,v6
        3, 0, 7,  // polygon v3,v0,v7
        0, 4, 7,  // polygon v0,v4,v7
        4, 5, 7,  // polygon v4,v5,v7
        5, 6, 7,  // polygon v5,v6,v7
        3, 2, 0,  // polygon v3,v2,v0
        2, 1, 0   // polygon v2,v1,v0
    },
    {
        0.0, 0.0,  // mapping coordinates for vertex v0
        1.0, 0.0,  // mapping coordinates for vertex v1
        1.0, 0.0,  // mapping coordinates for vertex v2
        0.0, 0.0,  // mapping coordinates for vertex v3
        0.0, 1.0,  // mapping coordinates for vertex v4
        1.0, 1.0,  // mapping coordinates for vertex v5
        1.0, 1.0,  // mapping coordinates for vertex v6
        0.0, 1.0   // mapping coordinates for vertex v7
    },
    0,
};

 void SetupRC()
	{
	// Light values and coordinates
	GLfloat  ambientLight[] = {0.4f, 0.4f, 0.4f, 1.0f };
	GLfloat  diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat  specular[] = { 0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat	 lightPos[] = { -50.0f, 500.0f, 200.0f, 1.0f };
	GLfloat  specref[] =  { 0.6f, 0.6f, 0.6f, 1.0f };


	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glEnable(GL_CULL_FACE);		// Do not calculate inside of solid object
	glFrontFace(GL_CCW);

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);

	// Position and turn on the light
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a moderate shine
	glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,64);

	// Black background
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
	}

int LoadBitmap(char *filename)
{
    int i, j=0; //Index variables
    FILE *l_file; //File pointer
    unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture

    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader;
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++; // The counter of the current texture is increased

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

    fread(&fileheader, sizeof(fileheader), 1, l_file); // Read the fileheader

    fseek(l_file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
    fread(&infoheader, sizeof(infoheader), 1, l_file); // and read the infoheader

    // Now we need to allocate the memory for our image (width * height * color deep)
    l_texture = (BYTE *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    // And fill it with zeros
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);

    // At this point we can read every pixel of the image
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {
            // We load an RGB value from the file
            fread(&rgb, sizeof(rgb), 1, l_file);

            // And store it
            l_texture[j+0] = rgb.rgbtRed; // Red component
            l_texture[j+1] = rgb.rgbtGreen; // Green component
            l_texture[j+2] = rgb.rgbtBlue; // Blue component
            l_texture[j+3] = 255; // Alpha value
            j += 4; // Go to the next position
    }

    fclose(l_file); // Closes the file stream

    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}

void loadObj(char *fname)
{
    GLfloat mat[4];
    FILE *fp;
    int read;

    float x, y, z, a, b, c, d, e, f,g,l,h;
    float normal[4],corners[2][3];	// Vertex calculation storage
	float step = (3.1415f/50.0f);
    char ch,ch1;
    model = glGenLists(1);
    fp = fopen(fname,"r");
    if(!fp)
        {
            printf("can't open file %s\n", fname);
          exit(1);
        }
    glPointSize(1.0);
    glNewList(model, GL_COMPILE);
    {
    glPushMatrix();
    int i=0,i1=0,i2=0,i3=0,j=0;

            while(!(feof(fp)))
             {
                 read=fscanf(fp,"%c",&ch);
              if(ch=='v')
              {
                  read=fscanf(fp,"%c",&ch);
                  if(read==1 && ch=='t' )
                  {
                       read=fscanf(fp,"%f %f",&x,&y);
                       m1[i1]=x;
                       m2[i1]=y;
                       i1++;
                  }
                  else if(read==1 && ch=='n')
                  {
                       read=fscanf(fp,"%f %f %f",&x,&y,&z);
                       xn[i2]=x;
                       yn[i2]=y;
                       zn[i2]=z;
                       i2++;
                  }
                  else {
                   read=fscanf(fp," %f %f %f",&x,&y,&z);
                   x1[i]=x;
                   y1[i]=y;
                   z1[i]=z;
                   i++;
                  }

              }


              if(ch=='f')
              {
                  char ch2,ch4;
                  int x2, y2, z2, a1, b1, c1, d1, e1, f1,g1,l1,h1;
                   read=fscanf(fp,"%d %c %d %c %d ",&x2,&ch1,&y2,&ch1,&z2);
                   read=fscanf(fp,"%d %c %d %c %d ",&a1,&ch2,&b1,&ch2,&c1);
                   read=fscanf(fp,"%d %c %d %c %d ",&d1,&ch2,&e1,&ch2,&f1);
                   read=fscanf(fp,"%d %c %d %c %d ",&g1,&ch2,&l1,&ch2,&h1);
                   normal[0]=z2;
                   normal[1]=c1;
                   normal[2]=f1;
                   normal[3]=h1;
                   glPointSize(1.0);
                glColor3d(0,0,1);
                glBegin(GL_QUADS);

                   glNormal3fv(normal);

                   glTexCoord2f(m1[int(y2-1)],m2[int(y2-1)]);
                   glVertex3f(x1[x2-1],y1[x2-1],z1[(x2-1)]);
                   glTexCoord2f(m1[int(b1-1)],m2[int(b1-1)]);
                   glVertex3f(x1[(a1-1)],y1[int(a1-1)],z1[int(a1-1)]);
                   glTexCoord2f(m1[int(e1-1)],m2[int(e1-1)]);
                   glVertex3f(x1[int(d1-1)],y1[int(d1-1)],z1[int(d1-1)]);
                   glTexCoord2f(m1[int(l1-1)],m2[int(l1-1)]);
                   glVertex3f(x1[int(g1-1)],y1[int(g1-1)],z1[int(g1-1)]);
                   glEnd();
              }

            }

            glPopMatrix();
    glEndList();
    fclose(fp);
    }
}



void  init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to dark blue
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons

    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f); // We define the "viewing volume"

    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

    glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

    cube.id_texture=LoadBitmap("D:/hiceel/Computer graphic/lab9/lab9/potato1.bmp"); // The Function LoadBitmap() return the current texture ID

    // If the last function returns -1 it means the file was not found so we exit from the program
    if (cube.id_texture==-1)
    {
        MessageBox(NULL,"Image file: file not found", "Zetadeck",MB_OK | MB_ICONERROR);
        exit (0);
    }
}


void resize (int width, int height)
{
    screen_width = width; // We obtain the new screen width values and store it
    screen_height = height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0, 0, width, height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective (100.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
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

void  display(void)
{
    int l_index;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue

    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity
    glPushMatrix();
    glTranslatef(0.0,-5.0,-15.0); // We move the object 50 points forward (the model matrix is multiplied by the translation matrix)

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

    //glBindTexture(GL_TEXTURE_2D, cube.id_texture); // We set the active texture
    glColor3d(1.0,0.23,0.27);
    glCallList(model);

    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
    glPopMatrix();
}


int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(450,450);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Texture mapping");
    glutDisplayFunc(display);
    //
    glutIdleFunc(display);
    glutReshapeFunc (resize);
    //glutKeyboardFunc (SpecialKeys);
    glutSpecialFunc (SpecialKeys);
    SetupRC();
    loadObj("D:/hiceel/Computer graphic/lab9/lab9/Character.obj");
    init();
    glutMainLoop();

    return(0);
}
