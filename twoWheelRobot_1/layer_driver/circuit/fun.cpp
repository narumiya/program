#include "fun.hpp"

Fun::Fun(Pwm &pwmPin){
	pwm=&pwmPin;
	pulse=0;
}

int Fun::setup(){
	period=16.528;
	int i=pwm->setupPwmOut(1.0/(period/1000.0), 1.0/period);
	return i;
}

void Fun::duty(float value){
	pulse=value+1.0;
}

void Fun::cycle(){
	pwm->pwmWrite(pulse/period);
}
