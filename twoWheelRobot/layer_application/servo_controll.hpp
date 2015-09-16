#ifndef SERVO_CONTROLL_HPP
#define SERVO_CONTROLL_HPP

#include "layer_driver/base/serial.hpp"
#include "layer_driver/circuit/servo.hpp"

class ServoControll:public SerialInterface{
private:
	Servo *servo;
public:
	ServoControll(Serial &serialPin,Servo &servoPin);
	int setup();
};
#endif
