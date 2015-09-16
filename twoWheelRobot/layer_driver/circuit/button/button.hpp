#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "digital.hpp"
#include "mcutime.h"

class Button{
private:
	Digital *pin;
	bool onWhenHigh;
	int CHATTERING_TIME;
	int outputState;
	int64_t time;
public:
	Button(Digital &digital);
	Button(Digital *digital);
	int setup(bool onWhenWhat=true,int millisArg=0);
	void cycle();
	int value();

	void setChatteringTime(int millisArg);
	void setOnWhenHigh(bool onArg);
};

#endif//BUTTON_HPP
