#ifndef CHAI_YO_HPP
#define CHAI_YO_HPP

#include "layer_controller/robo_center.hpp"
#include "layer_controller/move.hpp"
#include "mcutime.h"
class ChaiYo{
private:
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
		DOWNHILL,			//down hill �J�n���O
		DOWNHILL1_0,	//down hill 1��ڃJ�[�u�J�n
		DOWNHILL1_1,	//down hill 1��ڃJ�[�u�I���
		DOWNHILL2_0,	//down hill 2��ڂ̃J�[�u�J�n
		DOWNHILL2_1,	//down hill 2��ڂ̃J�[�u�I���
		DOWNHILL3_0,	//down hill 3��ڂ̃J�[�u�J�n
		DOWNHILL3_1,	//down hill 3��ڂ̃J�[�u�I���
		DOWNHILL3_2,	//down hill 3��ڂ̃J�[�u��̒��i
		FIN						//�Ō�
	};
	Move *move;
	RoboCenter *eco;
	Buzzer *buzz;
	Led1 *led1;
	Led2 *led2;
	Led3 *led3;
	ButtonInfo *b0;
	ButtonInfo *b1;
	int64_t time;
	int controlPeriod;//ms
	bool startFlag;
	float startX;
	float startY;
	float startAngle;
	int startTask;
	int task;
	float coord[2][20];
	float servoAngle;
	float initServoAngle;
	float circleCenter[2][3];	//down hill ��^�̒��S���W
	float initCurveAngle[3];//down hill �˓��������p�x
	float curveRadius[3];//down hill ���a
	float centralAngle[3];//down hill ���S�p
public:
	ChaiYo(Move &move,RoboCenter &eco,Buzzer &buzz,Led1 &l1,Led2 &l2,Led3 &l3,ButtonInfo &b0,ButtonInfo &b1);
	int setup();
	void setCoord();
	void cycle();
};

#endif