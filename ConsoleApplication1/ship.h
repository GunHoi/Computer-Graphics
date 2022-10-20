// A simplified spaceship that you can use in flybys, flight simulators and
// other 3D programs.  A ship has a position, an orientation and a speed		//배는 위치,방향,속도를 가지고 있ㅇㅏ.
// The position is simply a point.  The orientation is given by three			//배의 위치는 단순한 점
// UNIT vectors: (1) forward, the vector along which the ship is currently		//방향은 3가지 벡터로 제공됨
// moving, (2) up, a vector perpendicular to forward that describes which		// 1. 현재 배가 이동중인 벡터
// direction is "up" to someone sitting in the ship, and (3) right, which		// 2. 어떤 방향이 "위" 방향인지를 나타내는 직각 벡터
// is really just the cross product of forward and up that we store to			// 3. 계산을 단순화 하기 위해 forwawrd와 직각벡터의 cross product인 오른쪽 벡터
// simplify most of the calculations.  The speed of the ship is simply the		//배의 속도는 단순히 fly()가 호출되는 거리.
// distance that the ship moves every time fly() is called.
//
// The public members of the Ship class are:
//
// Ship()           initialize the ship so that it is located at the		//배의 위치를 초기화(출발지 0,0,0)
//                  origin, is travelling in the direction <0, 0, -1>		//-z축을 따라 0,1,0 방향으로 이동
//                  that is, along the -z axis, has up vector <0, 1, 0>
//                  (and therefore right = <1, 0, 0>) and has initial
//                  speed 0.01.
// getPosition()    return the current position of the ship.				//배의 현재 위치 반환
// teleport(p)      move the ship to absolute position p, but preserve		//절대위치 p로 배를 이동시키지만, 방향과 속도는 보존
//                  the orientation and speed.
// getDirection()   return the current direction of the ship.				//배의 현재 방향을 반환
// getVertical()    return the "up" vector of the ship.						//배의 up 벡터 반환
// pitch(theta)     reorient the ship so that it is rising theta radians;	//배의 방향을 바꾸어서 세타 라디안을 떠오르게 한다
//                  technically, rotate forward and up theta radians		//기술적으로 오른쪽을 중심으로 forward,up 세타 라디안 회전
//                  around right.
// roll(theta)      rotate up and right theta radians around forward.		//forward을 중심으로 up, right 세타 라디안 회전
// yaw(theta)       rotate forward and right theta radians around up.		//up을 중심으로 forward,right 세타 라디안 회전
// getSpeed()       return the current speed.								//현재 속도 반환
// setSpeed(s)      set the current speed to s.								//현재 속도 설정

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