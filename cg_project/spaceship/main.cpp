#ifdef __APPLE__
#include <GLUT/glut.h>
#include <window.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <windows.h>
#include "glm/glm.hpp"

#define WINDOW_WIDTH  (600)//1280
#define WINDOW_HEIGHT  (375)//800

#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (16)

#define PART_WIDTH   (WINDOW_WIDTH / 16)
#define PART_HEIGHT   (WINDOW_HEIGHT / 16)

float posx=0,posy=0;
enum {
    TEX_SHIP,
    TEX_GALAXY,
    TEX_METEOR,
    TEX_MAX
};


typedef struct {
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    GLuint texture;
    glm::ivec2 rect;
}TEX;

TEX tex[TEX_MAX];

const char course[COURSE_HEIGHT][COURSE_WIDTH] = {
"bqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbq",
"qbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqb",
"bqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbq",
"qbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqb",
"bqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbq",
"qbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqb",
"bqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbq",
"qbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqb",
"bqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbq",
"qbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqb",
"bqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbq",
"qbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqb",
"bqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbq",
"qbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqb",
"bqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbq",
"qbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqbqb",
};
void keyboard(unsigned char key,int x,int y){
    switch (key){
        case GLUT_KEY_DOWN:
            posx=0;
            posy-=0.1;
            break;
        case GLUT_KEY_UP:
            posx=0;
            posy+=0.1;
            break;
        case GLUT_KEY_LEFT:
            posx-=0.1;
            posy=0;
            break;
        case GLUT_KEY_RIGHT:
            posx+=0.1;
            posy=0;
            break;
    }
    glutPostRedisplay();
}

