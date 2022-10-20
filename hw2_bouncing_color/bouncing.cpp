// This application shows balls bouncing on a checkerboard, with no respect
// for the laws of Newtonian Mechanics.  There's a little spotlight to make
// the animation interesting, and arrow keys move the camera for even more
// fun.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// Colors
GLfloat WHITE[] = { 1, 1, 1 };
GLfloat RED[] = { 1, 0, 0 };
GLfloat GREEN[] = { 0, 1, 0 };
GLfloat MAGENTA[] = { 1, 0, 1 };

GLfloat BLUE[] = { 0,0,1 };     //색 추가
GLfloat YELLOW[] = { 1,1,0 };   //색 추가
GLfloat CYAN[] = { 0,1,1 };     //색 추가

// A camera.  It moves horizontally in a circle centered at the origin of
// radius 10.  It moves vertically straight up and down.
class Camera {
    double theta;      // determines the x and z positions
    double y;          // the current y position
    double dTheta;     // increment in theta for swinging the camera around
    double dy;         // increment in y for moving the camera up/down
public:
    Camera() : theta(0), y(3), dTheta(0.04), dy(0.2) {}
    double getX() { return 10 * cos(theta); }
    double getY() { return y; }
    double getZ() { return 10 * sin(theta); }
    void moveRight() { theta += dTheta; }
    void moveLeft() { theta -= dTheta; }
    void moveUp() { y += dy; }
    void moveDown() { if (y > dy) y -= dy; }
};

// A ball.  A ball has a radius, a color, and bounces up and down between
// a maximum height and the xz plane.  Therefore its x and z coordinates
// are fixed.  It uses a lame bouncing algorithm, simply moving up or
// down by 0.05 units at each frame.
class Ball {
    double radius;
    GLfloat* color;
    double maximumHeight;
    double x;
    double y;
    double z;
    int direction;
    int count = 0;  //bounding 후 꼭대기에 다다르면 1 / 제일 아래에 도착하면 0 을 통해 구분
    int arriveEdge = 0; //바운딩 후 좌우로 움직임 0이면 direction방향으로, 1이면 -direction방향으로 이동
public:
    Ball(double r, GLfloat* c, double h, double x, double z) :  //반지름,색,최대높이,x,z좌표
        radius(r), color(c), maximumHeight(h), direction(-1),
        y(h), x(x), z(z) {
    }
    void update() {     //이 함수를 통해 좌우로 통통 튀는 주전자를 만들 수 있다.
        y += direction * 0.05;
        if (y > maximumHeight) {
            count = 1;      //꼭대기에 다다르면 count를 1로 바꿔서 현재 꼭대기에 위치함을 저장.
            y = maximumHeight; direction = -1;
        }
        else if (y < radius) {
            count = 0;      //바닥에 위치함을 저장
            y = radius; direction = 1;
        }
        if (arriveEdge == 0) {  //초기값,캡쳐화면 기준 왼쪽칸
            if (count == 1) {   //현재위치가 초기위치or왼쪽위치이고 꼭대기에 다다르면
                x += direction; //x의 값을 +direction만큼 이동
                count = 0;      //count=0으로 초기화
                arriveEdge = 1; //한칸 우측으로 이동했으므로 arriveEdge를 1로 설정
            }
        }
        else if (arriveEdge == 1) { // 초기값에서 한칸 움직인 곳
            if (count == 1) {       //현재 위치가 오른쪽위치이고 꼭대기에 다다르면
                x -= direction;     //x의 값을 -direction만큼 이동
                count = 0;          //count =0으로 초기화
                arriveEdge = 0;     //한칸 좌측으로 이동했으므로 arriveEdge를 0으로 설정
            }
        }
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
        glTranslated(x, y, z);
        //glutSolidSphere(radius, 30, 30);
        glutSolidTeapot(radius);        //주전자로 변경
        glPopMatrix();
    }
    void update2_X() {      //y축으로 통통 튀는게 아닌 maximum높이에서 x축을 기준으로 움직이는 공
        x += direction * 0.05;
        if (x > maximumHeight) {    //x축을 기준으로 각 maximum height 값만큼 좌우로 반복해서 이동
            x = maximumHeight; direction = -1;
        }
        else if (x < radius) {
            x = radius; direction = 1;
        }
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
        glTranslated(x, y, z);
        glutSolidSphere(radius, 30, 30);
        glPopMatrix();
    }
};

// A checkerboard class.  A checkerboard has alternating red and white
// squares.  The number of squares is set in the constructor.  Each square
// is 1 x 1.  One corner of the board is (0, 0) and the board stretches out
// along positive x and positive z.  It rests on the xz plane.  I put a
// spotlight at (4, 3, 7).
class Checkerboard {
    int displayListId;
    int width;
    int depth;
public:
    Checkerboard(int width, int depth) : width(width), depth(depth) {}
    double centerx() { return width / 2; }
    double centerz() { return depth / 2; }
    void create() {
        displayListId = glGenLists(1);
        glNewList(displayListId, GL_COMPILE);
        GLfloat lightPosition[] = { 4, 3, 7, 1 };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glBegin(GL_QUADS);
        glNormal3d(0, 1, 0);
        for (int x = 0; x < width - 1; x++) {
            for (int z = 0; z < depth - 1; z++) {
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                    (x + z) % 2 == 0 ? CYAN : WHITE);   //체크보드 바닥색을 CYAN으로 변경
                glVertex3d(x, 0, z);
                glVertex3d(x + 1, 0, z);
                glVertex3d(x + 1, 0, z + 1);
                glVertex3d(x, 0, z + 1);
            }
        }
        glEnd();
        glEndList();
    }
    void draw() {
        glCallList(displayListId);
    }
};

// Global variables: a camera, a checkerboard and some balls.
Checkerboard checkerboard(8, 8);
Camera camera;
Ball balls[] = {                //ball들을 추가.
  Ball(1, GREEN, 7, 6, 1),      //주전자
  Ball(1.5, MAGENTA, 6, 3, 4),  // 공
  Ball(0.4, WHITE, 5, 1, 7),    //주전자
  Ball(0.2,BLUE,7,6,1),         // 공
  Ball(0.2,YELLOW,7,6,2),       //주전자
  Ball(0.2,CYAN,7,6,3)          // 공
};


// Application-specific initialization: Set up global lighting parameters
// and create display lists.
void init() {
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    checkerboard.create();
}

// Draws one frame, the checkerboard then the balls, from the current camera
// position.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
        checkerboard.centerx(), 0.0, checkerboard.centerz(),
        0.0, 1.0, 0.0);
    checkerboard.draw();
    for (int i = 0; i < sizeof balls / sizeof(Ball); i++) {
        if (i % 2 == 0)
            balls[i].update();     //초록,하양,노랑 Teapot은 위아래로 bounding 하면서 x축으로 한칸씩 왔다갔다함.
        else
            balls[i].update2_X();   //보라,파랑,하늘 구체는 x축으로 정해진 범위 내로 bounding
    }
    glFlush();
    glutSwapBuffers();
}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

// Requests to draw the next frame.
void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, v);
}

// Moves the camera according to the key pressed, then ask to refresh the
// display.
void special(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT: camera.moveLeft(); break;
    case GLUT_KEY_RIGHT: camera.moveRight(); break;
    case GLUT_KEY_UP: camera.moveUp(); break;
    case GLUT_KEY_DOWN: camera.moveDown(); break;
    }
    glutPostRedisplay();
}

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(800, 600);
    glutCreateWindow("201713922_이건회_Bouncing Balls");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutTimerFunc(100, timer, 0);
    init();
    glutMainLoop();
}