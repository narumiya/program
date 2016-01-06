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
 * üŠú			16.528ms
 * ƒpƒ‹ƒX•	1ms~2ms
 */
#endif
