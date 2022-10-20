#define _CRT_SECURE_NO_WARNINGS
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <windows.h>
#include <math.h>
#include <iostream>


#define WIDTH 800
#define HEIGHT 600
#define AXIS_SIZE 60

void SetupRC();
GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info);
void RenderScene(void);
void ChangeSize(int w, int h);
void Keyboard(unsigned char key, int x, int y);

float xRot = 0.0f;
float yRot = 0.0f;
float zRot = 0.0f;


GLubyte* pBytes; // 데이터를 가리킬 포인터
BITMAPINFO* info; // 비트맵 헤더 저장할 변수


GLuint textures[6];




int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("컴퓨터공학부 201713922 이건회");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutKeyboardFunc(Keyboard);

	SetupRC();
	glutMainLoop();

	return 0;
}

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);  // 은면 제거
	glFrontFace(GL_CCW);   // 앞면 설정 
	glEnable(GL_CULL_FACE);  // 내부는 잘라낸다 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // 배경색 설정

}

void RenderScene(void)
{

	glGenTextures(6, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	pBytes = LoadDIBitmap("KGU.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, textures[1]);
	pBytes = LoadDIBitmap("KGU.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, textures[2]);
	pBytes = LoadDIBitmap("KGU.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, textures[3]);
	pBytes = LoadDIBitmap("KGU.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, textures[4]);
	pBytes = LoadDIBitmap("KGU.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glBindTexture(GL_TEXTURE_2D, textures[5]);
	pBytes = LoadDIBitmap("KGU.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);




	glEnable(GL_TEXTURE_2D);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glDisable (GL_CULL_FACE);

	glPushMatrix();
	glLoadIdentity();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(zRot, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	{

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		//앞면
	  //  glColor3f(1.0f,1.0f,0.0f);  // Yellow
		glTexCoord2f(1, 1);
		glVertex3f(50.0, 50.0, 50.0f);
		//  glColor3f(1.0f,0.0,1.0f);  // Magenta
		glTexCoord2f(0, 1);
		glVertex3f(-50.0, 50.0, 50.0f);
		//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
		glTexCoord2f(0, 0);
		glVertex3f(-50.0, -50.0, 50.0f);
		//  glColor3f(0.0f,0.0f,1.0f);  // Blue
		glTexCoord2f(1, 0);
		glVertex3f(50.0, -50.0, 50.0f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	{
		//뒷면
	  //  glColor3f(1.0f,1.0f,1.0f);  // White
		glTexCoord2f(1, 1);
		glVertex3f(-50.0, 50.0, -50.0);
		//  glColor3f(0.0f,1.0f,0.0f);  // Green
		glTexCoord2f(0, 1);
		glVertex3f(50.0, 50.0, -50.0);
		//  glColor3f(1.0f,0.0f,0.0f);  // Red
		glTexCoord2f(0, 0);
		glVertex3f(50.0f, -50.0f, -50.0f);
		//  glColor3f(0.0f,0.0f,0.0f);  // Black
		glTexCoord2f(1, 0);
		glVertex3f(-50.0, -50.0, -50.0);

	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	{
		//윗면
	  //  glColor3f(1.0f,0.0,1.0f);  // Magenta
		glTexCoord2f(1, 1);
		glVertex3f(-50.0, 50.0, 50.0f);
		//  glColor3f(1.0f,1.0f,0.0f);  // Yellow
		glTexCoord2f(0, 1);
		glVertex3f(50.0, 50.0, 50.0f);
		//  glColor3f(0.0f,1.0f,0.0f);  // Green
		glTexCoord2f(0, 0);
		glVertex3f(50.0, 50.0, -50.0);
		//  glColor3f(1.0f,1.0f,1.0f);  // White
		glTexCoord2f(1, 0);
		glVertex3f(-50.0, 50.0, -50.0);

	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[3]);

	glBegin(GL_QUADS);
	{
		//아랫면
	  //  glColor3f(1.0f,0.0f,0.0f);  // Red
		glTexCoord2f(1, 1);
		glVertex3f(50.0f, -50.0f, -50.0f);
		//  glColor3f(0.0f,0.0f,0.0f);  // Black
		glTexCoord2f(0, 1);
		glVertex3f(50.0, -50.0, 50.0f);
		//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
		glTexCoord2f(0, 0);
		glVertex3f(-50.0, -50.0, 50.0f);
		//  glColor3f(0.0f,0.0f,1.0f);  // Blue
		glTexCoord2f(1, 0);
		glVertex3f(-50.0, -50.0, -50.0);

	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[4]);

	glBegin(GL_QUADS);
	{
		//왼면
	  //  glColor3f(1.0f,0.0,1.0f);  // Magenta
		glTexCoord2f(1, 1);
		glVertex3f(-50.0, 50.0, 50.0f);
		//  glColor3f(1.0f,1.0f,1.0f);  // White
		glTexCoord2f(0, 1);
		glVertex3f(-50.0, 50.0, -50.0);
		//  glColor3f(0.0f,0.0f,0.0f);  // Black
		glTexCoord2f(0, 0);
		glVertex3f(-50.0, -50.0, -50.0);
		//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
		glTexCoord2f(1, 0);
		glVertex3f(-50.0, -50.0, 50.0f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	{
		//오른면
	  //  glColor3f(0.0f,1.0f,0.0f);  // Green
		glTexCoord2f(1, 1);
		glVertex3f(50.0, 50.0, -50.0);
		//  glColor3f(1.0f,1.0f,0.0f);  // Yellow
		glTexCoord2f(0, 1);
		glVertex3f(50.0, 50.0, 50.0f);
		//  glColor3f(0.0f,0.0f,1.0f);  // Blue
		glTexCoord2f(0, 0);
		glVertex3f(50.0, -50.0, 50.0f);
		//  glColor3f(1.0f,0.0f,0.0f);  // Red
		glTexCoord2f(1, 0);
		glVertex3f(50.0f, -50.0f, -50.0f);
	}
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	// h가 0일 때
	if (h == 0)
		h = 1;

	// 윈도우의 폭과 넓이 설정
	glViewport(0, 0, w, h);

	//원근투영 사용
	GLfloat fAspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fAspect = (float)w / (float)h;
	gluPerspective(60.0, fAspect, 1.0, 500.0);
	glTranslatef(0.0f, 0.0f, -300.0f);
	glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(20.0f, 0.0f, 1.0f, 0.0f);

	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutSwapBuffers();

}


GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE* fp;
	GLubyte* bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char*)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x') {        // x축 10도회전
		xRot += 10.0f;
		glutPostRedisplay();
	}

	if (key == 'X') {        // x축 10도회전
		xRot += 10.0f;
		glutPostRedisplay();
	}
	if (key == 'y') {        // y축 10도회전
		yRot += 10.0f;
		glutPostRedisplay();
	}

	if (key == 'Y') {        // y축 10도회전
		yRot += 10.0f;
		glutPostRedisplay();
	}
	if (key == 'z') {        // z축 10도회전
		zRot += 10.0f;
		glutPostRedisplay();
	}

	if (key == 'Z') {        // z축 10도회전
		zRot += 10.0f;
		glutPostRedisplay();
	}

}