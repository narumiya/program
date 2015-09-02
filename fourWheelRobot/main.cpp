//libraries

//application
#include "my_standard_io.h"
//controller
#include "layer_controller/blink.hpp"
#include "robotCenter.hpp"
//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"

//circuit

int main(void)
{
	long long int time=0;
	Led0 led;Blink blink0(led);blink0.setup();blink0.time(100);
	A0 a0;Blink blink1(a0);blink1.setup();blink1.time(100);
	Serial0 serial;serial.setup(115200);
	Serial2 ps3;
	Enc0 l;Enc1 r;Enc2 b;
	RobotCenter center(l,r,b);center.setup();

	while(1){
		blink0.cycle();
		center.cycle();

		if(millis()-time>=500){
			time=millis();
			serial.printf("ang,% .4f, x,% .4f, y,% .4f\n",rtod(center.angle),center.x(),center.y());
		}
	}
	return 0;
}
