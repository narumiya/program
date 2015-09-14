#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "serial.hpp"
#include "circuit/md.hpp"
#include "pin.hpp"
#include "circuit/dual_shock.hpp"
#include "robotCenter.hpp"

class Debug:public SerialInterface{
private:
	Serial *serial;
	RobotCenter *center;
	DualShock *ps3;
	char str[256];
	int time;
	int availableFlag;
	int mode;
	int setupMode;
	//Encoder **enc;
	Md md[5];
	A0 a0;A1 a1; A2 a2;
	//CW1 cw5;CCW1 ccw5;Pwm1 pwm5;Md md5(cw5,ccw5,pwm5);
	//CW2 cw6;CCW2 ccw6;Pwm2 pwm6;Md md6(cw6,ccw6,pwm6);
	//CW3 cw7;CCW3 ccw7;Pwm3 pwm7;Md md7(cw7,ccw7,pwm7);
	/*Cw4 cw4;Ccw4 ccw4;Pwm4 pwm4;Md md4(cw4,ccw4,pwm4);
	Cw5 cw5;Ccw5 ccw5;Pwm5 pwm5;Md md5(cw5,ccw5,pwm5);
	Cw6 cw6;Ccw6 ccw6;Pwm6 pwm6;Md md6(cw6,ccw6,pwm6);
	Cw7 cw7;Ccw7 ccw7;Pwm7 pwm7;Md md7(cw7,ccw7,pwm7);*/
	enum{
		READY=1,
		ENCODER,
		CENTER,
		DUALSHOCK,
		DIGITAL,
		ANALOG,
		MOTOR
	};
	void setupDigitalIn();
	void setupDigitalOut();
	void setupAnalog();
	void setupEncoder();
	void setupMotor();
	int motorCycle();
	void encoderCycle();
	void robotCenterCycle();
	void dualShockCycle();
public:
	Debug(Serial &serialPin,RobotCenter &robot,DualShock &con);
	int setup();
	int stringAvailable(){return availableFlag;}
	void serialReadChar(char value);
	void serialReadString(char *data);

	void cycle();

};

#endif
