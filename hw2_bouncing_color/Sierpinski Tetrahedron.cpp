// This program is a modification and extension of an early program in Edward
// Angel's book, Interactive Computer Graphics: A top-down approach using
// OpenGL.  It plots the 3-D Sierpinski Tetrahedron using colors in a nice
// way.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>

float eye[3], at[3], up[3]; //새롭게 추가

// A simple three-dimensional point class to make life easy.  It allows you
// to reference points with x and y coordinates instead of array indices) and
// encapsulates a midpoint function.
struct Point {
    GLfloat x, y, z;
    Point(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}
    Point midpoint(Point p) { return Point((x + p.x) / 2, (y + p.y) / 2, (z + p.z) / 2); }
};

// Handles reshape requests by setting the the viewport to exactly match the
// pixel coordinates, so we can draw in the whole window.  Then sets up a
// simple perspective viewing volume to ensure that the pyramid will never
// be distorted when the window is reshaped.  The particular settings chosen
// ensure that the vertical extent of the pyramid will always be visible.
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, GLfloat(w) / GLfloat(h), 10.0, 1500.0);
}

// Handles display requests.  All it has to do is clear the viewport because
// the real drawing is done in the idle callback.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);    //새롭게 추가
}

// Draws the "next 500 points".  The function contains locally the definitions
// of the vertices and the current point as static objects so that their values
// are retained between calls.
void generateMorePoints() {

    // The tetrahedron has four vertices.  We also have to keep track of the
    // current point during the plotting.
    static Point vertices[5] = {
        //Point(-250, -225, -200),
        //Point(-150, -225, -700),
        //Point(250, -225, -275),
        //Point(0, 450, -500)
                                                  //정사면체 -> 사각뿔
        Point(-250, -225, -200),
        Point(-150, -225, -600),
        Point(250, -225, -275),
        Point(350,-225,-675),
        Point(0, 450, -500)
    };
    static Point lastPoint = vertices[0];

    // Here is the code to draw the "next 500 points".  The closer the point is
    // to the camera, the brighter we make it.  The coloring technique is a
    // quick hack which (unprofessionally) depends on the fact that the range
    // of z-coordinates in the tetrahedron run from -200 to -700.  By adding
    // 700 to any z-value and then dividing by 500, we get values in the range
    // 0 to 1 - just perfect for coloring.
    glBegin(GL_POINTS);
    for (int i = 0; i <= 500; i++) {
        //lastPoint = lastPoint.midpoint(vertices[rand() % 4]);
        lastPoint = lastPoint.midpoint(vertices[rand() % 5]);           //Point수 증가에 따른 Rand()%5
        GLfloat intensity = (700 + lastPoint.z) / 500.0;
        glColor3f(intensity, 0, intensity);                             //색 변경
        glVertex3f(lastPoint.x, lastPoint.y, lastPoint.z);
    }
    glEnd();
    glFlush();
}



// Performs application-specific initialization.  In this program we want to
// do depth buffering, which has to be explicitly enabled in OpenGL.
void init() {
    glEnable(GL_DEPTH_TEST);
    eye[0] = 5; eye[1] = 0; eye[2] = 50;    //새롭게 추가(카메라 위치)            //시점 변경
    at[0] = 0; at[1] = 0; at[2] = 0;        //새롭게 추가(바라볼 곳)
    up[0] = 0; up[1] = 1; up[2] = 0;        //새롭게 추가(카메라의 법선?)
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("201713922 이건회(수정)_Sierpinski Tetrahedron");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(generateMorePoints);
    init();
    glutMainLoop();
}