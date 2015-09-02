#include "move.hpp"
#include <math.h>
extern "C" {
#include "util.h"
#include "calculate.h"
}
#include "base/digital.hpp"
#include "base/pwm.hpp"

Move::Move(Md &md0,Md &md1,Md &md2,Md &md3){
	md[FRONTR]=&md0;
	md[FRONTL]=&md1;
	md[BACKL]=&md2;
	md[BACKR]=&md3;
	xComponent=0;yComponent=0;
}


void Move::setup(){
	for(int i=0;i<4;i++)md[i]->setup();
	freeAngle[FRONTR]=dtor(45);
	freeAngle[FRONTL]=dtor(135);
	freeAngle[BACKL]=dtor(-135);
	freeAngle[BACKR]=dtor(-45);
}

void Move::cycle(){
	for(int i=0;i<4;i++){
		md[i]->duty(duty[i]);
		md[i]->cycle();
	}
}

void Move::getXYComponent(float vector,float angle){
	xComponent=fabs(vector)*cos(angle+radiusReverse(vector));
	yComponent=fabs(vector)*sin(angle+radiusReverse(vector));
}

void Move::getParallelOutput(float vector){
	float angle=0;

}
