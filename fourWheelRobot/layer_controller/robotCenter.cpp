#include "robotCenter.hpp"
#include <math.h>
extern "C" {
#include "util.h"
#include "calculate.h"
}

RobotCenter::RobotCenter(Encoder &l,Encoder &r,Encoder &b){
	enc[LEFT]=&l;
	enc[RIGHT]=&r;
	enc[BACK]=&b;
	encRadius=0.0;
	angle=0.0;
	coordX=0.0;
	coordY=0.0;
	velocity=0.0;
	omega=0.0;
	for(int i=0;i<3;i++){
		oldEncDisi[i]=0;
		gapEncDis[i]=0;
		encDis[i]=0;
		encMountAngle[i]=0;
		encMoveNormal[i]=0;
	}
}

void RobotCenter::setup(){
	for(int i=0;i<3;i++)	enc[i]->cpr(1000);
	enc[LEFT]->rev(true);
	enc[RIGHT]->rev(true);
	enc[BACK]->rev(true);
	enc[LEFT]->mlt(50.8);
	enc[RIGHT]->mlt(50.8);
	enc[BACK]->mlt(50.8);
	encMountAngle[LEFT]=dtor(-30);
	encMountAngle[RIGHT]=dtor(30);
	encMountAngle[BACK]=dtor(-90);
	encRadius=0.0;
}

void RobotCenter::cycle(){
	for(int i=0;i<3;i++){
		gapEncDis[i]=enc[i]->value()-oldEncDisi[i];
		encDis[i]+=gapEncDis[i];
		oldEncDisi[i]=enc[i]->value();
		encAngle[i]=gapEncDis[i]/encRadius;
	}
	angle+=area((encAngle[0]+encAngle[1]+encAngle[2])/3.0,(-1.0)*M_PI,M_PI);

}
