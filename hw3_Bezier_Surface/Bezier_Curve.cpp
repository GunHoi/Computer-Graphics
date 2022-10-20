#include <iostream>
#include <GL/glut.h> /* includes gl.h glu.h */

GLfloat ctrlpoints[10][3] = {
    {-20,-6,0} ,{-15,2,0},{-7,-12,0},
    { -4.0, -4.0, 0.0}, { -2.0, 4.0, 0.0},
    {2.0, -4.0, 0.0}, {4.0, 4.0, 0.0},
    {6,8,0},{8,6,0},{10,10,0}
};

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 10; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
    ///////////////////////////////////////////////////////////////////
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    for (i = 0; i <= 30; i++)
        glEvalCoord1f((GLfloat)i / 30.0);
    glEnd();
    //////////////////////////////////////////////////////////////
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[3][0]);
    glEnable(GL_MAP1_VERTEX_3);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    for (i = 0; i <= 30; i++)
        glEvalCoord1f((GLfloat)i / 30.0);
    glEnd();
    ////////////////////////////////////////////////////////////
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[6][0]);
    glEnable(GL_MAP1_VERTEX_3);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    for (i = 0; i <= 30; i++)
        glEvalCoord1f((GLfloat)i / 30.0);
    glEnd();

    glFlush();
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-30.0, 30.0, -30.0 * (GLfloat)h / (GLfloat)w,
            30.0 * (GLfloat)h / (GLfloat)w, -30, 30);
    else
        glOrtho(-30 * (GLfloat)w / (GLfloat)h,
            30 * (GLfloat)w / (GLfloat)h, -30, 30, -30, 30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("컴퓨터공학부 201713922 이건회 3-2 Bezier Curve");
    glutInitWindowPosition(100, 100);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}