#ifndef RONO_CENTER_HPP
#define RONO_CENTER_HPP

#include "encoder.hpp"
#include "circuit/button_info.hpp"
#include "circuit/r1350n/r1350n.hpp"
#include "util.hpp"
#include "advanced_encoder.hpp"

class RoboCenter:public Coord{
private:
	AdvancedEncoder *enc0;
	R1350n *gyro;
	ButtonInfo *resetSw;
	unsigned int time;
	float encX;//エンコーダから計算できる座標
	float encY;
	float x;//後ろのタイヤの軸上座標
	float y;
	float z;
	float servoX;
	float servoY;
	float frontRTireX;
	float frontRTireY;
	float frontLTireX;
	float frontLTireY;
	float backRTireX;
	float backRTireY;
	//float backLtireX;
	float def;
	float angle;
	float startAngle;
	float initAngle;
	float value;//エンコーダ進んだ距離
	float oldValue;
	float initValue;
	float radian;
	float oldRadian;
	float initRadian;
	float velocity;
	float initAccx;
	float encToServo;
	float encToAxis;//エンコーダから後ろ軸の距離
	float axisToTire;//後ろの軸から前のタイヤまでの距離
	float axisToRbTire;//後ろの軸から右後ろまでの距離
	float angularVelocity;
	float tread;
	float wheelBase;//ロボットの全長
public:
	RoboCenter(AdvancedEncoder &enc,R1350n &gyroPin,ButtonInfo &resetPin);
	int setup();
	float getVelocity(){return velocity;};
	float getX(){return x;};
	float getY(){return y;};
	float getAngle(){return angle;};
	float getServoX(){return servoX;};
	float getServoY(){return servoY;};
	float getFrontRTireX(){return frontRTireX;};
	float getFrontRTireY(){return frontRTireY;};
	float getFrontLTireX(){return frontLTireX;};
	float getFrontLTireY(){return frontLTireY;};
	float getBackRTireX(){return backRTireX;};
	float getBackRTireY(){return backRTireY;};
	void setAngle(float value){startAngle=value;};
	void setX(float value){encX=value;};
	void setY(float value){encY=value;};
	float getEncCnt(){return def;};
	float getSlope();
	float getTread(){return tread;};
	int getSlopeCount();
	void cycle();
	void accCycle();
	void reset();
	void reset(float x, float y);
};

#endif
