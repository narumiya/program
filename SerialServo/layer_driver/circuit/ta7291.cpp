#include "ta7291.hpp"

Ta7291::Ta7291(Digital &cwPin,Digital &ccwPin,Pwm &pwmPin){
	cw=&cwPin;
	ccw=&ccwPin;
	pwm=&pwmPin;
}

int Ta7291::setup(){
	int i=0;
	i+=cw->setupDigitalOut();
	i+=ccw->setupDigitalOut();
	i+=pwm->setupPwmOut(10000,1.0);
	return i;
}

void Ta7291::cycle(){
	if(request>0.0){
		cw->digitalHigh();
		ccw->digitalLow();
		pwm->pwmWrite(1.0-request);
	}else if(request<0.0){
		cw->digitalLow();
		ccw->digitalHigh();
		pwm->pwmWrite(1.0+request);
	}else{
		cw->digitalLow();
		ccw->digitalHigh();
		pwm->pwmWrite(1.0);
	}
}

void Ta7291::duty(float value){
	if(value>1.0) request=1.0;
	else if(value<-1.0) request=-1.0;
	else request=value;
}
