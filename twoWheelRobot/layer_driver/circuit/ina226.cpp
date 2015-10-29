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
	unsigned char data[3]={0};
	const float MaxCurrent=100.0;
	const float shunt=0.002;
	float calibra=0.00512/((MaxCurrent/32768)*shunt);
	i2cSetup();
	time=millis();
	readAddress=0x81;
	sendAddress=0x80;
	data[0]=0x00;//設定レジスタ
	data[1]=0x07;//モードと時間
	data[3]=0x02;//時間
	i2cWrite(sendAddress,data,3,TX);
	data[0]=0x05;//キャリブレレジスタ
	data[1]=(int)(calibra)&0xFF;
	data[2]=((int)(calibra)>>8)&0xFF;
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

void Ina226::i2cRead(char *data){
	if(flag==1){//電圧
		voltage=data[0]|data[1]<<8;
		voltage*=1.25;
	}else if(flag==2){
		current=data[0]|data[1]<<8;
	}
}

void Ina226::i2cReStartSend(char data){
	if(data==0x02){
		//電圧読み込み
		flag=1;
		I2c0::rxBufferSize=2;
		I2c0::rxSlaveAddress=readAddress;
		I2c0::directionFlag=RX;
		I2C_GenerateSTART(I2C2, ENABLE);
	}else if(data==0x04){
		//電圧読み込み
		flag=2;
		I2c0::rxBufferSize=2;
		I2c0::rxSlaveAddress=readAddress;
		I2c0::directionFlag=RX;
		I2C_GenerateSTART(I2C2, ENABLE);
	}
}

void Ina226::cycle(){
	unsigned char data[2];
	if(millis()-time>=5){
		time=millis();
		data[0]=0x02;data[1]=0x00;
		i2cWrite(sendAddress,data,1,TX);
		data[0]=0x04;data[1]=0x00;
		i2cWrite(sendAddress,data,1,TX);
	}
}
