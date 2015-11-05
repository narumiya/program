#include "ina226.hpp"
#include "pin.hpp"
#include "config_i2c.h"
#include "mcutime.h"

Ina226::Ina226(I2c &i2cPin){
	i2cPin.addInterface(this);
	voltage=0;
	current=0;
	flag=0;
}

int Ina226::setup(){
	unsigned char data[4]={0};
	const float MaxCurrent=0.148;
	const float shunt=0.002;
	float calibra=0.00512/((MaxCurrent/32768)*shunt);
	i2cSetup();
	time=millis();
	readAddress=0x81;
	sendAddress=0x80;
	data[0]=0x00;//設定レジスタ
	data[1]=0x45;//モードと時間0x42
	data[2]=0x27;//時間0x07
	i2cWrite(sendAddress,data,3,TX);
	calibra=2560;
	data[0]=0x05;//キャリブレレジスタ
	data[1]=((int)(calibra)>>8);
	data[2]=(int)(calibra)&0xFF;
	i2cWrite(sendAddress,data,3,TX);
	return 0;
}

int Ina226::i2cAddress(int address){
	if(I2c0::directionFlag==RX){
		return address==readAddress;
	}else{
		return address==sendAddress;
	}
}

void Ina226::i2cRead(unsigned char *data){
	int value=((data[1])& 0xFF)|((data[0]<<8)&0xFF00);
	if(value>32768) value=value-65536;
	if(flag==1){
		current=(float)value*2.5/2.0;
	}else if(flag==2){
		voltage=(float)value*1.25;
	}
}

void Ina226::i2cReStartSend(char data){
	if(data==0x01){
		//シャント電圧
		flag=1;
		I2c0::rxBufferSize=2;
		I2c0::rxSlaveAddress=readAddress;
		I2c0::directionFlag=RX;
		I2C_GenerateSTART(I2C2, ENABLE);
	}else if(data==0x02){
		//電圧読み込み
		flag=2;
		I2c0::rxBufferSize=2;
		I2c0::rxSlaveAddress=readAddress;
		I2c0::directionFlag=RX;
		I2C_GenerateSTART(I2C2, ENABLE);
	}
}

void Ina226::cycle(){
	unsigned char data[3];
	static int change=0;

	if(millis()-time>=10){
		time=millis();
		if(change==0){
			//シャント電圧
			data[0]=0x01;data[1]=0x00;
			i2cWrite(sendAddress,data,1,TX);
			change=1;
		}else if(change==1){
			//電圧
			data[0]=0x02;data[1]=0x00;
			i2cWrite(sendAddress,data,1,TX);
			change=0;
		}
	}
}
