#ifndef RONO_CENTER_HPP
#define RONO_CENTER_HPP

#include "encoder.hpp"
#include "circuit/button_info.hpp"
#include "circuit/r1350n/r1350n.hpp"
#include "util.hpp"

class roboCenter:public Coord{
private:
	Encoder *enc0;
	R1350n *gyro;
	ButtonInfo *resetSw;
	unsigned int time;
	float x;
	float y;
	float z;
	float angle;
	float initAngle;
	float value;
	float oldValue;
	float initValue;
	float velocity;
	float initAccx;
	//float velocity;
	float encToServo;
public:
	roboCenter(Encoder &enc,R1350n &gyroPin,ButtonInfo &resetPin);
	int setup();
	float getAngle();
	float getVelocity(){return velocity;};
	float getX();
	float getY();
	void cycle();
	void accCycle();
};

#endif
