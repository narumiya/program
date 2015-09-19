#include "servo_controll.hpp"
#include <stdlib.h>

int ServoControll::commandRequest(int argc,char **argv){

	if(!strcmp(argv[1],"deg")){
		mode=DEG;
		degree=atof(argv[2]);
	}else{
		mode=0;
	}


	return 0;
}

void ServoControll::cycle(){
	if(mode==DEG){
		designateAngleCycle();
	}
}

void ServoControll::designateAngleCycle(){
	servo->duty(degree);
	servo->cycle();
}


