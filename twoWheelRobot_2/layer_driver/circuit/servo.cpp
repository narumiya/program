#include <math.h>
#include "servo.hpp"
#include "mcutime.h"
#include "pin.hpp"
#include "util.h"
#include <stdio.h>


Servo::Servo(Pwm &pwmPin){
	pwm=&pwmPin;
}

int Servo::setup(float setPeriod, float setRangeRad, float setNeutral, float setMaxPulse){
	period = setPeriod;
	rangeRad = setRangeRad;
	neutPulse = setNeutral;
	maxPulse = setMaxPulse;
	pwm->setupPwmOut((1.0/(period/1000.0)),1);
	delay_ms(500);
	return 0;
}

void Servo::setAngle(float rad){
	float duty=0.0;

	duty=cvtPulse(rad);
	request= duty;
}

void Servo::setDuty(float pos){
	request=pos;
}

float Servo::cvtPulse(float rad){
	float pulseWidth=0.0;
	pulseWidth=(fabs(maxPulse-neutPulse)/fabs(rangeRad/2.0))*rad+neutPulse;
	return (pulseWidth/period);
}
float Servo::getVelocity(){
	const float rad=dtor(60.0);
	const float time=0.15;
	return (time/rad);
}
void Servo::cycle(){
	if(fabs(oldRequest-request)>=cvtPulse(dtor(10.0))){
		if((oldRequest-request)<0){
			pwm->pwmWrite(fabs(1.0-(request-oldRequest)/2.0));
			oldRequest=(request-oldRequest)/2.0;
		}else{
			pwm->pwmWrite(fabs(1.0-(oldRequest-request)/2.0));
			oldRequest=(oldRequest-request)/2.0;
		}
	}else{
		pwm->pwmWrite(fabs(1.0-request));
		oldRequest=request;
	}
}

#if 0
Servo::Servo(Pwm &pwmPin){
	pwm=&pwmPin;
	time=millis();
}

Servo::Servo(Serial &serialPin){
	serial=&serialPin;
	for(int i=0;i<NUM;i++){
		targetAngle[i]=0;
		servoAngle[i]=0;
	}
	time=millis();
	Id=0;
}

int Servo::setup(float setPeriod, float setRangeDeg, float setNeutral, float setMaxPulse){
	Period = setPeriod;
	RangeDeg = setRangeDeg;
	NeutPulse = setNeutral;
	MaxPulse = setMaxPulse;
	pwm->setupPwmOut(1/(Period/1000),0);
	delay_ms(500);
	return 0;
}

int Servo::setup(){
	serial->setup(115200,USART_Parity_Even,USART_WordLength_9b);
	return 0;
}

void Servo::setAngle(float rad){
	static float old=0.0;
	float duty=0.0;
	//if(!((-RangeDeg/2.0)<=deg && deg <=(RangeDeg/2.0)))
	if(!(dtor((-RangeDeg/2.0))<=rad && rad <=dtor((RangeDeg/2.0))))
		request=old;
	else{
		//duty = (fabs(MaxPulse-NeutPulse)) / (Period * fabs(RangeDeg/2.0)) * deg + NeutPulse/Period;
		duty=cvtPulse(rad);
		request= duty;
		old=duty;
	}
}

void Servo::setDuty(float pos){
	static float old=0.0;
	float duty;
	if((NeutPulse-fabs(MaxPulse-NeutPulse))/Period<=pos && pos<=MaxPulse/Period){//neutPulse-(MaxPulse-neutPulse)
		duty=pos;
		request=duty;
		old=duty;
	}else{
		request=old;
	}
}

float Servo::cvtPulse(float rad){
	//return (fabs(MaxPulse-NeutPulse)) / (Period * fabs(RangeDeg/2.0)) * deg + NeutPulse/Period;
	return  (fabs(MaxPulse-NeutPulse)) / (Period * dtor(fabs(RangeDeg/2.0))) *rad + NeutPulse/Period;
}

void Servo::cycle(){
	pwm->pwmWrite(request);
}
void Servo::setAngle(int id,float angle){
	Id=id;
	targetAngle[id]=degToPos(angle);
}

void Servo::rec(int id,char data){
	static int angleVerify[NUM]={0};
	static int cnt[NUM]={0};
	static char msg[NUM][3]={0x00};
	int pos=0;

	if(data & (id | 0x80)){
		cnt[id]=0;
	}else if(cnt[id]<3){
		msg[id][cnt[id]]=data;
		if(cnt[id]==2){
			pos=(int)(msg[id][1]<<7 | msg[id][2]);
			if(pos!=targetAngle[id] || pos==angleVerify[id]){
				servoAngle[id]=pos;
			}
			angleVerify[id]=pos;
		}
	}
	cnt[id]++;
}

void Servo::serialCycle(){
	int data=0;
	char msg[3]={0x00};

	if(millis()-time>=5){
		time=millis();
		data=targetAngle[Id];
		msg[0] = 0x80 | Id;
		msg[1] = (data>>7) & 0x7f;
		msg[2] = data & 0x7f;
		for(int i=0; i<3;i++){
			serial->writeChar(msg[i]);
		}
		while(serial->charAvailable())
			rec(Id,serial->readChar());
	}
}

float Servo::getAngle(int id){
	return posToDeg(servoAngle[id]);
}

int Servo::degToPos(float degree){
	if(degree==FREE){
		return 0;
	}else{
		return (int)((4000.0/135.0)*degree)+7500.0;
	}
}

float Servo::posToDeg(int pos){
	return (((135.0/4000.0))*(float)(pos) - (7500.0*135.0)/4000.0);
}

/*
 * mode	2 ストレッチ
 * 			3 スピード
 */
int Servo::readPara(int id,int mode){
	char msg[2]={0x00};
	char data[3]={0x00};
	int cnt=0;
	msg[0]= 0xA0 | id;
	msg[1]= mode;

	for(int i=0;i<2;i++){
		serial->writeChar(msg[i]);
	}
	if(mode==2){
		while(serial->charAvailable()){
			data[cnt]=serial->readChar();
			cnt++;
		}
		return (int)data[2];
	}else if(mode==3){
		while(serial->charAvailable()){
			data[cnt]=serial->readChar();
			cnt++;
		}
		return (int)data[2];
	}
	return 0;
}
/*
 * mode	2 ストレッチ
 * 			3 スピード
 * value 0~1
 */
int Servo::setPara(int id,int mode,float value){
	char msg[3]={0x00};
	char data[3]={0x00};
	int cnt=0;

	msg[0]=0xC0 | id;
	msg[1]=mode;
	if(value==0){
		msg[2]=1;
	}else{
		msg[2]=(char)(127*value);
	}

	for(int i=0;i<3;i++){
		serial->writeChar(msg[i]);
	}
	while(serial->charAvailable()){
		data[cnt]=serial->readChar();
		cnt++;
	}
	return (int)data[2];
}

/*＜注意＞
 * ID コマンドを使用する際は、必ず送り側とシリアルサーボを１対１で接続すること！
 * mode 	0 id読み込み
 * 			1 id書き込み
 */

int Servo::setId(const int id,const int mode){
	char msg[4]={0x00};

	msg[0]=0xE0|id;
	for(int i=1;i<4;i++){
		msg[i]=mode;
	}
	for(int i=0;i<4;i++){
		serial->writeChar(msg[i]);
	}

	return (int)(serial->readChar() ^ 0xE0);
}
#endif
