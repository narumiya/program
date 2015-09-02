#ifndef ROBOTCENTER_HPP
#define ROBOTCENER_HPP

#include "encoder.hpp"
#include "util.hpp"
#include "mcutime.h"

class RobotCenter:public Coord,public PhysicalObject{
private:
	Encoder *enc[3];
	float oldEncDisi[3];				//1つ前のエンコーダが進んだ距離
	float gapEncDis[3];				//エンコーダが進んだ距離の偏差
	float encDis[3];					//エンコーダが進んだ距離の合計
	float encAngle[3];				//エンコーダから求められる中心角度
	float encMountAngle[3];	//エンコーダ取り付け角度
	float moveEncX[3];			//エンコーダの移動量
	float moveEncY[3];
	float temporaryX[3];			//連立の計算結果
	float temporaryY[3];
	float encRadius;					//中心からエンコーダまでの距離
	float coordX;
	float coordY;
	int64_t time;
	enum{
		LEFT,
		RIGHT,
		BACK
	};
public:
	float angle;
	float velocity;
	float omega;
	RobotCenter(Encoder &l,Encoder &r,Encoder &b);
	void setup();
	void cycle();
	void resetInfo();
};

#endif
