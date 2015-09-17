#ifndef SERVO_CONTROLL_HPP
#define SERVO_CONTROLL_HPP

#include "layer_driver/base/serial.hpp"
#include "layer_driver/circuit/servo.hpp"
#include "layer_application/console.hpp"

class ServoControll:public ConsoleCommand,public SerialInterface{
private:
	Servo *servo;
public:
	ServoControll(Servo &servoPin,Serial &serialPin,Console &console):ConsoleCommand(console){servo=&servoPin;serial=&serialPin;};
	int commandCompare(char *str){return !strcmp(str,"servo");}
	int commandRequest(int argc,char **argv);
};
#endif
