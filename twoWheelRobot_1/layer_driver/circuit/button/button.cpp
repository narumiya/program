#include "button.hpp"


Button::Button(Digital &pinArg){
	pin=&pinArg;
}

Button::Button(Digital *pinArg){
	pin=pinArg;
}


int Button::setup(bool onWhenWhat,int millisArg){

	setChatteringTime(millisArg);
	setOnWhenHigh(onWhenWhat);
	return pin->setupDigitalInPullDown();
}

void Button::cycle(){
	if(millis()-time>CHATTERING_TIME){
		outputState=pin->digitalRead();
	}else{
		if(pin->digitalRead()!=outputState) time=millis();
	}
}

int Button::value(){
	if(CHATTERING_TIME!=0) return !(onWhenHigh^outputState);//xnor
	else return !(onWhenHigh^pin->digitalRead());//xnor
}

void Button::setChatteringTime(int millisArg){
	CHATTERING_TIME=millisArg;
}

void Button::setOnWhenHigh(bool onArg){
	onWhenHigh=onArg;
}
