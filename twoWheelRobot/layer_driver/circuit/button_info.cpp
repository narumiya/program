#include "button_info.hpp"
#include "mcutime.h"

ButtonInfo::ButtonInfo(Digital &digitalPin){
	pin=&digitalPin;
	raw=0;
	info=0;
	count=0;
	upEdge=0;
	downEdge=0;
	state=0;
	timer=0;
	old=0;
	chatTime=0;
	normalyClose=false;
	cycleTime=millis();
}

int ButtonInfo::setup(bool normaly,int time){
	normalyClose=normaly;
	chatTime=time;
	return pin->setupDigitalInPullDown();
}

void ButtonInfo::cycle(){
	if(millis()-cycleTime>=5){
		cycleTime=millis();

		raw=pin->digitalRead();

		if(raw!=state) timer+=5;
		else timer=0;

		if(timer>=chatTime){
			timer=0;
			state=!state;
			if(state) count++;
		}
		info=state;
		if(normalyClose) info=~info&1;

		if(info==1 && old==0){
			upEdge=1;downEdge=0;
		}else if(info==0&&old==1){
			upEdge=0;downEdge=1;
		}else{
			upEdge=0;downEdge=0;
		}
		old=info;
	}
}
