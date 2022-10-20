//밑변 ABCD / 높이 H	(0.<-생략) 5=0.5 // 25 = 0.25
//a(0,0,0)	  b(0,0,5)	c(5,5,0)	d(5,0,0)	H(5,25,5)

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
	
	glBegin(GL_POLYGON);
		//LEFT
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);	//blue
		glVertex3f(0.0f, 0.0f, 0.0f);	//a
		glVertex3f(0.0f, 0.0f, 0.5f);	//b
		glVertex3f(0.25f, 0.5f, 0.25f);	//h
		
		//FRONT
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);	//red
		glVertex3f(0.0f, 0.0f, 0.5f);	//b
		glVertex3f(0.5f, 0.0f, 0.5f);	//c
		glVertex3f(0.25f, 0.5f, 0.25f);	//h
		
		//RIGHT
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);	//green
		glVertex3f(0.5f, 0.0f, 0.5f);	//c
		glVertex3f(0.5f, 0.0f, 0.0f);	//d
		glVertex3f(0.25f, 0.5f, 0.25f);	//h
		
		//BACK
		glColor4f(1.0f, 1.0f, 0.0f, 1.0f);	//red+green
		glVertex3f(0.0f, 0.0f, 0.0f);	//a
		glVertex3f(0.5f, 0.0f, 0.0f);	//d
		glVertex3f(0.25f, 0.5f, 0.25f);	//h
		
		//BOTTOM
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);	//green+blue
		glVertex3f(0.0f, 0.0f, 0.0f);	//a
		glVertex3f(0.0f, 0.0f, 0.5f);	//b
		glVertex3f(0.5f, 0.0f, 0.5f);	//c
		glVertex3f(0.5f, 0.0f, 0.0f);	//d
	glEnd();
	glFlush(); // 화면에 출력하기
}