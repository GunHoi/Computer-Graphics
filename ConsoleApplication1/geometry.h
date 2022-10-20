// Classes and utility functions for three-dimensional Points, Vectors,
// Planes, and Rays.

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cmath>

class Point;
class Vector;
class Plane;
class Ray;

// Comparing doubles for equality is useless; allow clients to supply a
// tolerance.
inline bool equal(double x, double y, double epsilon = 0.000001) {
	return fabs(x - y) <= epsilon;
}

// A class for 3-D Vectors.
//
//   v.i, v.j, v.k              Components of vector v								//벡터 v의 (성분)좌표
//   Vector(i, j, k)            Construct from components							//벡터(i,j,k)의 (성분)좌표 생성
//   Vector(p)                  Construct from a point								//벡터(p) 생성
//   u + v, u += v              Vector addition										//벡터의 덧셈
//   u - v, u -= v              Vector subtraction									//벡터의 뺄셈
//   -v                         <0, 0, 0> - v										
//   u.dot(v)                   Dot product of u and v								//u와 v의 곱
//   u.cross(v)                 Cross product of u and v							//u와 v의 교차곱
//   v * c, c * v, v *= c       Multiplication of a vector and a scalar				//벡터와 스칼라의 곱
//   v / c, v /= c              Division of a vector by a scalar					//벡터를 스칼라로 나눔
//   v.magnitude()              The length of v										//v의 길이
//   unit(v)                    The vector of length 1 in the direction of v		//단위벡터 v
//   normalize(v)               Changes v to unit(v)								//정규화 v를 단위벡터v로 바꿈
//   cosine(u, v)               The cosine of the angle from u to v					//u에서 v까지 코사인각
//   u.isPerpendicularTo(v)     Whether u is almost perpendicular to v				//수직인지?
//   u.isParallelTo(v)          Whether u is almost parallel to v					//평행인지?
//   u.projectionOnto(v)        The projection of u onto v							//투영
//   u.reflectionAbout(v)       The mirror image of u over v						//반사

class Vector {
public:
	double i, j, k;
	Vector(double i = 0, double j = 0, double k = 0) : i(i), j(j), k(k) {}
	Vector(Point p);
	Vector operator +(Vector v) { return Vector(i + v.i, j + v.j, k + v.k); }
	Vector& operator +=(Vector v) { i += v.i; j += v.j; k += v.k; return *this; }
	Vector operator -(Vector v) { return Vector(i - v.i, j - v.j, k - v.k); }
	Vector& operator -=(Vector v) { i -= v.i; j -= v.j; k -= v.k; return *this; }
	Vector operator -() { return Vector(-i, -j, -k); }
	double dot(Vector v) { return i * v.i + j * v.j + k * v.k; }
	Vector cross(Vector);
	Vector operator *(double c) { return Vector(i * c, j * c, k * c); }
	friend Vector operator *(double c, Vector v) { return v * c; }
	Vector& operator *=(Vector v) { i *= v.i; j *= v.j; k *= v.k; return *this; }
	Vector operator /(double c) { return Vector(i / c, j / c, k / c); }
	Vector& operator /=(double c) { i /= c; j /= c; k /= c; return *this; }
	double magnitude() { return sqrt(this->dot(*this)); }
	friend Vector unit(Vector v) { return v / v.magnitude(); }
	friend void normalize(Vector& v) { v /= v.magnitude(); }
	friend double cosine(Vector u, Vector v) { return unit(u).dot(unit(v)); }
	bool isPerpendicularTo(Vector v) { return equal(this->dot(v), 0); }
	bool isParallelTo(Vector v) { return equal(cosine(*this, v), 1.0); }
	Vector projectionOnto(Vector v) { return this->dot(unit(v)) * unit(v); }
	Vector reflectionAbout(Vector v) { return 2 * projectionOnto(v) - *this; }
};

// A class for 3-D Points.
//
//   p.x, p.y, p.z              Components (coordinates) of point p		//점 p의 성분(좌표)
//   p + v, p += v              Add a point to a vector					//벡터에 점 추가
//   p - q                      The vector from q to p					//p - q 벡터
//   p.distanceTo(q)            The distance between p and q			// p와 q 사이 거리(=벡터의 크기)
//   p.distanceTo(P)            The distance between p and the plane P	//p와 평면 P사이 거리(=벡터의 시작점)

class Point {
public:
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
	Point operator +(Vector v) { return Point(x + v.i, y + v.j, z + v.k); }
	Point& operator +=(Vector v) { x += v.i; y += v.j; z += v.k; return *this; }
	Vector operator -(Point p) { return Vector(x - p.x, y - p.y, z - p.z); }
	double distanceTo(Point p) { return (p - *this).magnitude(); }
	double distanceTo(Plane);
};

// A class for 3-D planes.
//
//   P.a, P.b, P.c, P.d         The components of plane P (P is the set of		//평면 P의 성분에 대한 모든 점들의 집합
//                              all points (x, y, z) for which P.a * x +
//                              P.b * y + P.c * z + P.d = 0)
//   Plane(a, b, c d)           Construct from components		
//   Plane(p1, p2, p3)          Construct by giving three points on the plane	//평면에 점 3개를 주어 생성
//                              (may fail if the points are collinear): the		//평면의 노선은 오른손 법칙에 의해 얻어짐.
//                              plane's normal is obtained by a right hand
//                              rule: curl your right hand ccw around p1 to
//                              p2 to p3 then your thumb orients the normal
//   P.normal()                 The vector <P.a, P.b, P.c>

class Plane {
public:
	double a, b, c, d;
	Plane(double a = 0, double b = 0, double c = 1, double d = 0);
	Plane(Point p1, Point p2, Point p3);
	Vector normal() { return Vector(a, b, c); }
};

// A class for 3-D rays.
//
//   r.origin, r.direction      The components of the ray r		//광성 r의 성분
//   Ray(origin, direction)     Construct from components		
//   r(u)                       The point on r at distance u * |r.direction|		//원점으로 부터 거리 u*|r.direction|에 있는 점
//                              from r.origin.

class Ray {
public:
	Point origin;
	Vector direction;
	Ray(Point origin, Vector direction) : origin(origin), direction(direction) {}
	Point operator()(double u) { return origin + u * direction; }
};

// Bodies of inlined operations.

inline Vector::Vector(Point p) : i(p.x), j(p.y), k(p.z) {
}

inline Vector Vector::cross(Vector v) {
	return Vector(j * v.k - k * v.j, k * v.i - i * v.k, i * v.j - j * v.i);
}

inline Plane::Plane(double a, double b, double c, double d) :
	a(a), b(b), c(c), d(d)
{
}

inline double Point::distanceTo(Plane P) {
	return fabs(P.a * x + P.b * y + P.c * z + P.d) / P.normal().magnitude();
}

inline Plane::Plane(Point p1, Point p2, Point p3) {
	Vector n = (p2 - p1).cross(p3 - p1);
	a = n.i;
	b = n.j;
	c = n.k;
	d = -(Vector(p1).dot(n));
}

#endif