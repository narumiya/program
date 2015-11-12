#ifndef MOVE_HPP
#define MOVE_HPP

#include "layer_driver/circuit/mini_md_1.0/mini_md.hpp"
#include "circuit/servo.hpp"
#include "layer_driver/base/analog.hpp"
#include "layer_driver/circuit/button_info.hpp"
#include "pin.hpp"
extern "C"{
#include "my_else_calculation.h"
}
//#define INITANGLE -75.0

class Move{
private:
	enum{
		NONSENSOR,
		USESENSOR
	};

	MiniMD *md[2];
	Servo *servo;
	unsigned int time;
	Analog *an[5];
	ButtonInfo *startSw;
	Led1 led1;
	Led2 led2;
	Led3 led3;
	bool startFlag;
	int mode;
	bool useServo;
	float adData[5];
	float roboAngle;
	unsigned int countWhile;
	unsigned int countAverage;
	float white;
	float other;
	float middle;
	bool calibraFlag;
	float initAngle;
public:
	Move(MiniMD &l,MiniMD &r,ButtonInfo &swPin);
	Move(MiniMD &l,MiniMD &r,Analog &a0,Analog &a1,Analog &a2,Analog &a3,Analog &a4,ButtonInfo &swPin);
	Move(Analog &a0,Analog &a1,Analog &a2,Analog &a3,Analog &a4,ButtonInfo &swPin,Servo &servo);
	int calibra();
	int setup();
	void cycle();
	void setAngle(float angle){roboAngle=angle;}
	void setDuty(float straight,float rotat);
	void TPR105Cycle();
	void printAdValue();
	float rotationOutput(pid_gain_t gain);
};

#endif
