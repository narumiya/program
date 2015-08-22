#include "robotCenter.hpp"

RobotCenter::RobotCenter(Encoder &l,Encoder &r,Encoder &b){
	enc[LEFT]=&l;
	enc[RIGHT]=&r;
	enc[BACK]=&b;
	centerToEnc=0;
}

void RobotCenter::setup(){
	for(int i=0;i<3;i++)	enc[i]->cpr(1000);
	enc[LEFT]->rev(true);
	enc[RIGHT]->rev(true);
	enc[BACK]->rev(true);
	enc[LEFT]->mlt(50.8);
	enc[RIGHT]->mlt(50.8);
	enc[BACK]->mlt(50.8);
}
