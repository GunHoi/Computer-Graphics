// Implementation of the Landscape class.

#include "landscape.h"
#include "geometry.h"

GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat darkGreen[] = { 0.0, 0.5, 0.0, 1.0 };
GLfloat brown[] = { 0.5, 0.5, 0.0, 1.0 };
GLfloat lightBrown[] = { 0.7, 0.7, 0.3, 1.0 };
GLfloat gray[] = { 0.6, 0.6, 0.6, 1.0 };
GLfloat forest[] = { 0.4, 0.8, 0.5, 1.0 };
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };

// Hack.
double Landscape::unused = -10032.4775;

// Constructor.  Ensure the matrix is loaded with the unused constant in    //매트릭스를 사용하지 않는 모든 cell 에 상수가 실려있는지 확인
// every cell.
Landscape::Landscape(int r, int c) : rows(r), columns(c) {
    std::vector<double> nullRow(columns, unused);
    std::vector< std::vector<double> > nullMatrix(rows, nullRow);
    d = nullMatrix;
}

// create() sets the elevations of the four grid corners to 0, generates        //그리드의 모서리의 고도를 0으로 설정하고
// internal elevations remembering the highest point, then generates display    //가장 높은 점을 기억하는 내부 고도를 생성한 후 
// lists.                                                                       // 디스플레이 목록을 생성한다.
void Landscape::create(double rug) {
    int r, c;

    // First put zeros for the elevations around the whole boundary:            //모든 경계 주변의 고도에 대해 0입력
    for (r = 0; r < rows; r++) d[r][0] = d[r][columns - 1] = 0;
    for (c = 0; c < columns; c++) d[0][c] = d[rows - 1][c] = 0;

    // Then put zeros in the corners inset two units and generate               //모서리에 0을 넣고, 직사각형 모양으로 fractal 풍경 생성
    // a fractal landscape in that rectangle.
    d[2][2] = d[2][columns - 3] = d[rows - 3][2] = d[rows - 3][columns - 3] = 0;
    generate(2, 2, rows - 3, columns - 3, rug);

    // Then smooth out the inner fractal so it meets the zeroed out         //내부 fractal이 영점 처리된 가장자리를 충족하도록 평탄화한다.
    // edges.  Make the part just outside the fractal one-third higher      //fractal 바로 바깥 부분을 1/3 더 높게 만들어 해변을 더 평평하게 만든다. 
    // so it simulates flatter beaches.
    for (r = 2; r < rows - 2; r++) d[r][1] = d[r][2] / 3.0;
    for (r = 2; r < rows - 2; r++) d[r][c - 2] = d[r][c - 3] / 3.0;
    for (c = 1; c < columns - 1; c++) d[1][c] = d[2][c] / 3.0;
    for (c = 1; c < columns - 1; c++) d[r - 2][c] = d[r - 3][c] / 3.0;

    // Finally it part of the land is underwater make that elevation 0.     //마지막으로 육지의 일부가 물속에 잠겨 고도가 0이된다.    
    highest = 0.0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (d[i][j] < 0) d[i][j] = 0;
            if (d[i][j] > highest) highest = d[i][j];
        }
    }

    // Generate the display lists.
    solidId = glGenLists(2);
    wireFrameId = solidId + 1;
    createSolidDisplayList();
    createWireFrameDisplayList();
}

