#ifndef COCKPIT_H_
#define COCKPIT_H_

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "ship.h"

class Cockpit {
    Ship ship;
    int cockpitId;
public:
    Cockpit(Ship ship) : ship(ship) {}
    void create();
    void draw();
};

void Cockpit::create() {
    cockpitId = glGenLists(1);
    glNewList(cockpitId, GL_COMPILE);   //glNewList와 glEndList 를 이용해 그림을 그리는데, 리스트를 사용하면 속도면에서 빠르다는 장점이 있습니다.
    glDisable(GL_LIGHTING);         //gl_LIghting기능을 비활성화
    glColor3f(0.8, 0.8, 0.7);       //color 설정
    glBegin(GL_TRIANGLE_FAN);       //중심을 공유하는 삼각형을 그려준다.
    glVertex3f(0, -1, 0);
    glVertex3f(1, -1, 0);
    for (double x = 1.0; x >= -1.05; x -= 0.05) {
        glVertex3f(x, 20 * cos(x / 10.0) - 20.6, 0);
    }
    glVertex3f(-1, -1, 0);
    glEnd();
    glEnable(GL_LIGHTING);        //gl_Lighting기능 활성화

    glEndList();
}

inline void Cockpit::draw() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glCallList(cockpitId);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

#endif