#include "robo_center.hpp"
extern "C"{
#include <math.h>
#include "mcutime.h"
#include "calculate.h"
#include "util.h"
}
roboCenter::roboCenter(Encoder &enc,R1350n &gyroPin,ButtonInfo &resetPin){
	enc0=&enc;
	gyro=&gyroPin;
	resetSw=&resetPin;
	x=0.0;y=0.0;z=0.0;
	angle=0.0;
	oldValue=0.0;
}

int roboCenter::setup(){
	int i=enc0->setup();
	i+=gyro->setup();
	resetSw->setup(true,50);
	time=millis();
	enc0->mlt(33.2);
	enc0->rev(false);
	enc0->cpr(1000.0);
	initValue=enc0->value();
	initAngle=gyro->angle();
	/*while((millis()-initTime<=4000)){
		initaccx=gyro.accelx();// *9806.65/4095;
	}*/
	return i;
}

void roboCenter::cycle(){
	resetSw->cycle();
	if(millis()-time>=10){
		time=millis();
		if(resetSw->readValue()){
			initValue=enc0->value();
			oldValue=enc0->value()-initValue;
			gyro->reset();
			x=0.0;y=0.0;
		}
		value=enc0->value()-initValue;
		//printf("%f\n",value);
		//angle=gyro->angle()-initAngle;
		angle=gyro->angle();
		angle*=(-1.0);
		float def=value-oldValue;
		float theta=area(angle+radiusReverse(value-oldValue),-M_PI,M_PI);
		x+=fabs(def)*cos(theta);
		y+=fabs(def)*sin(theta);
		oldValue=value;
	}
}
float roboCenter::getX(){
	return x;
}float roboCenter::getY(){
	return y;
}
float roboCenter::getAngle(){
	return angle;
}
void roboCenter::accCycle(){
	const float alfa=0.1;
	//const float threshold=4.0;
	static float currentOrientationValuesOld[3]={0};
//	static float oldX=0.0,oldY=0.0,oldZ=0.0;
	//static float vectorSixeMax=0.0;
	static float oldVelocity=0.0;
	static float location=0.0;
	static float wait=0.0;
	static float oldAcc=0.0;
	//static bool noiseflg=false;
	//static bool counted=false;
	float currentOrientationValues[3]={0};
	//float currentAccelerationValues[3]={0};

	resetSw->cycle();
	if(millis()-time>=10){
		time=millis();
		float accx=((gyro->accelx()-initAccx)/1000.0)*9.80;
		float accy=(gyro->accely()/1000.0)*9.80;
		float accz=(gyro->accelz()/1000.0)*9.80;
		//ローパスフィルタ
		currentOrientationValues[0]=currentOrientationValuesOld[0]*(1.0-alfa)+accx*alfa;
		currentOrientationValues[1]=currentOrientationValuesOld[1]*(1.0-alfa)+accy*alfa;
		currentOrientationValues[2]=currentOrientationValuesOld[2]*(1.0-alfa)+accz*alfa;
		//重力の値を省く
		//currentAccelerationValues[0]=accx-currentOrientationValues[0];
		//currentAccelerationValues[1]=accy-currentOrientationValues[1];
		//currentAccelerationValues[2]=accz-currentOrientationValues[2];
		// ベクトル値を求めるために差分を計算
		/*float dx = currentAccelerationValues[0] - oldX;
		float dy = currentAccelerationValues[1] - oldY;
		float dz = currentAccelerationValues[2] - oldZ;
		oldX = currentAccelerationValues[0];
		oldY = currentAccelerationValues[1];
		oldZ = currentAccelerationValues[2];
		float vectorSize=sqrtf(dx * dx + dy * dy + dz * dz);
		 // 一回目はノイズになるから省く
		if (noiseflg == true) {
			noiseflg = false;
		} else {
			if (vectorSize>threshold){
				if(counted){
					printf("accx:,%f,accz:,%f,vector:,%f\n",dx,dz,vectorSize);
					counted=false;
					if(vectorSize>vectorSixeMax){
						vectorSixeMax=vectorSize;
					}
				}else if(!counted){
					counted=true;
				}
			}
		}*/
		for(int i=0;i<3;i++)
			currentOrientationValuesOld[i]=currentOrientationValues[i];

		if(fabs(currentOrientationValues[0])<=0.07){
			velocity=0;
			currentOrientationValues[0]=0;
		}
		if(wait>=100){
			velocity+=((currentOrientationValues[0]+oldAcc)*0.01)/2.0;//[m/s]
			location+=((velocity+oldVelocity)*0.01)/2.0;//[m]
			x=location*1000.0;
			oldAcc=currentOrientationValues[0];
			oldVelocity=velocity;
		}else{
			wait+=10;
		}
	}
}

