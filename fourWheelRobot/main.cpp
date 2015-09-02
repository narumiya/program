//libraries

//application
#include "my_standard_io.h"
//controller
#include "layer_controller/blink.hpp"
#include "robotCenter.hpp"
#include "move.hpp"
//base
#include "system.h"
#include "mcutime.h"

//board
#include "pin.hpp"

//circuit
#include "circuit/md.hpp"

int main(void)
{
	long long int time=0;
	Led0 led;Blink blink0(led);blink0.setup();blink0.time(100);
	A0 a0;Blink blink1(a0);blink1.setup();blink1.time(100);
	Serial0 serial;serial.setup(115200);
	Serial2 ps3;
	Enc0 l;Enc1 r;Enc2 b;
	RobotCenter center(l,r,b);center.setup();
	Cw4 cw4;Ccw4 ccw4;Pwm4 pwm4;Md md4(cw4,ccw4,pwm4);
	Cw5 cw5;Ccw5 ccw5;Pwm5 pwm5;Md md5(cw5,ccw5,pwm5);
	Cw6 cw6;Ccw6 ccw6;Pwm6 pwm6;Md md6(cw6,ccw6,pwm6);
	Cw7 cw7;Ccw7 ccw7;Pwm7 pwm7;Md md7(cw7,ccw7,pwm7);
	Move move(md4,md5,md6,md7);move.setup();

	while(1){
		blink0.cycle();
		center.cycle();
		move.cycle();
		if(millis()-time>=500){
			time=millis();
			serial.printf("ang,% .4f, x,% .4f, y,% .4f\n",rtod(center.angle),center.x(),center.y());
		}
	}
	return 0;
}
