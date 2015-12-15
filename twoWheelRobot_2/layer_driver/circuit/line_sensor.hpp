#ifndef LINE_SENSOR_HPP
#define LINE_SENSOR_HPP

#include "analog.hpp"

class LineSensor{
private:
	Analog *an[5];
public:
	LineSensor(Analog &a0,Analog &a1,Analog &a2,Analog &a3,Analog &a4);
	int setup();
	float getValue(int num);
};

#endif
