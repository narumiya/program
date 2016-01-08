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
	int targetAngle[4];
	int servoAngle[4];
	unsigned long long int time;
	int Id;
public:
	KondoServo(Pwm &pwmPin);
	KondoServo(Serial &serialPin);
	int setup();
	using Servo::setAngle;
	void setAngle(int id,float angle);
	void rec(int id,char data);
	void cycle();
	float getAngle(int id);
	int radToPos(float degree);
	float posToRad(int pos);
	int readPara(int id,int mode);
	int setPara(int id,int mode,float value);

	/*�����Ӂ�
	 * ID �R�}���h���g�p����ۂ́A
	 * �K�����葤�ƃV���A���T�[�{���P�΂P�Őڑ����邱�ƁI
	 */
	int setId(int id,int mode);
};

#endif