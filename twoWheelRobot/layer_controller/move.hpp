#ifndef MOVE_HPP
#define MOVE_HPP

#include "circuit/servo.hpp"
#include "layer_driver/circuit/button_info.hpp"
#include "layer_controller/robo_center.hpp"
#include "layer_driver/circuit/line_sensor.hpp"
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
	enum{
		CX,//ç¿ïWx
		CY//ç¿ïWy
	};

	Servo *servo;
	LineSensor *line;
	ButtonInfo *startSw;
	RoboCenter *robo;
	Led1 led1;
	Led2 led2;
	Led3 led3;

	bool startFlag;
	int mode;
	int task;
	float adData[5];
	float roboAngle;
	float coord[2][20];
	float startX;
	float startY;
	float servoAngle;
	float servoX;
	float servoY;
	float targetAngle;
	float distance;
	unsigned int time;
	unsigned int countWhile;
	unsigned int countAverage;
	float initAngle;
public:
	Move(LineSensor &line,ButtonInfo &swPin,Servo &servo,RoboCenter &robo);
	int setup();
	void cycle();
	void setCoord();
	void setAngle(float angle){roboAngle=angle;}
	void setDuty(float straight,float rotat);
	void TPR105Cycle();
	void printAdValue();
	void printRoboInfo();
	float getTargetAngle();
	float getDistance();
	float getVerticalDistance();
	float rotationOutput(pid_gain_t gain);
};

#endif
