#include "md.hpp"
#include <math.h>
#include "mcutime.h"

Md::Md(Digital &cwPin,Digital &ccwPin,Pwm &pwmPin){
	cw=&cwPin;
	ccw=&ccwPin;
	pwm=&pwmPin;
	flag=0;
	deadtime=millis();
	request=0;
}

int Md::setup(){
	int i=0;
	i+=cw->setupDigitalOut();
	i+=ccw->setupDigitalOut();
	i+=pwm->setupPwmOut(100000,0);
	free();
	return i;
}

void Md::cycle(){
	if(request>0){
		if(flag!=NORMAL){
			free();
			request=0;
			if(millis()-deadtime>=10){
				deadtime=millis();
				flag=NORMAL;
			}
		}else{
			deadtime=millis();
			cw->digitalHigh();
			ccw->digitalLow();
			flag=NORMAL;
		}
	}else if(request<0){
		if(flag!=REVERSE){
			free();
			request=0;
			if(millis()-deadtime>=10){
				deadtime=millis();
				flag=REVERSE;
			}
		}else{
			deadtime=millis();
			cw->digitalLow();
			ccw->digitalHigh();
			flag=REVERSE;
		}
	}
	pwm->pwmWrite(fabs(request));
}

void Md::free(){
	cw->digitalLow();
	ccw->digitalLow();
	pwm->pwmWrite(0);
}

void Md::duty(float value){
	if(value>0.95) request=0.95;
	else if(value<-0.95) request=-95.0;
	else if(0<value&&value<0.05 ) request=0.05;
	else if(-0.05<value&&value<0) request=-0.05;
	else request=value;
}
