#ifndef MD_HPP
#define MD_HPP

#include "Digital.hpp"
#include "Pwm.hpp"

class Md{
private:
	Digital *cw;
	Digital *ccw;
	Pwm *pwm;
	float request;
	int deadtime;
	int flag;
	enum{
		NORMAL,
		REVERSE
	};
public:
	Md(Digital &cwPin,Digital &ccwPin,Pwm &pwmPin);
	int setup();
	void cycle();
	void free();
	void duty(float value);
};

#endif
