#include <GL/glut.h>


float vel = 10.0f;
float vel2 = 10.0f;
float vel3 = 10.0f;
float X, C, D = 0.0f;
float A, B;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON); // 1번째 장애물
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-100.0f + X, 80.0f, 0.0f);
	glVertex3f(-90.0f + X, 80.0f, 0.0f);
	glVertex3f(-90.0f + X, 70.0f, 0.0f);
	glVertex3f(-100.0f + X, 70.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON); // 두번째 장애물
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(-100.0f + C, 40.0f, 0.0f);
	glVertex3f(-80.0f + C, 40.0f, 0.0f);
	glVertex3f(-80.0f + C, 30.0f, 0.0f);
	glVertex3f(-100.0f + C, 30.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON); // 세번째 장애물
	glColor3f(0.0, 0.0, 0.1);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-10.0f + D, 10.0f, 0.0f);
	glVertex3f(10.0f + D, 10.0f, 0.0f);
	glVertex3f(10.0f + D, -10.0f, 0.0f);
	glVertex3f(-10.0f + D, -10.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON); // 닿으면 끝
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(100.0f, 100.0f, 0.0f);
	glVertex3f(-100.0f, 100.0f, 0.0f);
	glVertex3f(-100.0f, 90.0f, 0.0f);
	glVertex3f(100.0f, 90.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES); //비행기
	glVertex3f(0.0f + B, -95.0f + A, 0.0f);
	glVertex3f(-5.0f + B, -100.0f + A, 0.0f);
	glVertex3f(5.0f + B, -100.0f + A, 0.0f);
	glEnd();
	glFlush();
}
void MyReshape(int NewWidth, int NewHeight) {
	GLfloat nRange = 100.0f;
	if (NewHeight == 0) NewHeight = 1;
	glViewport(0, 0, NewWidth, NewHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (NewWidth <= NewHeight)
		glOrtho(-nRange, nRange, -nRange * NewHeight / NewWidth,
			nRange * NewHeight / NewWidth, -nRange, nRange);
	else
		glOrtho(-nRange * NewWidth / NewHeight, nRange * NewWidth / NewHeight, -nRange,
			nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
}

void MySpecial(int key, int X, int Y) {
	if (A == 185) {
		exit(0);
	}
	if (key == GLUT_KEY_UP) {
		A += 5.0f;
	}
	if (key == GLUT_KEY_DOWN) {
		A -= 5.0f;
	}
	if (key == GLUT_KEY_LEFT) {
		B -= 5.0f;
	}
	if (key == GLUT_KEY_RIGHT) {
		B += 5.0f;
	}
}

void MyTimer(int Value) {
	D = D + vel;
	if ((D > 80 && vel > 0) || (D < -80 && vel <= 0)) vel *= -1;
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1); //세번째 장애물 타이머
}
void MyTimer2(int Value) {
	X = X + vel2;
	if ((X > 180 && vel2 > 0) || (X < 10 && vel2 < 0))
		vel2 *= -1;

	C = C + vel3;
	if ((C > 170 && vel3 > 0) || (C < 10 && vel3 < 0))
		vel3 *= -1;

	glutPostRedisplay();
	glutTimerFunc(40, MyTimer2, 2);
}
void initFunc() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("네모피하기");
	initFunc();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutSpecialFunc(MySpecial);
	glutTimerFunc(40, MyTimer, 1);
	glutTimerFunc(40, MyTimer2, 2);
	glutMainLoop();
	return 0;
}