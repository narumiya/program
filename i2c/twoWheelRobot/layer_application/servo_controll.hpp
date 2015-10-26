#ifndef SERVO_CONTROLL_HPP
#define SERVO_CONTROLL_HPP

#include "layer_driver/base/serial.hpp"
#include "layer_driver/circuit/servo.hpp"
#include "layer_application/console.hpp"

class ServoControll:public ConsoleCommand{
private:
	enum{
		DEG=1,
	};
	Servo *servo;
	int mode;
	float degree;
	void moveCycle();
	void designateAngleCycle();
public:
	ServoControll(Servo &servoPin,Console &console):ConsoleCommand(console){servo=&servoPin;mode=0;};
	int commandCompare(char *str){return !strcmp(str,"servo");}
	int commandRequest(int argc,char **argv);
	void cycle();
};
#endif
