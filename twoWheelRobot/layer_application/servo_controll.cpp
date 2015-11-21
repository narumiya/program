#include "servo_controll.hpp"
#include <stdlib.h>

#include <stdio.h>

int ServoControll::commandRequest(int argc,char **argv){
	if(!strcmp(argv[1],"deg")){
		mode=DEG;
		degree=atof(argv[2]);
	}else if(!strcmp(argv[1],"duty")){
		mode=PULSE;
		value=atof(argv[2]);
		if(value>1.0||value<0.0){
			value=0.0;
		}
		return 1;//1‚ð•Ô‚µ‚½‚çcommandCycleŒÄ‚Î‚ê‚é
	}else{
		mode=0;
	}
	return 0;
}

void ServoControll::consoleReadChar(char data){
	if(data=='\r'){
		mode=0;
		value=0;
	}
}
int ServoControll::commandCycle(){
	if(mode==PULSE){
		printf("%.2f\n",value);
		return 1;//1‚ð•Ô‚µ‚½‚ç‚à‚¤ˆê“xcommandCycle‚ªŒÄ‚Î‚ê‚é
	}
	return 0;
}
void ServoControll::cycle(){
	if(mode==DEG){
		designateAngleCycle();
	}else if(mode==PULSE){
		//pulseCycle();
	}
	pulseCycle();
}

void ServoControll::designateAngleCycle(){
	servo->setAngle(dtor(degree));
	servo->cycle();
}

void ServoControll::pulseCycle(){
	/*float output=0;
	output=value+1.0;
	pwm->pwmWrite(output/16.528);*/
	fun->duty(value);
	fun->cycle();
}
#include "mcutime.h"
int ServoControll::setup(){
	//pwm->setupPwmOut(1.0/(16.528/1000.0), 1.0/16.528);
	fun->setup();
	return 0;
}

