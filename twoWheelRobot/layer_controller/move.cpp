#include "move.hpp"
#include <stdio.h>

#include "pin.hpp"
extern "C"{
#include "mcutime.h"
#include "calculate.h"
#include "my_else_calculation.h"
}

Move::	Move(MiniMD &l,MiniMD &r,ButtonInfo &swPin){
	md[0]=&l;md[1]=&r;
	sw=&swPin;
	mode=NONSENSOR;
	countWhile=0;
	countAverage=500;
	time=millis();
	startFlag=false;
}

Move::Move(MiniMD &l,MiniMD &r,Analog &a0,Analog &a1,Analog &a2,Analog &a3,Analog &a4,ButtonInfo &swPin){
	mode=USESENSOR;
	sw=&swPin;
	md[0]=&l;md[1]=&r;
	an[0]=&a0;an[1]=&a1;
	an[2]=&a2;an[3]=&a3;
	an[4]=&a4;
	for(int i=0;i<5;i++){
		adData[i]=0.0;
	}
	countWhile=0;
	countAverage=500;
	time=millis();
	startFlag=false;
	calibraFlag=false;
}
int Move::setup(){
	sw->setup(false,50);
	led1.setupDigitalOut();
	led2.setupDigitalOut();
	led3.setupDigitalOut();
	for(int i=0;i<2;i++){
		md[i]->setup();
	}
	if(mode==USESENSOR){
		/*for(int i=0;i<5;i++){
			an[i]->setupAnalogIn();
		}*/
	}
	return 0;
}

void Move::cycle(){
	if(mode==USESENSOR){
		TPR105Cycle();
		if(!calibraFlag)calibraFlag=calibra();
	}else	calibraFlag=true;
	sw->cycle();
	if(millis()-time>=5){
		time=millis();
		if(!startFlag){
			//if(calibraFlag){
				if(sw->readDownEdge()) startFlag=true;
			//}
		}else if(startFlag){
			led3.digitalHigh();
			float speed=0.35;
			float rotation=rotationOutput();
			setDuty(speed,rotation);
			//printf("output,%.2f",rotation);
			//printf("middle%f",middle);
			//printf("sw,%d",sw->readValue());
			//printf("\n");
		}
		countAverage=countWhile;
		countWhile=0;
	}
	for(int i=0;i<2;i++)
		md[i]->cycle();
}

void Move::setDuty(float straight,float rotat){
	md[0]->duty(straight-rotat);
	md[1]->duty(straight+rotat);
}

void Move::TPR105Cycle(){
	countWhile++;
	for(int i=0;i<5;i++){
		adData[i]=get_Average(countAverage,i,an[i]->analogRead());
	}
}

float Move::rotationOutput(){
	static pid_data_t data={0};
	const pid_gain_t gain=set_pid_gain(0.3,0.0,0.0);
	static int reset=millis();
	//const pid_gain_t gain=set_pid_gain(0.2,0.0,0);

	if(millis()-reset>=100){
		reset=millis();
		reset_pid_data(&data);
	}
	//float ad=((adData[1]+adData[3])-middle);///((other-white));
	float ad=((adData[1]-adData[3]));
	//printf("ad,%f",ad);
	return  floatlimit(-1.0,calc_pid(&data,ad,gain),1.0);
	//return calc_pid(&data,ad,gain);
}


void Move::printAdValue(){
	for(int i=0;i<5;i++){
		printf("ad%d,%.4f",i,adData[i]);
	}
}


int Move::calibra(){
	static int flag=0;
	switch(flag){
	case 0:
		if(!sw->readDownEdge())	white=adData[1]+adData[3];
		else{
			flag=1;
			led1.digitalHigh();
			delay_ms(500);
		}
		break;
	case 1:
		if(!sw->readDownEdge())	other=adData[1]+adData[3];
		else{
			flag=2;
			middle=(white+other)/2;
			led2.digitalHigh();
			delay_ms(500);
			return 1;
		}
		break;
	}
	return 0;
}
