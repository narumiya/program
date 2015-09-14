#include "move.hpp"
#include <math.h>
extern "C" {
#include "util.h"
#include "calculate.h"
#include "my_else_calculation.h"
#include "mcutime.h"
}
#include "base/digital.hpp"
#include "base/pwm.hpp"

Move::Move(Md &md0,Md &md1,Md &md2,Md &md3,RobotCenter &robot,DualShock con){
	md[FRONTR]=&md0;
	md[FRONTL]=&md1;
	md[BACKL]=&md2;
	md[BACKR]=&md3;
	center=&robot;
	ps3=&con;
	xComponent=0;yComponent=0;
	startFlag=false;
	time=millis();
	for(int i=0;i<4;i++){
		parallelOutput[i]=0.0;
		freeAngle[i]=0.0;
		duty[i]=0.0;
	}
}

void Move::setDuty(int mode){
	if(mode==MOVE){
		for(int i=0;i<4;i++)
			duty[i]=parallelOutput[i]+rotationOutput;
	}else{
		for(int i=0;i<4;i++) duty[i]=0;
	}
}

void Move::setup(){
	ps3->setup();
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
printf("FR,%.4f,FL,%.4f,BL,%.4f,BR,%.4f,\n",duty[FRONTR],duty[FRONTL],duty[BACKL],duty[BACKR]);
}

void Move::getXYComponent(float vector,float angle){
	xComponent=fabs(vector)*cos(angle+radiusReverse(vector));
	yComponent=fabs(vector)*sin(angle+radiusReverse(vector));
}

void Move::getParallelOutput(void){
	float angle=0;//center->angle;
	float freeXComponent=0.0,freeYComponent=0.0;
	for(int i=0;i<4;i++){
		freeXComponent=fabs(xComponent)*cos(angle+freeAngle[i]+radiusReverse(xComponent));
		freeYComponent=fabs(yComponent)*sin(angle+freeAngle[i]+radiusReverse(yComponent));
		parallelOutput[i]=area(freeXComponent+freeYComponent,-1.0,1.0);
	}
}

void Move::getRotationOutput(float angle){
	const pid_gain_t gain=set_pid_gain(0,0,0);
	static pid_data_t data={0};

	rotationOutput=calc_pid(&data,area(angle-center->getAngle(),-M_PI,M_PI),gain);
}

void Move::manualModeCycle(){
	const float maxOutput=0.5;
	const float maxAngle=dtor(90);//stick maxŽž 1000ms‚Å‚Ç‚ê‚¾‚¯“®‚­‚©
	float joylx=ps3->ly(),joyly=ps3->lx();
	float joyry=ps3->rx();
	static float targetAngle=0.0;
	bool stopFlag=false;

	if(millis()-time>=5){
		time=millis();
		if(!startFlag){
			if(ps3->start()==1) startFlag=true;
			setDuty(STOP);
		}else if(startFlag){
			if(joylx>maxOutput) joylx=maxOutput;
			xComponent=joylx;
			if(joyly>maxOutput) joyly=maxOutput;
			yComponent=joyly;
			getParallelOutput();

			targetAngle+=((maxAngle*joyry*5) / 1000);
			getRotationOutput(targetAngle);

			if(fabs(center->getOriginalAngle())>dtor(360)) stopFlag=true;
			if(!stopFlag) setDuty(MOVE);
			else setDuty(STOP);
		}
	}
	if(ps3->disconnect())	setDuty(STOP);

	cycle();
}
