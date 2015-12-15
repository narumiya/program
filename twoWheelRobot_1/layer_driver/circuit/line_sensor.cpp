#include "line_sensor.hpp"

LineSensor::LineSensor(Analog &a0,Analog &a1,Analog &a2,Analog &a3,Analog &a4){
	an[0]=&a0;an[1]=&a1;
	an[2]=&a2;an[3]=&a3;
	an[4]=&a4;
}

int LineSensor::setup(){
	/*for(int i=0;i<5;i++){
		an[i]->setupAnalogIn();
	}*/
	//ã‚ÌŽÀs‚·‚é‚Æ’l‚¸‚ê‚Ä‚¢‚­
	return 1;
}

float LineSensor::getValue(int num){
	return an[num]->analogRead();
}
