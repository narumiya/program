#ifndef ROBOTCENTER_HPP
#define ROBOTCENER_HPP

#include "encoder.hpp"
#include "util.hpp"

class RobotCenter:public Coord{
private:
	Encoder *enc[3];
	float oldEncDisi[3];				//1つ前のエンコーダが進んだ距離
	float gapEncDis[3];				//エンコーダが進んだ距離の偏差
	float encDis[3];					//エンコーダが進んだ距離の合計
	float encAngle[3];				//エンコーダから求められる中心角度
	float encMountAngle[3];	//エンコーダ取り付け角度
	float encMoveNormal[3];	//エンコーダから求められる法線
	float encRadius;					//中心からエンコーダまでの距離
	enum{
		LEFT,
		RIGHT,
		BACK
	};
public:
	float angle;
	float coordX;
	float coordY;
	float velocity;
	float omega;
	RobotCenter(Encoder &l,Encoder &r,Encoder &b);
	void setup();
	void cycle();
};

#endif
