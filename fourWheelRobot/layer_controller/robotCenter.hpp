#ifndef ROBOTCENTER_HPP
#define ROBOTCENER_HPP

#include "encoder.hpp"

class RobotCenter{
private:
	Encoder *enc[3];
	float centerToEnc;
	enum{
		LEFT,
		RIGHT,
		BACK
	};
public:
	RobotCenter(Encoder &l,Encoder &r,Encoder &b);
	void setup();
};

#endif
