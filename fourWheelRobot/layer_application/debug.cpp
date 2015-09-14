#include "debug.hpp"
#include <string.h>
#include <stdio.h>
#include "mcutime.h"

Debug::Debug(Serial &serialPin,RobotCenter &robot,DualShock &con){
	this->serial=&serialPin;
	center=&robot;
	ps3=&con;
	//Enc0 enc0;Enc1 enc1;Enc2 enc2;
	//enc[0]=new Enc0;//enc[1]=&enc1;enc[2]=&enc2;
	mode=0;
	setupMode=0;
	CW0 cw4;CCW0 ccw4;Pwm0 pwm4;Md md4(cw4,ccw4,pwm4);
	CW1 cw5;CCW1 ccw5;Pwm1 pwm5;//Md md5(cw5,ccw5,pwm5);
	CW2 cw6;CCW2 ccw6;Pwm2 pwm6;//Md md6(cw6,ccw6,pwm6);
	CW3 cw7;CCW3 ccw7;Pwm3 pwm7;//Md md7(cw7,ccw7,pwm7);
	md[4]=md4;//Md(cw4,ccw4,pwm4);md[5]=new Md(cw5,ccw5,pwm5);
	//md[6]=new Md(cw6,ccw6,pwm6);md[7]=new Md(cw7,ccw7,pwm7);
	for(int i=0;i<256;i++) str[i]='\r';
	availableFlag=0;
	time=millis();
}

int Debug::setup(){
	serial->setup(115200,(*this));
	ps3->setup();
	center->setup();
	//enc[0]->setup();
	//setupEncoder();
	//setupMotor();
	md[4].setup();
	return 0;
}


void Debug::cycle(){
	if(millis()-time>=100){
		time=millis();
		if(stringAvailable()){
			if(mode==0){
				serial->printf(">>");
				if(!strcmp(str,"ready")) mode=READY;
				else availableFlag=0;
			}else if(mode==READY){
				serial->printf("[encoder][center][digital][analog][motor][dualshock]\n");
				serial->printf("\r>>");
				if(!strcmp(str,"encoder")) mode=ENCODER;
				else if(!strcmp(str,"center")) mode=CENTER;
				else if(!strcmp(str,"digital")) mode =DIGITAL;
				else if(!strcmp(str,"analog")) mode=ANALOG;
				else if(!strcmp(str,"motor")) mode=MOTOR;
				else if(!strcmp(str,"dualshock")) mode=DUALSHOCK;
				else availableFlag=0;
			}else if(mode==ENCODER){
				encoderCycle();
				if(!strcmp(str,"\n")) mode=READY;
			}else if(mode==CENTER){
				robotCenterCycle();
				if(!strcmp(str,"\n")) mode=READY;
			}else if(mode==DIGITAL){
				mode=READY;
			}else if(mode==ANALOG){
				mode=READY;
			}else if(mode==MOTOR){
				if(motorCycle()) mode=READY;
			}else if(mode==DUALSHOCK){
				dualShockCycle();
				if(!strcmp(str,"\n")) mode=READY;
			}
		}
	}
}

void Debug::serialReadChar(char value)
{
    rxBuffer.write(value);
    serial->printf("%c",value);
    if(value==DEFAULT_LINEFEED){
    	serial->printf("\n");
        char data[SERIAL_BUFFER_LENGTH];
        for(int i=0;i<SERIAL_BUFFER_LENGTH;i++){
            if(rxBuffer.isEmpty()){
                data[i]=0;
                break;
            }
            data[i]=rxBuffer.read();
            if(data[i]==DEFAULT_LINEFEED||i>=SERIAL_BUFFER_LENGTH-1){
                data[i]=0;
                availableFlag=1;
                serialReadString(data);
                break;
            }
        }
    }
}

void Debug::serialReadString(char *data){
	strcpy(str,data);
}

int Debug::motorCycle(){
	static int motorMode=0;
	static int num=10;static float duty=0.0;

	if(motorMode==0){
		if(!strcmp(str,"return")) return 1;
		serial->printf("[number] [duty]\n");
		serial->printf(">>");
		sscanf(str,"%d %f",&num,&duty);
		if((0<=num&&num<=9)&&(-1.0<=duty&&duty<=1.0)){
			motorMode=1;
		}else{
			availableFlag=0;
		}
	}else if(motorMode==1){
		serial->printf("num[%d], duty[%f]\n",num,duty);
		if(!strcmp(str,"\n")){
			motorMode=0;
			num=0;duty=0;
		}
		//md[num]->duty(duty);
		//md[num]->cycle();
	}
	return 0;
}

void Debug::encoderCycle(){
	//for(int i=0;i<3;i++)serial->printf("enc%d:,%d",i,enc[i]);
	serial->printf("\n");
}

void Debug::dualShockCycle(){
	serial->printf("lx:%.4f",ps3->lx());
	serial->printf("ly:%.4f",ps3->ly());
	serial->printf("rx:%.4f",ps3->rx());
	serial->printf("ry:%.4f",ps3->ry());
	serial->printf("u:%.4f",ps3->up());
	serial->printf("r:%.4f",ps3->right());
	serial->printf("d:%.4f",ps3->down());
	serial->printf("l:%.4f",ps3->left());
	serial->printf("tri:%.4f",ps3->triangle());
	serial->printf("cir:%.4f",ps3->circle());
	serial->printf("cro:%.4f",ps3->cross());
	serial->printf("squ:%.4f",ps3->square());
	serial->printf("l1:%.4f",ps3->l1());
	serial->printf("l2:%.4f",ps3->l2());
	serial->printf("r1:%.4f",ps3->r1());
	serial->printf("r2:%.4f",ps3->r2());
	serial->printf("st:%d",ps3->start());
	serial->printf("se:%d",ps3->select());
	serial->printf("dis:%d\n",ps3->disconnect());
}

void Debug::robotCenterCycle(){
	serial->printf("x:,%.4f,y:,%.4f,ang:,%.4f",center->x(),center->y(),rtod(center->getAngle()));
}
void Debug::setupDigitalIn(){

}
void Debug::setupDigitalOut(){

}
void Debug::setupAnalog(){

}
void Debug::setupEncoder(){
	//for(int i=0;i<3;i++) enc[i]->setup();
	//enc[0]->rev(true);enc[1]->rev(true);enc[2]->rev(true);
}
void Debug::setupMotor(){
	for(int i=4;i<8;i++){
		//md[i]->setup();
		//md[i]->duty(0);
	}
}
