// A simplified spaceship that you can use in flybys, flight simulators and
// other 3D programs.  A ship has a position, an orientation and a speed		//��� ��ġ,����,�ӵ��� ������ �֤���.
// The position is simply a point.  The orientation is given by three			//���� ��ġ�� �ܼ��� ��
// UNIT vectors: (1) forward, the vector along which the ship is currently		//������ 3���� ���ͷ� ������
// moving, (2) up, a vector perpendicular to forward that describes which		// 1. ���� �谡 �̵����� ����
// direction is "up" to someone sitting in the ship, and (3) right, which		// 2. � ������ "��" ���������� ��Ÿ���� ���� ����
// is really just the cross product of forward and up that we store to			// 3. ����� �ܼ�ȭ �ϱ� ���� forwawrd�� ���������� cross product�� ������ ����
// simplify most of the calculations.  The speed of the ship is simply the		//���� �ӵ��� �ܼ��� fly()�� ȣ��Ǵ� �Ÿ�.
// distance that the ship moves every time fly() is called.
//
// The public members of the Ship class are:
//
// Ship()           initialize the ship so that it is located at the		//���� ��ġ�� �ʱ�ȭ(����� 0,0,0)
//                  origin, is travelling in the direction <0, 0, -1>		//-z���� ���� 0,1,0 �������� �̵�
//                  that is, along the -z axis, has up vector <0, 1, 0>
//                  (and therefore right = <1, 0, 0>) and has initial
//                  speed 0.01.
// getPosition()    return the current position of the ship.				//���� ���� ��ġ ��ȯ
// teleport(p)      move the ship to absolute position p, but preserve		//������ġ p�� �踦 �̵���Ű����, ����� �ӵ��� ����
//                  the orientation and speed.
// getDirection()   return the current direction of the ship.				//���� ���� ������ ��ȯ
// getVertical()    return the "up" vector of the ship.						//���� up ���� ��ȯ
// pitch(theta)     reorient the ship so that it is rising theta radians;	//���� ������ �ٲپ ��Ÿ ������ �������� �Ѵ�
//                  technically, rotate forward and up theta radians		//��������� �������� �߽����� forward,up ��Ÿ ���� ȸ��
//                  around right.
// roll(theta)      rotate up and right theta radians around forward.		//forward�� �߽����� up, right ��Ÿ ���� ȸ��
// yaw(theta)       rotate forward and right theta radians around up.		//up�� �߽����� forward,right ��Ÿ ���� ȸ��
// getSpeed()       return the current speed.								//���� �ӵ� ��ȯ
// setSpeed(s)      set the current speed to s.								//���� �ӵ� ����

#ifndef SHIP_H_
#define SHIP_H_

#include "geometry.h"

class Ship {
	Point position;
	Vector forward, up, right;
	double speed;
public:
	Ship(Point initialPosition = Point(0, 0, 0));
	Point getPosition() { return position; }
	void fly() { position += speed * forward; }
	void teleport(Point newPosition) { position = newPosition; }
	Vector getDirection() { return forward; }
	Vector getVertical() { return up; }
	void pitch(double angle);
	void roll(double angle);
	void yaw(double angle);
	double getSpeed() { return speed; }
	void setSpeed(double newSpeed) { speed = newSpeed; }
};

inline Ship::Ship(Point initialPosition) :
	position(initialPosition),
	forward(0, 0, -1),
	up(0, 1, 0),
	right(1, 0, 0),
	speed(0.01)
{
}

inline void Ship::pitch(double angle) {
	forward = unit(forward * cos(angle) + up * sin(angle));
	up = right.cross(forward);
}

inline void Ship::roll(double angle) {
	right = unit(right * cos(angle) + up * sin(angle));
	up = right.cross(forward);
}

inline void Ship::yaw(double angle) {
	right = unit(right * cos(angle) + forward * sin(angle));
	forward = up.cross(right);
}

#endif