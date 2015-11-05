#include "kondo_servo.hpp"

KondoServo::KondoServo(Pwm &pwmPin){
	mode=PWM;
	pwm=&pwmPin;
}

KondoServo::KondoServo(Serial &serialPin){
	mode=SERIAL;
	serial=&serialPin;
}

