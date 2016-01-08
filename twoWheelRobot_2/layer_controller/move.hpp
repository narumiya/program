#ifndef MOVE_HPP
#define MOVE_HPP

#include "circuit/servo.hpp"
#include "layer_driver/circuit/button_info.hpp"
#include "layer_controller/robo_center.hpp"
#include "layer_driver/circuit/line_sensor.hpp"
#include "pin.hpp"
extern "C"{
#include "my_else_calculation.h"
#include <stdint.h>
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
	//RIVER3=10,				//river3��ڋȂ��钼�O//river ���i��̍��W
	//RIVER4,				//river4��ڋȂ��钼�O
//	RIVERFIN,			//river�I��蒼�O
	DOWNHILL,			//down hill �J�n���O
	DOWNHILL1_0,	//down hill 1��ڃJ�[�u�J�n
	DOWNHILL1_1,	//down hill 1��ڃJ�[�u�I���
	DOWNHILL2_0,	//down hill 2��ڂ̃J�[�u�J�n
	DOWNHILL2_1,	//down hill 2��ڂ̃J�[�u�I���
	DOWNHILL3_0,	//down hill 3��ڂ̃J�[�u�J�n
	DOWNHILL3_1,	//down hill 3��ڂ̃J�[�u�I���
	DOWNHILL3_2,	//down hill 3��ڂ̃J�[�u��̒��i
	/*DOWNHILL1,		//down hill 1��ڋȂ��钼�O
	DOWNHILL2,		//down hill 2��ڋȂ��钼�O
	DOWNHILL3,		//down hill 3��ڋȂ��钼�O
	DOWNHILLFIN,	//down hill �Ō�*/
	FIN						//�Ō�
};
	Servo *servo;
	LineSensor *line;
	ButtonInfo *startSw;
	RoboCenter *robo;
	Digital *buzz;
	Led1 led1;
	Led2 led2;
	Led3 led3;

	bool startFlag;
	int mode;
	int task;
	int cycleTime;
	float adData[5];
	float roboAngle;
	float coord[2][30];
	float circleCenter[2][3];	//down hill ��^�̒��S���W
	float initCurveAngle[3];//downhill �˓��������p�x
	float curveRadius[3];//down hill ���a
	float centralAngle[3];//down hill ���S�p
	float startX;
	float startY;
	float startAngle;
	float startTask;
	float servoAngle;
	float targetAngle;
	float distance;
	float velocity;
	float pGain;
	float iGain;
	float dGain;
	float output;
	int64_t time;
	unsigned int countWhile;
	unsigned int countAverage;
	float initAngle;
	float timeLeft;
	float angleTime;
	float radius;//���񔼌a
	float radiusServo;
public:
	Move(LineSensor &line,Digital &digital,ButtonInfo &swPin,Servo &servoPin,RoboCenter &robo);
	int setup();
	void cycle();
	void setCoord();
	void setAngle(float angle){roboAngle=angle;}
	void setDuty(float straight,float rotat);
	void setPid(float p, float i, float d){pGain=p;iGain=i;dGain=d;}
	void LineCycle();
	void printAdValue();
	void printRoboInfo();
	float rotationOutput(float diff,pid_gain_t gain);
	float getTargetAngle();
	float getTargetAngle(float targetX,float targetY,float nowX,float nowY);
	float getDistance();
	float getDistance(float targetX, float targetY,float nowX,float nowY);
	float getVerticalDistance();
	float getSteeringOuterRingAngle(float angle);
	float getSteeringInnerRingAngle(float angle);
	float getTurningRadius(float angle);//���݂̃T�[�{�p�x���猻�݂̐��񔼌a���o��
	float getTargetTurningRadius();//�ڕW�̔��a��Ԃ�
	//float getTargetTurningRadius(float distance,float radian);//�ڕW�̔��a��Ԃ�
	float getTargetTurningRadius(float targetX,float targetY);//�ڕW�̐��񔼌a��Ԃ�
	float getTargeRadiusAngle(float radius);//���a����T�[�{���X����p�x���o��
	float getServoAngle(float targetX,float targetY);//�ڕW���W����T�[�{�̊p�x�Ԃ�
	float radiusToServo(float radius);//�ŏ����񔼌a����T�[�{�̊p�x
	float getServoAngle();
	float getTimeLeft(float distance);//�ڕW���W�ɓ��B����܂ł̎���(ms)
	float getAngleTime(float targetRad,float nowRad);//�ڕW�p�x�ɓ��B����܂ł̎���(ms)
	void requestAngle(float targetX,float targetY,float nowX,float nowY);
	void DecisionRestartTesk();
};

#endif