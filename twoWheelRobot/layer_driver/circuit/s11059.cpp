#include "s11059.hpp"
#include "mcutime.h"
#include "pin.hpp"
#include "config_i2c.h"
#include <stdio.h>
S11059::S11059(I2c &i2cPin){
	readAddress=0x55;
	sendAddress=0x54;
	mode=0;
	i2cPin.addInterface(this);
	red=0;
	green=0;
	blue=0;
	infrared=0;
}

int S11059::setup(){
	time=millis();
	return i2cSetup();
}

void	S11059::i2cRead(char *data){
	red=data[0]<<8 | data[1];
	green=data[2]<<8 | data[3];
	blue=data[4]<<8 | data[5];
	infrared=data[6]<<8 | data[7];
}

void S11059::cycle(){
	static int flag=0;
	unsigned char data[3]={'\0'};

	if(millis()-time>=10){
		time=millis();
		if(flag==0){
			if(mode==LOW){
				data[0]=0x00;data[1]=0x84;
				i2cWrite(0x54,data,2,TX);
				flag=1;
			}else if(mode==HIGH){
				data[0]=0x00;data[1]=0x89;
				i2cWrite(0x54,data,2,TX);
				flag=1;
			}
		}else if(flag==1){
			if(mode==LOW){
				data[0]=0x00;data[1]=0x04;
				i2cWrite(0x54,data,2,TX);
				flag=2;
			}else if(mode==HIGH){
				data[0]=0x00;data[1]=0x09;
				i2cWrite(0x54,data,2,TX);
				flag=2;
			}
		}else if(flag==2){
			flag=3;
		}else if(flag==3){
			data[0]=0x03;data[1]=0x00;
			i2cWrite(0x54,data,1,TX);
		}
	}
}

int S11059::i2cAddress(int address){
	if(I2c0::directionFlag==RX){
		return address==readAddress;
	}else{
		return address==sendAddress;
	}
}

void S11059::i2cReStartSend(char data){
	if(data==0x03){
		I2c0::rxBufferSize=8;
		I2c0::rxSlaveAddress=0x55;
		I2c0::directionFlag=RX;
		I2C_GenerateSTART(I2C2, ENABLE);
	}
}
