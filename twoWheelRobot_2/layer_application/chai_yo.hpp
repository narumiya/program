#ifndef CHAI_YO_HPP
#define CHAI_YO_HPP

#include "layer_controller/robo_center.hpp"
#include "layer_controller/move.hpp"
#include "mcutime.h"
class ChaiYo{
private:
	enum{
		CX,//座標x
		CY//座標y
	};
	enum{
		SLOPE1=0,				//slope1直前
		HILL1,					//hill1直前
		SLOPE2,				//slope2直前
		HILL2,					//hill2直前
		SLOPE3,				//slope3直前
		HILL3,					//hill3直前
		HILL4,					//hill3の途中
		RIVER,					//river直前
		RIVER1,				//river1回目曲がる直前
		RIVER2,				//river2回目曲がる直前
		RIVER3,				//river3回目曲がる直前
		RIVER4,				//river4回目曲がる直前
		DOWNHILL,			//down hill 開始直前
		DOWNHILL1_0,	//down hill 1回目カーブ開始
		DOWNHILL1_1,	//down hill 1回目カーブ終わり
		DOWNHILL2_0,	//down hill 2回目のカーブ開始
		DOWNHILL2_1,	//down hill 2回目のカーブ終わり
		DOWNHILL3_0,	//down hill 3回目のカーブ開始
		DOWNHILL3_1,	//down hill 3回目のカーブ終わり
		DOWNHILL3_2,	//down hill 3回目のカーブ後の直進
		FIN						//最後
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
	float circleCenter[2][3];	//down hill 扇型の中心座標
	float initCurveAngle[3];//down hill 突入時初期角度
	float curveRadius[3];//down hill 半径
	float centralAngle[3];//down hill 中心角
public:
	ChaiYo(Move &move,RoboCenter &eco,Buzzer &buzz,Led1 &l1,Led2 &l2,Led3 &l3,ButtonInfo &b0,ButtonInfo &b1);
	int setup();
	void setCoord();
	void cycle();
};

#endif
