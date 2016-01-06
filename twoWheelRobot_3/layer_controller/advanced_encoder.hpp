#ifndef ADVANCED_ENCODER_HPP
#define ADVANCED_ENCODER_HPP
#include "encoder.hpp"
#include <stdint.h>

class AdvancedEncoder:public Encoder{
public:
	AdvancedEncoder(Encoder &enc,int cpr);
	int setup();
	void cycle();

	int count();

	float revolution();
	float radian();
	float rps();
	float rps2();

	float rads();
	float rads2();

private:
	Encoder *enc;

	int64_t time;
	int64_t lastCountChangeMicros;
	int oldCount;
	float oldVelocity;

	int maxVelIntervalMicros;

	int countData;
	float rpsData;
	float rps2Data;

	bool encRev;
};

#endif//ADVANCED_ENCODER_HPP
