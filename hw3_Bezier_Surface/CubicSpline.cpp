#include <iostream>
#include <GL/glut.h> /* includes gl.h glu.h */
/*
GLfloat ctrlpoints[7][3] = { { -3.5, -3.5, 0.0 }, { -2.5, 2.5, 0.0 },
                             { -2.0, 3.0, 0.0 }, { 0.0, 1.0, 0.0 },
                             { 1.0, -2.0, 0.0 }, { 3.0, 0.0, 0.0 },
                             { 3.5, 3.5, 0.0 }
};
*/

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
    /*
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 10, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
    */
}

float polyint(float  points[][3], float x, int N) {
    float y;
    float num = 1.0, den = 1.0;
    float sum = 0.0;

    for (int i = 0; i < N; ++i) {
        num = den = 1.0;
        for (int j = 0; j < N; ++j) {
            if (j == i) continue;
            //x - xj
            num = num * (x - points[j][0]);
        }
        for (int j = 0; j < N; ++j) {
            if (j == i) continue;
            //xi - xj
            den = den * (points[i][0] - points[j][0]);
        }
        sum += num / den * points[i][1];
    }
    y = sum;
    return y;
}

void display(void) {

    int i;
    float x, y;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.3, 0.3);
    glBegin(GL_LINE_STRIP);
    for (i = -200; i <= -40; i++) {
        x = (float)i / 10.0;
        y = polyint(ctrlpoints, x, 4);
        glVertex2f(x, y);
    }
    for (i = -40; i <= 40; i++) {
        x = (float)i / 10.0;
        y = polyint(ctrlpoints, x, 7);
        glVertex2f(x, y);
    }
    for (i = 40; i <= 100; i++) {
        x = (float)i / 10.0;
        y = polyint(ctrlpoints, x, 10);
        glVertex2f(x, y);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);

    glEnd();
    // 설계한 제어점을 출력
    glPointSize(5.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 10; i++)
        glVertex3fv(&ctrlpoints[i][0]);
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
    glutCreateWindow("컴퓨터공학부 201713922 이건회 3-1 Cubic Spline");
    glutInitWindowPosition(100, 100);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}