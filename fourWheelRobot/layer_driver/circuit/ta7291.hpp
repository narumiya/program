#ifndef TA7291_HPP
#define TA7291_HPP

#include "Digital.hpp"
#include "Pwm.hpp"

class Ta7291{
private:
	Digital *cw;
	Digital *ccw;
	Pwm *pwm;
	float request;
public:
	Ta7291(Digital &cwPin,Digital &ccwPin,Pwm &pwmPin);
	int setup();
	void cycle();
	void duty(float value);
};

#endif//TA7291_HPP
