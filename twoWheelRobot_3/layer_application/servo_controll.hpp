#ifndef SERVO_CONTROLL_HPP
#define SERVO_CONTROLL_HPP

#include "layer_driver/base/serial.hpp"
#include "layer_driver/circuit/servo.hpp"
#include "layer_application/console.hpp"
#include "layer_driver/base/pwm.hpp"
#include "layer_driver/circuit/fun.hpp"
class ServoControll:public ConsoleCommand{
private:
	enum{
		DEG=1,
		PULSE=2,
	};
	Servo *servo;
	Fun *fun;
	int mode;
	float degree;
	float value;
	void moveCycle();
	void designateAngleCycle();
	void pulseCycle();
public:
	ServoControll(Servo &servoPin,Console &console):ConsoleCommand(console){servo=&servoPin;mode=0;};
	ServoControll(Servo &servoPin,Fun &funPin,Console &console):ConsoleCommand(console){servo=&servoPin;fun=&funPin;mode=0;};
	int setup();
	int commandCycle();
	void consoleReadChar(char data);
	int commandCompare(char *str){return !strcmp(str,"servo");}
	int commandRequest(int argc,char **argv);
	void cycle();
};
#endif
