#include "servo_controll.hpp"

ServoControll::ServoControll(Serial &serialPin,Servo &servoPin){
	serial=&serialPin;
	servo=&servoPin;
}

int ServoControll::setup(){
	serialInterfaceSetup(serial);
	serial->setup(115200);
	servo->setup(30,270,1.5,2.3);
	return 0;
}
