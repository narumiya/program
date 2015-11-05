#ifndef	KONDO_SERVO_HPP
#define	KONDO_SERVO_HPP

#include "servo.hpp"
#include "serial.hpp"

class KondoServo:public Servo,public SerialInterface{
private:
	int mode;
	enum{
		PWM,
		SERIAL
	};
	unsigned long long int time;
	int Id;
public:
	KondoServo(Pwm &pwmPin);
	KondoServo(Serial &serialPin);
};

#endif
