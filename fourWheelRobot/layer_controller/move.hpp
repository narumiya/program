#ifndef MOVE_HPP
#define MOVE_HPP
#include "circuit/md.hpp"

class Move{
private:
	Md *md[4];
	float xComponent;			//ベクトルのx成分
	float yComponent;			//ベクトルのy成分
	float freeAngle[4];			//フリー回転する方向
	float duty[4];
	enum{
		FRONTR,
		FRONTL,
		BACKL,
		BACKR
	};
public:
	Move(Md &md0,Md &md1,Md &md2,Md &md3);
	void getParallelOutput(float vector);						//平行移動の出力計算
	void getRotationOutput();					//回転の出力
	void getXYComponent(float vector, float angle);		//ベクトルをxy成分に分解
	void setDuty(float vector);
	void cycle();
	void setup();
};

#endif
