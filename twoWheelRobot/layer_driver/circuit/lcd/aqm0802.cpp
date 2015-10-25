#include "aqm0802.hpp"

#include "mcutime.h"
#include <string.h>
#include <stdio.h>

Aqm0802::Aqm0802(I2c &i2cPin){
	address=0x7C;
	i2cPin.addInterface(this);
}

int Aqm0802::setup(){
	char data[3]={0};
	i2cSetup();
	data[0]=0x00;
	data[1]=0x38;
	i2cWrite(0x7C,data,2,TX);delay_ms(2);
	data[1]=0x39;
	i2cWrite(0x7C,data,2,TX);delay_ms(2);
	data[1]=0x14;
	i2cWrite(0x7C,data,2,TX);delay_ms(2);
	data[1]=0x70;
	i2cWrite(0x7C,data,2,TX);delay_ms(2);
	data[1]=0x56;
	i2cWrite(0x7C,data,2,TX);delay_ms(2);
	data[1]=0x6C;
	i2cWrite(0x7C,data,2,TX);delay_ms(2);
	data[1]=0x38;
	i2cWrite(0x7C,data,2,TX);delay_ms(2);
	data[1]=0x0C;
	i2cWrite(0x7C,data,2,TX);delay_ms(2);
	data[1]=0x01;
	i2cWrite(0x7C,data,2,TX);delay_ms(10);
	return 0;
}

void Aqm0802::sendString(const char *data){
	char send[10]={'\0'};
	send[0]=0x40;
	for(int i=0;*(data+i)!='\0';i++){
		send[i+1]=*(data+i);
	}
	int size=(int)strlen(send);
	i2cWrite(0x7C,send,size,TX);
}

void Aqm0802::sendChar(const char data){
	char send[2];
	send[0]=0x40;send[1]=data;
	i2cWrite(0x7C,send,2,TX);
}

void Aqm0802::setCursor(const char x,const char y){
	char data[2];
	data[0]=0x00;
	data[1]=0x80|y*0x40|x;
	i2cWrite(0x7C,data,2,TX);
}

void Aqm0802::clear(){
	char data[2];
	data[0]=0x00;
	data[1]=0x01;
	i2cWrite(0x7C,data,2,TX);
}
