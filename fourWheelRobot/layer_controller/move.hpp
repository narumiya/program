#ifndef MOVE_HPP
#define MOVE_HPP

#include "circuit/md.hpp"
#include "circuit/dual_shock.hpp"
#include "robotCenter.hpp"
class Move{
private:
	Md *md[4];
	RobotCenter *center;
	DualShock *ps3;
	int time;
	float xComponent;			//ベクトルのx成分
	float yComponent;			//ベクトルのy成分
	float freeAngle[4];			//フリー回転する方向
	float parallelOutput[4];	//平行移動出力
	float rotationOutput;		//回転出力
	float duty[4];
	bool startFlag;
	enum{
		FRONTR,
		FRONTL,
		BACKL,
		BACKR
	};
	enum{
		STOP,
		MOVE
	};
public:
	Move(Md &md0,Md &md1,Md &md2,Md &md3,RobotCenter &robot,DualShock con);
	void getParallelOutput(void);						//平行移動の出力計算
	void getRotationOutput(float value);					//回転の出力計算
	void getXYComponent(float vector, float angle);		//ベクトルをxy成分に分解
	void setDuty(int mode);
	void cycle();
	void setup();
	void manualModeCycle();		//手動
};

#endif
