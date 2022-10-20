#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib, "glaux.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <gl/glut.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include <gl/glaux.h>
#include <process.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

static float zoom = 5.0; //줌 변수
static float eye1 = 0.0, eye2 = 0.0, eye3 = 0.0; // 시점 변환
static int day = 2; //밤/낮 변환

GLUquadricObj* earth;
GLUquadricObj* earth1;
GLuint tex[2]; //텍스쳐 맵핑 변수

int lof = 0, ani = 0; //조명효과, 애니매이션 효과

GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f }; //조명의 위치

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, zoom, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glRotatef(eye1, 1.0, 0.0, 0.0);
	glRotatef(eye2, 0.0, 0.0, 1.0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);

	if (lof == 0)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	glEnable(GL_LIGHT0);
	glPushMatrix();
	glRotatef(0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(eye3, 0, 0, 1);

	if (day == 0) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[0]);
		gluSphere(earth, 1.3, 100, 100);
	}
	else if (day == 1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		gluSphere(earth, 1.3, 100, 100);
	}
	else if (day == 2) {
		glDisable(GL_TEXTURE_2D);
		glutWireSphere(1.3, 30, 30);
	}
	glPopMatrix();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void MyReshape(int x, int y) {
	glViewport(0, 0, (GLsizei)x, (GLsizei)y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, (GLdouble)x / (GLdouble)y, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

AUX_RGBImageRec* LoadBMPFile(const char* filename) { // 이미지 읽어오기
	FILE* pFile = NULL;
	if (!filename) return NULL;
	pFile = fopen(filename, "r");

	if (pFile) {
		fclose(pFile);
		return auxDIBImageLoad(filename);
	}
	return NULL;
}

int LoadGLTextures() { //텍스쳐 맵핑
	int i;
	earth = gluNewQuadric();
	earth1 = gluNewQuadric();
	gluQuadricDrawStyle(earth, GLU_FILL);
	gluQuadricTexture(earth, GL_TRUE);
	gluQuadricDrawStyle(earth1, GLU_FILL);
	gluQuadricTexture(earth1, GL_TRUE);

	AUX_RGBImageRec* textureimg[2];
	int status = FALSE;
	memset(textureimg, 0, sizeof(void*) * 1);

	if ((textureimg[0] = LoadBMPFile("KG3.bmp")) && (textureimg[1] = LoadBMPFile("KGU5.bmp"))) {
		glGenTextures(2, &tex[0]);

		for (i = 0; i < 2; i++) {
			glBindTexture(GL_TEXTURE_2D, tex[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, textureimg[i]->sizeX, textureimg[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureimg[i]->data);
		}
	}
	else return FALSE;

	for (i = 0; i < 2; i++) {
		if (textureimg[i]) {
			if (textureimg[i]->data) free(textureimg[i]->data);
			free(textureimg[i]);
		}
		else return FALSE;
	}

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return TRUE;
}

void InitLight() { //조명
	//조명 속성
	GLfloat sLight[4] = { 0.9, 0.9, 0.9,1.0 };
	GLfloat whiteLight[4] = { 0.3,0.3, 0.3, 0.33 };
	GLfloat MySpotAngle[] = { 90.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specref[] = { 1.0, 1.0, 1.0, 1.0 };

	//지구 속성	
	GLfloat material_ambient[] = { 0.4,0.4,0.4,1.0 };
	GLfloat material_diffuse[] = { 0.9,0.9,0.9,1.0 };
	GLfloat material_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyTimer(int value) {//애니매이션
	if (ani) {
		eye3 = eye3 + 3;
		glutPostRedisplay();
		glutTimerFunc(10, MyTimer, 1);
	}
}

void MyMainMenu(int entryID) {//메뉴콜백
	switch (entryID) {
	case 1:
		if (lof == 0)
			lof = 1;
		else
			lof = 0;
		break;

	case 2:
		if (ani == 0)
			ani = 1;
		else
			ani = 0;
		glutTimerFunc(10, MyTimer, 1);
		break;

	case 3:
		exit(0);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void MySubMenu(int entryID) {//서브메뉴
	if (entryID == 1)
		day = 0;
	else if (entryID == 2)
		day = 1;
	else if (entryID == 3)
		day = 2;
	glutPostRedisplay();
}

void keyboard(int Key, int x, int y) {
	switch (Key) {

	case GLUT_KEY_PAGE_DOWN: //줌 축소
		zoom = zoom + 1;
		break;

	case GLUT_KEY_PAGE_UP: //줌 확대
		zoom = zoom - 1;
		break;

	case GLUT_KEY_UP:
		eye1 = eye1 + 1.5;
		break;

	case GLUT_KEY_DOWN:
		eye1 = eye1 - 1.5;
		break;

	case GLUT_KEY_LEFT:
		eye2 = eye2 - 1.5;
		break;

	case GLUT_KEY_RIGHT:
		eye2 = eye2 + 1.5;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("컴퓨터공학부 201713922 이건회");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	//메뉴 시작
	GLint MySubMenuID = glutCreateMenu(MySubMenu);
	glutAddMenuEntry("Day", 1);
	glutAddMenuEntry("Night", 2);
	glutAddMenuEntry("Wire Frame", 3);
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddSubMenu("Shape", MySubMenuID);
	glutAddMenuEntry("Light On/Off", 1);
	glutAddMenuEntry("Animation", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//메뉴 끝
	LoadGLTextures();
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(keyboard);
	glutMainLoop();
	return 0;
}
