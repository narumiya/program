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
	RIVER3,				//riiver 直進後の座標
	//RIVER4,				//river4回目曲がる直前
//	RIVERFIN,			//river終わり直前
	HIGHLAND,			//HIGHLAND始まり
	DOWNHILL,			//down hill 開始直前
	DOWNHILL1_0,	//down hill 1回目カーブ開始
	DOWNHILL1_1,	//down hill 1回目カーブ終わり
	DOWNHILL2_0,	//down hill 2回目のカーブ開始
	//DOWNHILL2_1,	//down hill 2回目のカーブ終わり
	DOWNHILL3_0,	//down hill 3回目のカーブ開始
	DOWNHILL3_1,	//down hill 3回目のカーブ終わり
	DOWNHILL3_2,	//down hill 3回目のカーブ後の直進
	/*DOWNHILL1,		//down hill 1回目曲がる直前
	DOWNHILL2,		//down hill 2回目曲がる直前
	DOWNHILL3,		//down hill 3回目曲がる直前
	DOWNHILLFIN,	//down hill 最後*/
	FIN						//最後
};
	Servo *servo;
	LineSensor *line;
	ButtonInfo *button0;
	ButtonInfo *button1;
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
	float startCoord[2][5];
	float circleCenter[2][3];	//down hill 扇型の中心座標
	float initCurveAngle[3];//downhill 突入時初期角度
	float curveRadius[3];//down hill 半径
	float centralAngle[3];//down hill 中心角
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
	float radius;//旋回半径
	float radiusServo;
	float radiusR;
	float radiusL;
public:
	Move(LineSensor &line,Digital &digital,ButtonInfo &sw0Pin,ButtonInfo &sw1Pin,Servo &servoPin,RoboCenter &robo);
	int setup();
	void cycle();
	void setCoord();
	void setStartCoord();
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
	float getTargetTurningRadius();//目標の半径を返す
	float getTargetTurningRadius(float targetX,float targetY);//目標の旋回半径を返す
	float getTargeRadiusAngle(float radius);//半径からサーボを傾ける角度を出す
	float getServoAngle(float targetX,float targetY);//目標座標からサーボの角度返す
	float radiusToServo(float radius);//最小旋回半径からサーボの角度
	float getServoAngle();
	float getTimeLeft(float distance);//目標座標に到達するまでの時間(ms)
	float getAngleTime(float targetRad,float nowRad);//目標角度に到達するまでの時間(ms)
	void requestAngle(float targetX,float targetY,float nowX,float nowY);
	void decisionRestartTesk();
	void getStartCoord(int task);
	bool getStart(){return startFlag;};
};

#endif
