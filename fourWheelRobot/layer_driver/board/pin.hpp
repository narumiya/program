#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED

#include "serial.hpp"
#include "digital.hpp"
#include "Analog.hpp"
#include "encoder.hpp"
#include "pwm.hpp"

/**********IO****************************/
class Led0:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Led1:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D0:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D1:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D2:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D3:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D4:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D5:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D6:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D7:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D8:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class D9:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw0:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw0:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw1:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw1:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw2:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw2:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw3:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw3:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw4:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw4:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw5:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw5:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw6:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw6:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw7:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw7:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw8:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw8:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Cw9:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};

class Ccw9:public Digital{
private:
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();
public:

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator int() {
		return digitalRead();
	}
};
/***********AD**************************/
class A0:public Digital,public Analog{
private:
	enum{
		MODE_NULL,
		MODE_ANALOG,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupAnalogIn();
	float _analogRead();
public:
	A0(){mode=0;};

	int analogResolution(){return 4095;};
	float analogVoltage(){return 3.3;};
	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		return analogRead();
	}
};

class A1:public Digital,public Analog{
private:
	enum{
		MODE_NULL,
		MODE_ANALOG,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupAnalogIn();
	float _analogRead();
public:
	A1(){mode=0;};

	int analogResolution(){return 4095;};
	float analogVoltage(){return 3.3;};

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		return analogRead();
	}
};

class A2:public Digital,public Analog{
private:
	enum{
		MODE_NULL,
		MODE_ANALOG,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupAnalogIn();
	float _analogRead();
public:
	A2(){mode=0;};

	int analogResolution(){return 4095;};
	float analogVoltage(){return 3.3;};

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		return analogRead();
	}
};

class A3:public Digital,public Analog{
private:
	enum{
		MODE_NULL,
		MODE_ANALOG,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupAnalogIn();
	float _analogRead();
public:
	A3(){mode=0;};

	int analogResolution(){return 4095;};
	float analogVoltage(){return 3.3;};

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		return analogRead();
	}
};

class A4:public Digital,public Analog{
private:
	enum{
		MODE_NULL,
		MODE_ANALOG,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupAnalogIn();
	float _analogRead();
public:
	A4(){mode=0;};

	int analogResolution(){return 4095;};
	float analogVoltage(){return 3.3;};

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		return analogRead();
	}
};

class A5:public Digital,public Analog{
private:
	enum{
		MODE_NULL,
		MODE_ANALOG,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupAnalogIn();
	float _analogRead();
public:
	A5(){mode=0;};

	int analogResolution(){return 4095;};
	float analogVoltage(){return 3.3;};

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		return analogRead();
	}
};

class A6:public Digital,public Analog{
private:
	enum{
		MODE_NULL,
		MODE_ANALOG,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupAnalogIn();
	float _analogRead();
public:
	A6(){mode=0;};

	int analogResolution(){return 4095;};
	float analogVoltage(){return 3.3;};

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		return analogRead();
	}
};

class A7:public Digital,public Analog{
private:
	enum{
		MODE_NULL,
		MODE_ANALOG,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupAnalogIn();
	float _analogRead();
public:
	A7(){mode=0;};

	int analogResolution(){return 4095;};
	float analogVoltage(){return 3.3;};

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		return analogRead();
	}
};

/********pwm****************/
class Pwm0:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm0(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};

class Pwm1:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm1(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};
class Pwm2:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm2(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};

class Pwm3:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm3(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};

class Pwm4:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm4(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};

class Pwm5:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm5(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};

class Pwm6:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm6(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};

class Pwm7:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm7(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};
class Pwm8:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm8(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};

class Pwm9:public Digital,public Pwm{
private:
	enum{
		MODE_NULL,
		MODE_PWM,
		MODE_DIGITAL
	};
	int mode;
	int _digitalWrite();
	void _digitalWrite(int value);
	int _digitalRead();
	int _setupDigitalIn();
	int _setupDigitalOut();
	int _setupDigitalInPullUp();
	int _setupDigitalInPullDown();

	int _setupPwmOut(float frequency,float duty);
	void _pwmWrite(float duty);
	float _pwmWrite();
public:
	Pwm9(){mode=0;}

	Digital& operator= (int value) {
		digitalWrite(value);
		return *this;
	}

	Digital& operator= (Digital& dig) {
		digitalWrite(dig.digitalRead());
		return *this;
	}

	Pwm& operator= (float value) {
		pwmWrite(value);
		return *this;
	}

	Pwm& operator= (Pwm& pwm) {
		pwm.pwmWrite(pwm.pwmWrite());
		return *this;
	}

	operator bool(){
		return digitalRead();
	}

	operator int() {
		return digitalRead();
	}

	operator float() {
		if (mode==MODE_PWM)return pwmWrite();
		else return 0.0;
	}
};
/********encoder*************/
class Enc0:public Encoder{
public:
	int setup();
	int count();

	operator int() {
		return count();
	}
};

class Enc1:public Encoder{
public:
	int setup();
	int count();
	operator int() {
		return count();
	}
};

class Enc2:public Encoder{
public:
	int setup();
	int count();
	operator int() {
		return count();
	}
};

class Enc3:public Encoder{
public:
	int setup();
	int count();
	operator int() {
		return count();
	}
};


/*********Serial*************/
class Serial0:public Serial{
private:
	static SerialInterface *interface;
	int _setup(int baudrate, SerialInterface &interfaceArg, int parity, int wordLength);
	friend int std_char_out_setup();
	friend void serial0_interrupt();
public:
	static void transmit(char);
	void charWrite(char value);
};

class Serial1:public Serial{
private:
	static SerialInterface *interface;
	int _setup(int baudrate, SerialInterface &interfaceArg, int parity, int wordLength);
	friend void serial1_interrupt();
public:
	static void transmit(char);
	void charWrite(char value);
};

class Serial2:public Serial{
private:
	static SerialInterface *interface;
	int _setup(int baudrate, SerialInterface &interfaceArg, int parity, int wordLength);
	friend void serial2_interrupt();
public:
	static void transmit(char);
	void charWrite(char value);
};

#include "can.hpp"
#define NUMBER_OF_CAN_INTERFACE 30
class Can0:public Can{
public:
	Can0();
	int setup();
	int setupLoopBack();
	int addInterface(CanInterface &interfaceArg);
	int setId(int id);
	int setIdAll();
	int write(int id,int number,unsigned char data[8]);
private:
	int filter_number;
	short filter[14*4];
	bool setuped;
	static CanInterface *canInterface[30];
	static int canInterfaceCursor;
	static int read(int id,int number,unsigned char data[8]);
	friend void Can0_Interrupt();
};
#endif // PIN_H_INCLUDED
