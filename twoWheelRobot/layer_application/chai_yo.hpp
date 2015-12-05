#ifndef CHAI_YO_HPP
#define CHAI_YO_HPP

#include "layer_controller/robo_center.hpp"
#include "layer_controller/move.hpp"
#include "mcutime.h"
class ChaiYo{
private:
	enum{
		CX,//ç¿ïWx
		CY//ç¿ïWy
	};
	Move *move;
	RoboCenter *eco;
	Buzzer *buzz;
	Led1 *led1;
	Led2 *led2;
	Led3 *led3;
	ButtonInfo *b0;
	ButtonInfo *b1;
	int64_t time;
	int controlPeriod;//ms
	bool startFlag;
	float coord[2][20];
public:
	ChaiYo(Move &move,RoboCenter &eco,Buzzer &buzz,Led1 &l1,Led2 &l2,Led3 &l3,ButtonInfo &b0,ButtonInfo &b1);
	int setup();
	void setCoord();
	void cycle();
};

#endif
