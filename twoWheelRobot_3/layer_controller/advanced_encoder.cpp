#include "advanced_encoder.hpp"
#include "mcutime.h"
#include <math.h>
#include "util.hpp"

AdvancedEncoder::AdvancedEncoder(Encoder &enc,int cpr){
	this->enc=&enc;
	this->cprData=cpr;

	time=0;
	lastCountChangeMicros=0;
	oldCount=0;
	oldVelocity=0;

	maxVelIntervalMicros=50000;

	countData=0;
	rpsData=0;
	rps2Data=0;
}
int AdvancedEncoder::setup(){
	return enc->setup();
}
void AdvancedEncoder::cycle(){
	int dtMicros=micros()-time;
	time=micros();
	if(dtMicros<=0) return;
	int gap=enc->count()-oldCount;
	oldCount=enc->count();

	if(revFlag)gap*=-1;

	//Max permissible revolution of encoders of omron is 5000 r/min
	//If over the value, this is wrong value.
	//if(gap>=cprData*dtMicros/12000||gap<=-cprData*dtMicros/12000)return;//5000*cpr/60*(dtMicros/1000000)
	if(gap>=cprData*dtMicros/6000||gap<=-cprData*dtMicros/6000)return;//10000*cpr/60*(dtMicros/1000000)
	countData+=gap;
	if(micros()-lastCountChangeMicros==0) return;
	if(gap!=0)rpsData=gap*1000000/cprData/(float)(micros()-lastCountChangeMicros);//gap/(dtMicros/1000000)/cprData
	if(micros()-lastCountChangeMicros>maxVelIntervalMicros)rpsData=0.0;
	if(gap!=0)lastCountChangeMicros=micros();
}

int AdvancedEncoder::count(){
	return countData;
}

float AdvancedEncoder::revolution(){
	return (float)countData/cprData;
}

float AdvancedEncoder::radian(){
	return 2.0*M_PI*(float)countData/cprData;
}

float AdvancedEncoder::rps(){
	return rpsData;
}
float AdvancedEncoder::rps2(){
	return rps2Data;
}

float AdvancedEncoder::rads(){
	return rpsData*2*M_PI;
}
float AdvancedEncoder::rads2(){
	return rps2Data*2*M_PI;
}
