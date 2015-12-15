#include "okmtmd.hpp"
#include "util.h"
#include "mcutime.h"
#include <math.h>


#define MOTOR_DIRECTION_CCW 1
#define MOTOR_DIRECTION_CW  0

OkamotoMD::OkamotoMD(Digital &cw,Digital &ccw,Pwm &pwm){
	deadTimeMicrosData=10000;//micros
	underLimitDuty=0.05;
	overLimitDuty=0.95;
	requestDuty=0.0;
	reverse=false;
	oldDirection=0;
	time=micros();
	this->cw=&cw;
	this->ccw=&ccw;
	this->pwm=&pwm;
}

int OkamotoMD::setup(){
	int i=0;
	i+=0!=cw->setupDigitalOut();
	i+=0!=ccw->setupDigitalOut();
	i+=0!=pwm->setupPwmOut(100000,0.0);
	return i;
}

void OkamotoMD::outRev(bool value){
	reverse=value;
}

void OkamotoMD::duty(float dutyArg){
	requestDuty=constrain(dutyArg,-overLimitDuty,overLimitDuty);
	if(fabs(requestDuty)<underLimitDuty)requestDuty=0;
}

void OkamotoMD::output(float request){
	if(request>0.0){
			if(!reverse)cw->digitalHigh();
			else cw->digitalLow();
			if(!reverse)ccw->digitalLow();
			else ccw->digitalHigh();
			pwm->pwmWrite(request);
		}else if(request<0.0){
			if(!reverse)cw->digitalLow();
			else cw->digitalHigh();
			if(!reverse)ccw->digitalHigh();
			else ccw->digitalLow();
			pwm->pwmWrite(-request);//(-request)
		}else{
			cw->digitalHigh();
			ccw->digitalHigh();
			pwm->pwmWrite(0.0);
		}
}

void OkamotoMD::cycle(){
	float outputDuty;
	outputDuty=requestDuty;
	if(requestDuty>0&&oldDirection==MOTOR_DIRECTION_CCW){//要求と前回の回転方向が違うとき
		time=micros();
		oldDirection=MOTOR_DIRECTION_CW;
	}
	if(requestDuty<0&&oldDirection==MOTOR_DIRECTION_CW){//要求と前回の回転方向が違うとき
		time=micros();
		oldDirection=MOTOR_DIRECTION_CCW;
	}

	if(micros()-time<deadTimeMicrosData){//デッドタイムのとき
		outputDuty=0;
	}
	output(outputDuty);
}
