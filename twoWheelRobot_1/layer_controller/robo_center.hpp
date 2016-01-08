#ifndef RONO_CENTER_HPP
#define RONO_CENTER_HPP

#include "encoder.hpp"
#include "circuit/button_info.hpp"
#include "circuit/r1350n/r1350n.hpp"
#include "util.hpp"

class RoboCenter:public Coord{
private:
	Encoder *enc0;
	R1350n *gyro;
	ButtonInfo *resetSw;
	unsigned int time;
	float cx;
	float cy;
	float x;
	float y;
	float z;
	float def;
	float angle;
	float startAngle;
	float initAngle;
	float value;
	float oldValue;
	float initValue;
	float velocity;
	float initAccx;
	//float velocity;
	float encToServo;
public:
	RoboCenter(Encoder &enc,R1350n &gyroPin,ButtonInfo &resetPin);
	int setup();
	float getAngle();
	float getVelocity(){return velocity;};
	float getX();
	float getY();
	void setAngle(float value){startAngle=value;};
	void setX(float value){cx=value;};
	void setY(float value){cy=value;};
	float getEncCnt(){return def;};
	float getSlope();
	int getSlopeCount();
	void cycle();
	void accCycle();
	void reset();
	void reset(float x, float y);
};

#endif