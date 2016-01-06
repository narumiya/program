#include "kondo_servo.hpp"
#include "util.h"
#include "mcutime.h"
#include "config_usart.h"

KondoServo::KondoServo(Pwm &pwmPin){
	mode=PWM;
	pwm=&pwmPin;
}

KondoServo::KondoServo(Serial &serialPin){
	mode=SERIAL;
	serial=&serialPin;
	for(int i=0;i<4;i++){
		targetAngle[i]=0;
		servoAngle[i]=0;
	}
}

int KondoServo::setup(){
	if(mode==PWM){
		period = 30.0;
		rangeRad = dtor(270);
		neutPulse = 1.5;
		maxPulse = 2.3;
		pwm->setupPwmOut(1/(period/1000),0);
		delay_ms(500);
	}else if(mode==SERIAL){
		serial->setup(115200,USART_Parity_Even,USART_WordLength_9b);
		time=millis();
		Id=0;
	}
	return 0;
}

void KondoServo::setAngle(int id,float angle){
	Id=id;
	targetAngle[id]=radToPos(angle);
}

void KondoServo::rec(int id,char data){
	static int angleVerify[4]={0};
	static int cnt[4]={0};
	static char msg[4][3]={0x00};
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

void KondoServo::cycle(){

	if(mode==PWM){
		pwm->pwmWrite(request);
	}else if(mode==SERIAL){
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
}

float KondoServo::getAngle(int id){
	return posToRad(servoAngle[id]);
}

int KondoServo::radToPos(float degree){
	return (int)((4000.0/dtor(135.0))*degree)+7500.0;
}

float KondoServo::posToRad(int pos){
	return (((dtor(135.0)/4000.0))*(float)(pos) - (7500.0*dtor(135.0))/4000.0);
}

/*
 * mode	2 ストレッチ
 * 			3 スピード
 */
int KondoServo::readPara(int id,int mode){
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
int KondoServo::setPara(int id,int mode,float value){
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

int KondoServo::setId(const int id,const int mode){
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
