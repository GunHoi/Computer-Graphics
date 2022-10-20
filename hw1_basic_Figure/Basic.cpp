#include <GL/glut.h> /* includes gl.h glu.h */

GLvoid drawScene(GLvoid);
void main(int argc, char* argv[])
{
	// 초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정
	glutInitWindowSize(250, 250); // 윈도우의 크기 지정
	glutCreateWindow("컴퓨터공학부 201713922 이건회"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glutWireTeapot(0.5);				//주전자

	glColor4f(1, 0, 0, 1);
	glPushMatrix();
	glTranslatef(-0.6, 0.6, 0.0);		//좌측 상단
	glutWireCone(0.3, 0.6, 20, 10);		//구체
	glPopMatrix();

	glColor4f(0, 1, 0, 0);
	glPushMatrix();
	glTranslatef(0.6, 0.6, 0.0);		//우측 상단
	glutWireSphere(0.3, 20, 20);	//원뿔
	glPopMatrix();

	glColor4f(0, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0.6, -0.6, 0.0);		//우측 하단
	glutWireTorus(0.1,0.2,20, 20);	//도넛
	glPopMatrix();

	glColor4f(1, 1, 0, 0);
	glPushMatrix();
	glTranslatef(-0.6, -0.6, 0.0);		//좌측 하단
	glutWireCube(0.4);	//정육면체
	glPopMatrix();

	glFlush(); // 화면에 출력하기
}