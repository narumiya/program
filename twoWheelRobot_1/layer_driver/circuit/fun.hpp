#ifndef FUN_HPP
#define FUN_HPP

#include "pwm.hpp"
class Fun{
private:
	Pwm *pwm;
	float pulse;
	float period;//[ms]
public:
	Fun(Pwm &pwmPin);
	void duty(float value);//0~1
	void cycle();
	int setup();
};

/*
 * ����			16.528ms
 * �p���X��	1ms~2ms
 */
#endif
