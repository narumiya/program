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

class Move{
private:
	enum{
		NONSENSOR,
		USESENSOR
	};
	enum{
		CX,//���Wx
		CY//���Wy
	};
	enum{
		SLOPE1=0,				//slope1���O
		HILL1,					//hill1���O
		SLOPE2,				//slope2���O
		HILL2,					//hill2���O
		SLOPE3,				//slope3���O
		HILL3,					//hill3���O
		HILL4,					//hill3�̓r��
		RIVER,					//river���O
		RIVER1,				//river1��ڋȂ��钼�O
		RIVER2,				//river2��ڋȂ��钼�O
		RIVER3,				//river3��ڋȂ��钼�O
		RIVER4,				//river4��ڋȂ��钼�O
	//	RIVERFIN,			//river�I��蒼�O
		DOWNHILL,		//down hill �J�n���O
		DOWNHILL1,		//down hill 1��ڋȂ��钼�O
		DOWNHILL2,		//down hill 2��ڋȂ��钼�O
		DOWNHILL3,		//down hill 3��ڋȂ��钼�O
		DOWNHILLFIN,	//down hill �Ō�
		FIN					//�Ō�
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
	float startAngle;
	float startTask;
	float servoAngle;
	float targetAngle;
	float distance;
	float velocity;
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
	void LineCycle();
	void printAdValue();
	void printRoboInfo();
	float getTargetAngle();
	float getDistance();
	float getVerticalDistance();
	float rotationOutput(pid_gain_t gain);
};

#endif