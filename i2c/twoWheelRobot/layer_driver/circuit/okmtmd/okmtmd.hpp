#ifndef MDPLUS_H
#define MDPLUS_H
//Okamoto Motor Driver Driver

#include "digital.hpp"
#include "pwm.hpp"

class OkamotoMD{
private:
	Digital *cw;
	Digital *ccw;
	Pwm *pwm;
	long deadTimeMicrosData;//micros
	float requestDuty;
	bool reverse;
	int oldDirection;//0:‚È‚µ 1:CW 2:CCW
	float underLimitDuty;
	float overLimitDuty;
	long time;
	void output(float request);
public:
	OkamotoMD(Digital &cw,Digital &ccw,Pwm &pwm);
	int setup();
	void outRev(bool);
	void duty(float dutyArg);
	float duty();
	void cycle();

	int deadTimeMicros(){return deadTimeMicrosData;};
};

#endif//MOTOR_DRIVER_PLUS_H
