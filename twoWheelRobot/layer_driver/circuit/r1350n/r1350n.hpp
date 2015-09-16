#ifndef R1350NPLUS_HPP
#define R1350NPLUS_HPP
/*******************************************
 * can_encoderplus ver0.1 2015/3/5
 * Classes of can encoder node for ichigo system.
 *
 * [Dependency]
 * serial
 * util
 * math
 *
 * [Note]
 *
 * [Change history]
 * ver0.1 2015/ 3/ 5 The first version.Test.
 ******************************************/
#include "serial.hpp"
#include <math.h>

class R1350n:public SerialInterface{
private:
	int angleData;
	int rateData;
	int accelXData;
	int accelYData;
	int accelZData;
	int initialAngleData;
	char readingData[15];
	int readingCount;
	int readStart;
	int angleRoopCount;
	int initialSetStart;

	Serial *serial;

public:
	R1350n(Serial &serial){angleData=0;readingCount=0;readStart=0;initialSetStart=0;angleRoopCount=0;this->serial=&serial;};
	void serialReadChar(char data);
	int setup(){initialSetStart=1;return serial->setup(115200,(*this));};
	float angle();
	float rate(){return rateData*M_PI/18000.0;};
	float accelx(){return accelXData;};
	float accely(){return accelYData;};
	float accelz(){return accelZData;};
	void reset(){initialAngleData=angleData;angleRoopCount=0;};
};

#endif//R1350NPLUS_HPP
