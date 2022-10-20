//bezmesh.c
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <windows.h>
#include <math.h>


void Keyboard(unsigned char key, int x, int y);
float xRot = 0.0f;
float yRot = 0.0f;
float zRot = 0.0f;

/*
GLfloat ctrlpoints[4][4][3] = {
    { {-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},{0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
    { {-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},{0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
    { {-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},{0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
    { {-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},{0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};*/
/*
GLfloat ctrlpoints[4][4][3] = {
    { {0,0 ,1 }, {1,0 ,0 },{0,0 ,-1 }, {-1, 0, 0}},
    { {0.5, 0.24,0.87}, {0.87, 0.24,0.5 },{0.87,0.24 ,-0.5 }, {0.5,0.24 ,-0.87 }},
    { {-0.5,0.24 ,-0.87 }, {-0.87,0.24 , -0.5},{-0.87, 0.24, 0.5}, {-0.5,0.24 ,0.87 }},
    { {0, 0.33,0.19 }, {0.19, 0.33, 0},{0,0.33 ,-0.19 }, {-0.19,0.33 ,0 }}
};*/

GLfloat ctrlpoints[4][4][3] = {
    { {0,0 ,-1 }, {-0.5,0.24 ,-0.87 }, {-0.87,0.24 , -0.5}, {-1, 0, 0}},
    { {0.5,0.24 ,-0.87 },{0,0.33 ,-0.19 },{-0.19,0.33 ,0 }, {-0.87, 0.24, 0.5}},
    { {0.87,0.24 ,-0.5 }, {0.19, 0.33, 0},{0, 0.33,0.19 }, {-0.5,0.24 ,0.87 }},
    { {1,0 ,0 }, {0.87, 0.24,0.5 },{0.5, 0.24,0.87}, {0,0 ,1 }}
};




void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    //glRotatef(30,1.0, 1.0, 1.0);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    glPointSize(5);
    glEvalMesh2(GL_LINE, 0, 20, 0, 20);
    glPopMatrix();
    glFlush();
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -2.0, 2.0);
    else
        glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("컴퓨터공학부 201713922 이건회 3-3 Bezier Surface");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();
}

void Keyboard(unsigned char key, int x, int y)
{
    if (key == 'x') {        // x축 로테이션
        xRot += 1;
        glutPostRedisplay();
    }
    if (key == 'y') {        // y축 로테이션
        yRot += 1;
        glutPostRedisplay();
    }
    if (key == 'z') {        // z축 로테이션
        zRot += 1;
        glutPostRedisplay();
    }
}