static void TexFromFile(const char * _fileName, int _tex, glm::ivec2 _rect){
    tex[_tex].rect = _rect;
    FILE *fp;
    fopen_s(&fp, _fileName, "rb");
    if(!fp){
        printf("%s open failed\n", _fileName);
        return;
    }
    printf("%s is opened\n", _fileName);
    //Zurgiin hemjee
    fread(&tex[_tex].bf, sizeof(BITMAPFILEHEADER), 1, fp);
    printf("bfSize: %d\n", tex[_tex].bf.bfSize);
    fread(&tex[_tex].bi, sizeof(BITMAPINFOHEADER), 1, fp);
    //Zurgiin orgon, ondor
    printf("%d * %d\n",tex[_tex].bi.biWidth, tex[_tex].bi.biHeight);
    //1px Ongiin medeelliig biteer avah
    typedef struct{
        unsigned char b, g, r;
    }BGR;
    BGR *bits = (BGR*)malloc(sizeof(BGR) * tex[_tex].bi.biWidth * tex[_tex].bi.biHeight);
    fread(bits, sizeof(BGR), tex[_tex].bi.biWidth * tex[_tex].bi.biHeight, fp);
    typedef struct{
        unsigned char r, g, b, a;
    }RGBA;
    RGBA *pixels = (RGBA*)malloc(sizeof(RGBA) * tex[_tex].bi.biWidth * tex[_tex].bi.biHeight);
    memset(pixels, 0, tex[_tex].bi.biWidth * tex[_tex].bi.biHeight);

    for(int i = 0; i < tex[_tex].bi.biWidth * tex[_tex].bi.biHeight; i++){
        pixels[i].r = bits[i].r;
        pixels[i].g = bits[i].g;
        pixels[i].b = bits[i].b;
        pixels[i].a = ((bits[i].r == 0xff) && (bits[i].g == 0xff) && (bits[i].b == 0xff)) ? 0x00 : 0xff;  //18fe00
    }

    for(int y = 0; y < tex[_tex].bi.biHeight / 2; y++){
        for(int x = 0; x < tex[_tex].bi.biWidth; x++){
            RGBA temp = pixels[y * tex[_tex].bi.biWidth + x];
            pixels[y * tex[_tex].bi.biWidth + x] = pixels[(tex[_tex].bi.biHeight - 1 - y) * tex[_tex].bi.biWidth + x];
            pixels[(tex[_tex].bi.biHeight - 1 - y) * tex[_tex].bi.biWidth + x] = temp;
        }
    }
    free(bits);
    glGenTextures(1, &tex[_tex].texture);
    glBindTexture(GL_TEXTURE_2D, tex[_tex].texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex[_tex].bi.biWidth, tex[_tex].bi.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    free(pixels);
    fclose(fp);
    printf("%s is closed\n", _fileName);
}
//Hodolgoon zurah
void DrawSprite(int _tex, float _width, float _height, int _index){
    glBindTexture(GL_TEXTURE_2D, tex[_tex].texture);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPushMatrix();
        glBegin(GL_QUADS);
          float w = tex[_tex].bi.biWidth;
          float h = tex[_tex].bi.biHeight;
          float tw = tex[_tex].rect.x;
          float th = tex[_tex].rect.y;
          int columnMax = w / tw;
          int rowMax = h / th;
          int tx = tw * (_index % columnMax);
          int ty = th * (_index / columnMax);
          glTexCoord2f(tx / (float)w, ty / (float)h);
          glVertex2f(0, 0);
          glTexCoord2f(tx / (float)w, (ty + th) / (float)h);
          glVertex2f(0, _height);
          glTexCoord2f((tx + tw) / (float)w, (ty + th) / (float)h);
          glVertex2f(_width, _height);
          glTexCoord2f((tx + tw) / (float)w, ty / (float)h);
          glVertex2f(_width, 0);
        glEnd();
    glPopMatrix();
}

void Init(){
    //TexFromFile("C:\\Com Graphic\\game2\\elves2.bmp", TEX_ELVES, {100, 100});
    //TexFromFile("D:/hiceel/Computer graphic/cg_project/Map/Map/block2.bmp", TEX_BLOCK, {16, 16});
    //TexFromFile("D:/hiceel/Computer graphic/cg_project/spaceship/galaxy_back.bmp", TEX_GALAXY, {1280, 800});
    TexFromFile("D:/hiceel/Computer graphic/cg_project/spaceship/galaxy_back2.bmp", TEX_GALAXY, {600, 375});
    TexFromFile("D:/hiceel/Computer graphic/cg_project/spaceship/spaceship.bmp", TEX_SHIP, {64, 64});
    //TexFromFile("D:/hiceel/Computer graphic/cg_project/spaceship/meteor.bmp", TEX_METEOR, {50, 51});
}

/*void DrawPart(glm::vec2 _position, char _c){
     int x = (int)_position.x / PART_WIDTH;
     int y = (int)_position.y / PART_HEIGHT;
     if(x < 0 || x >= COURSE_WIDTH || (y < 0) || (y >= COURSE_HEIGHT))
        return;

    int index = -1;
    switch(_c){
        case 'b':
            index = 2;
            break;
        case 'q':
            index = 3;
            break;
    }

    if(index >= 0)
        DrawSprite(TEX_BLOCK, PART_WIDTH, PART_HEIGHT, index, _position);
}*/
/*void shoot(){
    while(1){
        glColor3d(1,1,1);
        glBegin(GL_LINE);
            glVertex2d(0,0);
            glVertex2d(0,2+posy);
        glEnd();
    }
}*/
static void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //shoot();

    //for(int y = 1; y < COURSE_HEIGHT; y++){
        /*for(int x = 0; x < COURSE_WIDTH; x++){
            DrawPart({x * PART_WIDTH, y * PART_HEIGHT}, course[y][x]);

        }*/

    //}
    DrawSprite(TEX_GALAXY, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    DrawSprite(TEX_SHIP, 64, 64, 0);
    //xDrawSprite(TEX_METEOR, 50, 51, 0);

    glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("Galaxy");
    glutDisplayFunc(display);
    //glutIdleFunc(Idle);
    glutKeyboardFunc(keyboard);
    //glutKeyboardUpFunc(KeyboardUp);
    //glutTimerFunc(12, timer, 0);
    Init();
    //glClearColor(1,1,1,1);
    glutMainLoop();

    return EXIT_SUCCESS;
}


