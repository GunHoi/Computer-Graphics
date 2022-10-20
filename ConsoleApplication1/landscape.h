// A simple landscape class.  A landscape is essentially an elevation grid		//wireframe, solid 형태로 그릴 수 있음.
// which can be drawn in wireframe or as a solid.  Landscape elevations are		//Random Midpoint Displacement 기술을 이용한다.
// set using the Random Midpoint Displacement technique.
//
// Landscape(m, n)      (constructor) sets the x and z bounds of the landscape	//x와 z의 경계를 설정하여 객체가 점집합 (x,y,z)가 되도록한다.
//                      so that the constructed object will be a set of points	//여기서 x와 z는 정수이고 , 0<=x<m / 0<=z<n , y는 undefined로 설정
//                      (x, y, z) where x and z are integers and 0 <= x < m
//                      and 0 <= z < n, and y is undefined.
// create(rug)          assigns random elevations based on the ruggedness		//고도를 ruggedness confficient rug에 기반하여 랜덤하게 할당
//                      coefficient rug (rug == 0 defines the completely		//rug ==0 -> 완전히 평평한 그리드
//                      flat grid).  This routine also generates OpenGL
//                      display lists for efficient drawing.
// draw()               draws the landscape using a fixed coloring scheme.		//고정된 색으로 풍경 표현
// drawWireFrame()      draws a wireframe representation of the landscape.		//wire frame으로 풍경 표현

#ifndef LANDSCAPE_H_
#define LANDSCAPE_H_

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <cmath>
#include <cstdlib>

class Landscape {
	int rows;
	int columns;
	double highest;                         // the highest point in the mesh
	std::vector< std::vector<double>  > d;  // the grid of elevations
	int solidId;                            // display list id for solid mesh
	int wireFrameId;                        // display list id for wire mesh
	static double unused;
	void generate(int x1, int y1, int x2, int y2, double rug);
	double scale(double x) { return x * (((double)rand() / RAND_MAX) - 0.5); }
	void drawTriangle(int x1, int z1, int x2, int z2, int x3, int z3);
	void vertex(double x, double z);
	void createSolidDisplayList();
	void createWireFrameDisplayList();
public:
	Landscape(int rows, int columns);
	void create(double rug);
	void draw() { glCallList(solidId); }
	void drawWireFrame() { glCallList(wireFrameId); }
};

#endif