#include "move.hpp"
#include <stdio.h>

#include "pin.hpp"
extern "C"{
#include "mcutime.h"
#include "calculate.h"

}

Move::Move(MiniMD &l,MiniMD &r,ButtonInfo &swPin){
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
	useServo=false;
}
Move::Move(Analog &a0,Analog &a1,Analog &a2,Analog &a3,Analog &a4,ButtonInfo &swPin,Servo &servoPin){
	mode=USESENSOR;
	sw=&swPin;
	servo=&servoPin;
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
	useServo=true;
}
int Move::setup(){
	sw->setup(true,25);
	led1.setupDigitalOut();
	led2.setupDigitalOut();
	led3.setupDigitalOut();
	if(mode==USESENSOR){
		/*for(int i=0;i<5;i++){
			an[i]->setupAnalogIn();
		}*/
	}
	if(useServo) servo->setup(30,270,1.5,2.3);
	else{
		for(int i=0;i<2;i++){
			md[i]->setup();
		}
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
			if(!useServo){
				pid_gain_t gain=set_pid_gain(0.65,0.0,1.2);//p0.3直進の出力なし
				float speed=0.0;
				float rotation=floatlimit(-1.0,rotationOutput(gain),1.0);
				setDuty(speed,rotation);
				//printf("output,%.2f",rotation);
				//printf("middle%f",middle);
				//printf("sw,%d",sw->readValue());
				//printf("\n");
			}else{
				static float output=servo->initAngle(INITANGLE);
				pid_gain_t gain=set_pid_gain(0.000035,0.0,0.0);//1度→0.0019
				float angle=rotationOutput(gain);
				output+=angle;
				if(output>=servo->initAngle(45)){
					output=servo->initAngle(45);
				}else if(output<=servo->initAngle(-45)){
					output=servo->initAngle(-45);
				}
				//printf("output,%.2f\n",output);
				servo->setDuty(output);
			}
		}
		countAverage=countWhile;
		countWhile=0;
	}
	if(!useServo){
		for(int i=0;i<2;i++)
			md[i]->cycle();
	}else{
		servo->cycle();
	}
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

float Move::rotationOutput(pid_gain_t gain){
	static pid_data_t data={0};
	//const pid_gain_t gain=set_pid_gain(0.65,0.0,1.2);//p0.3直進の出力なし
	float ad=0;

	//static int reset=millis();
	//const pid_gain_t gain=set_pid_gain(0.2,0.0,0);

	/*if(millis()-reset>=100){
		reset=millis();
		reset_pid_data(&data);
	}*/
	//float ad=((adData[1]+adData[3])-middle);///((other-white));
	ad=((adData[1]-adData[3]));//差分を0にするように
	//printf("ad,%f",ad);
	float output=calc_pid(&data,ad,gain);
	//printf("%f,  %f,   %f\n",adData[3],adData[1],output);

	return  output;
	//return calc_pid(&data,ad,gain);
}


void Move::printAdValue(){
	//printf("ad%d,%.4f",0,adData[0]);
	printf("ad%d,%.4f",1,adData[1]);
	//printf("ad%d,%.4f",2,adData[2]);
	printf("ad%d,%.4f",3,adData[3]);
	//printf("ad%d,%.4f",4,adData[4]);
	printf("\n");
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