// Simple math for random midpoint displacement.
void Landscape::generate(int x1, int y1, int x2, int y2, double rug) {
    int x3 = (x1 + x2) / 2;
    int y3 = (y1 + y2) / 2;
    if (y3 < y2) {
        if (d[x1][y3] == unused) {
            d[x1][y3] = (d[x1][y1] + d[x1][y2]) / 2 + scale(rug * (y2 - y1));
        }
        d[x2][y3] = (d[x2][y1] + d[x2][y2]) / 2 + scale(rug * (y2 - y1));
    }
    if (x3 < x2) {
        if (d[x3][y1] == unused) {
            d[x3][y1] = (d[x1][y1] + d[x2][y1]) / 2 + scale(rug * (x2 - x1));
        }
        d[x3][y2] = (d[x1][y2] + d[x2][y2]) / 2 + scale(rug * (x2 - x1));
    }
    if (x3 < x2 && y3 < y2) {
        d[x3][y3] = (d[x1][y1] + d[x2][y1] + d[x1][y2] + d[x2][y2]) / 4
            + scale(rug * (fabs((double)(x2 - x1)) + fabs((double)(y2 - y1))));
    }
    if (x3 < x2 - 1 || y3 < y2 - 1) {
        generate(x1, y1, x3, y3, rug);
        generate(x1, y3, x3, y2, rug);
        generate(x3, y1, x2, y3, rug);
        generate(x3, y3, x2, y2, rug);
    }
}

 //파란색 - 물 / 녹색 - 잔디 / 갈색 - 산 / 흰색 - 눈
 //고도별로 색상을 정해준다.
void Landscape::vertex(double x, double z) {
    double y = d[(int)x][(int)z];
    double h = y / highest;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
        (h < 0.03) ? forest :
        (h < 0.2) ? green :
        (h < 0.32) ? darkGreen :
        (h < 0.45) ? brown :
        (h < 0.7) ? lightBrown :
        (h < 0.8) ? gray : white);
    glVertex3f(x, y, z);
}

void Landscape::drawTriangle(int x1, int z1, int x2, int z2, int x3, int z3) {
    Point p[] = { Point(x1, d[x1][z1], z1),
                 Point(x2, d[x2][z2], z2),
                 Point(x3, d[x3][z3], z3) };
    Vector normal = unit(Plane(p[0], p[1], p[2]).normal());
    //if (normal.j < 0.0) normal = -normal;
    double h = 0.005;
    if (d[x1][z1] < h && d[x2][z2] < h && d[x3][z3] < h) {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
        glNormal3d(0, 1.0, 0);
        glVertex3dv((GLdouble*)&p[0]);
        glVertex3dv((GLdouble*)&p[1]);
        glVertex3dv((GLdouble*)&p[2]);
    }
    else {
        glNormal3dv((GLdouble*)&normal);
        vertex(x1, z1);
        vertex(x2, z2);
        vertex(x3, z3);
    }
}

// Drawing the landscape as a solid is fairly simple using GL_TRIANGLE_STRIP.   //GL_TRIANGLE_STRIP을 통해 단면으로 풍경을 그린다.
// We generate a display list with a triangle strip on each row.               
void Landscape::createSolidDisplayList() {
    glNewList(solidId, GL_COMPILE);
    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);
    glVertex3f(-200, 0, columns + 200);
    glVertex3f(-200, 0, -200);
    glVertex3f(rows + 200, 0, -200);
    glVertex3f(rows + 200, 0, columns + 200);
    glEnd();

    glBegin(GL_TRIANGLES);
    for (int x = 0; x < rows - 1; x++) {
        for (int z = 0; z < columns - 1; z++) {
            drawTriangle(x, z, x + 1, z, x, z + 1);
            drawTriangle(x + 1, z, x + 1, z + 1, x, z + 1);
        }
    }
    glEnd();
    glEndList();
}

// Generating a display list for a wire frame representation of the     //풍경을 wire frame으로 표현
// landscape is straightforward though a little tedious.
void Landscape::createWireFrameDisplayList() {
    glNewList(wireFrameId, GL_COMPILE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);
    int x, z;
    for (x = 0; x < rows; x++) {
        glBegin(GL_LINE_STRIP);
        glVertex3f(x, d[x][0], 0);
        for (z = 1; z < columns; z++) {
            glVertex3f(x, d[x][z], z);
        }
        glEnd();
    }
    for (z = 0; z < columns; z++) {
        glBegin(GL_LINE_STRIP);
        glVertex3f(0, d[0][z], z);
        for (x = 1; x < rows; x++) {
            glVertex3f(x, d[x][z], z);
        }
        glEnd();
    }
    glEndList();
}